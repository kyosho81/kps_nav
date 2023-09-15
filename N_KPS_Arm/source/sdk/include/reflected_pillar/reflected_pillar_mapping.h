#ifndef _REFLECTED_PILLAR_MAPPING_KYOSHO_20191120_
#define _REFLECTED_PILLAR_MAPPING_KYOSHO_20191120_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

//#include "quadtree/QuadTree.h"
#include "protobuf_msg/protobuf_bag_ex.h"

#include "scanmatcher/psm_node.h"
#include "gmapping/gridfastslam/gridslamprocessor.h"
#include "gmapping/sensor/sensor_base/sensor.h"

#include "reflected_pillar/reflected_pillar.h"

namespace octomap {
	class OcTree;
}

class protobuf_reflector;

class reflected_pillar_mapping
{
public:
	reflected_pillar_mapping();
	~reflected_pillar_mapping();

	void init();
	void mapping(std::string str_path);

	void put_one_frame(const SPUB_BAG_EX &pub_bag_ex);
	
	void bind_show_bag(boost::function<void(SPUB_BAG_EX &pub_bag_ex)> fnc);
	void bind_map_bag(boost::function<void(SPUB_BAG_EX &pub_bag_ex)> fnc);
	void bind_map_reflector(boost::function<void(protobuf_reflector *, SPUB_BAG_EX *,double nx, double ny)> fnc);
	void bind_clear_bag_item(boost::function<void(void)> fnc);
	//int get_mapping_reflector(std::vector<SVec> &reflector_list);
	
	bool gmapping_bag_ex(std::string path_bag_ex);
	bool modify_bag_ex(std::string path_bag_ex);
	bool g2omapping_bag_ex(std::string path_bag_ex);

private:
	int make_reflector_union();
	int make_reflector_union2();
	//bool make_g2o_data(std::string str_path);
	SLaser_para laser_para_;
	int laser_count_;

	int g2o_mapping(std::string path_name,SlamGMapping* p_g_mapping = 0);
	bool gmapping(std::string path_name);
	bool gmapping2(std::string path_bag_ex);
	
	void clear_m_calib_odom_log();
	void clear_v_calib_odom_log();
	void clear_m_bag_ex_bind_over();

	void save_pgm(std::string path,const GMapping::ScanMatcherMap &smap);
	int laser_ex2laser(SLaser &laser,const SLaser_Ex &laser_ex);

	bool shift_origin();
	SBuffer<SPUB_BAG_EX> bag_ex_list_;
	boost::function<void(SPUB_BAG_EX &pub_bag_ex)> fnc_pub_bag_;

	boost::function<void(SPUB_BAG_EX &pub_bag_ex)> fnc_map_bag_;

	boost::function<void(void)> fnc_clear_bag_item_;

	boost::function<void(protobuf_reflector *, SPUB_BAG_EX *,double nx, double ny)> fnc_show_reflector_;

private:
	
	F32 tolerance_k_;
	F32 max_laser_radii_;
	int max_ref_count_;
	SPos laser_diff_;

	reflected_pillar_loc ref_loc_;
	
	std::map<U32,SPUB_BAG_EX*> m_calib_odom_log_;
	std::vector<SPUB_BAG_EX*> v_calib_odom_log_;

	//QuadTree<protobuf_reflector*>* qtree_;
	octomap::OcTree* octree_;
	std::map<protobuf_reflector*,SPUB_BAG_EX*> m_bag_ex_bind_over_;

	//SlamGMapping* p_g_slam_ ;
};

typedef boost::serialization::singleton<reflected_pillar_mapping> Singleton_Reflected_Pillar_Mapping;

#endif//_REFLECTED_PILLAR_MAPPING_KYOSHO_20191120_
