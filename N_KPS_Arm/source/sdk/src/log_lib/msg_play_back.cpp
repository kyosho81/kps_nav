#include <cassert>
#include <iostream>

#include "Comm/PortDef.h"
#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "trans_dev/trans_dev.h"
#include "Comm/TimerDiff.h"
#include "Comm/PortDef.h"
#include "Log4cppArm.hpp"
#include "log/Log4cppMsgIndex.h"
#include "interpro_shared/sh_pool.hpp"
#include "robot/msg_def.h"

#include "protobuf_msg/pos.pb.h"
#include "protobuf_msg/base.pb.h"
#include "protobuf_msg/laser_ex.pb.h"
#include "protobuf_msg/dev_status.pb.h"
#include "protobuf_msg/loc_confidence.pb.h"
#include "protobuf_msg/reflector.pb.h"
#include "protobuf_msg/conf_ref_pos.pb.h"
#include "protobuf_msg/dio.pb.h"

#include "sqlite3/sqlite3.h"

#include "log/msg_play_back.h"

//#define SHOW_PUB_LOG 1

msg_play_back::msg_play_back():
pub_func_list_(200)
{
	str_path_ = ".//pkg_log//";
	db_ = 0;

	total_rows_ = 0;

}

msg_play_back::~msg_play_back()
{

}

bool msg_play_back::init()
{
	
	Config::getConfig("log_pkg_path",str_path_);
	std::cout<<"log_pkg_path:"<<str_path_<<std::endl;

	time_coefficient_ = 1.0;

	return true;
}


bool msg_play_back::th_run()
{
	U64 time_stamp = 0;
	boost::function<void (void)> fnc_pub;
	
	U64 dt = dt_.End();
	dt_.Begin();
	dt *= time_coefficient_;
	time_select_begin_ += dt;

	//std::cout<<"time_select_begin_:"<<time_select_begin_<<" dt:"<<dt*1e-3<<std::endl;
	for ( int i = 0 ; i < pub_func_list_.size() ; ++i){
		if( !pub_func_list_.get(time_stamp,fnc_pub,false) ){
			break;
		}
		if (time_stamp < time_select_begin_){
			std::cout<<" data:"<<time_stamp<<std::endl;
			fnc_pub();
		}else{
			//std::cout<<"pub later:"<<time_select_begin_<<" data:"<<time_stamp<<std::endl;
			pub_func_list_.put(time_stamp,fnc_pub,true);
			break;
		}
		
	}
	
	SLEEP(20);

	return th_pub_();
}
bool msg_play_back::destruct()
{
	th_pub_ = false;
	pattern_thread_.destory_thread();
	return true;
}

bool msg_play_back::play_db(const std::string &str_db)
{
	if (!open_db(str_db)){
		return false;
	}
	//get laser para
	get_laser_ex_para();
	//get log data total rows
	total_rows_ = 0;
	find_total_rows();
	//get time stamp head
	find_time_stamp_head();
	time_select_begin_ = time_stamp_first_;
	std::cout<<"time_stamp_first_:"<<time_stamp_first_<<std::endl;
	std::cout<<"time_select_begin_:"<<time_select_begin_<<std::endl;

	th_pub_ = true;
	dt_.Begin();

	pattern_thread_.run_thread(boost::bind(&msg_play_back::th_run,this));
	
	SLEEP(50);

	int i_pub_rows = 0;

	pub_all();

	return true;
}

bool msg_play_back::open_db(const std::string &str_db)
{
	char *zErrMsg=0;  
	int rc;  

	std::cout<<"msg_play_back db name:"<<str_db<<std::endl;

	rc=sqlite3_open(str_db.c_str(),&db_);  /* open database */  

	if(rc){  
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));  
		sqlite3_close(db_);  
		return false;
	}  
	return true;
}
bool msg_play_back::close_db()
{
	sqlite3_close(db_);
	return true;
}

