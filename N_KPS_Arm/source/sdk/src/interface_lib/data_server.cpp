#include <sstream>


#include "mapserver/map_def.h"
#include "mapserver/MapServer.h"

#include "interpro_shared/sh_pool.hpp"
#include "msg_pump/msg_pump.hpp"

#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"
#include "protobuf_msg/protobuf_seg_path.h"
#include "protobuf_msg/protobuf_chk_laser.h"

#include "robot/msg_def.h"
#include "msg_pump/msg_array_pump.hpp"
#include "interface/cfg.hpp"
#include "robot/dio_manage.h"

#include "interface/data_server.h"

data_server::data_server():
pub_bag_list_(100),
pub_bag_ex_list_(100),
pub_range_type_show_(20),
thb_qr_code_(1)
{
	
	SProcess_Bar pro_bar;
	memset(&pro_bar,0,sizeof(SProcess_Bar));
	th_process_bar_ = pro_bar;

	ths_contactor_in_ = int(0);
	ths_contactor_out_ = int(0);
	
	sub_id_sim_robot_pos_ = -1;
	sub_id_odom_ = -1;
	sub_id_fork_task_ = -1;
	sub_id_fork_data_ = -1;

	b_sim_ = false;
}

data_server::~data_server()
{

}

void data_server::init( bool b_sim )
{
	//normal module
	if(!b_sim){
		CREATE_SHARED_GMAP(SHARED_AMCL_MAP);
		GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
		if (g_map)
		{
			g_map->fill(MAP_UNKNOWN);
		}

		init_subcribe();
		init_subcribe_play_back();
		init_pipe();

		Singleton_ProtoBuf_Bag::get_mutable_instance().init();
		Singleton_ProtoBuf_Bag::get_mutable_instance().bind_process_bar(boost::bind(&data_server::pub_process_bar,this,_1));
		Singleton_ProtoBuf_Bag::get_mutable_instance().bind_pub_bag(boost::bind(&data_server::pub_bag,this,_1));

		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().init();
		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().bind_process_bar(boost::bind(&data_server::pub_process_bar,this,_1));
		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().bind_pub_bag(boost::bind(&data_server::pub_ex_bag,this,_1));

		protobuf_bag_.init_normal();
		protobuf_bag_ex_.init_normal_r();
	}else{
		//simulation module
// 		SBattery sb;
// 		sb.get_contactor_in_ = false;
// 		sb.percent_ = 0.8;
// 		sb.set_contactor_out_ = true;
// 		sb.voltage_ = 27.0;
// 		updata_battery(sb);

		init_sim_sub_msg();
	}

	b_sim_ = b_sim;
}

