#include <string.h>
#include "Geometry.h"
#include "math.h"
#include "Comm/Comm.h"

#include "my_tf.h"

my_tf::my_tf()
{
// 	pos_.x_ = 0;
// 	pos_.y_ = 0;
// 	pos_.th_ = 0;
// 
// 	for(int i = 0 ; i < LASER_COUNT ; ++i){
// 
// 		angle_list_[i] = 0;
// 	}

}

my_tf::~my_tf()
{

}
void my_tf::tf_l2lm( SLaserXY& des,const SLaser& src,const F32& odom_rotation )
{
	F32 sin_odom = sin(odom_rotation);
	F32 cos_odom = cos(odom_rotation);
	

	F32 tmp_x = 0;
	F32 tmp_y = 0;


	for (int i = 0 ; i < LASER_COUNT ; ++i)
	{
		if (int(src.seg_[i]) > 0)
		{

			tmp_x = src.data_[i]*cos_laser_[i] + laser_pos_.x_;
			tmp_y = src.data_[i]*sin_laser_[i] + laser_pos_.y_;

			des.x_[i] = tmp_x*cos_odom - tmp_y*sin_odom;
			des.y_[i] = tmp_x*sin_odom + tmp_y*cos_odom;
			//des.used_++;
			
			//std::cout<<"laser index:"<<i<<"seg:"<<int(src.seg_[i])<<" des used:"<<int(des.used_)<<std::endl;
		}
		
	}

	

}
void my_tf::tf_l2lm( SLaserXY& des,const SLaser& src,const F32& odom_rotation , const F32 &roi)
{
	F32 sin_odom = sin(odom_rotation);
	F32 cos_odom = cos(odom_rotation);


	F32 tmp_x = 0;
	F32 tmp_y = 0;
	
	memset(&des,0,sizeof(SLaserXY));

	for (int i = 0 ; i < LASER_COUNT ; ++i)
	{
		if (int(src.seg_[i]) > 0)
		{
			if( src.data_[i] > roi){
				continue;
			}
			tmp_x = src.data_[i]*cos_laser_[i] + laser_pos_.x_;
			tmp_y = src.data_[i]*sin_laser_[i] + laser_pos_.y_;

			des.x_[i] = tmp_x*cos_odom - tmp_y*sin_odom;
			des.y_[i] = tmp_x*sin_odom + tmp_y*cos_odom;
			des.used_[i] = 255;

			//std::cout<<"laser index:"<<i<<"seg:"<<int(src.seg_[i])<<" des used:"<<int(des.used_)<<std::endl;
		}

	}



}

void my_tf::tf_l2lm(SLaserXY& des,const SLaser& src,const SPos& robot_pos , const F32 &roi)
{
	memset(&des,0,sizeof(SLaserXY));
	SPos pos;
	memset(&pos,0,sizeof(SPos));

	for (int i = 0 ; i < LASER_COUNT ; ++i)
	{
		if (int(src.seg_[i]) > 0)
		{
			if( src.data_[i] > roi){
				continue;
			}
			if( src.seg_[i] == 0){
				continue;
			}

			pos.x_ = src.data_[i]*cos_laser_[i] + laser_pos_.x_;
			pos.y_ = src.data_[i]*sin_laser_[i] + laser_pos_.y_;
			pos.th_ = 0;

			pos = cComm::Local2World(pos,robot_pos);

			des.x_[i] = pos.x_;
			des.y_[i] = pos.y_;
			des.used_[i] = 255;
		}
	}
}

void my_tf::getLaserInBaselink( F32& x, F32& y ,F32 dx, F32 dy,F32 th )
{

	//				[ cos(th)  sin(th) 0]     
	//[x y 1]  *	[-sin(th)  cos(th) 0]  =  [ x*cos(th) - y*sin(th) + dx*1		x*sin(th) + y*cos(th) + dy*1    x*0 + y*0 + 1*1 ]
	//				[   dx      dy     1]
	F32 costh = cos(th);
	F32 sinth = sin(th);
	F32 nx = x*costh - y*sinth + dx;
	F32 ny = x*sinth + y*costh + dy;
	x = nx;
	y = ny;
}