bool msg_play_back::find_time_stamp_head()
{
	sqlite3_stmt * stat;
	//select * from apple order by id asc  LIMIT 1
	int nRes =sqlite3_prepare( db_, "select * from log order by TIMESTP asc  LIMIT 1", -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "select data sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	while(  SQLITE_ROW  == sqlite3_step( stat )){
		time_stamp_first_ = sqlite3_column_int64( stat, 0 );
	}
	sqlite3_finalize( stat ); 
	return true;
}

bool msg_play_back::find_total_rows()
{
	sqlite3_stmt * stat;
	//select * from apple order by id asc  LIMIT 1
	int nRes =sqlite3_prepare( db_, "select count(1) as num from log", -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "select count(1) sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	while(  SQLITE_ROW  == sqlite3_step( stat )){
		total_rows_ = sqlite3_column_int64( stat, 0 );
	}
	sqlite3_finalize( stat ); 

	return true;
}

bool msg_play_back::pub_all()
{
	sqlite3_stmt * stat;
	//select * from apple order by id asc  LIMIT 1
	std::stringstream ss;
	//ss<<"select * from log order by TIMESTP asc ;";
	ss<<"select * from log;";
	int nRes =sqlite3_prepare( db_, ss.str().c_str(), -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "select data sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	log_pair log_p;
	while(  SQLITE_ROW  == sqlite3_step( stat )){

		if (!th_pub_()){
			break;
		}

		memset(&log_p,0,sizeof(log_pair));
		
		log_p.time_stamp_ = sqlite3_column_int64( stat, 0 );
		log_p.msg_name_ = (char*)sqlite3_column_text( stat, 1 );
		log_p.msg_type_ = (char*)sqlite3_column_text( stat, 2 );
		log_p.ch_msg_ = (char*)sqlite3_column_blob( stat, 3 );
		log_p.ilen_ = sqlite3_column_bytes( stat, 3 );

		bind_pub_data(log_p);

		//std::cout<<"db release pub data:"<<log_p.time_stamp_<<std::endl;
	}
	log_p.ch_msg_ = 0;
	sqlite3_finalize( stat );

	for (int i = 0 ; i < 200; i++)
	{
		if (pub_func_list_.size() < 1)
		{
			break;
		}
		//std::cout<<"wait for pub over!"<<std::endl;
		SLEEP(500);
	}
	
	return true;
}
bool msg_play_back::get_laser_ex_para()
{
	memset(&laser_para_,0,sizeof(SLaser_para));

	sqlite3_stmt * stat;
	//select * from apple order by id asc  LIMIT 1
	//int nRes =sqlite3_prepare( db_, "select * from laser_ex_para order by TIMESTP asc  LIMIT 1;", -1, &stat, 0 );
	int nRes =sqlite3_prepare( db_, "select * from laser_ex_para;", -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "select laser ex para sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}

	KPS::mp_laser_ex_para k_laser_ex_para;
	log_pair log_p;
	while(  SQLITE_ROW  == sqlite3_step( stat )){
		
		log_p.time_stamp_ = sqlite3_column_int64( stat, 0 );
		log_p.msg_name_ = (char*)sqlite3_column_text( stat, 1 );
		log_p.msg_type_ = (char*)sqlite3_column_text( stat, 2 );
		log_p.ch_msg_ = (char*)sqlite3_column_blob( stat, 3 );
		log_p.ilen_ = sqlite3_column_bytes( stat, 3 );

		assert(log_p.msg_name_ == "laser_ex_para");

		
		if (k_laser_ex_para.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			std::string str_ip = k_laser_ex_para.laser_ip();
			cComm::String2Charlist((S8*)laser_para_.ch_laser_ip_,500,str_ip);
			laser_para_.laser_dx_ = k_laser_ex_para.laser_dx();
			laser_para_.laser_dy_ = k_laser_ex_para.laser_dy();
			laser_para_.laser_range_max_ = k_laser_ex_para.laser_range_max();
			laser_para_.laser_range_min_ = k_laser_ex_para.laser_range_min();
			laser_para_.laser_resolution_ = k_laser_ex_para.laser_resolution();
			laser_para_.laser_start_angle_ = k_laser_ex_para.laser_start_angle();
			laser_para_.reverse_ = k_laser_ex_para.laser_reverse();
			//sqlite3_finalize( stat );
			//return true;
		}

	}
	log_p.ch_msg_ = 0;
	sqlite3_finalize( stat );
	return true;
}
bool msg_play_back::bind_pub_data(log_pair &log_p)
{
	//log_p.msg_type_
	if ( log_p.msg_type_ == "SPos"){
		KPS::s_pos k_pos;
		if( !k_pos.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}
		SPos pos;
		pos.x_ = k_pos.x();
		pos.y_ = k_pos.y();
		pos.th_ = k_pos.th();

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_spos,this,log_p.msg_name_,pos);
		pub_func_list_.put(log_p.time_stamp_,fnc);
	}else if ( log_p.msg_type_ == "SOdomSpeed"){
		KPS::mp_odom_data k_odom;
		if( !k_odom.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}
		SOdomSpeed odom;
		odom.x_ = k_odom.x();
		odom.y_ = k_odom.y();
		odom.th_ = k_odom.th();
		odom.vx_ = k_odom.vx();
		odom.vy_ = k_odom.vy();
		odom.vw_ = k_odom.vw();

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_sodom,this,log_p.msg_name_,odom);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SLaser"){

		KPS::mp_laser_ex_data k_laser_ex;
		if( !k_laser_ex.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SLaser laser;
		memset(&laser,0,sizeof(SLaser));
 		laser.range_max_ = laser_para_.laser_range_max_;
 		laser.range_min_ = laser_para_.laser_range_min_;
 		laser.resolution_ = laser_para_.laser_resolution_;
		laser.start_angle_ = laser_para_.laser_start_angle_;

		laser.stamp_ = k_laser_ex.stamp();
		laser.used_ = k_laser_ex.used_ray();
		assert(laser.used_ == k_laser_ex.data().size() );
		assert(laser.used_ == k_laser_ex.seg().size() );

		for ( int i = 0 ; i < laser.used_ ; ++i ){
			laser.data_[i] = k_laser_ex.data(i);
			laser.seg_[i] = k_laser_ex.seg(i);
		}
		

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_laser,this,log_p.msg_name_,laser);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SLaser_Ex"){

		KPS::mp_laser_ex_data k_laser_ex;
		if( !k_laser_ex.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SLaser_Ex laser_ex;
		memset(&laser_ex,0,sizeof(SLaser_Ex));

		laser_ex.stamp_ = k_laser_ex.stamp();
		laser_ex.time_stamp_ = k_laser_ex.time_stamp();
		laser_ex.bean_dt_ = k_laser_ex.bean_dt();

		laser_ex.dx_ = laser_para_.laser_dx_;
		laser_ex.dy_ = laser_para_.laser_dy_;
		laser_ex.start_angle_ = laser_para_.laser_start_angle_;
		laser_ex.resolution_ = laser_para_.laser_resolution_;
		laser_ex.range_max_ = laser_para_.laser_range_max_;
		laser_ex.range_min_ = laser_para_.laser_range_min_;

		laser_ex.used_ray_ = k_laser_ex.used_ray();
		for ( int i = 0 ; i < laser_ex.used_ray_; ++i){
			if (i < k_laser_ex.data().size()){
				laser_ex.data_[i] = k_laser_ex.data(i);
			}
			if (i < k_laser_ex.seg().size()){
				laser_ex.seg_[i] = k_laser_ex.seg(i);
			}
			if (i < k_laser_ex.intensities().size()){
				laser_ex.intensities_[i] = k_laser_ex.intensities(i);
			}
		}
		
		
		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_laser_ex,this,log_p.msg_name_,laser_ex);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SPubDevStatus"){

		KPS::mp_dev_status k_dev_status;
		if( !k_dev_status.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SPubDevStatus dev_status;
		memset(&dev_status,0,sizeof(SPubDevStatus));

		std::string str_nm = k_dev_status.name();
		cComm::String2Charlist((S8*)dev_status.name_,200,str_nm);
		dev_status.dev_status_.device_id_ = k_dev_status.dev_id();
		dev_status.dev_status_.status_ = k_dev_status.status();
		dev_status.dev_status_.err_code_ = k_dev_status.err_code();
		dev_status.dev_status_.cycle_ms_ = k_dev_status.cycle_ms();
		dev_status.dev_status_.run_ms_ = k_dev_status.run_ms();


		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_dev_status,this,log_p.msg_name_,dev_status);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SAMCL_ENTROPY"){

		KPS::mp_loc_confidence k_loc_confidence;

		if( !k_loc_confidence.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SAMCL_CONFIDENCE amcl_conf;
		memset(&amcl_conf,0,sizeof(SAMCL_CONFIDENCE));

		SAMCL_ENTROPY amcl_entropy;
		memset(&amcl_entropy,0,sizeof(SAMCL_ENTROPY));

		amcl_conf.b_amcl_confidence_ = k_loc_confidence.b_amcl_conf();
		amcl_conf.amcl_confidence_ = k_loc_confidence.amcl_conf();

		amcl_entropy.b_amcl_entropy_ = k_loc_confidence.b_amcl_entropy();
		amcl_entropy.amcl_xy_entropy_ = k_loc_confidence.amcl_xy_entropy();
		amcl_entropy.amcl_theta_entropy_ = k_loc_confidence.amcl_theta_entropy();
		amcl_entropy.amcl_entropy_ = k_loc_confidence.amcl_entropy();

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_loc_conf,this,log_p.msg_name_,amcl_conf,amcl_entropy);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_name_ == "log"){
		std::string str_log = log_p.ch_msg_;

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_log,this,log_p.msg_name_,str_log);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SReflector"){

		KPS::mp_refs k_refs;
		if( !k_refs.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SReflector refs;
		memset(&refs,0,sizeof(SReflector));
		
		assert(k_refs.id().size() == k_refs.x().size());
		assert(k_refs.id().size() == k_refs.y().size());

		refs.used_ = k_refs.id().size();
		for ( int i = 0 ; i < refs.used_ ; ++i ){
			refs.id_[i] = k_refs.id(i);
			refs.pos_[i].x_= k_refs.x(i);
			refs.pos_[i].y_ = k_refs.y(i);
		}
		

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_refs,this,log_p.msg_name_,refs);
		pub_func_list_.put(log_p.time_stamp_,fnc);
	}else if(log_p.msg_type_ == "view_data"){
	
		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_view_data,this,log_p.msg_name_,(U8*)log_p.ch_msg_,log_p.ilen_);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SPOS_CONFIDENCE"){

		KPS::mp_conf_ref_pos k_conf_pos;
		if( !k_conf_pos.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SPOS_CONFIDENCE conf_pos;
		memset(&conf_pos,0,sizeof(SPOS_CONFIDENCE));
		conf_pos.confidence_.amcl_confidence_ = k_conf_pos.confidence();
		conf_pos.confidence_.b_amcl_confidence_ = k_conf_pos.b_conf();
		conf_pos.pos_.x_ = k_conf_pos.mutable_ref_pos()->x();
		conf_pos.pos_.y_ = k_conf_pos.mutable_ref_pos()->y();
		conf_pos.pos_.th_ = k_conf_pos.mutable_ref_pos()->th();

		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_ref_pos,this,log_p.msg_name_,conf_pos);
		pub_func_list_.put(log_p.time_stamp_,fnc);
	}else if(log_p.msg_type_ == "SDI"){

		KPS::mp_sdi k_sdi;
		if( !k_sdi.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SDI sdi;
		memset(&sdi,0,sizeof(SDI));

		assert(k_sdi.id().size() == k_sdi.di().size());

		sdi.used_ = k_sdi.id().size();
		for ( int i = 0 ; i < sdi.used_ ; ++i ){
			sdi.id_[i] = k_sdi.id(i);
			sdi.di_[i]= k_sdi.di(i);

		}


		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_sdi,this,log_p.msg_name_,sdi);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SDO"){

		KPS::mp_sdo k_sdo;
		if( !k_sdo.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SDO sdo;
		memset(&sdo,0,sizeof(SDO));

		assert(k_sdo.id().size() == k_sdo.doo().size());


		sdo.used_ = k_sdo.id().size();

		for ( int i = 0 ; i < sdo.used_ ; ++i ){
			sdo.id_[i] = k_sdo.id(i);
			sdo.do_[i]= k_sdo.doo(i);

		}


		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_sdo,this,log_p.msg_name_,sdo);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SFAI"){

		KPS::mp_sfai k_sfai;
		if( !k_sfai.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SFAI sfai;
		memset(&sfai,0,sizeof(SFAI));

		assert(k_sfai.id().size() == k_sfai.fai().size());


		sfai.used_ = k_sfai.id().size();
		for ( int i = 0 ; i < sfai.used_ ; ++i ){
			sfai.id_[i] = k_sfai.id(i);
			sfai.fai_[i]= k_sfai.fai(i);

		}


		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_fai,this,log_p.msg_name_,sfai);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else if(log_p.msg_type_ == "SFAO"){

		KPS::mp_sfai k_sfai;
		if( !k_sfai.ParseFromArray(log_p.ch_msg_,log_p.ilen_)){
			return false;
		}

		SFAO sfao;
		memset(&sfao,0,sizeof(SFAO));

		assert(k_sfai.id().size() == k_sfai.fai().size());


		sfao.used_ = k_sfai.id().size();
		for ( int i = 0 ; i < sfao.used_ ; ++i ){
			sfao.id_[i] = k_sfai.id(i);
			sfao.fao_[i]= k_sfai.fai(i);

		}


		boost::function<void(void)> fnc;
		fnc = boost::bind(&msg_play_back::pub_fao,this,log_p.msg_name_,sfao);
		pub_func_list_.put(log_p.time_stamp_,fnc);

	}else{
		std::cout<<"msg_play_back::bind_pub_data err log_p.msg_name_:"<<log_p.msg_name_ <<" or log_p.msg_type_:"<<log_p.msg_type_<<std::endl;
	}
	
	return true;
}