void data_server::init_pipe(){
	//shared_pool::Shared_Pipe_Pop(map_name_+"_pipe",layer,data,len);
	//shared_pool::Subscribe_Pipe(shared_pool::name(),"global_path",boost::bind())

// 	shared_pool::Subscribe_Pipe(shared_pool::name(),"global_path",boost::bind(&global_path::update_pipe_global_path,&global_path_,_1,_2,_3));
// 	shared_pool::Subscribe_Pipe(shared_pool::name(),SHARED_LASER_INF_MAP,boost::bind(&local_map::update_pipe_local_map,&laser_inf_map_,_1,_2,_3));
	SUB_PIPE_SH_POOL("global_path",boost::bind(&global_path::update_pipe_global_path,&global_path_,_1,_2,_3));
	SUB_PIPE_SH_POOL(SHARED_LASER_INF_MAP,boost::bind(&local_map::update_pipe_local_map,&laser_inf_map_,_1,_2,_3));

	//shared_pool::Subscribe_Pipe(shared_pool::name(),LOCAL_PATH_MAP,boost::bind(&local_map::update_pipe_local_map,&path_map_,_1,_2,_3));
	SUB_PIPE_SH_POOL(LOCAL_PATH_MAP,boost::bind(&local_map::update_pipe_local_map,&path_map_,_1,_2,_3));
	
	//shared_pool::Subscribe_Pipe(shared_pool::name(),"sim_path",boost::bind(&local_map::update_pipe_local_map,&sim_path_,_1,_2,_3));
	SUB_PIPE_SH_POOL("sim_path",boost::bind(&local_map::update_pipe_local_map,&sim_path_,_1,_2,_3));
//	shared_pool::Subscribe_Pipe(shared_pool::name(),GOAL_MAP,boost::bind(&local_map::update_pipe_local_map,&goal_map_,_1,_2,_3));
}
void data_server::init_subcribe()
{
	
 	boost::function<bool( const SLaser &laser_data )> fnc_usd_laser;
 	fnc_usd_laser = boost::bind(&data_server::updata_used_laser,this,_1);
 	//shared_pool::Subscribe(shared_pool::name(),"laser",fnc_usd_laser);
	SUB_MSG_SH_POOL("laser",fnc_usd_laser);

	boost::function<bool( const SOdomSpeed &odomspeed )> fnc_odom;
	fnc_odom = boost::bind(&data_server::update_odom,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"odom",fnc_odom);
	SUB_MSG_SH_POOL("odom",fnc_odom);

	boost::function<bool( const SPos &pos )> fnc_amcl;
	fnc_amcl = boost::bind(&data_server::update_amcl_pos,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_pos",fnc_amcl);
	SUB_MSG_SH_POOL("amcl_pos",fnc_amcl);

 	boost::function<bool( const SparticlePub &pub )> fnc_particles;
 	fnc_particles = boost::bind(&data_server::update_particle,this ,_1);
 	//shared_pool::Subscribe(shared_pool::name(),"particles",fnc_particles);
	SUB_MSG_SH_POOL("particles",fnc_particles);
 
  	boost::function<bool( const LocalShow &local_show )> fnc_local_show;
  	fnc_local_show = boost::bind(&data_server::update_local_show,this ,_1);
  	//shared_pool::Subscribe(shared_pool::name(),"local_show",fnc_local_show);
	SUB_MSG_SH_POOL("local_show",fnc_local_show);

	boost::function<bool( const SPubDevStatus &dev_status )> fnc_dev_status;
	fnc_dev_status = boost::bind(&data_server::update_dev_status,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"device_status",fnc_dev_status);
	SUB_MSG_SH_POOL("device_status",fnc_dev_status);

// 	boost::function<void( const SPubDevStatus &pub_status)> fnc_pub_status;
// 	fnc_pub_status = boost::bind(&data_server::update_all_status,this ,_1);
// 	shared_pool::Subscribe(shared_pool::name(),"status",fnc_pub_status);
 	

	boost::function<bool( const SCmd &scmd)> fnc_log_cmd;
	fnc_log_cmd = boost::bind(&data_server::update_log_cmd,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"log_cmd",fnc_log_cmd);
	SUB_MSG_SH_POOL("log_cmd",fnc_log_cmd);

	boost::function<bool( const SProcess_Bar &pro_bar )> fnc_pro_bar;
	fnc_pro_bar = boost::bind(&data_server::update_pro_bar,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"process_bar",fnc_pro_bar);
	SUB_MSG_SH_POOL("process_bar",fnc_pro_bar);

	boost::function<bool( const SCHK_LASER_RANGE &chk_laser_range )> fnc_chk_laser_range;
	fnc_chk_laser_range = boost::bind(&data_server::update_chk_laser_range,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"pub_laser_range",fnc_chk_laser_range);
	SUB_MSG_SH_POOL("pub_laser_range",fnc_chk_laser_range);

	boost::function<bool( const Range_type &range_type )> fnc_laser_range_show;
	fnc_laser_range_show = boost::bind(&data_server::update_laser_range_show,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"pub_laser_range_show",fnc_laser_range_show);
	SUB_MSG_SH_POOL("pub_laser_range_show",fnc_laser_range_show);

	boost::function<bool( const SReflector &ref )> fnc_reflector;
	fnc_reflector = boost::bind(&data_server::update_reflector,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"reflectors",fnc_reflector);
	SUB_MSG_SH_POOL("reflectors",fnc_reflector);

// 	boost::function<void( const SPos &ref_pos )> fnc_reflector_pos;
// 	fnc_reflector_pos = boost::bind(&data_server::update_reflector_pos,this ,_1);
// 	shared_pool::Subscribe(shared_pool::name(),"reflector_pos",fnc_reflector_pos);

	boost::function<bool( const SLaser_Ex &laser_ex )> fnc_laser_ex;
	fnc_laser_ex = boost::bind(&data_server::updata_laser_ex,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser_ex",fnc_laser_ex);
	SUB_MSG_SH_POOL("laser_ex",fnc_laser_ex);

	boost::function<bool( const SLaser_Ex_Ref &laser_ex_ref )> fnc_laser_ex_ref;
	fnc_laser_ex_ref = boost::bind(&data_server::updata_laser_ex_ref,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser_ex_ref",fnc_laser_ex_ref);
	SUB_MSG_SH_POOL("laser_ex_ref",fnc_laser_ex_ref);

	boost::function<bool( const SLaserXYEx &laser_ex_cab )> fnc_laser_ex_cab;
	fnc_laser_ex_cab = boost::bind(&data_server::updata_laser_ex_cab,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser_ex_cab",fnc_laser_ex_cab);
	SUB_MSG_SH_POOL("laser_ex_cab",fnc_laser_ex_cab);

	boost::function<bool( const SLaserXYEx &laser_sim )> fnc_sim_laser;
	fnc_sim_laser = boost::bind(&data_server::updata_sim_laser,this,_1);
	SUB_MSG_SH_POOL(PUB_DY_SIM_LASER,fnc_sim_laser);


	boost::function<bool( const SLoopCLosurePos &c_pos )> fnc_loopclosure;
	fnc_loopclosure = boost::bind(&data_server::updata_loop_closure,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"loop_closure",fnc_loopclosure);
	SUB_MSG_SH_POOL("loop_closure",fnc_loopclosure);

	boost::function<bool( const SAMCL_ENTROPY &amcl_entropy )> fnc_amcl_entropy;
	fnc_amcl_entropy = boost::bind(&data_server::updata_amcl_entropy,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_entropy",fnc_amcl_entropy);
	SUB_MSG_SH_POOL("amcl_entropy",fnc_amcl_entropy);

	boost::function<bool( const SAMCL_CONFIDENCE &amcl_confindence )> fnc_amcl_confidence;
	fnc_amcl_confidence = boost::bind(&data_server::updata_amcl_confidence,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_confidence",fnc_amcl_confidence);
	SUB_MSG_SH_POOL("amcl_confidence",fnc_amcl_confidence);

	boost::function<bool( const SPUB_BAG &pro_bag )> fnc_lc_bag;
	fnc_lc_bag = boost::bind(&data_server::pub_bag_lc,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"lc_particles_bag",fnc_lc_bag);
	SUB_MSG_SH_POOL("lc_particles_bag",fnc_lc_bag);

	boost::function<bool( const SPUB_BAG &pro_bag )> fnc_dynamic_scan;
	fnc_dynamic_scan = boost::bind(&data_server::pub_bag,this ,_1);
	SUB_MSG_SH_POOL(PUB_DYNAMIC_LOC_SCAN,fnc_dynamic_scan);

	boost::function<bool( const SPOS_CONFIDENCE &confidence_pos )> fnc_ref_pos;
	fnc_ref_pos = boost::bind(&data_server::updata_ref_pos,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"reflector_pos",fnc_ref_pos);
	SUB_MSG_SH_POOL(PUB_REFLECTOR_POS,fnc_ref_pos);

	boost::function<bool( const SPOS_CONFIDENCE &confidence_pos )> fnc_dynamic_loc;
	fnc_dynamic_loc = boost::bind(&data_server::updata_ref_pos,this ,_1);//temp use for dynamic loc
	SUB_MSG_SH_POOL(PUB_DYNAMIC_LOCACTION,fnc_dynamic_loc);


	boost::function<bool( const SBattery &bt )> fnc_bt;
	fnc_bt = boost::bind(&data_server::updata_battery,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"reflector_pos",fnc_ref_pos);
	SUB_MSG_SH_POOL(PUB_BATTERY_STATE,fnc_bt);

	/////////special localization
	boost::function<bool( const SPOS_CONFIDENCE &con_pos )> fnc_sl_conpos;
	fnc_sl_conpos = boost::bind(&data_server::updata_special_loc,this ,_1);
	SUB_MSG_SH_POOL(PUB_SPECIAL_LOC_POS,fnc_sl_conpos);

	boost::function<bool( const SWorldLM  &wlm )> fnc_special_landmark;
	fnc_special_landmark = boost::bind(&data_server::updata_special_landmark,this ,_1);
	SUB_MSG_SH_POOL(PUB_SPECIAL_LANDMARK_POS,fnc_special_landmark);

	//battery
// 	boost::function<bool( const int& bt_contact )> fnc_bt_contact;
// 	fnc_bt_contact = boost::bind(&data_server::update_bt_contactor_in,this,_1);
// 	SUB_MSG_SH_POOL(PUB_BATTERY_CNT_IN,fnc_bt_contact);
// 
// 	
// 	fnc_bt_contact = boost::bind(&data_server::update_bt_contactor_out,this,_1);
// 	SUB_MSG_SH_POOL(PUB_BATTERY_CNT_OUT,fnc_bt_contact);

	//steering
	boost::function<bool( const SSteering& st )> fnc_steering;
	fnc_steering = boost::bind(&data_server::update_steering,this,_1);
	SUB_MSG_SH_POOL("steeing_data",fnc_steering);

	//di ai
// 	boost::function<bool( const SDIAI &di_ai )> fnc_di_ai;
// 	fnc_di_ai = boost::bind(&data_server::update_di_ai,this,_1);
// 	SUB_MSG_SH_POOL(TH_PUB_DI_AI,fnc_di_ai);
// 
// 	//do ao
// 	boost::function<bool( const SDOAO &do_ao )> fnc_do_ao;
// 	fnc_do_ao = boost::bind(&data_server::update_do_ao,this,_1);
// 	SUB_MSG_SH_POOL(TH_PUB_DO_AO,fnc_do_ao);

	//sub di
	//boost::function<bool( const SDI &sdi )> fnc_sdi;
	//fnc_sdi = boost::bind(&data_server::update_sdi,this,_1);
	//SUB_MSG_SH_POOL(PUB_DI,fnc_sdi);

	//sub do
// 	boost::function<bool( const SDO &sdo )> fnc_sdo;
// 	fnc_sdo = boost::bind(&data_server::update_sdo,this,_1);
// 	SUB_MSG_SH_POOL(PUB_DO,fnc_sdo);

	//ex movement
	boost::function<bool( const SRunStatus &sta )> fnc_mv_status;
	fnc_mv_status = boost::bind(&data_server::update_mv_status,this ,_1);
	SUB_MSG_SH_POOL("mv_status",fnc_mv_status);

	//qr code
	boost::function<bool( const SQrCode &qr_code )> fnc_qr_code;
	fnc_qr_code = boost::bind(&data_server::update_qr_code,this ,_1);
	SUB_MSG_SH_POOL(PUB_QR_CODE,fnc_qr_code);

	boost::function<bool( const SDynamic_Speed &d_speed )> fnc_speed;
	fnc_speed = boost::bind(&data_server::update_priority_speed,this,_1);
	SUB_MSG_SH_POOL(PUB_PRIORITY_SPEED,fnc_speed);
}

bool data_server::updata_laser(const SLaser &laser_data){
	boost::mutex::scoped_lock lock(laser_mu_);
	laser_data_ = laser_data;
	return true;
}
bool data_server::updata_used_laser(const SLaser &used_laser_data){
	Singleton_ProtoBuf_Bag::get_mutable_instance().put_laser(used_laser_data);
	boost::mutex::scoped_lock lock(laser_mu_);
	used_laser_data_ = used_laser_data;
	return true;
}

bool data_server::updata_laser_ex_ref(const SLaser_Ex_Ref &laser_ex_ref)
{
	pub_ref_ = laser_ex_ref.laser_reflector_;
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().put_laser(laser_ex_ref);
	return true;
}
bool data_server::updata_laser_ex_cab(const SLaserXYEx &laser_ex_cab)
{
	pub_laser_ex_cab_.put( laser_ex_cab ) ;
	return true;
}

bool data_server::updata_sim_laser(const SLaserXYEx &sim_laser_data)
{
	pub_laser_sim_.put( sim_laser_data ) ;
	return true;
}

bool data_server::update_odom(const SOdomSpeed &odomspeed){
	Singleton_ProtoBuf_Bag::get_mutable_instance().put_odom(odomspeed);
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().put_odom(odomspeed);
	boost::mutex::scoped_lock lock(odom_mu_);
	odomspeed_ = odomspeed;
	return true;
}
bool data_server::update_amcl_pos(const SPos &amcl_pos){
	Singleton_ProtoBuf_Bag::get_mutable_instance().put_amcl(amcl_pos);
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().put_amcl(amcl_pos);
	boost::mutex::scoped_lock lock(amcl_mu_);
	amcl_pos_ = amcl_pos;
	std::stringstream ss;
	//ss<<"x:"<<amcl_pos.x_<<" "<<amcl_pos.y_<<" "<<amcl_pos.th_<<std::endl;
	//LOGS("dataserver_print")<<ss.str();
	//std::cout<<"amcl pos:"<<amcl_pos.x_<<" "<<amcl_pos.y_<<" "<<amcl_pos.th_<<std::endl;
	return true;
}

bool data_server::update_particle( const SparticlePub &pub )
{
	boost::mutex::scoped_lock lock(amcl_mu_);
	pub_ = pub;
	//LOGS("dataserver_print")<<"size:"<<pub_.pwsize_;
	return true;
}
bool data_server::update_local_show( const LocalShow &local_show )
{
	boost::mutex::scoped_lock lock(local_mu_);
	local_show_ = local_show;

	std::cout<<"data server  local show:"<<std::endl;
	return true;
}
bool data_server::set_estimate_pos(const double &x,const double &y ,const double &th ,const double& para1,const double& para2,const double& para3,const double& para4)
{
	if (b_sim_){
		std::cout<<"sim agv do nothing!"<<std::endl;
		return true;
	}

	SPos pos;
	pos.x_ = x;
	pos.y_ = y;
	pos.th_ = th;
	SInit_Pos init_pos;
	init_pos.pos_ = pos;
	
	init_pos.psize_ = para4;
	if(init_pos.psize_ < 1024){
		//init_pos.psize_ = 1024;
		std::cout<<"err particles:"<<para4<<std::endl;
	}
	init_pos.para1_ = para1;
	init_pos.para2_ = para2;
	init_pos.para3_ = para3;
	init_pos.para4_ = para4;

	if(check_init_pos(pos)){
		//shared_pool::Publish(shared_pool::name(),"set_estimate_pos",init_pos);
		PUB_MSG_SH_POOL("set_estimate_pos",init_pos);
		return true;
	}else{
		std::cout<<"set_estimate_pos check_init_pos error! maybe map load err!"<<std::endl;
		return false;
	}

}
bool data_server::check_init_pos(const SPos &pos){

	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		S8 value = MAP_UNKNOWN;
		g_map->lock();
		g_map->getgrid(pos.x_,pos.y_,value);
		g_map->unlock();

		if ( value >=0 )
		{
			return true;
		}
		
	}
	return false;
}
void data_server::set_target_pos( const double &x,const double &y ,const double &th )
{
	SPos pos;
	pos.x_ = x;
	pos.y_ = y;
	pos.th_ = th;
	//shared_pool::Publish(shared_pool::name(),"goal",pos);
	PUB_MSG_SH_POOL("goal",pos);
}
void data_server::set_sim_pos( const double &x,const double &y ,const double &th )
{
	SPos pos;
	pos.x_ = x;
	pos.y_ = y;
	pos.th_ = th;
	//shared_pool::Publish(shared_pool::name(),"set_sim_pos",pos);
	PUB_MSG_SH_POOL("set_sim_pos",pos);
}

void data_server::set_stop( const double &x,const double &y ,const double &th )
{
	boost::mutex::scoped_lock lock(amcl_mu_);
	SInit_Pos init_pos;
	init_pos.pos_ = amcl_pos_;
	init_pos.psize_ = 1024;
	//shared_pool::Publish(shared_pool::name(),"set_estimate_pos",init_pos);
	PUB_MSG_SH_POOL("set_estimate_pos",init_pos);
}

void data_server::get_Laser_data( std::vector<double> &v_dist )
{
	v_dist.clear();
	boost::mutex::scoped_lock lock(laser_mu_);
	if (laser_data_.start_angle_ < 0)
	{
		for (int i = 0 ; i < LASER_COUNT ; ++i)
		{
			v_dist.push_back(laser_data_.data_[i]);
		}
	}else{
		for (int i = 0 ; i < LASER_COUNT ; ++i)
		{
			v_dist.push_back(laser_data_.data_[LASER_COUNT - i]);
		}
	}
	
	
}
void data_server::get_Used_Laser_data( std::vector<double> &v_dist,std::vector<double> &v_angle )
{
	v_dist.clear();
	v_angle.clear();
	boost::mutex::scoped_lock lock(laser_mu_);

	for (int i = 0 ; i < LASER_COUNT ; ++i)
	{
		if(used_laser_data_.seg_[i]){
			F32 angle = used_laser_data_.start_angle_ + used_laser_data_.resolution_*i;
			v_dist.push_back(used_laser_data_.data_[i]);
			v_angle.push_back(angle);
		}
		
	}

}
void data_server::get_Ex_Laser_data(std::vector<double> &v_dist,std::vector<double> &v_angle)
{
	v_dist.clear();
	v_angle.clear();

	SLaser_Ex laser_ex;
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().get_laser(laser_ex);
	for (int i = 0 ; i < LASER_COUNT_EX ; ++i)
	{
		if (laser_ex.seg_[i] > 0)
		{
			F32 angle = laser_ex.start_angle_ + laser_ex.resolution_*i;
			v_angle.push_back(angle);
			v_dist.push_back(laser_ex.data_[i]);
			
			if (--laser_ex.used_ray_ < 1)
			{
				break;
			}
		}
		
		
	}
	
}
void data_server::get_Excab_Laser_data(std::vector<double> &v_x,std::vector<double> &v_y)
{
	v_x.clear();
	v_y.clear();

	SLaserXYEx laser_ex_cab;
	if (pub_laser_ex_cab_.size() > 0)
	{
		pub_laser_ex_cab_.get(laser_ex_cab);
	}else{
		return;
	}


	for (int i = 0 ; i < laser_ex_cab.used_cnt_ ; ++i)
	{
		v_x.push_back(laser_ex_cab.x_[i]);
		v_y.push_back(laser_ex_cab.y_[i]);
		
	}
}

void data_server::get_Sim_Laser_data(std::vector<double> &v_x,std::vector<double> &v_y)
{
	v_x.clear();
	v_y.clear();

	SLaserXYEx laser_sim;
	if (pub_laser_sim_.size() > 0)
	{
		pub_laser_sim_.get(laser_sim);
	}else{
		return;
	}


	for (int i = 0 ; i < laser_sim.used_cnt_ ; ++i)
	{
		v_x.push_back(laser_sim.x_[i]);
		v_y.push_back(laser_sim.y_[i]);

	}
}

void data_server::get_particles( std::vector<SparticleFAW> &v_particle )
{
	v_particle.clear();
	boost::mutex::scoped_lock lock(amcl_mu_);

	for (int i = 0 ; i < pub_.pwsize_ ; ++i)
	{
		v_particle.push_back(pub_.data_w_[i]);
	}
}
void data_server::get_robot_pos(double &x,double &y,double &th)
{
	boost::mutex::scoped_lock lock(amcl_mu_);
	x = amcl_pos_.x_;
	y = amcl_pos_.y_;
	th = amcl_pos_.th_;
	
	
}

void data_server::test_set_laser( const std::vector<double> &v_dist )
{

	boost::mutex::scoped_lock lock(laser_mu_);
	for (int  i = 0 ; i < v_dist.size() ; ++i)
	{
		if (i < LASER_COUNT)
		{
			laser_data_.data_[i] = v_dist[i];
		}

	}
	
}

void data_server::test_set_amcl_pos( const double &x,const double &y ,const double &th )
{
	boost::mutex::scoped_lock lock(amcl_mu_);
	amcl_pos_.x_ = x;
	amcl_pos_.y_ = y;
	amcl_pos_.th_ = th;
}


bool data_server::get_check_laser_range(const Range_type &range_type, char* &data,int &ilen)
{
	
	boost::mutex::scoped_lock lock(mu_pub_ch_laser_range_);
	std::map<Range_type, SCHK_LASER_RANGE>::iterator it = m_pub_chk_laser_range_.find(range_type);
	
	if ( it != m_pub_chk_laser_range_.end() )
	{
		SCHK_LASER_RANGE &chk_laser_range(it->second);
		protobuf_chk_laser::set_chk_laser(chk_laser_range.type_,chk_laser_range.laser_);
		protobuf_chk_laser::proto2byte(data,ilen);
		return true;
	}
	return false;
}


int data_server::get_check_laser_range_show(std::vector<int> &show_list)
{
	show_list.clear();

	for ( int i = 0 ; i < pub_range_type_show_.size() ; ++i )
	{
		Range_type type;
		pub_range_type_show_.get(type);

		show_list.push_back((int)type);
	}
	return show_list.size();
}


int data_server::get_remote_file(char* p_data, int &ilen , std::string str_cmd)
{
	std::vector<std::string> v_cmd ;
	cComm::SplitString(str_cmd," " ,v_cmd);
	std::string cmd = "";
	if (v_cmd.size() > 0)
	{
		cmd = v_cmd[0];
	}

	if ( "open" == cmd){

		std::string file_path = "tmp.proto";
		if (v_cmd.size() > 1)
		{
			file_path = v_cmd[1];
		}else{
			std::cout<<"err open file name:"<<file_path<<std::endl;
			return -3;
		}
		std::cout<<"open file name:"<<file_path<<std::endl;
		ilen = file_.open_file(file_path);
		return 0;
	
	}else if ( "close" == cmd){
		std::cout<<"close file name!"<<std::endl;
		file_.close_file();
		return 0;

	}else if( "get" == cmd){
		int irec = file_.read_file(p_data,ilen,ilen);
		std::cout<<"read file file!read len:"<<ilen<<std::endl;
		return irec;
	}else{
		std::cout<<"err file cmd:"<<cmd<<std::endl;
		return 0;
	}


	
}


void data_server::get_reflector(SReflector &ref)
{
	ref = pub_ref_();
}


// bool data_server::get_reflector_pos(SPos &pos)
// {
// 	
// 	if ( pub_reflector_pos_.size() )
// 	{
// 		pub_reflector_pos_.get(pos);
// 		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
// 		return true;
// 	}
// 	return false;
// }


bool data_server::get_loop_closure_pos(SLoopCLosurePos &c_pos)
{
	if ( pub_loop_closure_.size() )
	{
		pub_loop_closure_.get(c_pos);
		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
		return true;
	}
	return false;
}


bool data_server::get_amcl_entropy(SAMCL_ENTROPY &amcl_entropy)
{
	if ( pub_amcl_entropy_.size() ){
		pub_amcl_entropy_.get(amcl_entropy);
		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
		return true;
	}
	return false;
}


bool data_server::get_amcl_confidence(SAMCL_CONFIDENCE &amcl_confidence)
{
	if ( pub_amcl_confidence_.size() ){
		pub_amcl_confidence_.get( amcl_confidence );
		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
		return true;
	}
	return false;
}

void data_server::get_local_show( LocalShow& local_show )
{
	boost::mutex::scoped_lock lock(local_mu_);
	local_show = local_show_;
}
std::string data_server::get_para( const std::string name )
{
	std::string value;
	if (Config::getConfig(name,value))
	{

	}else{
		value = "";
	}
	return value;
}

bool data_server::update_dev_status( const SPubDevStatus &dev_status )
{
	boost::mutex::scoped_lock lock(dev_status_mu_);
	m_dev_status_[dev_status.dev_status_.device_id_] = dev_status;
	return true;
}
// void data_server::update_all_status( const SPubDevStatus &dev_status ){
// 	boost::mutex::scoped_lock lock(dev_status_mu_);
// 	m_dev_status_[dev_status.dev_status_.device_id_] = dev_status;
// }
void data_server::get_dev_status( std::map<int,SPubDevStatus> &dev_status )
{
	boost::mutex::scoped_lock lock(dev_status_mu_);
	dev_status = m_dev_status_;
// 	std::string nm = "laser";
// 	SPubDevStatus tmp;
// 	memset(tmp.name_,0,200);
// 	memcpy(tmp.name_ , nm.c_str(), nm.length());
// 	tmp.dev_status_.device_id_ = 0;
// 	tmp.dev_status_.status_ = 1;
// 	tmp.dev_status_.err_code_ = 2;
// 
// 	dev_status.push_back(tmp);
}

void data_server::get_dev_status(SPubDevStatus &dev_status , int dev_id)
{
	memset(&dev_status,0,sizeof(SPubDevStatus));
	boost::mutex::scoped_lock lock(dev_status_mu_);
	std::map<int,SPubDevStatus>::iterator it = m_dev_status_.find(dev_id);
	if( it != m_dev_status_.end() ){
		dev_status = it->second;
	}
}


void data_server::set_mapping_cmd( const std::string cmd )
{
	SCmd scmd;
	memset(scmd.cmd_str_,0,200);
	if(cmd.length() > 199){
		std::cout<<"mapping cmd err:too long "<<cmd<<std::endl;
		return;
	}
	memcpy(scmd.cmd_str_,cmd.c_str(),cmd.length() );

	//shared_pool::Publish(shared_pool::name(),"mapping_cmd",scmd);
	PUB_MSG_SH_POOL("mapping_cmd",scmd);
}
void data_server::set_map_cmd( const std::string str_cmd )
{


	std::vector<std::string> v_cmd ;
	cComm::SplitString(str_cmd," " ,v_cmd);
	std::string cmd = "";
	if (v_cmd.size() > 0)
	{
		cmd = v_cmd[0];
	}

	if ( "load" == cmd){

		std::string para = "load_err.pgm";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load map name:"<<para<<std::endl;
			return;
		}
		std::stringstream ss;
		ss<<".//map//"<<para;
		std::cout<<"begin load map:"<<ss.str()<<std::endl;
		GridMap* p_map = MAP_SERVER.LoadPgmMap(ss.str(),map_data_base::MEM,"");
		if (p_map)
		{
			MAP_SERVER.clone(p_map->Get_name(),SHARED_AMCL_MAP);
			std::cout<<"load map over!!clone map to shared map:"<<ss.str()<<std::endl;
		}

		MAP_SERVER.RemoveGridMap(p_map);


		SCmd scmd;
		memset(scmd.cmd_str_,0,200);
		if(cmd.length() > 199){
			std::cout<<"mapping cmd err:too long "<<cmd<<std::endl;
		}
		memcpy(scmd.cmd_str_,str_cmd.c_str(),str_cmd.length() );

		Config::setConfig("dev_map_name",para);

	}if ( "save" == cmd){

		std::string para = "s.pgm";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load map name:"<<para<<std::endl;
			return;
		}

		std::stringstream ss;
		ss<<".//map//"<<cComm::Get_FileName(para)<<".pgm";
		std::cout<<"begin save amcl map:"<<ss.str()<<std::endl;

		MAP_SERVER.save_map(SHARED_AMCL_MAP,ss.str());
	}

}
void data_server::get_file_list( std::vector<std::string> &v_str_name , const std::string str_path, const std::string &filename)
{
	cComm::Find_files(str_path,filename,v_str_name);
}

int data_server::get_map( std::vector<int> &v_data, const std::string &str_map )
{
	v_data.clear();
	GridMap* g_map = MAP_SERVER.GetGridMap(str_map);
	if (g_map)
	{
		std::cout<<"upload map data list, lock map"<<std::endl;
		g_map->lock();
		g_map->check_unknow();
		std::map<U32,SGridXY>::iterator it = g_map->known_point_.begin();
		for ( ; it != g_map->known_point_.end() ; ++it )
		{
			SGridXY &gp = it->second;
			v_data.push_back(gp.x_);
			v_data.push_back(gp.y_);
			v_data.push_back(gp.value_);
		}
		g_map->unlock();
		std::cout<<"upload map data list, unlock map"<<std::endl;
	}
	return v_data.size();
}



int data_server::get_map(std::vector<int> &v_data, std::string str_cmd, const std::string &str_map)
{
	if ( str_cmd == "load" ){
		
		get_map(v_map_data_,str_map);
		i_map_data_index_ = 0;
		return v_map_data_.size();

	}else if ( str_cmd == "read" ){
		v_data.clear();
		
		int i_remains = v_map_data_.size() - i_map_data_index_ ;
		//separate small package
		i_remains = cComm::Min(i_remains,200000);
		if (i_remains > 0){
			std::vector<int>::iterator it_begin = v_map_data_.begin() + i_map_data_index_ ;
			std::vector<int>::iterator it_end = it_begin + i_remains;
			v_data.insert(v_data.end(),it_begin, it_end);
			i_map_data_index_ += i_remains;
			return v_data.size();
		}
		return 0;
	}
}

void data_server::set_map_lock( const bool &block )
{
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		if (block)
		{
			g_map->lock();
		}else{
			g_map->unlock();
		}
		
	}
	
}

void data_server::set_map_value( const int &gx,const int &gy,const int &value )
{
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		U32 ux = gx;
		U32 uy = gy;
		S8 uv = value;
		g_map->setgrid(ux,uy,uv);
	}
}

void data_server::set_map_fill( const int &value )
{
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		g_map->fill(value);
	}
}

