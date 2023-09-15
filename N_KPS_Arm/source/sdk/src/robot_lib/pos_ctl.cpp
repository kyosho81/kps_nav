
#include "math.h"
#include "iostream"
#include "Comm.h"
#include "Comm/Acc.h"

#include "pos_ctl.h"

pos_ctl::pos_ctl()
{
	f_ahead_ = 1.0;

	f_stop_distance_ = 0.1;//0.1m
	actl_.Init_pid(1.0,0);

	task_speed_v_ = 0.2; //0.5m/s
	min_speed_ = 0.005;  //0.005m/s

	b_moving_ = true;
}

pos_ctl::~pos_ctl()
{

}
void pos_ctl::Set_ahead( const F32& ahead )
{
	f_ahead_ = ahead;
}
void pos_ctl::Make_target_line( const SPos& C,const SPos& L )
{
	// set value
	v_C_ = VecPosition(C.x_,C.y_);
	v_L_ = VecPosition(L.x_,L.y_);

	//make vector
	VecPosition new_v_target = v_L_ - v_C_;

	
	F32 angle =  VecPosition::normalizeAngle(new_v_target.getDirection() - v_target_.getDirection());

	//if angle diff small ,and direction > 0.1
	if (new_v_target.getMagnitude() > 0.0001)
	{
		v_target_ = new_v_target;
		//make line
		//target_line_
	}else{
		//used last line
	}

	
	//make line
	target_line_ = Line::makeLineFromPositionAndAngle(v_C_,v_target_.getDirection());



}
void pos_ctl::get_data(SVec& H,SLinePA& line,const SPos& C){
	H.x_ = v_mH_.getX();
	H.y_ = v_mH_.getY();
	line.angle_ = Deg2Rad(v_target_.getDirection());
	line.p_.x_ = C.x_;
	line.p_.y_ = C.y_;
}
void pos_ctl::Cal_speed( SSpeed &speed,const SPos& target,const SPos& current )
{
	dt_.End();

	current_pos_ = current;
	
	//cal ahead pos
	VecPosition v_head_tmp(f_ahead_,Rad2Deg(current_pos_.th_),POLAR);
	v_H_ = VecPosition(current_pos_.x_,current_pos_.y_) + v_head_tmp;
	
	//cal ahead pos mirror
	VecPosition pOnline = target_line_.getPointOnLineClosestTo(v_H_);
	VecPosition vMirror = pOnline - v_H_;
	v_mH_ = pOnline;// + vMirror;

			
	//cal OH'
	VecPosition v_OmH = v_mH_ - VecPosition(current_pos_.x_,current_pos_.y_);

	//cal w
	F32 t_angle = Deg2Rad(v_OmH.getDirection());
	actl_.Cal_vw(speed.vw_,current_pos_.th_,t_angle);


	//cal stop pos
	F32 angle = v_OmH.getDirection();
	angle = VecPosition::normalizeAngle(angle + 180);
	VecPosition v_stop(f_stop_distance_,angle,POLAR);
	v_stop = VecPosition(target.x_,target.y_) + v_stop;

	//cal v

	F32 fdt = dt_.GetTime();
	fdt /= 1e6;

	if (moving(v_stop))
	{
		F32 target_v = task_speed_v_;
		if(fabs(current_pos_.th_ - t_angle) > Deg2Rad(30)){
			target_v = 0;
		}

		speed.vx_ = Acc::CalAcc( fdt,speed.vx_,0.1,0.2,target_v);

	}else{
		//stopping
		//Uniform deceleration motion
		// t = 2d /v  ; a = -(v*v)/2d;
		f_stop_time_ = f_stop_distance_ * 2 / speed.vx_;
		f_stop_acc_ = - (speed.vx_*speed.vx_ ) / f_stop_distance_*2;

		if(fabs(f_stop_acc_)< 0.01){
			f_stop_acc_ = -0.01;	
		}
		speed.vx_ += f_stop_acc_*fdt;
		
		if ( fabs(speed.vx_) < min_speed_)
		{
			speed.vx_ = min_speed_;
		}
		std::cout<<"????stop speed:"<<speed.vx_<<std::endl;
	}
	
	dt_.Begin();
}

bool pos_ctl::moving(const VecPosition &v_stop)
{
	VecPosition vpos(current_pos_.x_,current_pos_.y_);
	vpos -= v_stop;
	F32 diff = vpos.getMagnitude();
	std::cout<<"!!!!!!!!!!!!! diff:"<<diff<<std::endl;
	if (diff < f_stop_distance_)
	{
		//stopping
		b_moving_ = false;

	}else{
		if (!b_moving_)
		{//when stopping , make a threshold
			if (vpos.getMagnitude() >  ( f_stop_distance_ + 0.1)){
				b_moving_ = true;
			}
		}
		else{
			b_moving_ = true;
		}
	}
	return b_moving_;
}