void msg_play_back::pub_spos( std::string str_msg_nm, const SPos pos)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pos x y th:"<<pos.x_<<" "<<pos.y_<<" "<<pos.th_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,pos);
}

void msg_play_back::pub_sodom( std::string str_msg_nm, const SOdomSpeed odom)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_sodom x y th vx vy w:"<<odom.x_<<" "<<odom.y_<<" "<<odom.th_<<" "<<odom.vx_<<" "<<odom.vy_<<" "<<odom.vw_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,odom);
}
void msg_play_back::pub_laser( std::string str_msg_nm, const SLaser laser)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" laser stamp:"<<laser.stamp_;
	std::cout<<" laser start angle:"<<laser.start_angle_;
	std::cout<<" laser resolution:"<<laser.resolution_;
	std::cout<<" laser range max:"<<laser.range_max_;
	std::cout<<" laser range min:"<<laser.range_min_;
	std::cout<<" laser used size:"<<laser.used_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,laser);
}
void msg_play_back::pub_laser_ex( std::string str_msg_nm, const SLaser_Ex laser_ex)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" laser stamp:"<<laser_ex.stamp_;
	std::cout<<" laser ex start angle:"<<laser_ex.start_angle_;
	std::cout<<" laser ex resolution:"<<laser_ex.resolution_;
	std::cout<<" laser ex  range max:"<<laser_ex.range_max_;
	std::cout<<" laser ex range min:"<<laser_ex.range_min_;
	std::cout<<" laser ex used size:"<<laser_ex.used_ray_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,laser_ex);
}



