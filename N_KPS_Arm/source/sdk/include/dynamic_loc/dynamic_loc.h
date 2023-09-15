#ifndef _DYNAMIC_LOCALIZATION_KYOSHO_20210704_
#define _DYNAMIC_LOCALIZATION_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "pf/merge_tf.h"
#include "g2o_slam/loc_pos_graph.h"

#include "dynamic_loc/laser_odom_merge.h"

using namespace g2o::slam2d;

class dynamic_loc
{
public:

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	dynamic_loc();
	~dynamic_loc();

	bool init( bool b_sim = false);
	void set_laser_para(SLaser_para laser_para, std::string str_robot_shape );
	int load_key_frame(std::string str_map_nm);
	void do_dy_location();

	typedef enum{
		RUNTIME = 0,
		PLAYBACK = 1,
		DEVICE = 2
	}DY_SUB_TYPE;

	bool updata_used_laser(const SLaser &laser);
	bool update_odom(const SOdomSpeed &odomspeed);
	bool update_amcl_pos(const SPos &amcl_pos);
	bool updata_amcl_conf(const SAMCL_CONFIDENCE &amcl_conf);
	
	bool s_init_pos( const SInit_Pos &pos );

	SPos final_pos_;
	SPOS_CONFIDENCE conf_pos_;

	static DY_SUB_TYPE get_sub_type();

	THSafe<int> th_reflash_sliding_wind_;

protected:
	static dynamic_loc::DY_SUB_TYPE sub_type_;

	merge_tf location_tf_;

private:
	bool init_sub_msg();

	SBuffer<SPos> tl_amcl_pos_;
	SBuffer<SLaser> tl_laser_;
	SBuffer<SOdomSpeed> tl_odom_;

	THSafe<SAMCL_CONFIDENCE> th_amcl_conf_;
	int i_count_;

	int sub_id_odom_;
	int sub_id_amcl_;
	int sub_id_laser_;
	int sub_id_amcl_confidence_;
	int sub_id_estimate_;

	std::string sub_nm_odom_;
	std::string sub_nm_amcl_;
	std::string sub_nm_laser_;
	std::string sub_nm_amcl_confidence_;
	std::string sub_nm_estimate_;


private:
	laser_odom_merge odom_merge_;

private:

	void do_dy_location(SOdomSpeed odomspeed,const SPos &amcl_pos, SLaser &laser, const SAMCL_CONFIDENCE &amcl_conf);
	void pub_dy_loc();
	
private:
	bool do_g2o_loc(SPos &final_pos, std::vector<void*> data , SOdomSpeed odomspeed);

	g2o_loc g2o_loc_;
	SLaser_para laser_para_;

	bool b_first_call_;
};

#endif//_DYNAMIC_LOCALIZATION_KYOSHO_20210704_