void data_server::get_robot_odom( double &x,double &y,double &th,double &vx,double &vy,double &vw )
{
	boost::mutex::scoped_lock lock(odom_mu_);
	x = odomspeed_.x_;
	y = odomspeed_.y_;
	th = odomspeed_.th_;
	vx = odomspeed_.vx_;
	vy = odomspeed_.vy_;
	vw = odomspeed_.vw_;

}

void data_server::set_map_reflash()
{
	SReflash_map reflash;
	reflash.ref_type_ = SReflash_map::AMCL_REFLASH;
	//shared_pool::Publish(shared_pool::name(),"reflash_map",reflash);
	PUB_MSG_SH_POOL("reflash_map",reflash);
}

void data_server::set_amcl_run( const bool &run )
{
	SReflash_map reflash;
	if (run)
	{
		reflash.ref_type_ = SReflash_map::AMCL_RUN;
	}else{
		reflash.ref_type_ = SReflash_map::AMCL_STOP;
	}
	
	//shared_pool::Publish(shared_pool::name(),"reflash_map",reflash);
	PUB_MSG_SH_POOL("reflash_map",reflash);
}


void data_server::set_onboard_map(const std::string str_local_map)
{
	set_map_lock(true);
	std::cout<<"xml set_map:set_map_lock true"<<std::endl;
	set_map_fill(MAP_UNKNOWN);
	std::cout<<"xml set_map:set_map_fill unknow"<<std::endl;

	std::string str_file_name = cComm::Get_FileName(str_local_map);
	std::string str_path = cComm::Get_FilePath(str_local_map);
	std::string str_yaml = str_path + str_file_name + ".yaml";
	std::string str_file_type = cComm::Get_FileType(str_local_map);

	GridMap* file_map = 0;
	if( "pgm" == str_file_type){
		if ( cComm::FileExist(str_yaml) )
		{
			file_map = MAP_SERVER.LoadPgmMap(str_local_map,map_data_base::MEM,"");
			// 		MAP_SERVER.fast_inflation(0.1,file_map->Get_name());
			// 		MAP_SERVER.save_map(file_map->Get_name(),"d://1.igm");
		}else{
			file_map = CREATE_MEM_GMAP(str_file_name);
			if (!MAP_SERVER.LoadPgmMapM(str_local_map,file_map))
			{
				MAP_SERVER.RemoveGridMap(file_map);
				std::cout<<"-----data_server::set_onboard_map err!  "<<file_map<<std::endl;
				set_map_lock(false);
				return;
			}
			// 		MAP_SERVER.fast_inflation(0.1,file_map->Get_name());
			// 		MAP_SERVER.save_map(file_map->Get_name(),"d://1.igm");
		}
	}else if( "maproto" == str_file_type ){
		file_map = CREATE_MEM_GMAP(str_file_name);
		MAP_SERVER.LoadScanMap(str_local_map,file_map);
		//MAP_SERVER.save_map(file_map->Get_name(),"d://s1.pgm");
	}
	// 	GridMap* amcl_map = CREATE_MEM_GMAP("amcl");
	// 	GridMap* file_map = MAP_SERVER.LoadPgmMapM(str_map_path,amcl_map);
	// 	MAP_SERVER.save_map(amcl_map->Get_name(),"d://1.pgm");
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);

	if ( file_map && g_map)
	{
		MAP_SERVER.clone( file_map->Get_name() , g_map->Get_name());

		MAP_SERVER.RemoveGridMap(file_map);
	}
	////////////////////pub load reflected pillar map////////////////////
	std::stringstream ss;
	ss<<"load "<<str_file_name<<".lm";
	SCmd scmd;
	memset(scmd.cmd_str_,0,200);
	if(ss.str().length() > 199){
		std::cout<<"set map cmd err:too long "<<str_file_name<<std::endl;
	}
	memcpy(scmd.cmd_str_,ss.str().c_str(),ss.str().length() );
	//shared_pool::Publish(shared_pool::name(),"set_map_cmd",scmd);
	PUB_MSG_SH_POOL("set_map_cmd",scmd);
	////////////////////pub load reflected pillar map////////////////////
	Config::setConfig("dev_map_name",str_file_name + "." + str_file_type);

	std::cout<<"xml set_map:set_map_value over! "<<std::endl;
	set_map_lock(false);
	std::cout<<"xml set_map:set_map_lock false! "<<std::endl;
}

