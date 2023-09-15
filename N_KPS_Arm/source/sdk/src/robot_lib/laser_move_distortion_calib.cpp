#include "math.h"
#include <boost/thread.hpp>
#include "Comm.h"
#include "robot/Geometry.h"
#include "Comm/TimerDiff.h"
#include "robot/polyfit.h"

#include "robot/laser_move_distortion_calib.h"

#define ODOM_BUF_SIZE 4

laser_md_calib::laser_md_calib() : buffer_odom_(ODOM_BUF_SIZE)
{
	SOdomSpeedEx odom_zero;
	memset(&odom_zero,0,sizeof(SOdomSpeedEx));
	cur_odom_ = odom_zero;
}

laser_md_calib::~laser_md_calib()
{

}

void laser_md_calib::set_odom(const SOdomSpeed& new_odom)
{
	SOdomSpeedEx odom_t;
	odom_t.x_ = new_odom.x_;
	odom_t.y_ = new_odom.y_;
	odom_t.th_ = new_odom.th_;
	odom_t.vx_ = new_odom.vx_;
	odom_t.vy_ = new_odom.vy_;
	odom_t.vw_ = new_odom.vw_;
	odom_t.time_stamp_ =  cTimerDiff::total_ms();
	odom_t.time_stamp_ *=  1e-6;

	set_odom(odom_t);
}

void laser_md_calib::set_odom(const SOdomSpeedEx& new_odom)
{   
	cur_odom_ = new_odom;

	boost::mutex::scoped_lock lock(mu_);

	buffer_odom_.push_back(new_odom);

	if ( buffer_odom_.size() == ODOM_BUF_SIZE )
	{

		th_poly_type_ = cal_odom_covariance(buffer_odom_);
		if (th_poly_type_ > 0)
		{
			cal_fit(buffer_odom_);
		}
	}
}

//return 2 angle fit
//return 1 xy  fit
//return 0 no fit
int laser_md_calib::cal_odom_covariance(  boost::circular_buffer<SOdomSpeedEx> odom_tmp){
	SPos pos_mid;
	memset(&pos_mid,0,sizeof(SPos));
	VecPosition va;
	boost::circular_buffer<SOdomSpeedEx>::iterator it = odom_tmp.begin();
	for ( ; it != odom_tmp.end() ; ++it )
	{
		pos_mid.x_ += it->x_;
		pos_mid.y_ += it->y_;
		va += VecPosition( 1, Rad2Deg(it->th_), POLAR);
		va /= 2.0;
	}

	F32 dx = 0 ; 
	F32 dy = 0 ;
	F32 da = 0 ;
	it = odom_tmp.begin();
	pos_mid.x_ /= ODOM_BUF_SIZE;
	pos_mid.y_ /= ODOM_BUF_SIZE;
	pos_mid.th_ = Deg2Rad(va.getDirection());
	for ( ; it != odom_tmp.end() ; ++it )
	{
		dx += fabs(pos_mid.x_ - it->x_);
		dy += fabs(pos_mid.y_ - it->y_);
		da += fabs( VecPosition::normalizeAngleRad( pos_mid.th_ - it->th_) );
	}
	if( (dx + dy) < 0.1){
		if (da < Deg2Rad(2))
		{
			return 0;
		}else{
			return 2;
		}
	}
	return 1;
}

bool laser_md_calib::cal_fit(boost::circular_buffer<SOdomSpeedEx> odom_tmp)
{
	std::vector<F64> vt;
	std::vector<F64> vx;
	std::vector<F64> vy;

	v_x_poly_.clear();
	v_y_poly_.clear();

	boost::circular_buffer<SOdomSpeedEx>::iterator it = odom_tmp.begin();
	st_ = odom_tmp.front().time_stamp_;

	if( th_poly_type_  > 0 ){

		point_slope_x_ = odom_tmp.front().time_stamp_-  st_;
		point_slope_y_ = odom_tmp.front().th_;
		point_slope_k_ = ( VecPosition::normalizeAngleRad(odom_tmp.back().th_ - point_slope_y_)) / ( (odom_tmp.back().time_stamp_ - st_) - point_slope_x_);
		// ( x - x0 ) / ( x1 - x0) = ( y - y0 ) / ( y1  - y0)
		// k = ( y1  - y0) / ( x1 - x0)
		// y - y0 = k ( x - x0)
	}

	
	if( th_poly_type_ == 1){//xy poly
		while(odom_tmp.size() > 0){
			//for (; it != odom_tmp.end() ; ++it ){

			vt.push_back(odom_tmp.front().time_stamp_ -  st_);
			vx.push_back(odom_tmp.front().x_);
			vy.push_back(odom_tmp.front().y_);
			odom_tmp.pop_front();
		}

		v_x_poly_ = polyfit::fit(vt,vx,2);
		v_y_poly_ = polyfit::fit(vt,vy,2);
	}
	
	if ( th_poly_type_ == 0 )
	{
		return false;
	}
	return true;
}

