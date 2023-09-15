#ifndef _HEALTH_EXAMINATION_WANGHONGTAO_20200329_
#define _HEALTH_EXAMINATION_WANGHONGTAO_20200329_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/buffer_con.hpp"
#include "laser_filter/laser_filter.h"
#include "lowpass_filter.h"
#include "buffer_con.hpp"
#include "robot/RobotStruct.h"

class GridMap;

class health_examination
{
public:

	health_examination();
	~health_examination();

	

	void init();
	//set amcl pos delta dis > min_dis or delta angle > min_angle, 
	//will trigger health examination
	bool set_para(const F32 &min_dis,const F32 &min_angle,const F32 &threshhold);
	bool run_once();


	bool update_amcl_pos(const SPos &pos);
	bool update_ref_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool update_dy_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool updata_used_laser(const SLaser &laser_data);

	static void sim_laser_bin( SLaser &laser_sim , const SPos &pos ,GridMap* p_map ,const SimLaser_tf* laser_tf, const F32 &dx, const F32 &dy);
	static F32 cal_score(const SLaser &sim, const SLaser &real, const F32 &max_bean_diff);
	static void init_laser_th(SimLaser_tf* laser_tf,const SLaser &laser_data);
	static F32 cal_gridmap_score(const SLaser &laser_real , const SPos &pos ,GridMap* p_map ,const SimLaser_tf* laser_tf, const F32 &dx, const F32 &dy);

protected:
private:

	


	GridMap* shared_amcl_map_;
	SPos old_pos_;
	SBuffer<SPUB_BAG> new_bag_;
	SBuffer<SLaser> new_laser_;
	
// 	SBuffer<SPOS_CONFIDENCE> th_ref_pos_;
// 	SBuffer<SPOS_CONFIDENCE> th_dy_pos_;
	THSafe<int> th_pos_type_;// 0 : amcl 1 : dynamic loc 2: ref loc
	
	lowpass_filter lowpass_filter_;
	SLaser_para laser_para_;
	F32 min_dis_ ;
	F32 min_angle_ ;

	laser_filter l_filter_;
	bool b_first_laser_;
	bool b_first_odom_;
	
	F32 max_err_score_;
	F32 max_bean_diff_;
	
	SimLaser_tf laser_tf_[LASER_COUNT];

	SAMCL_CONFIDENCE amcl_confidence_;
};

#endif//_HEALTH_EXAMINATION_WANGHONGTAO_20200329_