int data_server::set_log_cmd( const std::string str_cmd )
{
	boost::mutex::scoped_lock lock(log_mu_);

	std::vector<std::string> v_cmd ;
	cComm::SplitString(str_cmd," " ,v_cmd);
	std::string cmd = "";
	if (v_cmd.size() > 0)
	{
		cmd = v_cmd[0];
	}

	if ( "begin_save" == cmd){

		std::string para = "tmp.proto";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load bag name:"<<para<<std::endl;
			return 0;
		}
		std::stringstream ss;
		ss<<".//pro_log//"<<para;
		std::cout<<"begin save log:"<<ss.str()<<std::endl;
		Singleton_ProtoBuf_Bag::get_mutable_instance().begin_save_file(ss.str());
	}else if ( "stop_save" == cmd){
		Singleton_ProtoBuf_Bag::get_mutable_instance().stop_save_file();
	}else if( "play_back" == cmd){

		std::string para = "tmp.proto";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load bag name:"<<para<<std::endl;
			return 0;
		}
		std::stringstream ss;
		ss<<".//pro_log//"<<para;
		return Singleton_ProtoBuf_Bag::get_mutable_instance().begin_play_back(ss.str());

	}else if( "end_play_back" == cmd){
		Singleton_ProtoBuf_Bag::get_mutable_instance().stop_play_back();
	}else if( "continue_play_back" == cmd){
		return Singleton_ProtoBuf_Bag::get_mutable_instance().continue_play();
	}

	return 0;
	
	
}


