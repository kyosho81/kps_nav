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
#include "robot/dio_def.h"

#include "sqlite3/sqlite3.h"


#include "log/msg_log_server.h"

#define MSG_LOG_MAX_BUFFER 4096
//#define DB_FILE_SIZE       136314880 //1024*1024*13 = 130m
#define DB_FILE_SIZE         1048000 //1024*1024*1 = 1m
//#define DB_FILE_SIZE         10480000 //1024*1024*1 = 10m

msg_log_server::msg_log_server()
:l_msg_pair_(MSG_LOG_MAX_BUFFER),v_save_db_(10)
{
	db_ = 0;
	th_save_cnt_ = 1;
}

msg_log_server::~msg_log_server()
{

}

bool msg_log_server::init()
{

	v_save_db_.clear();

	str_path_ = ".//db_log//";
	Config::getConfig("log_db_path",str_path_);
	str_db_ ="";

	th_status_ = IDLE;
	b_record_ = true;
	pattern_thread_.run_thread(boost::bind(&msg_log_server::th_run,this));

	sub_log_msg();

	pk_laser_ex_para_ = 0;

	b_laser_para_ = true;
	b_laser_ex_para_ = true;

	std::stringstream ss;
	ss<<DIO_DEV_ONBOARD<<":"<<DIO_DEV_PLCLUJIE<<":"<<DIO_DEV_MUSHINY;
	sub_DIO( ss.str(),ss.str() );

	return true;

}

bool msg_log_server::put_data(U64 time_stamp , const std::string &msg_name, const std::string &msg_type ,char* const ch_msg,int ilen)
{

	boost::mutex::scoped_lock lock(mu_msg_pair_);

	log_pair* p_log = new log_pair();

	p_log->time_stamp_ = time_stamp;
	p_log->msg_name_ = msg_name;
	p_log->msg_type_ = msg_type;
	p_log->ch_msg_ = ch_msg;
	p_log->ilen_ = ilen;

	
	l_msg_pair_.push_back(p_log);

	return true;
}



std::string msg_log_server::get_db_name()
{
	
	std::stringstream ss;
	ss<<str_path_<<cTimerDiff::get_file_now() <<"_"<<cComm::ConvertToString(cTimerDiff::total_ms()) <<".db";

	return ss.str();
}

