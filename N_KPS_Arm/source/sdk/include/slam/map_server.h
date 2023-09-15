#ifndef _MAP_SERVER_KYOSHO_20180709_
#define _MAP_SERVER_KYOSHO_20180709_

#include <list>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>


#include "RobotStruct.h"
#include "buffer_con.hpp"

#include "bag/bag.h"
#include "laser_filter/laser_filter.h"

class GridMap;
class SlamGMapping;

class map_server
{
public:
	map_server();
	~map_server();

	void init();
	
	GridMap* open_file(std::string file_name);
	void begin_run_gmapping();
	bool stop_run_gmapping();

	void begin_bag_gmapping();
	bool stop_bag_gmapping();
	void wait_save_map_over();

	bool save_gmapping_map(std::string map_name);
	bool load_amcl_map(GridMap* p_map);

	
	void do_bag_mapping(std::string bag_name);

	GridMap* get_mem_map();
	void do_show_mapping();

	std::string get_state();
	void pub_process_bar(SProcess_Bar &pro_bar);

	void bind_show_bag(boost::function<void(SPUB_BAG &pub_bag)> fnc);

protected:
private:
	void end_sub();

 	bool updata_laser(const SLaser &new_laser);
	bool update_odom(const SOdomSpeed &odom);
	bool update_pub_bag(const SPUB_BAG &pub_bag);
	bool update_pub_bar(const SProcess_Bar &pub_bar);

	void put_bag(SBAG bag);
	

	cbag bag_;
	CSBuffer<SPUB_BAG,100> pub_bag_;
	//thread

	void init_thread();
	void end_thread();
	void th_run();
	
	bool b_run_;
	boost::thread* slam_th_;
	
	std::string str_save_file_;

//gmapping
private:

	

	std::string get_map_file(std::string file_name);
	std::string get_map_path(std::string file_name);

	SlamGMapping* g_slam_;
	GridMap* mem_slam_map_;
	GridMap* shared_amcl_map_;

	

	THSafe<bool> th_first_odom_ ;
	SLaser_para laser_para_cfg_;
private:
	//state machine
	THSafe<eMAP_STATUS> th_ms_mapping_;
	void pub_ms(int err_code);
	void continue_log();
	void show_gmapping();


	bool do_one_bag( const SPUB_BAG &pro_bag );
	

//	SBuffer<SPUB_BAG> bag_list_;

	boost::function<void(SPUB_BAG &pub_bag)> fnc_pub_bag_;

};

#endif//_MAP_SERVER_KYOSHO_20180709_