int data_server::set_log_ex_cmd(const std::string str_cmd)
{
	boost::mutex::scoped_lock lock(log_ex_mu_);

	std::vector<std::string> v_cmd ;
	cComm::SplitString(str_cmd," " ,v_cmd);
	std::string cmd = "";
	if (v_cmd.size() > 0)
	{
		cmd = v_cmd[0];
	}

	if ( "begin_save" == cmd){

		std::string para = "tmp.protoex";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load bag name:"<<para<<std::endl;
			return 0;
		}
		std::stringstream ss;
		ss<<".//pro_log//"<<para;
		std::cout<<"begin save log:"<<ss.str()<<std::endl;
		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().begin_save_file(ss.str());
	}else if ( "stop_save" == cmd){
		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().stop_save_file();
	}else if( "play_back" == cmd){

		std::string para = "tmp.exbag";
		if (v_cmd.size() > 1)
		{
			para = v_cmd[1];
		}else{
			std::cout<<"err load bag name:"<<para<<std::endl;
			return 0;
		}
		std::stringstream ss;
		ss<<".//pro_log//"<<para;
		return Singleton_ProtoBuf_Bag_ex::get_mutable_instance().begin_play_back(ss.str());

	}else if( "end_play_back" == cmd){
		Singleton_ProtoBuf_Bag_ex::get_mutable_instance().stop_play_back();
	}else if( "continue_play_back" == cmd){
		return Singleton_ProtoBuf_Bag_ex::get_mutable_instance().continue_play();
	}

	return 0;
}

