#ifndef _AGV_BASE_WANGHONGTAO_KYOSHO_20200912_
#define _AGV_BASE_WANGHONGTAO_KYOSHO_20200912_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include "boost/unordered/unordered_map.hpp"




#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"
#include "interpro_shared/sh_pool.hpp"
#include "Comm/pattern_thread.h"

#include "mapserver/MapServer.h"
#include "project/project_manage.h"
#include "battery_strategy.h"
#include "schedule.h"
#include "task_run_time.h"


class xml_rpc_client;
class rpc_config_client;
class task_rpc_client;
class task_creater;


typedef enum 
{
	AGV_CH_INIT         = 0, //check statue :1  close to charge pos contactor ok 2 close to charge pos contactor err 3 far from charge pos
	AGV_CH_CLOSETO_NODE = 1, //create path follow node
	AGV_CH_CLOSETO      = 2, //check arrived node where charge pos nearest
	AGV_CH_CHARGEPATH   = 3, //create charge path by charge pos (0.5 far from charge pos)
	AGV_CH_CLOSETOCHARGE= 4, //check run charge path over
	AGV_CH_CHARGEPATH_BK   = 5, //create charge path by charge pos (1 far from charge pos)
	AGV_CH_CLOSETOCHARGE_BK= 6, //check run charge path over
	AGV_CH_OPEN_CTL     = 7, //create open control path
	AGV_CH_PLATE_CONTACT= 8, //stop when plate contact
	AGV_CH_CHARGE		= 9, //charge and check voltage
	AGV_CH_OVER			= 10, //charge over
	AGV_CH_BACK_CLOSETO	= 11, //go back and tray again
	AGV_CH_BACK_OVER	= 12, //go back over
	AGV_CH_ERROR		= 13  //error
}AGV_CHARGE;

class agv_base
{
public:
	agv_base();
	virtual ~agv_base();

	virtual bool init(const std::string &str_ip, const SAGV_Info &agv_info);
	virtual AGV_SM run_sm();
	//virtual AGV_SM run_agv_sm();

	std::string get_ip();
	std::string get_ip_port();

	int get_id();

	void set_heart_beat(int i_heartbeat, int i_sim_speed);
	SAGV_Info get_agv_info();
	SRobot_Inf get_robot_inf();
	SBattery get_battery();

	std::list<SPathData> get_run_path();
	std::vector<SVec> get_robot_shape();

	int get_belong_node();
	
	void set_pallet_uuid(std::string str_pallet_uuid);
	std::string get_pallet_uuid();
	//0:off line 1:lock 2:unlock 
	THSafe<int> th_lock_;

	bool set_pause( bool b_pause );
	THSafe<int> th_pause_;

	void data_lock(bool b_lock);

	void get_ex_data( SAct_Fork &fork_para );
	virtual void set_off_line();
	virtual void set_on_line();
	void set_init();


	void bind_release_role(protobuf_base* p_base);
	
	boost::function<int(void)> fnc_release_role_;
	protobuf_base* p_release_role_;

protected:
	
	THSafe<AGV_SM> th_agv_sm_;

	std::string str_ip_;


	virtual bool do_init();
	bool do_get_status();
	virtual bool do_check_park();
	virtual bool do_check_charge();
	bool do_check_wander();
	bool do_check_awayfm_charge();


	int do_pack();
	int do_charge();
	int do_wander();
	int do_awayfm_charge();


	void set_err(const std::string &str_err);
	std::string str_err_;

	int i_heartbeat_;
	int i_sim_speed_;

protected:
	bool conn_data_rpc();
	bool conn_cfg_rpc();
	bool conn_task_rpc();
	xml_rpc_client* data_svr_rpc_;
	rpc_config_client* cfg_rpc_;
	task_rpc_client* task_rpc_;
	task_creater* task_creater_;

	SAGV_Info agv_info_;
	SRobot_Inf robot_inf_;
	battery_strategy bs_;
	pschedule pschedule_;
	SAct_Fork fork_para_;

	THSafe<AGV_CHARGE> th_charge_sm_;
	int i_create_specified_path_;
	int i_create_charege_path_;
	int i_create_open_ctl_;


	int i_create_rand_path_;

	bool get_charge_node(SPos &charge_node_pos);
	bool get_charge_pos(SPos &charge_pos);

	int check_charge_status();

	std::string str_pallet_uuid_;

	std::vector<SVec> v_robot_shape_;

	boost::mutex mu_agv_manage_lock_;
	
	pattern_thread p_thread_;

	std::string str_robot_shape_;

	
	SPos pack_pos_;

	cTimerDiff idle_dt_;

	int i_idle_timeout_;//second
	int i_charging_;    //0 no charging 1 charging

	//task ref
public: 
	task_run_time task_run_time_;
	
private:
	void init_redo();
	bool check_redo();
	int i_charge_err_cnt_;
	int i_charge_err_try_;

	int last_contactor_in_;

	bool b_send_away_from_;

	std::vector<SVec> get_robot_shape(const std::string &str_robot_shape);

private:
	
	int i_belong_node_;

	
//check pack	
private:

	SOdomSpeed last_odom_;
	
	
	//protobuf_base* p_occupy_role_;
};


#endif //_AGV_BASE_WANGHONGTAO_KYOSHO_20200912_