bool msg_log_server::destruct()
{
	pattern_thread_.destory_thread();
	return true;
}
int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
bool msg_log_server::create_table(const std::string &table_name)
{
	char *zErrMsg=0;  
	int rc; 

	std::stringstream ss;
	ss<<"CREATE TABLE "<<table_name;
	//ss<<"( TIMESTP INTEGER PRIMARY KEY     NOT NULL, 
	ss<<"( TIMESTP        INTEGER NOT NULL, \
	       NAME           TEXT    NOT NULL, \
	       TYPE           TEXT    NOT NULL, \
	       DATA		      BLOB \
		 );";

	rc = sqlite3_exec(db_, ss.str().c_str(), callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}else{
		fprintf(stdout, "Table created successfully\n");
	}
	return true;
}
bool msg_log_server::save_one(log_pair* log)
{
 	std::string strSql = "";
 	strSql += "insert into log(TIMESTP,NAME,TYPE,DATA)";
 	strSql += "values('";
 	strSql += cComm::ConvertToString(log->time_stamp_);
 	strSql += "','";
 	strSql += log->msg_name_ ;
 	strSql += "','";
 	strSql += log->msg_type_ ;
 	strSql += "', ? );";

	//std::cout<<"strSql:"<<strSql<<std::endl;

	sqlite3_stmt * stat;
	int nRes = sqlite3_prepare_v2( db_, strSql.c_str() , -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "insert data sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	nRes = sqlite3_bind_blob( stat, 1, log->ch_msg_,log->ilen_,NULL );
	if (nRes != SQLITE_OK){
		std::cout << "insert data sql bind char fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	nRes = sqlite3_step( stat );
	if (nRes != SQLITE_DONE){
		std::cout << "insert data into db fail: " <<nRes<<" "<<log->msg_name_ << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	sqlite3_finalize( stat );
	
	//std::cout<<"save one log:"<<log->time_stamp_<<std::endl;
	return true;
// 	char* cErrMsg;
//  	int nRes = sqlite3_exec(db_, ch_sql_, 0, 0, &cErrMsg);
//  	if (nRes != SQLITE_OK)
//  	{
//  		std::cout << "insert data fail: " << cErrMsg << std::endl;
//  		return false;
//  	}
//  	else
//  	{
//  		std::cout << "insert data success: " << log->time_stamp_ << " " << log->msg_name_ <<" " <<log->msg_type_ << std::endl;
//  	}

	
}
bool msg_log_server::open_db()
{

	char *zErrMsg=0;  
	int rc;  

	str_db_ = get_db_name();
	std::cout<<"msg_log_server db name:"<<str_db_<<std::endl;

	rc=sqlite3_open(str_db_.c_str(),&db_);  /* open database */  
	if(rc){  
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));  
		sqlite3_close(db_);  
		str_db_ = "";
		return false;
	}  
	return true;
}

bool msg_log_server::close_db()
{
	sqlite3_close(db_);
	return true;
}

bool msg_log_server::th_run()
{
	char *pErrMsg = 0;
	switch(th_status_()){
	case IDLE:
		if(b_record_){
			th_status_ = OPEN;
			std::cout<<"try to open db!"<<std::endl;
		}else{
			std::cout<<"msg log IDLE!!!!!"<<std::endl;

			SLEEP(1000);
		}
		break;
	case OPEN:
		if (open_db()){
			

			create_table("log");
			create_table("laser_ex_para");
			b_laser_para_ = true;

			th_status_ = RECORD;
			std::cout<<"go to record db!"<<std::endl;
		}else{
			th_status_ = IDLE;
			b_record_ = false;
			std::cout<<"oped db error! go to IDLE!"<<std::endl;
			SLEEP(100);
		}
		
		break;
	case RECORD:
		{
			//save data
			std::list<log_pair*> v_rec;

			
			for (int i = 0 ; i < 300 ; ++i ){
				boost::mutex::scoped_lock lock(mu_msg_pair_);
				if (l_msg_pair_.size() < 1){
					break;
				}
				//save all log and save all data when err status 
				log_pair* p_plog = l_msg_pair_.front();
				if( ( p_plog->msg_name_=="log") || check_save_data()){
					v_rec.push_back(p_plog);
				}else{
					SDelete(p_plog);
				}
				
				l_msg_pair_.pop_front();
			}
			std::cout<<"v_rec:"<<v_rec.size()<<std::endl;
			//beg transaction
			int rc = sqlite3_exec(db_, "begin;", NULL, 0, &pErrMsg);
			if (rc != SQLITE_OK)
			{
				std::cout << "begin transaction err:" << pErrMsg << endl;;
				sqlite3_free(pErrMsg);
			}

			std::list<log_pair*>::iterator it = v_rec.begin();
			for ( ; it != v_rec.end();  ++it){
				log_pair* log = *it;

				if (!save_one(log)){
					
					//std::cout<<"save one log to db error! "<<std::endl;
				}
				
				SDelete(log);
			}
			//end transaction
			sqlite3_exec(db_, "commit;", NULL, 0, 0);

			//check db size if big to save
			if(check_db_size_save()){
				th_status_ = CLOSE;
				std::cout<<"go to close db!"<<std::endl;
// 				std::vector<log_pair*> v_log;
// 				get_rec(v_log);

			}else{
				SLEEP(3000);
			}
			
		}
		break;
	case CLOSE:
		if (str_db_.length() > 0){
			std::cout<<"save db:"<<str_db_<<std::endl;
			v_save_db_.put(str_db_);
		}

		close_db();
		th_status_ = OPEN;
		break;
	}
	return true;
}

bool msg_log_server::check_db_size_save()
{
	int i_db_size = cComm::Get_FileSize(str_db_);
	
	if ( i_db_size > DB_FILE_SIZE ){
		std::cout<<"db size:"<<i_db_size<<std::endl;
		return true;
	}
	
	return false;
}

void msg_log_server::sub_log_msg()
{
	//sub amcl pos
	std::string sub_msg_name = "amcl_pos";
	sub_spos(sub_msg_name);

	//sub odom 
	sub_msg_name = "odom";
	sub_sodom_pos(sub_msg_name);

	//sub laser
	sub_msg_name = "laser";
	sub_laser(sub_msg_name);

	//sub laser ex
	sub_msg_name = "laser_ex";
	sub_laser_ex(sub_msg_name);

	//sub dev status
	sub_msg_name = "device_status";
	sub_dev_status(sub_msg_name);

	//sub amcl conf
	sub_msg_name = "amcl_confidence";
	sub_amcl_conf(sub_msg_name);

	//sub reflector
	sub_msg_name = "reflectors";
	sub_reflector(sub_msg_name);

	//sub reflector pos
	sub_msg_name = "reflector_pos";
	sub_reflector_pos(sub_msg_name);

	//sub log pipe
	SUB_PIPE_SH_POOL(PUB_PIPE_LOG,boost::bind(&msg_log_server::update_pipe_log,this,_1,_2,_3));

	//sub view data pipe
	boost::function<bool (std::string name,U8* data,U32 len)> fnc;
	fnc = boost::bind(&msg_log_server::call_view_data_pipe,this,_1,_2,_3);
	std::string str_sub_pipe = pub_view_data::sub_view_pipe(fnc);
}

void msg_log_server::sub_spos(const std::string &sub_msg_name)
{
	boost::function<bool( const SPos &pos )> fnc;
	boost::shared_ptr<KPS::s_pos> pk_pos = boost::shared_ptr<KPS::s_pos>(new KPS::s_pos);
	fnc = boost::bind(&msg_log_server::update_pos,this ,_1,pk_pos,sub_msg_name,(char*)(0));
	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}

bool msg_log_server::update_pos(const SPos &pos,boost::shared_ptr<KPS::s_pos> pk_pos ,std::string sub_msg_name, char* ch_data ){

	pk_pos->set_x(pos.x_);
	pk_pos->set_y(pos.y_);
	pk_pos->set_th(pos.th_);

	ch_data = new char[pk_pos->ByteSize()];
	memset(ch_data,0,pk_pos->ByteSize());

	if (pk_pos->SerializeToArray( ch_data , pk_pos->ByteSize())){
		
		put_data(cTimerDiff::total_ms(),sub_msg_name,"SPos",ch_data,pk_pos->ByteSize());

	}else{
		std::cout<<"update_amcl_pos SerializeToArray Error!"<<std::endl;
	}

	return true;
}



void msg_log_server::sub_sodom_pos( const std::string &sub_msg_name )
{
	boost::function<bool( const SOdomSpeed &odom_pos )> fnc;
	boost::shared_ptr<KPS::mp_odom_data> pk_odom_pos = boost::shared_ptr<KPS::mp_odom_data>(new KPS::mp_odom_data);
	fnc = boost::bind(&msg_log_server::update_odomspeed,this ,_1,pk_odom_pos,sub_msg_name,(char*)(0));
	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}
bool msg_log_server::update_odomspeed( const SOdomSpeed &odom_pos,boost::shared_ptr<KPS::mp_odom_data> pk_odom_pos,std::string sub_msg_name, char* ch_data )
{
	pk_odom_pos->set_x(odom_pos.x_);
	pk_odom_pos->set_y(odom_pos.y_);
	pk_odom_pos->set_th(odom_pos.th_);
	pk_odom_pos->set_vx(odom_pos.vx_);
	pk_odom_pos->set_vy(odom_pos.vy_);
	pk_odom_pos->set_vw(odom_pos.vw_);

	ch_data = new char[pk_odom_pos->ByteSize()];
	memset(ch_data,0,pk_odom_pos->ByteSize());

	if (pk_odom_pos->SerializeToArray( ch_data , pk_odom_pos->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SOdomSpeed",ch_data,pk_odom_pos->ByteSize());

	}else{
		std::cout<<"update_amcl_pos SerializeToArray Error!"<<std::endl;
	}

	return true;
}

int msg_log_server::get_rec(std::vector<log_pair*> &v_log)
{
	v_log.clear();
	sqlite3_stmt * stat;
	int nRes =sqlite3_prepare( db_, "select * from log", -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "select data sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	while(  SQLITE_ROW  == sqlite3_step( stat )){
		log_pair* p_log = new log_pair;
		p_log->time_stamp_ = sqlite3_column_int64( stat, 0 );
		p_log->msg_name_ = (char*)sqlite3_column_text( stat, 1 );
		p_log->msg_type_ = (char*)sqlite3_column_text( stat, 2 );
		p_log->ch_msg_ = (char*)sqlite3_column_blob( stat, 3 );
		p_log->ilen_ = sqlite3_column_bytes( stat, 3 );
		if (p_log->msg_type_ == "SPos"){
			KPS::s_pos pos;
			pos.ParseFromArray(p_log->ch_msg_,p_log->ilen_);
			std::cout<<p_log->time_stamp_<<" "<<p_log->msg_name_<<" "<<p_log->msg_type_ <<" x:"<<pos.x()<<" y:"<<pos.y()<<" th:"<<pos.th()<<std::endl;

		}else if(p_log->msg_type_ == "string"){
			std::string str = p_log->ch_msg_;
			std::cout<<p_log->time_stamp_<<" "<<p_log->msg_name_<<" "<<p_log->msg_type_ <<" log str:"<<str<<std::endl;
		}
		v_log.push_back(p_log);
	}

	sqlite3_finalize( stat ); 
	//result = sqlite3_reset(stat);
	return v_log.size();
}

void msg_log_server::sub_laser( const std::string &sub_msg_name )
{
	boost::function<bool( const SLaser &laser )> fnc;
	boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser = boost::shared_ptr<KPS::mp_laser_ex_data>(new KPS::mp_laser_ex_data);
	
	pk_laser->set_bean_dt(0);

	fnc = boost::bind(&msg_log_server::update_laser,this ,_1,pk_laser,sub_msg_name,(char*)(0));
	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}


bool msg_log_server::update_laser( const SLaser &laser,boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser,std::string sub_msg_name, char* ch_data )
{
	if ( th_status_() == RECORD){
		update_laser_para(laser);
	}


	pk_laser->set_stamp(laser.stamp_);
	pk_laser->set_time_stamp(cTimerDiff::total_ms());
	pk_laser->set_bean_dt(0);

	pk_laser->set_used_ray(LASER_COUNT);

	pk_laser->clear_data();
	pk_laser->clear_seg();
	pk_laser->clear_intensities();
	for (int i = 0 ; i < LASER_COUNT ; ++i){
		pk_laser->add_data(laser.data_[i]);
		pk_laser->add_seg(laser.seg_[i]);
	}
	


	ch_data = new char[pk_laser->ByteSize()];
	memset(ch_data,0,pk_laser->ByteSize());

	if (pk_laser->SerializeToArray( ch_data , pk_laser->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SLaser",ch_data,pk_laser->ByteSize());

	}else{
		std::cout<<"update_laser SerializeToArray Error!"<<std::endl;
	}

	return true;
}

void msg_log_server::sub_laser_ex( const std::string &sub_msg_name )
{
	boost::function<bool( const SLaser_Ex &laser_ex )> fnc;
	boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser = boost::shared_ptr<KPS::mp_laser_ex_data>(new KPS::mp_laser_ex_data);

	fnc = boost::bind(&msg_log_server::update_laser_ex,this ,_1,pk_laser,sub_msg_name,(char*)(0));

	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}

bool msg_log_server::update_laser_ex( const SLaser_Ex &laser_ex,boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser,std::string sub_msg_name, char* ch_data )
{
	if (th_status_() == RECORD){
		update_laser_ex_para(laser_ex);
	}

	pk_laser->set_stamp(laser_ex.stamp_);
	pk_laser->set_time_stamp(laser_ex.time_stamp_);
	pk_laser->set_bean_dt(laser_ex.bean_dt_);

	pk_laser->set_used_ray(laser_ex.used_ray_);

	pk_laser->clear_data();
	pk_laser->clear_seg();
	pk_laser->clear_intensities();

	for (int i = 0 ; i < laser_ex.used_ray_ ; ++i){
		pk_laser->add_data(laser_ex.data_[i]);
		pk_laser->add_seg(laser_ex.seg_[i]);
		pk_laser->add_intensities(laser_ex.intensities_[i]);
	}

	ch_data = new char[pk_laser->ByteSize()];
	memset(ch_data,0,pk_laser->ByteSize());

	if (pk_laser->SerializeToArray( ch_data , pk_laser->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SLaser_Ex",ch_data,pk_laser->ByteSize());

	}else{
		std::cout<<"update_laser SerializeToArray Error!"<<std::endl;
	}

	return true;
}

bool msg_log_server::put_laser_para(U64 time_stamp , char* const ch_msg, int ilen)
{

	std::string strSql = "";
	strSql += "insert into laser_ex_para(TIMESTP,NAME,TYPE,DATA)";
	strSql += "values(";
	strSql += cComm::ConvertToString(cTimerDiff::total_ms());
	strSql += ",'";
	strSql += "laser_ex_para" ;
	strSql += "','";
	strSql += "mp_laser_ex_para" ;
	strSql += "', ?);";

	sqlite3_stmt * stat;
	int nRes = sqlite3_prepare( db_, strSql.c_str() , -1, &stat, 0 );
	if (nRes != SQLITE_OK){
		std::cout << "insert data sql prepare fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	nRes = sqlite3_bind_blob( stat, 1, ch_msg, ilen,NULL );
	if (nRes != SQLITE_OK){
		std::cout << "insert data sql bind char fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}
	nRes = sqlite3_step( stat );
	if (nRes != SQLITE_DONE){
		std::cout << "insert data into db fail: " << std::endl;
		sqlite3_finalize( stat );
		return false;
	}

	sqlite3_finalize( stat );
	//std::cout<<"save one log:"<<log->time_stamp_<<std::endl;
	return true;

}

void msg_log_server::update_laser_para(const SLaser &laser)
{
	if(b_laser_para_){
		pk_laser_ex_para_ = boost::shared_ptr<KPS::mp_laser_ex_para>(new KPS::mp_laser_ex_para);
		
		F32 start_angle_;
		F32 resolution_;	//
		F32 range_max_;
		F32 range_min_;
		
		std::string str_ip = "192.168.0.100";
		Config::getConfig("dev_laser_ip",str_ip);
		F32 laser_dx  = 0 ;
		F32 laser_dy  = 0 ;
		Config::getConfig("dev_laser_dx",laser_dx);
		Config::getConfig("dev_laser_dy",laser_dy);
		pk_laser_ex_para_->set_laser_dx(laser_dx);
		pk_laser_ex_para_->set_laser_dy(laser_dy);

		pk_laser_ex_para_->set_laser_start_angle(laser.start_angle_);
		pk_laser_ex_para_->set_laser_resolution(laser.resolution_);
		pk_laser_ex_para_->set_laser_range_max(laser.range_max_);
		pk_laser_ex_para_->set_laser_range_min(laser.range_min_);

		pk_laser_ex_para_->set_laser_max_ray(LASER_COUNT);
		pk_laser_ex_para_->set_laser_reverse(false);
		pk_laser_ex_para_->set_laser_ip(str_ip);


		char* ch_data = new char[pk_laser_ex_para_->ByteSize()];
		memset(ch_data,0,pk_laser_ex_para_->ByteSize());

		if (pk_laser_ex_para_->SerializeToArray( ch_data , pk_laser_ex_para_->ByteSize())){

			put_laser_para(cTimerDiff::total_ms(),ch_data,pk_laser_ex_para_->ByteSize());

		}else{
			std::cout<<"update_laser para SerializeToArray Error!"<<std::endl;
		}


		b_laser_para_ = false;

	}


}

void msg_log_server::update_laser_ex_para(const SLaser_Ex &laser_ex)
{
	if(b_laser_ex_para_){

		pk_laser_ex_para_ = boost::shared_ptr<KPS::mp_laser_ex_para>(new KPS::mp_laser_ex_para);
		
		std::string str_ip = "192.168.0.100";
		Config::getConfig("dev_laser_ip",str_ip);
		pk_laser_ex_para_->set_laser_dx(laser_ex.dx_);
		pk_laser_ex_para_->set_laser_dy(laser_ex.dy_);
		pk_laser_ex_para_->set_laser_start_angle(laser_ex.start_angle_);
		pk_laser_ex_para_->set_laser_resolution(laser_ex.resolution_);
		pk_laser_ex_para_->set_laser_range_max(laser_ex.range_max_);
		pk_laser_ex_para_->set_laser_range_min(laser_ex.range_min_);
		pk_laser_ex_para_->set_laser_max_ray(laser_ex.used_ray_);
		pk_laser_ex_para_->set_laser_reverse(false);
		pk_laser_ex_para_->set_laser_ip(str_ip);


		char* ch_data = new char[pk_laser_ex_para_->ByteSize()];
		memset(ch_data,0,pk_laser_ex_para_->ByteSize());

		if (pk_laser_ex_para_->SerializeToArray( ch_data , pk_laser_ex_para_->ByteSize())){

			put_laser_para(cTimerDiff::total_ms(),ch_data,pk_laser_ex_para_->ByteSize());

		}else{
			std::cout<<"update_laser para SerializeToArray Error!"<<std::endl;
		}

		b_laser_ex_para_ = false;
	}
	

}

void msg_log_server::sub_dev_status(const std::string &sub_msg_name)
{


	boost::function<bool( const SPubDevStatus &dev_status )> fnc;
	boost::shared_ptr<KPS::mp_dev_status> pk_dev_status = boost::shared_ptr<KPS::mp_dev_status>(new KPS::mp_dev_status);

	fnc = boost::bind(&msg_log_server::update_dev_status,this ,_1,pk_dev_status,sub_msg_name,(char*)(0));

	SUB_MSG_SH_POOL(sub_msg_name,fnc);


}

bool msg_log_server::update_dev_status(const SPubDevStatus &dev_status,boost::shared_ptr<KPS::mp_dev_status> pk_dev_status,std::string sub_msg_name, char* ch_data)
{
	boost::mutex::scoped_lock lock(mu_dev_);

	std::string str_nm = dev_status.name_;
	pk_dev_status->set_name(str_nm);
	pk_dev_status->set_dev_id(dev_status.dev_status_.device_id_);
	pk_dev_status->set_status(dev_status.dev_status_.status_);
	pk_dev_status->set_err_code(dev_status.dev_status_.err_code_);
	pk_dev_status->set_cycle_ms(dev_status.dev_status_.cycle_ms_);
	pk_dev_status->set_run_ms(dev_status.dev_status_.run_ms_);

	ch_data = new char[pk_dev_status->ByteSize()];
	memset(ch_data,0,pk_dev_status->ByteSize());

	if (pk_dev_status->SerializeToArray( ch_data , pk_dev_status->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SPubDevStatus",ch_data,pk_dev_status->ByteSize());

	}else{
		std::cout<<"update_laser para SerializeToArray Error!"<<std::endl;
	}

	return true;
}

void msg_log_server::sub_amcl_conf(const std::string &sub_msg_name)
{

	boost::function<bool( const SAMCL_ENTROPY &amcl_entropy )> fnc_amcl_entropy;
	fnc_amcl_entropy = boost::bind(&msg_log_server::updata_amcl_entropy,this ,_1);
	SUB_MSG_SH_POOL("amcl_entropy",fnc_amcl_entropy);


	boost::function<bool( const SAMCL_CONFIDENCE &amcl_confidence )> fnc;
	boost::shared_ptr<KPS::mp_loc_confidence> pk_loc_conf = boost::shared_ptr<KPS::mp_loc_confidence>(new KPS::mp_loc_confidence);

	fnc = boost::bind(&msg_log_server::update_amcl_conf,this ,_1,pk_loc_conf,sub_msg_name,(char*)(0));

	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}

bool msg_log_server::update_amcl_conf(const SAMCL_CONFIDENCE &amcl_confidence,boost::shared_ptr<KPS::mp_loc_confidence> pk_loc_conf,std::string sub_msg_name, char* ch_data)
{
	pk_loc_conf->set_b_amcl_conf(amcl_confidence.b_amcl_confidence_);
	pk_loc_conf->set_amcl_conf(amcl_confidence.amcl_confidence_);
	
	SAMCL_ENTROPY amcl_entropy = th_amcl_entropy_();
	pk_loc_conf->set_b_amcl_entropy(amcl_entropy.b_amcl_entropy_);
	pk_loc_conf->set_amcl_xy_entropy(amcl_entropy.amcl_xy_entropy_);
	pk_loc_conf->set_amcl_theta_entropy(amcl_entropy.amcl_theta_entropy_);
	pk_loc_conf->set_amcl_entropy(amcl_entropy.amcl_entropy_);


	ch_data = new char[pk_loc_conf->ByteSize()];
	memset(ch_data,0,pk_loc_conf->ByteSize());

	if (pk_loc_conf->SerializeToArray( ch_data , pk_loc_conf->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SAMCL_ENTROPY",ch_data,pk_loc_conf->ByteSize());

	}else{
		std::cout<<"update_laser para SerializeToArray Error!"<<std::endl;
	}

	return true;
}

bool msg_log_server::updata_amcl_entropy(const SAMCL_ENTROPY &amcl_entropy)
{
	th_amcl_entropy_ = amcl_entropy;
	return true;
}

bool msg_log_server::update_pipe_log(std::string name,U8* data,U32 len)
{
	U64 i_stamp = 0;
	cComm::ConvertToNum(i_stamp,name);
	put_log(i_stamp,data,len);

	return true;
}

bool msg_log_server::put_log(U64 time_stamp , U8* const ch_msg, int ilen)
{
	boost::mutex::scoped_lock lock(mu_msg_pair_);

	log_pair* p_log = new log_pair();

	p_log->time_stamp_ = time_stamp;
	p_log->msg_name_ = "log";
	p_log->msg_type_ = "string";
	p_log->ilen_ = ilen;
	p_log->ch_msg_ = new char[ilen];
	if (p_log->ilen_){
		memcpy(p_log->ch_msg_,ch_msg,p_log->ilen_);
	}

	l_msg_pair_.push_back(p_log);

	return true;
}
void msg_log_server::sub_reflector(const std::string &sub_msg_name)
{
	
	boost::function<bool( const SReflector &refs )> fnc;
	boost::shared_ptr<KPS::mp_refs> pk_refs = boost::shared_ptr<KPS::mp_refs>(new KPS::mp_refs);

	fnc = boost::bind(&msg_log_server::update_reflector,this ,_1,pk_refs,sub_msg_name,(char*)(0));

	SUB_MSG_SH_POOL(sub_msg_name,fnc);


}
bool msg_log_server::update_reflector(const SReflector &refs, boost::shared_ptr<KPS::mp_refs> pk_refs, std::string sub_msg_name, char* ch_data)
{
	pk_refs->clear_id();
	pk_refs->clear_x();
	pk_refs->clear_y();

	for (int i = 0 ; i  < refs.used_ ; ++i ){
		pk_refs->add_id(refs.id_[i]);
		pk_refs->add_x(refs.pos_[i].x_);
		pk_refs->add_y(refs.pos_[i].y_);
	}
	

	ch_data = new char[pk_refs->ByteSize()];
	memset(ch_data,0,pk_refs->ByteSize());

	if (pk_refs->SerializeToArray( ch_data , pk_refs->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SReflector",ch_data,pk_refs->ByteSize());

	}else{
		std::cout<<"update_reflector SerializeToArray Error!"<<std::endl;
	}

	return true;
}
bool msg_log_server::call_view_data_pipe(std::string name,U8* data,U32 len)
{
	std::vector<std::string> v_str;
	cComm::SplitString(name," ",v_str);
	if (v_str.size() > 1){
		name = v_str[1];
	}
	
	put_data(cTimerDiff::total_ms(),name,"view_data",(char*)data,len);
	return true;
}
bool msg_log_server::get_save_db(std::string &db_name)
{
	if (v_save_db_.size() > 0){
		v_save_db_.get(db_name);
		return true;
	}
	return false;
	
}

bool msg_log_server::check_save_data()
{
	if (th_save_cnt_() > 0){
		return true;
	}
	return false;
}
void msg_log_server::sub_reflector_pos(const std::string &sub_msg_name){

	boost::function<bool( const SPOS_CONFIDENCE &confidence_pos )> fnc;
	boost::shared_ptr<KPS::mp_conf_ref_pos> pk_reflector_pos = boost::shared_ptr<KPS::mp_conf_ref_pos>(new KPS::mp_conf_ref_pos);
	fnc = boost::bind(&msg_log_server::update_reflector_pos,this ,_1,pk_reflector_pos,sub_msg_name,(char*)(0));
	SUB_MSG_SH_POOL(sub_msg_name,fnc);
}

bool msg_log_server::update_reflector_pos(const SPOS_CONFIDENCE &confidence_pos,boost::shared_ptr<KPS::mp_conf_ref_pos> pk_ref_pos,std::string sub_msg_name, char* ch_data)
{
	pk_ref_pos->set_b_conf(confidence_pos.confidence_.b_amcl_confidence_);
	pk_ref_pos->set_confidence(confidence_pos.confidence_.amcl_confidence_);
	pk_ref_pos->mutable_ref_pos()->set_x(confidence_pos.pos_.x_);
	pk_ref_pos->mutable_ref_pos()->set_y(confidence_pos.pos_.y_);
	pk_ref_pos->mutable_ref_pos()->set_th(confidence_pos.pos_.th_);



	ch_data = new char[pk_ref_pos->ByteSize()];
	memset(ch_data,0,pk_ref_pos->ByteSize());

	if (pk_ref_pos->SerializeToArray( ch_data , pk_ref_pos->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SPOS_CONFIDENCE",ch_data,pk_ref_pos->ByteSize());

	}else{
		std::cout<<"update_reflector_pos  SerializeToArray Error!"<<std::endl;
	}

	return true;
}

void msg_log_server::sub_DIO(std::string str_sub_dev, std::string str_pub_dev)
{

	std::vector<std::string> v_res;
	cComm::SplitString(str_sub_dev , ":" ,v_res);
	auto it = v_res.begin();
	for ( ; it != v_res.end() ; ++it ){
		m_sub_dev_sdi_[*it] = 0;
		m_sub_dev_fai_[*it] = 0;
	}

	cComm::SplitString(str_pub_dev , ":" ,v_res);
	it = v_res.begin();
	for ( ; it != v_res.end() ; ++it ){
		m_sub_dev_sdo_[*it] = 0;
		m_sub_dev_fao_[*it] = 0;
	}


	auto it5 = m_sub_dev_sdi_.begin();
	for ( ; it5 != m_sub_dev_sdi_.end() ; ++it5 ){

		std::string str_sub_msg = PUB_FNC_DI + it5->first;
		END_MSG_SH_POOL(SDI,str_sub_msg);
		boost::function<bool(const SDI &sdi)> sfnc_sdi;
		boost::shared_ptr<KPS::mp_sdi> pk_dis = boost::shared_ptr<KPS::mp_sdi>(new KPS::mp_sdi);
		sfnc_sdi = boost::bind(&msg_log_server::call_fnc_sdi,this,it5->first,_1,pk_dis,str_sub_msg,(char*)(0));
		SUB_MSG_SH_POOL(str_sub_msg,sfnc_sdi);
	}

	auto it2 = m_sub_dev_sdo_.begin();
	for ( ; it2 != m_sub_dev_sdo_.end() ; ++it2 ){

		std::string str_sub_msg = PUB_FNC_DO + it2->first;
		END_MSG_SH_POOL(SDO,str_sub_msg);
 		boost::function<bool(const SDO &sdo)> sfnc_sdo;
		boost::shared_ptr<KPS::mp_sdo> pk_dos = boost::shared_ptr<KPS::mp_sdo>(new KPS::mp_sdo);
		sfnc_sdo = boost::bind(&msg_log_server::call_fnc_sdo,this,it2->first,_1,pk_dos,str_sub_msg,(char*)(0));
		SUB_MSG_SH_POOL(str_sub_msg,sfnc_sdo);
	}

	auto it4 = m_sub_dev_fai_.begin();
	for ( ; it4 != m_sub_dev_fai_.end() ; ++it4 ){

		std::string str_sub_msg = PUB_FNC_FAI + it4->first;
		END_MSG_SH_POOL(SFAO,str_sub_msg);
		boost::function<bool( const SFAI &fai)> sfnc_fai;
		boost::shared_ptr<KPS::mp_sfai> pk_fais = boost::shared_ptr<KPS::mp_sfai>(new KPS::mp_sfai);
		sfnc_fai = boost::bind(&msg_log_server::call_fnc_sfai,this,it4->first,_1,pk_fais,str_sub_msg,(char*)(0));
		SUB_MSG_SH_POOL(str_sub_msg,sfnc_fai);
	}

	auto it3 = m_sub_dev_fao_.begin();
	for ( ; it3 != m_sub_dev_fao_.end() ; ++it3 ){

		std::string str_sub_msg = PUB_FNC_FAO + it3->first;
		END_MSG_SH_POOL(SFAO,str_sub_msg);
		boost::function<bool(const SFAO &fao)> sfnc_fao;
		boost::shared_ptr<KPS::mp_sfao> pk_faos = boost::shared_ptr<KPS::mp_sfao>(new KPS::mp_sfao);
		sfnc_fao = boost::bind(&msg_log_server::call_fnc_sfao,this,it3->first,_1,pk_faos,str_sub_msg,(char*)(0));
		SUB_MSG_SH_POOL(str_sub_msg,sfnc_fao);
	}


}

bool msg_log_server::call_fnc_sdi(std::string str_dev, const SDI &sdi,boost::shared_ptr<KPS::mp_sdi> pk_dis,std::string sub_msg_name, char* ch_data)
{
	pk_dis->clear_id();
	pk_dis->clear_di();

	for ( int i = 0 ; i < sdi.used_ ; ++i ){
		pk_dis->add_id(sdi.id_[i]);
		pk_dis->add_di(sdi.di_[i]);
	}

	ch_data = new char[pk_dis->ByteSize()];
	memset(ch_data,0,pk_dis->ByteSize());

	if (pk_dis->SerializeToArray( ch_data , pk_dis->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SDI",ch_data,pk_dis->ByteSize());

	}else{
		std::cout<<"call_fnc_sdi  SerializeToArray Error!"<<std::endl;
	}


	return true;
}


bool msg_log_server::call_fnc_sdo(std::string str_dev, const SDO &sdo,boost::shared_ptr<KPS::mp_sdo> pk_dos,std::string sub_msg_name, char* ch_data)
{
	pk_dos->clear_id();
	pk_dos->clear_doo();

	for ( int i = 0 ; i < sdo.used_ ; ++i ){
		pk_dos->add_id(sdo.id_[i]);
		pk_dos->add_doo(sdo.do_[i]);
	}

	ch_data = new char[pk_dos->ByteSize()];
	memset(ch_data,0,pk_dos->ByteSize());

	if (pk_dos->SerializeToArray( ch_data , pk_dos->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SDO",ch_data,pk_dos->ByteSize());

	}else{
		std::cout<<"call_fnc_sdo  SerializeToArray Error!"<<std::endl;
	}


	return true;
}


bool msg_log_server::call_fnc_sfai(std::string str_dev, const SFAI &sfai,boost::shared_ptr<KPS::mp_sfai> pk_fais,std::string sub_msg_name, char* ch_data)
{
	pk_fais->clear_id();
	pk_fais->clear_fai();

	for ( int i = 0 ; i < sfai.used_ ; ++i ){
		pk_fais->add_id(sfai.id_[i]);
		pk_fais->add_fai(sfai.fai_[i]);
	}

	ch_data = new char[pk_fais->ByteSize()];
	memset(ch_data,0,pk_fais->ByteSize());

	if (pk_fais->SerializeToArray( ch_data , pk_fais->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SFAI",ch_data,pk_fais->ByteSize());

	}else{
		std::cout<<"call_fnc_sfai  SerializeToArray Error!"<<std::endl;
	}


	return true;
}


bool msg_log_server::call_fnc_sfao(std::string str_dev, const SFAO &sfao,boost::shared_ptr<KPS::mp_sfao> pk_faos,std::string sub_msg_name, char* ch_data)
{
	pk_faos->clear_id();
	pk_faos->clear_fao();

	for ( int i = 0 ; i < sfao.used_ ; ++i ){
		pk_faos->add_id(sfao.id_[i]);
		pk_faos->add_fao(sfao.fao_[i]);
	}

	ch_data = new char[pk_faos->ByteSize()];
	memset(ch_data,0,pk_faos->ByteSize());

	if (pk_faos->SerializeToArray( ch_data , pk_faos->ByteSize())){

		put_data(cTimerDiff::total_ms(),sub_msg_name,"SFAO",ch_data,pk_faos->ByteSize());

	}else{
		std::cout<<"call_fnc_sfao  SerializeToArray Error!"<<std::endl;
	}

	return true;
}




















// 
// {
// 	if (max_-- == 0){
// 		close_db();
// 		th_status_ = CLOSE;
// 		b_record_ = false;
// 
// 		int rc=sqlite3_open(str_db_.c_str(),&db_);  /* open database */  
// 		if(rc){  
// 			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));  
// 			sqlite3_close(db_);  
// 			return ;
// 		}
// 		std::vector<log_pair*> v_log;
// 		get_rec(v_log);
// 	}
// }
