void data_server::set_speed_cmd( const std::string str_cmd )
{
	SCmd scmd;
	memset(scmd.cmd_str_,0,200);
	if(str_cmd.length() > 199){
		std::cout<<"mapping cmd err:too long "<<str_cmd<<std::endl;
		return;
	}
	memcpy(scmd.cmd_str_,str_cmd.c_str(),str_cmd.length() );

	//shared_pool::Publish(shared_pool::name(),"set_speed_cmd",scmd);
	PUB_MSG_SH_POOL("set_speed_cmd",scmd);
}
void data_server::set_loop_clousure_cmd( const std::string str_cmd )
{
	SCmd scmd;
	memset(scmd.cmd_str_,0,200);
	if(str_cmd.length() > 199){
		std::cout<<"set_loop_clousure_cmd err:too long "<<str_cmd<<std::endl;
		return;
	}
	memcpy(scmd.cmd_str_,str_cmd.c_str(),str_cmd.length() );

	//shared_pool::Publish(shared_pool::name(),"loop_closure_cmd",scmd);
	PUB_MSG_SH_POOL("loop_closure_cmd",scmd);
}
void data_server::get_all_ms()
{
	
	SPubDevStatus bag_status = Singleton_ProtoBuf_Bag::get_mutable_instance().get_pub_status();
	
	boost::mutex::scoped_lock lock(dev_status_mu_);
	m_dev_status_[bag_status.dev_status_.device_id_] = bag_status;

}

// bool data_server::upload_bag( SPUB_BAG &p_bag, const std::string file_path )
// {
// 	return Singleton_ProtoBuf_Bag::get_mutable_instance().upload_bag(p_bag,file_path);
// }

bool data_server::update_log_cmd( const SCmd &scmd )
{
	std::string str = scmd.cmd_str_;
	set_log_cmd(str);
	return true;
}

void data_server::pub_process_bar( const SProcess_Bar &pro_bar )
{
	th_process_bar_ = pro_bar;
	//shared_pool::Publish(shared_pool::name(),"process_bar",pro_bar);
	PUB_MSG_SH_POOL("process_bar",pro_bar);
}

void  data_server::get_process_bar(SProcess_Bar &pro_bar)
{
	pro_bar = th_process_bar_();
		
}

bool data_server::update_pro_bar( const SProcess_Bar &pro_bar )
{
	th_process_bar_ = pro_bar;
	return true;
}


bool data_server::update_chk_laser_range(const SCHK_LASER_RANGE &chk_laser_range)
{
	boost::mutex::scoped_lock lock(mu_pub_ch_laser_range_);
	m_pub_chk_laser_range_[chk_laser_range.type_] = chk_laser_range;
	return true;
}
bool data_server::update_laser_range_show(const Range_type &range_type)
{
	pub_range_type_show_.put(range_type);
	return true;
}

bool data_server::update_reflector(const SReflector &ref)
{
	pub_ref_ = ref;
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().put_reflector(ref);
	return true;
}


// void data_server::update_reflector_pos(const SPos &ref_pos)
// {
// 	pub_reflector_pos_.put(ref_pos);
// }


bool data_server::updata_laser_ex(const SLaser_Ex &laser_ex)
{
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().put_laser(laser_ex);
	return true;
}


bool data_server::updata_loop_closure(const SLoopCLosurePos &c_pos)
{
	pub_loop_closure_.put(c_pos);
	return true;
}


bool data_server::updata_amcl_entropy(const SAMCL_ENTROPY &amcl_entropy)
{
	pub_amcl_entropy_.put(amcl_entropy);
	return true;
}


bool data_server::updata_amcl_confidence(const SAMCL_CONFIDENCE &amcl_confidence)
{
	pub_amcl_confidence_.put(amcl_confidence);
	return true;
}