void msg_play_back::pub_dev_status( std::string str_msg_nm, const SPubDevStatus dev_status)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm;
	std::cout<<" dev_status name:"<<dev_status.name_;
	std::cout<<" "<<int(dev_status.dev_status_.status_);
	std::cout<<" "<<int(dev_status.dev_status_.device_id_);
	std::cout<<" "<<int(dev_status.dev_status_.err_code_);
	std::cout<<" "<<(dev_status.dev_status_.run_ms_);
	std::cout<<" "<<(dev_status.dev_status_.cycle_ms_)<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,dev_status);
}

void msg_play_back::pub_loc_conf( std::string str_msg_nm, const SAMCL_CONFIDENCE amcl_conf, const SAMCL_ENTROPY amcl_entropy)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm;
	std::cout<<" amcl_conf amcl_confidence:"<<amcl_conf.amcl_confidence_;
	std::cout<<" amcl_conf b_amcl_confidence:"<<amcl_conf.b_amcl_confidence_;

	std::cout<<" amcl_entropy amcl_entropy:"<<amcl_entropy.amcl_entropy_;
	std::cout<<" amcl_entropy amcl_theta_entropy:"<<amcl_entropy.amcl_theta_entropy_;
	std::cout<<" amcl_entropy amcl_xy_entropy:"<<amcl_entropy.amcl_xy_entropy_;
	std::cout<<" amcl_entropy b_amcl_entropy:"<<amcl_entropy.b_amcl_entropy_<<std::endl;