bool laser_md_calib::get_odom_interpolation(SOdomSpeedEx &odom , F64 time_now)
{

	std::vector<F64> v_x_poly;
	std::vector<F64> v_y_poly;
	F64 point_slope_k;
	F64 point_slope_x;
	F64 point_slope_y;
	SOdomSpeedEx odom_interp = odom;

	{
		boost::mutex::scoped_lock lock(mu_);
		if (buffer_odom_.size() < ODOM_BUF_SIZE)
		{
			return false;
		}
		SOdomSpeedEx odom_last = buffer_odom_.front();
		if ( (odom_last.time_stamp_ - time_now) > 1000){
			buffer_odom_.clear();
			return false;
		}
		v_x_poly = v_x_poly_;
		v_y_poly = v_y_poly_;
		point_slope_k = point_slope_k_;
		point_slope_x = point_slope_x_;
		point_slope_y = point_slope_y_;
		odom_interp.time_stamp_ = time_now - st_;

		//odom diff to small do nothing and return;
		if (th_poly_type_  == 0)
		{
			return false;
		}

	}

	if (v_x_poly.size() > 0){
		odom_interp.x_ = polyfit::polyval(v_x_poly,odom_interp.time_stamp_);
	}else{
		odom_interp.x_ = odom.x_;
	}
	if (v_y_poly.size() > 0){
		odom_interp.y_ = polyfit::polyval(v_y_poly,odom_interp.time_stamp_);
	}else{
		odom_interp.y_ = odom.y_;
	}
	// y - y0 = k ( x - x0)
	// y = k (x - x0) + y0
	odom_interp.th_ = point_slope_k * (time_now - st_- point_slope_x) + point_slope_y;

	odom = odom_interp;

	return true;
}

F32 laser_md_calib::laser_calib( SLaserXYEx &laser_calibInodom, SLaser_Ex &laser_ex)
{
	memset(&laser_calibInodom,0,sizeof(SLaserXYEx));
	F64 time_stamp = laser_ex.time_stamp_;
	SOdomSpeedEx odom = cur_odom_();

	SOdomSpeedEx odom_base = odom;

	int jstep = 1;
	F32 odom_cos = 0;
	F32 odom_sin = 0;
	
	F32 base_cos = 0;
	F32 base_sin = 0;

	int index = 0;
	double nx = 0;
	double ny = 0;
	double na = 0;

	cTimerDiff dt;
	dt.Begin();
	int i_used_ray = laser_ex.used_ray_;
	for ( int i = 0 ; i < LASER_COUNT_EX ;  ((i + jstep) <= LASER_COUNT_EX)? i = i + jstep : i = LASER_COUNT_EX -1) {

		time_stamp = laser_ex.time_stamp_ + laser_ex.bean_dt_*i;
		bool b_cal = get_odom_interpolation(odom,time_stamp);
		//std::cout<<" index:"<<i<<" th:"<<odom.th_;
		//get laser base 
		if ( i == 0 )
		{
			
			odom_base = odom;
			//std::cout<<"odom_base th:"<<odom_base.th_<<std::endl;
			base_cos = cos(-odom_base.th_);
			base_sin = sin(-odom_base.th_);
		}
		odom_cos = cos(odom.th_);
		odom_sin = sin(odom.th_);

		for (int j = 0 ; j < jstep ; ++j ){

			index = jstep*i + j;

			if (laser_ex.seg_[index] > 0){

				F32 angle = laser_ex.start_angle_ + laser_ex.resolution_*index;
				laser_calibInodom.x_[laser_calibInodom.used_cnt_] = cos(angle)*laser_ex.data_[index] + laser_ex.dx_;
				laser_calibInodom.y_[laser_calibInodom.used_cnt_] = sin(angle)*laser_ex.data_[index] + laser_ex.dy_;

				if (b_cal)
				{
					nx =  odom_cos*laser_calibInodom.x_[laser_calibInodom.used_cnt_] - odom_sin*laser_calibInodom.y_[laser_calibInodom.used_cnt_] + odom.x_;
					ny =  odom_sin*laser_calibInodom.x_[laser_calibInodom.used_cnt_] + odom_cos*laser_calibInodom.y_[laser_calibInodom.used_cnt_] + odom.y_;

					//Local2World(laser_calibInodom.x_[laser_calibInodom.used_cnt_],laser_calibInodom.y_[laser_calibInodom.used_cnt_],0,odom.x_,odom.y_,odom.th_,nx,ny,na);
 					//World2Local(odom_base.x_,odom_base.y_,odom_base.th_,nx,ny,0,nx,ny,na);
// 					
// 					nx =  odom_cos*laser_calibInodom.x_[laser_calibInodom.used_cnt_] - odom_sin*laser_calibInodom.y_[laser_calibInodom.used_cnt_] + odom.x_;
// 					ny =  odom_sin*laser_calibInodom.x_[laser_calibInodom.used_cnt_] + odom_cos*laser_calibInodom.y_[laser_calibInodom.used_cnt_] + odom.y_;
#if 1
					//transfer to first bean coordinate
					nx = nx - odom_base.x_ ;
					ny = ny - odom_base.y_ ;

					laser_calibInodom.x_[laser_calibInodom.used_cnt_] = nx*base_cos - ny*base_sin;
					laser_calibInodom.y_[laser_calibInodom.used_cnt_] = nx*base_sin + ny*base_cos;

					//std::cout<<"index old :"<<index<<" "<<laser_calibInodom.x_[laser_calibInodom.used_cnt_]<<" y:"<<laser_calibInodom.y_[laser_calibInodom.used_cnt_]<<std::endl;
#endif
					//laser_calibInodom.x_[laser_calibInodom.used_cnt_] = nx;
					//laser_calibInodom.y_[laser_calibInodom.used_cnt_] = ny;

					//std::cout<<"index new :"<<index<<" "<<laser_calibInodom.x_[laser_calibInodom.used_cnt_]<<" y:"<<laser_calibInodom.y_[laser_calibInodom.used_cnt_]<<std::endl;
				}
				laser_calibInodom.used_cnt_++;
				
				if (--i_used_ray < 1)
				{
					//std::cout<<"final_base th:"<<odom.th_<<std::endl;
					//std::cout<<"diff th:"<<Rad2Deg(VecPosition::normalizeAngleRad( odom.th_ - odom_base.th_))<<std::endl;
					break;
				}
			}
		}
		if (i_used_ray < 1)
		{
			break;
		}
	}
	F32 fdt = dt.End();
	fdt *= 1e-6;
	return fdt;
}