bool data_server::pub_bag( const SPUB_BAG &pro_bag )
{
	pub_bag_list_.put(pro_bag);
	return true;
}
bool data_server::pub_bag_lc( const SPUB_BAG &pro_bag )
{
	pub_bag_list_.put(pro_bag);
	return true;
}

bool data_server::get_bag( char* &data,int &len )
{
	SPUB_BAG pub_bag;
	if (pub_bag_list_.get(pub_bag))
	{
		protobuf_bag_.bag2buf(data,len,pub_bag);

		return true;
	}
	return false;
}


void data_server::pub_ex_bag(const SPUB_BAG_EX &pro_bag)
{
	pub_bag_ex_list_.put(pro_bag);
}


bool data_server::get_ex_bag(char* &data,int &len)
{
	SPUB_BAG_EX pub_ex_bag;
	if (pub_bag_ex_list_.get(pub_ex_bag))
	{
		protobuf_bag_ex_.bag2buf(data,len,pub_ex_bag);

		return true;
	}
	return false;
}


bool data_server::get_laser_ex_ref(char* &data,int &len)
{
	return Singleton_ProtoBuf_Bag_ex::get_mutable_instance().get_laser(data,len);
// 	SPUB_BAG_EX bag_ex;
// 	proto_buf_parse_ex::init_static();
// 	proto_buf_parse_ex::buf2bag(bag_ex,data,len);
//	return true;
}

void data_server::set_path( std::string str_path,std::vector<SOdomSpeed> path )
{
	std::ofstream fout;
	fout.setf(std::ios::fixed, std::ios::floatfield); 
	fout.precision(6);

	str_path = "./plan/" + str_path;
	fout.open( str_path  ,std::ios::trunc | std::ios::binary );

	if(fout.is_open()){

		std::vector<SOdomSpeed>::iterator it = path.begin();
		for( ; it != path.end();  ++it)
		{
			fout<<it->x_<<" "<<it->y_<<" "<<it->th_<<" "
				<<it->vx_<<" "<<it->vy_<<" "<<it->vw_<<std::endl;
		}
	}

	fout.close();
}

void data_server::set_seg_path(char* data,int len)
{
	protobuf_seg_path seg_path;
	seg_path.byte2proto(data,len);

	std::vector<SPathData> seg_path_data;
	seg_path.get_seg_path(seg_path_data);

	len  = seg_path_data.size() * sizeof(SPathData);
	data = new char[len];
 
 	memcpy(data,(char*)&seg_path_data[0],len);
	
	//shared_pool::Publish_pipe(shared_pool::name(), "seg_path", WORLD_LAYER, (U8*)data, len);
	if (!b_sim_){
		PUB_PIPE_SH_POOL("seg_path", WORLD_LAYER, (U8*)data, len);
	}else{
		assert(false);
		msg_array_pump::pub_msg("seg_path", WORLD_LAYER, (U8*)data, len);
	}
	

 	if(NULL != data)
 	{
 		delete[] data;
 		data = NULL;
	}
}

bool data_server::download_file( std::string str_cmd,std::string str_file )
{
	if ( "open" == str_cmd ){
		if(download_file_.open_wfile(str_file) == 0){
			return true;
		}
	}else if ( "close" == str_cmd ){
		download_file_.close_wfile();
		return true;
	}
	return false;
}

bool data_server::download_file( char* p_data, int ilen )
{
	if (download_file_.write_file(p_data,ilen) == 0)
	{
		return true;
	}
	return false;
}




bool data_server::updata_ref_pos( const SPOS_CONFIDENCE &confidence_pos )
{
	pub_ref_confidence_.put(confidence_pos);
	return true;
}
bool data_server::updata_battery(const SBattery &bt)
{
	SBattery bt_tmp;
	bt_tmp = bt;
// 	bt_tmp.get_contactor_in_ = ths_contactor_in_();
// 	bt_tmp.set_contactor_out_ = ths_contactor_out_();
	battery_.put(bt_tmp);
	return true;
}
bool data_server::updata_special_loc(const SPOS_CONFIDENCE &confidence_pos)
{
	pub_special_loc_con_pos_.put(confidence_pos);
	return true;
}
bool data_server::updata_special_landmark(const SWorldLM &wlm)
{
	pub_special_loc_wlm_.put(wlm);
	return true;
}


bool data_server::update_pipe_log(std::string name,U8* data,U32 len)
{
	return true;
}

// bool data_server::update_bt_contactor_in(const int& bt_contact)
// {
// 	ths_contactor_in_ = bt_contact;
// 	return true;
// }
// bool data_server::update_bt_contactor_out(const int& bt_contact)
// {
// 	ths_contactor_out_ = bt_contact;
// 	return true;
// }

bool data_server::update_steering( const SSteering& st )
{
	boost::mutex::scoped_lock lock(mu_steering_);
	m_steering_[st.id_] = st;

	return true;
}


bool data_server::update_di_ai(const SDIAI &di_ai)
{
	return true;
}


bool data_server::update_do_ao(const SDOAO &do_ao)
{

	return true;
}


bool data_server::update_sdi(const SDI &sdi)
{
	return true;
}


bool data_server::update_sdo(const SDO &sdo)
{
	return true;
}

bool data_server::update_mv_status(const SRunStatus &sta)
{

	return true;
}


bool data_server::update_qr_code(const SQrCode &qr_code)
{
	thb_qr_code_.put(qr_code);

	return true;
}


bool data_server::update_priority_speed(const SDynamic_Speed &speed)
{
	boost::mutex::scoped_lock lock(mu_priority_speed_);
	m_priority_speed_[speed.id_] = speed;

	return true;
}

void data_server::init_sim_sub_msg()
{
	

	msg_pump::end_Sub(sub_id_sim_robot_pos_,SPos());
	boost::function<bool( const SPos &pos)> fnc_sim_pos;
	fnc_sim_pos = boost::bind(&data_server::s_robot_pos,this ,_1);
	sub_id_sim_robot_pos_ = msg_pump::sub_msg(PUB_AMCL_POS,fnc_sim_pos);

	msg_pump::end_Sub(sub_id_odom_,SOdomSpeed());
	boost::function<bool( const SOdomSpeed &odomspeed )> fnc_odom;
	fnc_odom = boost::bind(&data_server::update_odom,this ,_1);
	sub_id_odom_ = msg_pump::sub_msg(PUB_CHASSIS_ODOM_SPEED,fnc_odom);
	

	msg_pump::end_Sub(sub_id_fork_task_,SAct_Fork());
	boost::function<bool( const SAct_Fork &fork_task)> fnc_fork_task;
	fnc_fork_task = boost::bind(&data_server::s_fork_task,this ,_1);
	sub_id_fork_task_ = msg_pump::sub_msg(PUB_TASK_FORK,fnc_fork_task);

	msg_pump::end_Sub(sub_id_fork_data_,SAct_Fork_DATA());
	boost::function<bool( const SAct_Fork_DATA &fork_data)> fnc_fork_data;
	fnc_fork_data = boost::bind(&data_server::s_fork_data,this ,_1);
	sub_id_fork_data_ = msg_pump::sub_msg(PUB_ACT_FORK_DATA,fnc_fork_data);

	boost::function<bool( const SPubDevStatus &dev_status )> fnc_dev_status;
	fnc_dev_status = boost::bind(&data_server::update_dev_status,this ,_1);

	//SUB_MSG_SH_POOL("device_status",fnc_dev_status);
	msg_pump::sub_msg("device_status",fnc_dev_status);

	boost::function<bool( const SBattery &bt )> fnc_bt;
	fnc_bt = boost::bind(&data_server::updata_battery,this ,_1);
	//SUB_MSG_SH_POOL(PUB_BATTERY_STATE,fnc_bt);
	msg_pump::sub_msg(TH_PUB_BATTERY_STATE,fnc_bt);
}
bool data_server::s_fork_task( const SAct_Fork &fork_task )
{
	th_act_fork_ = fork_task;
	return true;
}
bool data_server::s_fork_data( const SAct_Fork_DATA &fork_data ){
	pub_fork_data_.put(fork_data);
	return true;
}
bool data_server::s_robot_pos(const SPos &pos)
{
	return update_amcl_pos(pos);
}

