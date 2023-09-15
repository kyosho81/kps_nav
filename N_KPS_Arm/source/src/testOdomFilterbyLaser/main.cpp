
#include <signal.h>


#include <iostream>
#include <fstream>

#include <string>
#include <cassert>


#include "Comm.h"
#include "Geometry.h"
#include "TimerDiff.h"

#include "RobotStruct.h"
#include "bag/bag.h"

#include "laser_filter/laser_filter.h"

#include "scanmatcher/psm_node.h"

std::string str_file_name = "D://2.bag";

bool brun = true;
bool bnext = false;
cbag bag;
cbag bag_res;

PSMNode psm_node_;
//PolarScanMatch psm_node_;

bool b_first_bag_ = true;
SOdomSpeed complex_odom_;
SOdomSpeed last_odom_;

F32 laser_dx = 1.45;
F32 laser_dy = 0.0;

// void add_diff(const SPos & laser_diff){
// 	
// 	double nx = 0;
// 	double ny = 0;
// 	double na = 0;
// 
// 	SPos odom_diff = laser_diff2odom_diff(laser_diff);
// 	//std::cout<<"22222 odom diff:"<<complex_odom_.x_<<" y:"<<complex_odom_.y_<<" a:"<<complex_odom_.th_<<std::endl;
// 	//std::cout<<"33333 odom diff:"<<odom_diff.x_<<" y:"<<odom_diff.y_<<" a:"<<odom_diff.th_<<std::endl;
// 	Local2World(odom_diff.x_,odom_diff.y_,odom_diff.th_,complex_odom_.x_,complex_odom_.y_,complex_odom_.th_,nx,ny,na);
// 	complex_odom_.x_ = nx;
// 	complex_odom_.y_ = ny;
// 	complex_odom_.th_ = na;
// 	//std::cout<<"111111111111111111111111111111111 new odom x:"<<nx<<" y:"<<ny<<" na:"<<na<<std::endl;
// }

SPos odom2laser(const SPos& w_pos){
	double laser_x;
	double laser_y;
	double laser_a;

	Local2World(laser_dx,laser_dy,0,w_pos.x_,w_pos.y_,w_pos.th_,laser_x,laser_y,laser_a);

	SPos laser_diff;
	laser_diff.x_ = laser_x;
	laser_diff.y_ = laser_y;
	laser_diff.th_ = laser_a;
	return laser_diff;
}

SPos odom_diff2laser_diff( SPos pos_amcl , SPos pos_ref){

	double dx = 0;
	double dy = 0;
	double da = 0;


	pos_ref = odom2laser(pos_ref);
	pos_amcl = odom2laser(pos_amcl);

	World2Local( pos_ref.x_,pos_ref.y_,pos_ref.th_, pos_amcl.x_ , pos_amcl.y_,pos_amcl.th_ ,dx,dy,da);

	SPos laser_diff;
	laser_diff.x_ = dx;
	laser_diff.y_ = dy;
	laser_diff.th_ = da;

	return laser_diff;
}
SPos laser_diff2odom_diff(const SPos& laser_diff){

	double odom_ref_x;
	double odom_ref_y;
	double odom_ref_th;


	World2Local(laser_dx,laser_dy,0,0,0,0,odom_ref_x,odom_ref_y,odom_ref_th);

	double odom_cur_x;
	double odom_cur_y;
	double odom_cur_th;

	World2Local(laser_diff.x_,laser_diff.y_,laser_diff.th_,0,0,0,odom_cur_x,odom_cur_y,odom_cur_th);
	World2Local(odom_cur_x,odom_cur_y,odom_cur_th,odom_ref_x,odom_ref_y,odom_ref_th,odom_cur_x,odom_cur_y,odom_cur_th);


	//World2Local(odom_cur_x,odom_cur_y,odom_cur_th,odom_ref_x,odom_ref_y,odom_ref_th,odom_cur_x,odom_cur_y,odom_cur_th);
	World2Local(odom_ref_x,odom_ref_y,odom_ref_th,odom_cur_x,odom_cur_y,odom_cur_th,odom_cur_x,odom_cur_y,odom_cur_th);

	SPos odom_diff;
	odom_diff.x_ = odom_cur_x;
	odom_diff.y_ = odom_cur_y;
	odom_diff.th_ = odom_cur_th;
	return odom_diff;
}

