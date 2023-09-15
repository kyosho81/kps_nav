#ifndef _LASER2LASEREX_20201030_
#define _LASER2LASEREX_20201030_

#include "robot/RobotStruct.h"
#include "Comm/Comm.h"

void Laser2LaserEx(  SLaser_Ex &laser_ex , const SLaser &laser ){

	memset(&laser_ex,0,sizeof(SLaser_Ex));

	laser_ex.range_max_ = laser.range_max_;
	laser_ex.range_min_ = laser.range_min_;
	laser_ex.resolution_ = laser.resolution_;
	laser_ex.stamp_ = laser.stamp_;
	laser_ex.start_angle_ = laser.start_angle_;
	laser_ex.used_ray_ = cComm::Min( (U32)laser.used_ ,(U32)LASER_COUNT_EX);

	memcpy( laser_ex.data_,laser.data_,sizeof(F32)*laser_ex.used_ray_);
	memcpy( laser_ex.seg_,laser.seg_,sizeof(U8)*laser_ex.used_ray_);

};
void LaserEx2Laser( SLaser &laser , const SLaser_Ex &laser_ex ){
	memset(&laser,0,sizeof(SLaser));
	
	laser.range_max_ = laser_ex.range_max_;
	laser.range_min_ = laser_ex.range_min_;
	laser.resolution_ = laser_ex.resolution_;
	laser.stamp_ = laser_ex.stamp_;
	laser.start_angle_ = laser_ex.start_angle_;
	laser.used_ = cComm::Min( (U32)laser_ex.used_ray_ ,(U32)LASER_COUNT_EX);

	memcpy( laser.data_,laser_ex.data_,sizeof(F32)*laser.used_);
	memcpy( laser.seg_,laser_ex.seg_,sizeof(U8)*laser.used_);

};

void PubBagEx2PubBag( SPUB_BAG &bag , SPUB_BAG_EX &bag_ex){
	LaserEx2Laser(bag.laser_,bag_ex.laser_ex_ref_.laser_ex_);
	bag.amcl_pos_ = bag_ex.amcl_pos_;
	bag.laser_para_ = bag_ex.laser_para_;
	bag.odom_ = bag_ex.odom_;
	memcpy( bag.robot_shape_, bag_ex.robot_shape_, 500);
};


#endif//_LASER2LASEREX_20201030_