bool data_server::get_ref_pos( SPOS_CONFIDENCE &pos_confi)
{

	if ( pub_ref_confidence_.size() ){
		pub_ref_confidence_.get(pos_confi);
		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
		return true;
	}
	return false;
}

void data_server::init_subcribe_play_back()
{
	boost::function<bool( const SLaser &laser_data )> fnc_usd_laser;
	fnc_usd_laser = boost::bind(&data_server::updata_used_laser,this,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser",fnc_usd_laser);
	std::string str = "laser";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL( str ,fnc_usd_laser);

	boost::function<bool( const SLaser_Ex &laser_ex )> fnc_laser_ex;
	fnc_laser_ex = boost::bind(&data_server::updata_laser_ex,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser_ex",fnc_laser_ex);
	str = "laser_ex";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL(str,fnc_laser_ex);


	boost::function<bool( const SOdomSpeed &odomspeed )> fnc_odom;
	fnc_odom = boost::bind(&data_server::update_odom,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"odom",fnc_odom);
	str = "odom";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL( str,fnc_odom);

	boost::function<bool( const SPos &pos )> fnc_amcl;
	fnc_amcl = boost::bind(&data_server::update_amcl_pos,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_pos",fnc_amcl);
	str = "amcl_pos";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL(str,fnc_amcl);


	boost::function<bool( const SPubDevStatus &dev_status )> fnc_dev_status;
	fnc_dev_status = boost::bind(&data_server::update_dev_status,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"device_status",fnc_dev_status);
	str = "device_status";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL(str,fnc_dev_status);


	boost::function<bool( const SAMCL_ENTROPY &amcl_entropy )> fnc_amcl_entropy;
	fnc_amcl_entropy = boost::bind(&data_server::updata_amcl_entropy,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_entropy",fnc_amcl_entropy);
	SUB_MSG_SH_POOL(PUB_AMCL_ENTROPY_PLAYBACK,fnc_amcl_entropy);

	boost::function<bool( const SAMCL_CONFIDENCE &amcl_confindence )> fnc_amcl_confidence;
	fnc_amcl_confidence = boost::bind(&data_server::updata_amcl_confidence,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"amcl_confidence",fnc_amcl_confidence);
	SUB_MSG_SH_POOL(PUB_AMCL_CONF_PLAYBACK,fnc_amcl_confidence);
	

	boost::function<bool( const SReflector &ref )> fnc_refs;
	fnc_refs = boost::bind(&data_server::update_reflector,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"laser_ex",fnc_laser_ex);
	str = "reflectors";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL(str,fnc_refs);


	boost::function<bool( const SPOS_CONFIDENCE &confidence_pos )> fnc_ref_pos;
	fnc_ref_pos = boost::bind(&data_server::updata_ref_pos,this ,_1);
	//shared_pool::Subscribe(shared_pool::name(),"reflector_pos",fnc_ref_pos);
	str = "reflector_pos";
	str += PUB_PLAYBACK;
	SUB_MSG_SH_POOL(str,fnc_ref_pos);

	SUB_PIPE_SH_POOL("pub_pipe_log",boost::bind(&data_server::update_pipe_log,this,_1,_2,_3));
}

bool data_server::get_battery(SBattery &bt)
{
	if ( battery_.size() ){
		battery_.get( bt );
		//std::cout<<"data_server x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<std::endl;
		return true;
	}
	return false;
	
}

bool data_server::set_bt_contact(const int &bt_contact)
{	
	PUB_MSG_SH_POOL(PUB_BATTERY_CNT_OUT, bt_contact );
 	return true;
}


bool data_server::get_special_loc_conpos(SPOS_CONFIDENCE &conpos)
{
	if ( pub_special_loc_con_pos_.size() ){
		pub_special_loc_con_pos_.get( conpos );
		std::cout<<"get_special_loc_conpos x:"<<conpos.pos_.x_<<" y:"<<conpos.pos_.y_<<" th:"<<conpos.pos_.th_<<std::endl;
		return true;
	}
	return false;
}

bool data_server::get_special_landmark(SWorldLM &wlm)
{
	if ( pub_special_loc_wlm_.size() ){
		pub_special_loc_wlm_.get( wlm );
		//std::cout<<"get_special_loc_conpos x:"<<conpos.pos_.x_<<" y:"<<conpos.pos_.y_<<" th:"<<conpos.pos_.th_<<std::endl;
		return true;
	}
	return false;
}

bool data_server::set_sim_init_pos(const SPos init_pos)
{
	return msg_pump::pub_msg(PUB_INIT_POS,init_pos);
}

bool data_server::set_heart_beat( const SHeartBeat &hb )
{
	if (b_sim_){
		return msg_pump::pub_msg(TH_PUB_HEART_BEAT,hb);
	}else{
		return PUB_MSG_SH_POOL(TH_PUB_HEART_BEAT, hb );
	}
	
	
	
}

bool data_server::get_fork( SAct_Fork &fork_para )
{
	fork_para = th_act_fork_();
	SAct_Fork_DATA fork_data;
	if (pub_fork_data_.size()){
		pub_fork_data_.get(fork_data);
		fork_para.act_data_ = fork_data;
		
	}
	return true;
}

bool data_server::set_pause( int i_pause )
{

	
	if (b_sim_){
		return msg_pump::pub_msg(TH_PUB_PAUSE,i_pause);
	}else{
		return PUB_MSG_SH_POOL(TH_PUB_PAUSE, i_pause );
	}
}


bool data_server::get_qr_code(SQrCode &qr_code)
{
// 	qr_code.time_stemp_ = cTimerDiff::total_ms();
// 	qr_code.qr_id_ = 1;
// 	qr_code.pos_.x_ = 0.1;
// 	qr_code.pos_.y_ = 0.2;
// 	qr_code.pos_.th_ = -0.3;
// 	cComm::String2Charlist((S8*)qr_code.ch_des_,200,std::string("uuid"));
// 	thb_qr_code_.put(qr_code);
	return thb_qr_code_.get(qr_code);
}

bool data_server::get_steering( std::vector<SSteering> &v_st )
{

	boost::mutex::scoped_lock lock(mu_steering_);
	auto it = m_steering_.begin();
	for (  ; it != m_steering_.end() ; ++it ){
		v_st.push_back(it->second);
	}
	if (v_st.size() > 0){

		return true;
	}
	return false;
	
}

bool data_server::get_dio_bind(std::map<std::string, SDIO_NM_INDEX> &m_fnc_bind)
{
	if(DIO_MANAGE.get_bind(m_fnc_bind)){
		return true;
	}
	return false;
}

bool data_server::get_dio_data(std::vector<SDIO_NM_INDEX> &v_data)
{
	return DIO_MANAGE.get_io_data(v_data);

}

//pipe 
// bool data_server::update_pipe_log(std::string name,U8* data,U32 len){
// 
// }






