void my_tf::getBaselinkInLaser( F32& x, F32& y ,F32 dx, F32 dy,F32 th )
{

	
	x -= dx;
	y -= dy;
	F32 costh = cos(th);
	F32 sinth = sin(th);
	F32 nx =  x*costh + y*sinth ;
	F32 ny = -x*sinth + y*costh ;
	x = nx;
	y = ny;

}
//base_link to world
void my_tf::tf_b2w( F32* out_x, F32* out_y ,F32* in_x, F32* in_y ,F32* dx, F32* dy,F32* sin_th,F32* cos_th ,U32 size ){
	
	for (int index = 0 ; index < size ;++index)
	{
		out_x[index] = in_x[index]*cos_th[index] - in_y[index]*sin_th[index] + dx[index];
		out_y[index] = in_x[index]*sin_th[index] + in_y[index]*cos_th[index] + dy[index];
	}

}
//base_laser to base_link
void my_tf::tf_l2b( F32* out_x, F32* out_y ,F32* in_x ,F32 dx, F32 dy,F32* th ,U32 size )
{

	for (int index = 0 ; index < size ;++index)
	{
		out_x[index] = in_x[index]*cos(th[index]) + dx;
		out_y[index] = in_x[index]*sin(th[index]) + dy;
	}
}
//base_link to local cost map
void my_tf::tf_b2c( F32* out_x, F32* out_y ,F32* in_x, F32* in_y ,F32 th ,U32 size ){
	F32 sin_th = sin(th);
	F32 cos_th = cos(th);

	for (int index = 0 ; index < size ;++index)
	{
		out_x[index] = in_x[index]*cos_th - in_y[index]*sin_th;
		out_y[index] = in_x[index]*sin_th + in_y[index]*cos_th;
	}
}
//base_laser to local cost map
void my_tf::tf_l2c( F32* out_x, F32* out_y ,const F32* in_x ,const F32 dx, F32 dy,const F32* th ,const F32& rotation,U32 size )
{
	F32 sin_th = sin(rotation);
	F32 cos_th = cos(rotation);
	F32 tmp_x = 0;
	F32 tmp_y = 0;

	for (int index = 0 ; index < size ;++index)
	{
		tmp_x = in_x[index]*cos(th[index]) + dx;
		tmp_y = in_x[index]*sin(th[index]) + dy;

		out_x[index] = tmp_x*cos_th - tmp_y*sin_th;
		out_y[index] = tmp_x*sin_th + tmp_y*cos_th;
	}
}

void my_tf::setLaserInBaseLink( const SLaser &laser,const F32& x,const F32& y,const F32& th )
{
	laser_pos_.x_ = x;
	laser_pos_.y_ = y;
	laser_pos_.th_ = th;
	for (int i = 0 ; i < LASER_COUNT ; ++i)
	{
		angle_list_[i] = laser.start_angle_ + laser.resolution_*i + laser_pos_.th_;
		sin_laser_[i] = sin(angle_list_[i]);
		cos_laser_[i] = cos(angle_list_[i]);
	}
}

//void my_tf::setLaserInBaselink( F32 x ,F32 y ,F32 th )
//{
//	pos_.x_ = x;
//	pos_.y_ = y;
//	pos_.th_ = th;
//}
//
//void my_tf::getDLaserInBaselink( F32 &x, F32 &y,F32 amcl_rotation )
//{
//	VecPosition p(x,y);
//	p.rotate(pos_.th_);
//
//	VecPosition vp(pos_.x_,pos_.y_);
//	vp += p;
//	
//	vp.rotate(amcl_rotation);
//
//	x = vp.getX();
//	y = vp.getY();
//}
//void my_tf::getBaselinkInLaser( VecPosition &npos ){
//
//	VecPosition vp(pos_.x_,pos_.y_);
//	npos = npos - vp;
//
//	npos.rotate(pos_.th_);
//}
//
//
//void my_tf::getDLaserInBaseOdom( F32 &x,F32 &y,F32 ox,F32 oy,F32 oth )
//{
//	getDLaserInBaselink(x,y,0);
//
//	VecPosition p(x,y);
//	p.rotate(oth);
//
//	VecPosition vp(ox,oy);
//	vp += p;
//
//	x = vp.getX();
//	y = vp.getY();
//}
//void my_tf::setLaserPara(const SLaser &lpara){
//
//	for(int i = 0 ; i < LASER_COUNT ; ++i){
//
//		angle_list_[i] = lpara.start_angle_ + lpara.resolution_*i;
//		cos_list_[i] = cos(angle_list_[i]);
//		sin_list_[i] = sin(angle_list_[i]);
//	}
//}
//void my_tf::getLaserXY(SLaserXY &laserxy,const SLaser &lpara,F32 amcl_rotation){
//
//	for(int i = 0 ; i < LASER_COUNT ; ++i){
//		if ((lpara.data_[i] > lpara.range_min_) && (lpara.data_[i] < lpara.range_max_))
//		{
//		
//			laserxy.x_[i] = cos_list_[i] *lpara.data_[i];
//			laserxy.y_[i] = sin_list_[i] *lpara.data_[i];
//			getDLaserInBaselink(laserxy.x_[i],laserxy.y_[i],amcl_rotation);
//			laserxy.used_[i] = 1;
//		}
//		else{
//			laserxy.x_[i] = 0;
//			laserxy.y_[i] = 0;
//			laserxy.used_[i] = 0;
//		}
//	}
//
//}
