#ifndef _COMB_FACTORY_WANGHONGTAO_20211230_
#define _COMB_FACTORY_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"


class comb_factory
{
public:
	comb_factory();
	~comb_factory();

	void init();

	int get_node(std::vector<std::string> &v_comb);

	int get_edge_dir(std::vector<std::string> &v_comb);
	int get_edge_dir_index(std::string str_dir);

	bool get_shape_comb( std::vector<std::string> &v_comb );
	bool get_pallet_category(std::vector<std::string> &v_comb);
	int get_cargo_type(std::vector<std::string> &v_comb);
	int get_pallet_type(std::vector<std::string> &v_comb);
	int get_action_type(std::vector<std::string> &v_comb);
	int get_action_sel(std::vector<std::string> &v_comb);
	
	int get_action_type_index(std::string str_type);
	int get_action_sel_index(std::string str_index);

	int get_pd_state_machine(std::vector<std::string> &v_comb);
	int get_cs_state_machine(std::vector<std::string> &v_comb);
	int get_pc_state_machine( std::vector<std::string> &v_comb );
	int get_st_state_machine( std::vector<std::string> &v_comb );
	int get_ch_state_machine( std::vector<std::string> &v_comb );

	bool check_pallet_type(std::string str_uuid);
	bool check_cargo_type(std::string str_uuid);

	int get_role_name(std::vector<std::string> &v_comb);
	int get_role_all(std::vector<std::string> &v_comb);

	int get_bind_io(std::vector<std::string> &v_comb);
	int get_bind_io_index(std::string str_index);
	
	int get_io_type(std::vector<std::string> &v_comb);
	int get_di_function(std::vector<std::string> &v_comb);
	int get_do_function(std::vector<std::string> &v_comb);
	int get_fai_function(std::vector<std::string> &v_comb);
	int get_fao_function(std::vector<std::string> &v_comb);

	int get_dev_type(std::vector<std::string> &v_comb);
	
	int get_di_pin(std::vector<std::string> &v_comb);
	int get_do_pin(std::vector<std::string> &v_comb);
	int get_fai_pin(std::vector<std::string> &v_comb);
	int get_fao_pin(std::vector<std::string> &v_comb);


	int get_getput(std::vector<std::string> &v_comb);
	int get_mv_seg(std::vector<std::string> &v_comb);
	int get_actions(std::vector<std::string> &v_comb, bool b_none_first = false);

	int get_task_flow_nms(std::vector<std::string> &v_comb, bool b_none_first = false);

protected:
private:

	boost::mutex mx_;
	std::map< std::string, std::vector<std::string> > m_comb_;
private:

};

typedef boost::serialization::singleton<comb_factory> Singleton_COMB_Factory;
#define COMB_FACTORY Singleton_COMB_Factory::get_mutable_instance()

#endif//_COMB_FACTORY_WANGHONGTAO_20211230_