void process_bag(const SBAG & b){

	SPos odom_diff;

	if (b_first_bag_)
	{
		complex_odom_.x_ = b.odom.x_;
		complex_odom_.y_ = b.odom.y_;
		complex_odom_.th_ = b.odom.th_;
		last_odom_ = complex_odom_;
	
		SPos pos;
		pos.x_ = 0;
		pos.y_ = 0;
		pos.th_ = 0;
		psm_node_.scanMatcher(pos,b.laser);
		b_first_bag_ = false;

		bag_res.put_laser(b.laser);
		bag_res.put_odom(b.odom,true);

		return;
	}

	double dx = 0;
	double dy = 0;
	double da = 0;


	//if ( (( dx*dx + dy*dy ) > ( 0.05*0.05 )) || fabs(da) > Deg2Rad(3))
	{
		
// 		odom_diff.x_ = dx;
// 		odom_diff.y_ = dy;
// 		odom_diff.th_ = da;
		SPos cur_odom;
		cur_odom.x_ = b.odom.x_;
		cur_odom.y_ = b.odom.y_;
		cur_odom.th_ = b.odom.th_;
		SPos last_odom;
		last_odom.x_ = last_odom_.x_;
		last_odom.y_ = last_odom_.y_;
		last_odom.th_ = last_odom_.th_;
		SPos estimate_pos = odom_diff2laser_diff( cur_odom , last_odom);

		std::cout<<"est pos x:"<<estimate_pos.x_<<" "<<estimate_pos.y_<<" "<<estimate_pos.th_<<std::endl;
		int match_point = 0;
		//SLaser temp_laser = b.laser;
		if(psm_node_.scanMatcher( estimate_pos,b.laser )){

			std::cout<<"mat pos x:"<<estimate_pos.x_<<" "<<estimate_pos.y_<<" "<<estimate_pos.th_<<std::endl;
		}

		odom_diff = laser_diff2odom_diff(estimate_pos);
		double nx = 0;
		double ny = 0;
		double na = 0;
		Local2World(odom_diff.x_,odom_diff.y_,odom_diff.th_,last_odom.x_,last_odom.y_,last_odom.th_,nx,ny,na);
		complex_odom_.x_ = nx;
		complex_odom_.y_ = ny;
		complex_odom_.th_ = na;

		

		

		complex_odom_.vx_ = b.odom.vx_;
		complex_odom_.vy_ = b.odom.vy_;
		complex_odom_.vw_ = b.odom.vw_;
		
		bag_res.put_laser(b.laser);
		bag_res.put_odom(complex_odom_,true);

		last_odom_.x_ = complex_odom_.x_;
		last_odom_.y_ = complex_odom_.y_;
		last_odom_.th_ = complex_odom_.th_;

	}
	



}
void play_run(){

	SBAG res;
	SBAG b;
	std::cout<<"play back!"<<str_file_name<<std::endl;

	bnext = true;
	bag_res.save(true);


	bool first_laser = true;
	laser_filter l_filter;

	while(brun)
	{
		if( bnext ){

			if (!bag.load_Bag(str_file_name,b))
			{
				break;
			}
			
			//bnext = false;
		}else{
			SLEEP(500);
			continue;
		}

		if(first_laser){
			l_filter.init_laser_para(b.laser,laser_dx,laser_dy);
			first_laser = false;
		}
		l_filter.filter_used(b.laser,true);

		process_bag(b);

	}
	
	bag_res.save(false);
	SLEEP(2000);
	brun = false;
}
void play_back(){

	boost::thread th(boost::bind(&play_run));

	while(brun){

		std::cout<<"get next bin!"<<std::endl;

		int i = 0;
		std::cin>>i;

		bnext =  true;

	}

}
int main(int argc, char *argv[])
{

	Config::getConfig("dev_laser_dx",laser_dx);
	Config::getConfig("dev_laser_dy",laser_dy);

	//::signal(SIGINT, shutdown);
	if (argc > 1)
	{
		str_file_name = ".//pro_log//";
		str_file_name += argv[1];

	}

	play_back();


	return 0;


}