#endif
	PUB_MSG_SH_POOL(PUB_AMCL_CONF_PLAYBACK,amcl_conf);
	PUB_MSG_SH_POOL(PUB_AMCL_ENTROPY_PLAYBACK,amcl_entropy);
}

void msg_play_back::pub_log( const std::string str_msg_nm, const std::string str_log )
{
	U8* data = 0; 
	int ilen = 0;
	cComm::String2Char(data,ilen,str_log);
	if(!pipe_shared_pool::push_back( PUB_LOG_PLAYBACK, "log" , data, ilen ,false )){

	}

	std::cout<<"str_log:"<<str_log<<std::endl;
	delete[] data;
	data = 0;
}

void msg_play_back::pub_refs(std::string str_msg_nm, const SReflector refs)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" refs size:"<<refs.used_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,refs);
}

void msg_play_back::pub_view_data(std::string str_msg_nm, U8* p_data,int ilen)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<"  size:"<<ilen<<std::endl;
#endif
	pub_view_data::pub(str_msg_nm,p_data,ilen);
}

void msg_play_back::pub_ref_pos(std::string str_msg_nm, const SPOS_CONFIDENCE conf_ref_pos)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_ref_pos conf:"<<conf_ref_pos.confidence_.amcl_confidence_<<" b_conf:"<<int(conf_ref_pos.confidence_.b_amcl_confidence_)<<std::endl;
	std::cout<<"pos :"<<conf_ref_pos.pos_.x_<<" "<<conf_ref_pos.pos_.y_<<" "<<conf_ref_pos.pos_.th_<<std::endl;
#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,conf_ref_pos);
}

void msg_play_back::pub_sdi( std::string str_msg_nm, const SDI &sdi )
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_sdi size:"<<sdi.used_<<std::endl;

#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,sdi);
}

void msg_play_back::pub_sdo(std::string str_msg_nm, const SDO &sdo)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_sdo size:"<<sdo.used_<<std::endl;

#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,sdo);
}

void msg_play_back::pub_fai(std::string str_msg_nm, const SFAI &sfai)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_fai size:"<<sfai.used_<<std::endl;

#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,sfai);
}

void msg_play_back::pub_fao(std::string str_msg_nm, const SFAO &sfao)
{
#if SHOW_PUB_LOG
	std::cout<<"name:"<<str_msg_nm<<" pub_fao size:"<<sfao.used_<<std::endl;

#endif
	str_msg_nm = str_msg_nm + PUB_PLAYBACK;
	PUB_MSG_SH_POOL(str_msg_nm,sfao);
}




