#ifndef _SCAN_MAP_MANAGE_KYOSHO_20221116_
#define _SCAN_MAP_MANAGE_KYOSHO_20221116_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "robot/RobotStruct.h"
#include "device/amcl_tf.h"
#include "Comm/pattern_thread.h"
#include "g2o_slam/loc_pos_graph.h"


#include "dynamic_loc/laser_odom_merge.h"
#include "dynamic_loc/pos_search.h"

using namespace g2o::slam2d;



typedef struct _SScan_bag
{
	std::string str_nm_;
	std::map<int, Scan_Frame* > scan_list_;
	SLaser_para laser_para_;

}SScan_bag;

class scan_map_manage
{
public:
	
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	scan_map_manage();
	~scan_map_manage();

	bool init(const SLaser_para &laser_para , std::string str_robot_shape);
	void set_laser_para(const SLaser &laser);

	int load_key_frame();
	int load_key_frame(std::string str_map_nm);

	void add_new_scan(std::map<int, Scan_Frame* > &m_sliding_wind, SLaser_para laser_para);
	bool save_scan_bag(std::string str_nm, SScan_bag &scan_bag);
	bool load_scan_bag(std::string str_nm, SScan_bag &scan_bag);

	int get_in_range( std::vector<Scan_Frame*> &v_res, SPos target_pos );

	bool clear();

	std::string get_frame_nm(Scan_Frame* p_frame);
	void remove_redundant_bag(std::map<std::string,F32> &m_bag_nm);

protected:
	
private:

	void set_laser_para(const SLaser_para &laser_para , std::string str_robot_shape);

	boost::mutex mu_bag_;
	std::map<std::string, SScan_bag > m_scan_bag_;

	pattern_thread th_optmize_;
	bool do_optmize();

	bool optimize_save(SScan_bag &s_bag);
	bool optimize(SScan_bag &s_bag);
	bool insert_scan_map(SScan_bag &s_bag);
	bool pub_sbag(SScan_bag &s_bag);
	bool save_sbag(SScan_bag &s_bag);

	g2o_loc g2o_loc_;

private:
	boost::mutex mu_scan_map_;
	std::map<std::string, SScan_bag> m_optimize_scan_;
	std::multimap<std::string,Scan_Frame*> mt_optimize_frame_;
	std::map<Scan_Frame*,std::string> m_frame_nm_;

	pos_search pos_search_;

	F32 count_match_pre(std::string str_bag_nm);
	bool clear_old_match_bag(std::string str_bag_nm);

private:
	SPUB_BAG pub_bag_;

private:
	
};


#endif//_SCAN_MAP_MANAGE_KYOSHO_20221116_
