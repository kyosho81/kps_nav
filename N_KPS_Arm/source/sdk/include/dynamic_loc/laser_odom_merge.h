#ifndef _LASER_ODOM_MERGE_KYOSHO_20210704_
#define _LASER_ODOM_MERGE_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "device/amcl_tf.h"

#include "dynamic_loc/scan_match_laser.h"

class scan_map_manage;

class laser_odom_merge
{
public:
	laser_odom_merge();
	~laser_odom_merge();

	bool init(const F32 &dx,const F32 &dy);
	void set_laser_para(SLaser_para laser_para, std::string str_robot_shape);
	int load_key_frame(std::string str_map_nm);
	
	bool dy_scan_loc(SPos &match_pos, const SPos &estimate_pos, SLaser &laser, SLaser_para laser_para);
	bool do_sliding_win_check(SLaser_para laser_para);

	bool insert_sliding_win(SOdomSpeed odomspeed,const SPos &amcl_pos, const SLaser &laser, const SAMCL_CONFIDENCE &amcl_conf, const SLaser_para &laser_para );
	bool amcl_merge( SPos &amcl, SOdomSpeed odomspeed );
	
	void get_g2o_data(std::vector<void*> &v_frame);

	void clear_sliding_wind();

protected:

	amcl_tf location_tf_;

private:
	
	bool check_odom_diff(const SOdomSpeed &odomspeed);

	bool b_first_odom_;
	SOdomSpeed odom_last_;

	F32 f_increase_megnitude_;
	F32 f_increase_angle_;

private:

	Scan_Frame* ins_new_scan(const SOdomSpeed &odomspeed,const SPos &amcl_pos, const SLaser &laser, const SAMCL_CONFIDENCE &amcl_conf, const SLaser_para &laser_para);
	
	bool scan_amcl_ok(Scan_Frame* p_frame);
	Scan_Frame* get_ref_scan();
	

	U32 wind_index_;
	std::map<int, Scan_Frame* > m_sliding_wind_; 

	bool scanmatch_odom(SPos &calib_diff,Scan_Frame* p_ref_frame,Scan_Frame* p_cur_frame);

	scan_match_laser sm_;

	Scan_Frame* get_final_ok();
	

	std::vector<std::vector<std::map<int, Scan_Frame *>::iterator> > segment_frame(std::map<int, Scan_Frame *> &m_sliding_wind);
	//if frame ok > 80% percent, remove sliding_win head
	int i_sliding_win_min_size_;

private:
	scan_map_manage* p_scan_map_manage_;

	bool pub_match_scan(Scan_Frame* p_frame);
	SPUB_BAG pub_bag_;
	bool b_pub_bag_;
};


#endif//_LASER_ODOM_MERGE_KYOSHO_20210704_
