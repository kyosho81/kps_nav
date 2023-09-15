#ifndef _KPS_ARM_KYOSHO_GAUSSIAN_NEWTON_SCANMATCH_SINGLETON_H_
#define _KPS_ARM_KYOSHO_GAUSSIAN_NEWTON_SCANMATCH_SINGLETON_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"
#include "threadpool/threadpool.hpp"
#include <Eigen/Dense>

class gn_scan_match{


public:

	gn_scan_match();
	~gn_scan_match();

	void init();
	
	void init_amcl_map();
	void init_amcl_map( GridMap* shared_map );

	bool call_gn_match(SPos &init_pos,SLaserXYEx laser_ex);
	bool call_gn_match(SPos &init_pos,F32 *px,F32 *py,int i_pcount,int max_iterator = 20);

	GridMap* get_amcl_map();

protected:

private:

	int cal_interpolation_gradient( Eigen::Matrix3d& H, Eigen::Vector3d& b , F32 *px,F32 *py,int i_pcount,F32 robot_x,F32 robot_y,F32 robot_th);

	GridMap* gn_map_;

	F32 f4x_resolution_;
	F32 f4x_origin_x_;
	F32 f4x_origin_y_;
	int i4x_grid_ox_;
	int i4x_grid_oy_;
	
	void set_laser_para(const SLaser &laser);
	bool b_first_;
	F32 laser_cos_[LASER_COUNT];
	F32 laser_sin_[LASER_COUNT];
	F32 laser_dx_;
	F32 laser_dy_;

};





#endif//_KPS_ARM_KYOSHO_GAUSSIAN_NEWTON_SCANMATCH_SINGLETON_H_
