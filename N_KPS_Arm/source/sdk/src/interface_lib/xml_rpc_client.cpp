#include "math.h"
#include "Comm.h"
#include "Geometry.h"

#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"
#include "protobuf_msg/protobuf_path.h"
#include "protobuf_msg/protobuf_seg_path.h"
#include "protobuf_msg/protobuf_chk_laser.h"

#include "Comm/file.h"

#include "interface/xml_rpc_client.h"

xml_rpc_client::xml_rpc_client()
:client_(0)
{
	pub_path_ = 0;
	protobuf_bag_ = 0;
	protobuf_bag_ex_ = 0;
}
xml_rpc_client::~xml_rpc_client(){
	client_->close();
}
void xml_rpc_client::init_conn( std::string ip, int port )
{
	client_ =  new XmlRpc::XmlRpcClient(ip.c_str(),port);
}

bool xml_rpc_client::is_connected()
{
	if (client_){
		return true;
	}
	return false;
}

void xml_rpc_client::init( std::string ip, int port )
{

	client_ =  new XmlRpc::XmlRpcClient(ip.c_str(),port);

	SDelete(pub_path_);
	SDelete(protobuf_bag_);
	SDelete(protobuf_bag_ex_);
	
	pub_path_ = new protobuf_path();
	protobuf_bag_ = new protobuf_bag();
	protobuf_bag_ex_ = new protobuf_bag_ex();

	protobuf_bag_->init_normal();
	protobuf_bag_ex_->init_normal_r();
}

bool xml_rpc_client::get_dev_status(std::vector<SPubDevStatus> &v_dev_status)
{
	XmlRpcValue sdata, result;

	sdata[0] = int(-1);

	if (client_)
	{
		if(execute("get_dev_status", sdata, result)){

			int icount = result.size();
		
			for ( int i = 0 ; i < icount ; ++i )
			{
				

				std::string nm = "unknow";
				int i_id=(int)result[i]["id"];
				nm =(std::string)result[i]["name"];
				int i_status =(int)result[i]["status"];
				int i_err_code =(int)result[i]["err_code"];
				F32 f_cycle_ms =(double)result[i]["cycle_ms"];
				F32 f_run_ms_ =(double)result[i]["run_ms"];

				SPubDevStatus tmp;
				memset(tmp.name_,0,200);
				memcpy(tmp.name_ , nm.c_str(), nm.length());
				tmp.dev_status_.device_id_ = i_id;
				tmp.dev_status_.status_ = i_status;
				tmp.dev_status_.err_code_ = i_err_code;
				tmp.dev_status_.cycle_ms_ = f_cycle_ms;
				tmp.dev_status_.run_ms_ = f_run_ms_;

				v_dev_status.push_back(tmp);
			}

			return true;
		}
		else
			std::cout << "Error calling  get_dev_status"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_dev_status(SPubDevStatus &dev_status,int dev_id)
{
	XmlRpcValue sdata, result;
	memset(&dev_status , 0 , sizeof(SPubDevStatus));

	sdata[0] = int(dev_id);

	if (client_)
	{
		if(execute("get_dev_status", sdata, result)){

		
			assert( 1 == result.size());
			int i = 0;
			std::string nm = "unknow";
			int i_id=(int)result[i]["id"];
			nm =(std::string)result[i]["name"];
			int i_status =(int)result[i]["status"];
			int i_err_code =(int)result[i]["err_code"];
			F32 f_cycle_ms =(double)result[i]["cycle_ms"];
			F32 f_run_ms_ =(double)result[i]["run_ms"];


			
			memcpy(dev_status.name_ , nm.c_str(), nm.length());
			dev_status.dev_status_.device_id_ = i_id;
			dev_status.dev_status_.status_ = i_status;
			dev_status.dev_status_.err_code_ = i_err_code;
			dev_status.dev_status_.cycle_ms_ = f_cycle_ms;
			dev_status.dev_status_.run_ms_ = f_run_ms_;


			return true;
		}
		else
			std::cout << "Error calling  get_dev_status:"<<dev_id<< std::endl;
	}
	return false;
}



bool xml_rpc_client::get_file_list( std::vector<std::string> &v_file_list ,const std::string str_path, const std::string &filename )
{
	XmlRpcValue sdata, result;

	sdata[0] = str_path;
	sdata[1] = filename;
	if (client_)
	{
		if(execute("get_file_list", sdata, result)){

			int icount = result.size();

			for ( int i = 0 ; i < icount ; ++i )
			{
				std::string file_name = (std::string)result[i];
				v_file_list.push_back(file_name);
			}

			return true;
		}
		else
			std::cout << "Error calling  get_file_list"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_begin_bag_mapping()
{
	XmlRpcValue sdata, result;


	sdata[0] = "begin_bag_gmapping";

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_end_bag_mapping()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	//ss<<"bag_mapping "<<bag_nm;
	sdata[0] = "stop_bag_gmapping";

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_begin_gmapping()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"syn_slam";
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_stop_gmapping()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"syn_slam_end";
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_show_gmapping()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"show_gmapping";
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_save_gmapping(std::string file_nm)
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"save_gmapping "<<file_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_mapping_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::set_map( const std::vector<int> v_map_date )
{
	XmlRpcValue  sdata,result;

	

	if (client_)
	{
		sdata =  int(-1);
		if(execute("set_map", sdata, result)){
			std::cout<<"set_map multi call data begin"<<std::endl;
		}
		sdata.clear();

		int index = 0;
		sdata[index++] = int(1);//index = 0
		
		int count = 1;
		std::vector<int>::const_iterator cit = v_map_date.begin();
		for ( ; cit != v_map_date.end() ; ++cit)
		{

			sdata[index++] = *cit; 

			if (index == (3*160000 + 1))
			{
				sdata[0] = count++;
				if(execute("set_map", sdata, result)){

					std::cout<<"set_map multi call data len:"<<index<<std::endl;

				}else{
					return false;
				}
				index = 1;
				sdata.clear();
				

			}


		}
	
		sdata[0] = count++;
		if ( (index > 0) && client_->execute("set_map", sdata, result)){

			if ( (result.size()) == 1 && ( 0 == int(result[0])) )
			{
				std::cout<<"set_map over data len:"<<index<<std::endl;
			}else{
				return false;
			}

		}
		else{
			std::cout << "Error calling  set_mapping_cmd"<< std::endl;
		}
		sdata.clear();
		
		sdata = ( int(-2));

		if(execute("set_map", sdata, result)){
			std::cout<<"set_map multi call data end."<<std::endl;
			return true;
		}else{
			return false;
		}
		

	}
	return false;
}

bool xml_rpc_client::do_set_onboard_map(const std::string str_map_name)
{

	XmlRpcValue sdata, result;

	sdata[0] = str_map_name;

	if (client_)
	{
		if(execute("set_onboard_map", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  get_map"<< std::endl;
	}
	return false;
	
}

bool xml_rpc_client::get_map( std::vector<int> &v_map_date ,const std::string &map_nm)
{
	XmlRpcValue sdata, result;

	sdata[0] = map_nm;

	if (client_)
	{
		if(execute("get_map", sdata, result)){

			for( int i = 0 ; i < result.size() ; ++i){
				v_map_date.push_back(int(result[i]));
			}
			std::cout<<"xml_rpc_client::get_map over. map data size:"<<v_map_date.size()<<std::endl;
			return true;
		}
		else
			std::cout << "Error calling  get_map"<< std::endl;
	}
	return false;
}



bool xml_rpc_client::get_map_separate(std::vector<int> &v_map_date, const std::string &map_nm)
{
	XmlRpcValue sdata, result;

	v_map_date.clear();

	if (client_)
	{
		sdata[0] = "load";
		sdata[1] = map_nm;
		if(execute("get_map_separate", sdata, result)){

			if(result.size() == 2){

				i_map_data_size_ = result[1];
				std::cout<<"xml_rpc_client::get_map_separate load over. map data size:"<<i_map_data_size_<<std::endl;
			}
			
		}else{
			std::cout << "Error calling  xml_rpc_client::get_map_separate load over. map data size:"<<i_map_data_size_<<std::endl;
			return false;
		}
		
		if(i_map_data_size_  <= 0 ){
			std::cout << "Error calling  xml_rpc_client::get_map_separate load over. map data size err:"<<std::endl;
			return false;
		}
		
		sdata[0] = "read";
		sdata[1] = map_nm;

		int i_get_data = 0;
		for ( ; i_get_data < i_map_data_size_ ;  ){
			
			if(execute("get_map_separate", sdata, result)){

				int i_data = result.size()  - 1;

				for( int i = 1 ; i < result.size()  ; ++i){
					v_map_date.push_back(int(result[i]));
				}

				i_get_data += i_data;
			}else{
				std::cout << "Error calling  xml_rpc_client::get_map_separate  "<<std::endl;
				break;
			}
		}
		std::cout << "Error calling  xml_rpc_client::get_map_separate read over!! "<<i_map_data_size_<<std::endl;
	}
	return false;
}

bool xml_rpc_client::do_load_map( std::string map_nm )
{
	XmlRpcValue sdata, result;


	std::stringstream ss;
	ss<<"load "<<map_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_map_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  load_map:"<<map_nm<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_save_onboard_map( std::string map_nm )
{
	XmlRpcValue sdata, result;


	std::stringstream ss;
	ss<<"save "<<map_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_map_cmd", sdata, result)){

			return true;
		}
		else
			std::cout << "Error calling  load_map:"<<map_nm<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_laser( std::vector<SLaser_used> &v_laser_data )
{
	XmlRpcValue sdata, result;

	sdata = 1;

	if (client_)
	{
		if(execute("get_used_laser", sdata, result)){

			for (int i = 0; i < result.size() ; )
			{
				SLaser_used ls;
				ls.angle_ = double( result[i++] );
				ls.dis_ = double( result[i++] );
				v_laser_data.push_back(ls);
			}

			if(v_laser_data.size() < 1){
				//std::cout << "get used laser size:"<< v_laser_data.size() << std::endl;
			}
			
			return true;
		}
		else
			std::cout << "Error calling  laser"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::get_ex_laser( std::vector<SLaser_used> &v_laser_data )
{
	XmlRpcValue sdata, result;

	sdata = 1;

	if (client_)
	{
		if(execute("get_ex_laser", sdata, result)){

			for (int i = 0; i < result.size() ; )
			{
				SLaser_used ls;
				ls.angle_ = double( result[i++] );
				ls.dis_ = double( result[i++] );
				v_laser_data.push_back(ls);
			}

			if(v_laser_data.size() < 1){
				std::cout << "get ex laser size:"<< v_laser_data.size() << std::endl;
			}

			return true;
		}
		else
			std::cout << "Error calling  ex laser"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::get_ex_cab_laser(SLaserXYEx &laser_ex)
{
	XmlRpcValue sdata, result;
	memset(&laser_ex,0,sizeof(SLaserXYEx));
	sdata = 1;

	if (client_)
	{
		if(execute("get_pub_laser_ex_cab", sdata, result)){

			for (int i = 0; i < result.size() ; i += 2 )
			{
				laser_ex.x_[laser_ex.used_cnt_] = double(result[i+0]);
				laser_ex.y_[laser_ex.used_cnt_] = double(result[i+1]);
				laser_ex.used_cnt_++;
			}
			if ( laser_ex.used_cnt_ == 0 )
			{
				return false;
			}
			return true;
		}
		else
			std::cout << "Error calling  laser_ex_cab"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_sim_laser(SLaserXYEx &laser_sim)
{
	XmlRpcValue sdata, result;
	memset(&laser_sim,0,sizeof(SLaserXYEx));
	sdata = 1;

	if (client_)
	{
		if(execute("get_sim_laser", sdata, result)){

			for (int i = 0; i < result.size() ; i += 2 )
			{
				laser_sim.x_[laser_sim.used_cnt_] = double(result[i+0]);
				laser_sim.y_[laser_sim.used_cnt_] = double(result[i+1]);
				laser_sim.used_cnt_++;
			}
			if ( laser_sim.used_cnt_ == 0 )
			{
				return false;
			}
			return true;
		}
		else
			std::cout << "Error calling  laser_ex_cab"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_robot_pos( SPos &pos )
{
	XmlRpcValue sdata, result;

	sdata = 1;

	if (client_)
	{
		if(execute("get_robot_pos", sdata, result)){

			if (result.size()  > 2)
			{
				pos.x_ = double(result[0]);
				pos.y_ = double(result[1]);
				pos.th_ = double(result[2]);
				//pos.th_ = Rad2Deg(pos.th_);
			}
			

			//std::cout << "get robot pos:"<< result.size() << std::endl;
			return true;
		}
		else
			std::cout << "Error calling get pos \n";
	}
	return false;
}

bool xml_rpc_client::get_robot_pos_hb(SPos &pos, int set_heartbeat , int set_sim_speed )
{
	XmlRpcValue sdata, result;

	sdata[0] = int(set_heartbeat);
	sdata[1] = int(set_sim_speed);

	if (client_)
	{
		if(execute("get_robot_pos_hb", sdata, result)){

			if (result.size()  > 2)
			{
				pos.x_ = double(result[0]);
				pos.y_ = double(result[1]);
				pos.th_ = double(result[2]);
				//pos.th_ = Rad2Deg(pos.th_);
			}


			//std::cout << "get robot pos heart beat:"<< result.size() << std::endl;
			return true;
		}
		else
			std::cout << "Error calling get pos heart beat \n";
	}
	return false;
}

bool xml_rpc_client::get_odom_speed( SOdomSpeed &odom )
{
	XmlRpcValue sdata, result;

	sdata = 1;
	
	if (client_)
	{
		if(execute("get_robot_odom", sdata, result)){

			if (result.size()  > 5)
			{
				odom.x_ = double(result[0]);
				odom.y_ = double(result[1]);
				odom.th_ = double(result[2]);
				odom.vx_ = double(result[3]);
				odom.vy_ = double(result[4]);
				odom.vw_ = double(result[5]);
				//speed.th_ = Rad2Deg(speed.th_);
			}


			//std::cout << "get speed:"<< result.size() << std::endl;
			return true;
		}
		else
			std::cout << "Error calling get speed \n";
	}
	return false;
}

bool xml_rpc_client::get_para( std::string &str_value ,const std::string &str_para )
{
	XmlRpcValue sdata, result;

	if (client_)
	{
		sdata[0] = str_para;
		if(execute("get_para", sdata, result)){

			if (result.size()  > 0)
			{
				str_value = std::string(result[0]);
			}


			std::cout << "get_para name:"<< str_para <<" value:"<< str_value << std::endl;
			return true;
		}
		else
			std::cout << "Error calling get speed \n";
	}
	return false;
}

bool xml_rpc_client::set_est_pos( const SPos &pos , const bool &b_descrete )
{
	std::cout<<"set est pos:"<<pos.x_<<" "<<pos.y_<<" "<<pos.th_<<std::endl;
	XmlRpcValue sdata, result;

	double para1 = 1.0;
	double para2 = 1.0;
	double para3 = 0.0;
	
	if (!b_descrete)
	{
		para3 = 2.0;
	}

	double para4 = 1024;
	//double para4 = 64;

	if (client_)
	{

		sdata[0] = pos.x_;
		sdata[1] = pos.y_;
		sdata[2] = pos.th_;

		sdata[3] = para1;
		sdata[4] = para2;
		sdata[5] = para3;
		sdata[6] = para4;

		if(execute("set_estimate_pos", sdata, result)){

			if ( int(result) > 0)
			{
				std::cout << "set init pos over:"<< sdata.size() << std::endl;
				return true;
			}else{
				std::cout << "set init pos err:"<< sdata.size() << std::endl;
				return false;
			}
			
		}
		else
			std::cout << "Error calling set pos"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_particles( std::vector<STriangle>& v_particles )
{
	XmlRpcValue sdata, result;
	STriangle ps;

	sdata = 1;

	if (client_)
	{
		if(execute("get_particles", sdata, result)){
			v_particles.clear();
			for (int i = 0; i < result.size() ; i += 4)
			{
				ps.x = double(result[ i + 0]);
				ps.y = double(result[ i + 1]);
				ps.angle = double(result[ i + 2]);
				ps.weight = double(result[ i + 3]);

				v_particles.push_back(ps);
			}
			if (v_particles.size()> 0)
			{
				return true;
			}
			
		}else{
			std::cout << "Error calling get particle "<< std::endl;
		}

	}
	return false;
}

bool xml_rpc_client::do_begin_log( std::string file_nm )
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"begin_save "<<file_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_log_cmd", sdata, result)){
			std::cout << "calling  set_log_cmd:"<<ss.str()<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_cmd:"<<ss.str()<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_end_log()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"stop_save";
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_log_cmd", sdata, result)){
			std::cout << "calling  set_log_cmd:"<<ss.str()<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_cmd:"<<ss.str()<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_cmd_speed( std::string speed_cmd )
{
	XmlRpcValue sdata, result;

	sdata[0] = speed_cmd;

	if (client_)
	{
		if(execute("set_speed_cmd", sdata, result)){
			std::cout << "calling  set_speed_cmd:"<<speed_cmd<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_speed_cmd:"<<speed_cmd<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_set_loop_clusure_cmd( std::string scmd )
{
	XmlRpcValue sdata, result;

	sdata[0] = scmd;

	if (client_)
	{
		if(execute("set_loop_closure_cmd", sdata, result)){
			std::cout << "calling  set_loop_closure_cmd:"<<scmd<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_loop_closure_cmd:"<<scmd<< std::endl;
	}
	return false;
}
bool xml_rpc_client::do_play_back_log( std::string file_nm )
{
	
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"play_back "<<file_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_log_cmd", sdata, result)){
			std::cout << "calling  set_log_cmd:"<<ss.str()<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_cmd:"<<ss.str()<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_end_play_back_log()
{
	XmlRpcValue sdata, result;

	sdata[0] = "end_play_back";

	if (client_)
	{
		if(execute("set_log_cmd", sdata, result)){
			std::cout << "calling  set_log_cmd:end_play_back"<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_cmd:end_play_back"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_continue_play_log()
{
	XmlRpcValue sdata, result;

	sdata[0] = "continue_play_back";

	if (client_)
	{
		if(execute("set_log_cmd", sdata, result)){
			std::cout << "calling  set_log_cmd:do_continue_play_log"<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_cmd:do_continue_play_log"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_begin_log_ex(std::string file_nm)
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"begin_save "<<file_nm;
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_log_ex_cmd", sdata, result)){
			std::cout << "calling  set_log_ex_cmd:"<<ss.str()<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_ex_cmd:"<<ss.str()<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_end_log_ex()
{
	XmlRpcValue sdata, result;

	std::stringstream ss;
	ss<<"stop_save";
	sdata[0] = ss.str();

	if (client_)
	{
		if(execute("set_log_ex_cmd", sdata, result)){
			std::cout << "calling  set_log_ex_cmd:"<<ss.str()<< std::endl;
			return true;
		}
		else
			std::cout << "Error calling  set_log_ex_cmd:"<<ss.str()<< std::endl;
	}
	return false;
}

bool xml_rpc_client::do_get_process_bar( SProcess_Bar &pro_bar, const std::string &str_name )
{
	XmlRpcValue sdata, result;

	sdata[0] = str_name;
	memset(&pro_bar,0,sizeof(SProcess_Bar));

	if (client_)
	{
		if(execute("get_process_bar", sdata, result)){

			if(result.size() > 2){

				std::string str_pro_bar;
				str_pro_bar = std::string(result[0]);
				
				memcpy(pro_bar.name_,str_pro_bar.c_str(),str_pro_bar.length());
				pro_bar.current_step_ = int(result[1]);
				pro_bar.max_step_ = int(result[2]);
				return true;
			}
			

			
		}
		else
			std::cout << "Error calling  get_process_bar"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_pub_bag(SPUB_BAG & pub_bag)
{
	XmlRpcValue sdata, result;

	bool bres = false;

	if (client_)
	{
		sdata[0] = 1;
		if(execute("get_pub_bag", sdata, result)){

			if(result.size() > 1){
				int ilen = result[0];
				if (ilen > 0)
				{
					std::vector<char> vdata = result[1];
					assert( vdata.size() == ilen);

					char* data = new char[vdata.size()];
					std::copy(vdata.begin(),vdata.end(),data);
					
					
					//if ( proto_buf_parse::buf2bag(pub_bag,data,ilen))
					if(protobuf_bag_->buf2bag(pub_bag,data,ilen))
					{
						bres = true;
					}
					delete[] data;
				}

				
				return bres;
			}



		}
		else
			std::cout << "Error calling  get_pub_bag"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_pub_bag_ex(SPUB_BAG_EX & pub_bag_ex)
{
	XmlRpcValue sdata, result;

	bool bres = false;

	if (client_)
	{
		sdata[0] = 1;
		if(execute("get_pub_bag_ex", sdata, result)){

			if(result.size() > 1){
				int ilen = result[0];
				if (ilen > 0)
				{
					std::vector<char> vdata = result[1];
					assert( vdata.size() == ilen);

					char* data = new char[vdata.size()];
					std::copy(vdata.begin(),vdata.end(),data);

					if ( protobuf_bag_ex_->buf2bag(pub_bag_ex,data,ilen))
					{
						bres = true;
					}
					delete[] data;
				}


				return bres;
			}



		}
		else
			std::cout << "Error calling  get_pub_bag"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_pub_laser_ex_ref(SLaser_Ex_Ref &laser_ex_ref)
{
	XmlRpcValue sdata, result;

	bool bres = false;

	if (client_)
	{
		sdata[0] = 1;
		if(execute("get_pub_laser_ex_ref", sdata, result)){

			if(result.size() > 1){
				int ilen = result[0];
				if (ilen > 0)
				{
					std::vector<char> vdata = result[1];
					assert( vdata.size() == ilen);

					char* data = new char[vdata.size()];
					std::copy(vdata.begin(),vdata.end(),data);

					SPUB_BAG_EX pbag_ex;
					if ( protobuf_bag_ex_->buf2bag(pbag_ex,data,ilen))
					{
						laser_ex_ref = pbag_ex.laser_ex_ref_;
						bres = true;
					}
					delete[] data;
				}


				return bres;
			}



		}
		else
			std::cout << "Error calling  get_pub_laser_ex_ref"<< std::endl;
	}
	return false;

}

bool xml_rpc_client::set_seg_path(const std::vector<SOdomSpeed> &v_run_path)
{
	XmlRpcValue  result;

	bool bres = false;
	
	if ( v_run_path.size() < 1)
	{
		std::cout<<"set_seg_path size err 0"<<std::endl;
		return false;
	}
	protobuf_seg_path p_seg_path;
	p_seg_path.set_seg_path(v_run_path);
	char* data = 0;
	int len = 0;
	p_seg_path.proto2byte(data,len);
	XmlRpcValue sdata(data,len);
	//XmlRpcValue sdata((char*)&v_run_path[0],sizeof(SOdomSpeed)*v_run_path.size());
	

	if (client_)
	{

		if(execute("set_seg_path", sdata, result)){
			delete[] data;
			len = 0;
			return true;
		}else{
			std::cout << "Error calling  set_seg_path"<< std::endl;
		}
	}
	delete[] data;
	len = 0;
	return false;
}

bool xml_rpc_client::get_check_laser_range(const Range_type &range_type, SCHK_LASER_RANGE &chk_laser_range)
{

	XmlRpcValue sdata, result;


	if (client_)
	{
		sdata = (int)range_type;

		if(execute("get_check_laser_range", sdata, result)){

			if(result.size() > 0){

				std::vector<char> vdata = result[0];

				//char* data = new char[vdata.size()];
				//std::copy(vdata.begin(),vdata.end(),data);
			
				if( vdata.size()  && (protobuf_chk_laser::byte2proto(&vdata[0],vdata.size())) )
				//if ( proto_buf_parse::buf2bag(pub_bag,data,ilen))
				{
					protobuf_chk_laser::get_chk_laser(chk_laser_range.type_,chk_laser_range.laser_);
					return true;

				}
					//delete[] data;
			
				
			}



		}
		else
			std::cout << "Error calling  get_check_laser_range"<< std::endl;
	}
	return false;

}

bool xml_rpc_client::get_chk_laser_show(std::vector<Range_type> &v_show_list)
{
	XmlRpcValue sdata, result;

	if (client_){

		sdata[0] = 1;
		if(execute("get_chk_laser_show", sdata, result)){


			if( result.getType() == XmlRpcValue::TypeArray && result.size() > 0){
				int itype = result[0];

				v_show_list.push_back((Range_type)itype);

				return true;
			}

		}
		else
			std::cout << "Error calling  get_chk_laser_show"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::get_sim_path(std::vector<STriangle> &v_sim_data)
{
	v_sim_data.clear();

	XmlRpcValue sdata, result;

	if (client_)
	{

		sdata[0] = "all";
		if(execute("get_sim_path", sdata, result)){


			if ( result.getType() != XmlRpc::XmlRpcValue::TypeBase64 )
			{
				return false;
			}
			XmlRpc::XmlRpcValue::BinaryData vpath = result;

			if (vpath.size() > 0)
			{
				pub_path_->byte2proto(&vpath[0],vpath.size());
				std::vector<SOdomSpeed> v_list;
				pub_path_->get_path(v_list);

				std::vector<SOdomSpeed>::iterator it = v_list.begin();
				for ( ; it != v_list.end(); ++it )
				{
					STriangle path_point;
					path_point.x = it->x_;
					path_point.y = it->y_;
					path_point.angle = -99;
					path_point.color = it->th_;
					path_point.weight = it->vw_;

					v_sim_data.push_back(path_point);
				}
				return true;
			}
			


		}

	}

	return false;
}

bool xml_rpc_client::get_remote_file(const std::string &file_path , const std::string &new_file_path)
{
	XmlRpcValue sdata, result;

	file fget;
	std::string str_new_file = new_file_path;
	//std::string str_new_file = ".//pro_log//" + cComm::Get_FileName(new_file_path) + "." + cComm::Get_FileType(new_file_path);
	if( fget.open_wfile(str_new_file) < 0){
		return false;
	}

	if (client_)
	{
		std::stringstream ss;
		ss<<"open "<<file_path;
		sdata[0] = ss.str();

		if(execute("get_remote_file", sdata, result)){

			if ( result.getType() != XmlRpc::XmlRpcValue::TypeArray )
			{
				return false;
			}else{
				int irec = result[0];
				if ( irec < 0)
				{
					std::cout<<"open file err:"<<file_path<<std::endl;
					return false;
				}
			}
			
		}else{
			return false;
		}

		while (1)
		{
			sdata[0] = "get";
			if(execute("get_remote_file", sdata, result)){
				
				if ( result.getType() != XmlRpc::XmlRpcValue::TypeArray )
				{
					return false;
				}else{

					int irec = result[0];

					if ( irec > 0)
					{
						XmlRpc::XmlRpcValue::BinaryData vpath = result[1];
						fget.write_file( &vpath[0], vpath.size());
					}else if( irec == 0){
						fget.close_wfile();
						break;
					}else{
						return false;
					}
				}
			}else{
				return false;
			}
		}
		sdata[0] = "close";
		if(execute("get_remote_file", sdata, result)){
			return true;
		}
		
	}
	return false;
}


bool xml_rpc_client::get_scan_reflector( SReflector &ref )
{
	XmlRpcValue sdata, result;

	memset(&ref,0,sizeof(SReflector));

	if (client_){

		sdata[0] = 1;
		if(execute("get_scan_reflector", sdata, result)){

			for (int i = 0; i < result.size() ; )
			{
				int i_id=(int)result[i]["id"];
				double x =(double)result[i]["x"];
				double y =(double)result[i]["y"];

				ref.id_[i] = i_id;
				ref.pos_[i].x_ = x;
				ref.pos_[i].y_ = y;
				ref.used_++;
				i++;
			}

			return true;


		}
		else
			std::cout << "Error calling  get_scan_reflector"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_reflector_pos(SPOS_CONFIDENCE &pos_confi)
{
	XmlRpcValue sdata, result;

	memset(&pos_confi,0,sizeof(SPOS_CONFIDENCE));


	if (client_){

		sdata[0] = 1;
		if(execute("get_reflector_pos", sdata, result)){

			if(result.size() > 4){
	
				pos_confi.pos_.x_ = (double)result[0];
				pos_confi.pos_.y_ = (double)result[1];
				pos_confi.pos_.th_ = (double)result[2];
				pos_confi.confidence_.b_amcl_confidence_ = int(result[3]);
				pos_confi.confidence_.amcl_confidence_ = double(result[4]);

				return true;
			}else{
				return false;
			}
			


		}
		else
			std::cout << "Error calling  get_reflector_pos"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_loop_closure_pos(SLoopCLosurePos &cpos)
{
	XmlRpcValue sdata, result;

	memset(&cpos,0,sizeof(SLoopCLosurePos));

	if (client_){

		sdata[0] = 1;
		if(execute("get_loop_closure", sdata, result)){

			if(result.size() > 3){

				cpos.pos_.x_ = (double)result[0];
				cpos.pos_.y_ = (double)result[1];
				cpos.pos_.th_ = (double)result[2];
				cpos.confidence_ = (double)result[3];
				return true;
			}else{
				return false;
			}

		}
		else
			std::cout << "Error calling  get_loop_closure_pos"<< std::endl;
	}
	return false;
}


bool xml_rpc_client::do_download_file( std::string pc_file,std::string arm_file )
{
	XmlRpcValue sdata, result;

	if (!cComm::FileExist(pc_file))
	{
		std::cout<<"do_download_file file no exist!"<<pc_file<<std::endl;
		return false;
	}

	file red_file;
	int i_len = red_file.open_file(pc_file);
	char* p_data = new char[DOWN_LOAD_PACKAGE_SIZE];
	memset(p_data,0,DOWN_LOAD_PACKAGE_SIZE);

	if (i_len > 0)
	{
		std::stringstream ss;
		ss<<"open "<<arm_file;
		sdata[0] = ss.str();
		if (!client_->execute("do_download_file", sdata, result)){
			red_file.close_file();
			return false;
		}
		if ( (int)result[0] != 99 )
		{
			red_file.close_file();
			return false;
		}
	}
	for (;;)
	{
			
		red_file.read_file(p_data,i_len,DOWN_LOAD_PACKAGE_SIZE);
		
		if (i_len < 1)
		{
			break;
		}
		sdata[0] = "write";
		sdata[1] = XmlRpc::XmlRpcValue(p_data,i_len);
		
		if (!client_->execute("do_download_file", sdata, result)){
			red_file.close_file();
			return false;
		}
		memset(p_data,0,DOWN_LOAD_PACKAGE_SIZE);
	}

	sdata[0] = "close";
	if (!client_->execute("do_download_file", sdata, result)){
		return false;
	}

	delete[] p_data;
	p_data = 0;
	red_file.close_file();

	return true;
}

bool xml_rpc_client::get_amcl_entropy(SAMCL_ENTROPY &ae)
{
	XmlRpcValue sdata, result;

	memset(&ae,0,sizeof(SAMCL_ENTROPY));

	if (client_){

		sdata[0] = 1;
		if(execute("get_amcl_entropy", sdata, result)){

			if(result.size() > 3){

				ae.b_amcl_entropy_ = (int)result[0];
				ae.amcl_xy_entropy_ = (double)result[1];
				ae.amcl_theta_entropy_ = (double)result[2];
				ae.amcl_entropy_ = (double)result[3];

				return true;
			}else{
				return false;
			}

		}
		else
			std::cout << "Error calling  get_amcl_entropy"<< std::endl;
	}
	return false;
}


bool xml_rpc_client::get_amcl_confidence(SAMCL_CONFIDENCE &ac)
{
	XmlRpcValue sdata, result;

	memset(&ac,0,sizeof(SAMCL_CONFIDENCE));

	if (client_){

		sdata[0] = 1;
		if(execute("get_amcl_confidence", sdata, result)){

			if(result.size() > 1){

				ac.b_amcl_confidence_ = (int)result[0];
				ac.amcl_confidence_ = (double)result[1];

				return true;
			}else{
				return false;
			}

		}
		else
			std::cout << "Error calling  get_amcl_confidence"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_view_data(std::vector<SView_Data> &v_data)
{
	XmlRpcValue sdata, result;
	assert(v_data.size() == 0);

	if (client_)
	{
		sdata[0] = 1;
		if(execute("get_view_data", sdata, result)){

			if(result.size() > 2){
				
				SView_Data vd;

				int ilen = result.size();
				assert( (ilen % 3) == 0);

				for ( int i = 0 ; i < ilen ;  i+=3){

					std::string str_name = result[ i + 0];
					int idata_len =  (int)result[ i + 1];
					std::vector<char> vdata = result[ i + 2];

					assert(idata_len == vdata.size());
 					char* data = new char[idata_len];
 					std::copy(vdata.begin(),vdata.end(),data);

					memset(&vd,0,sizeof(SView_Data));
					int iname_len = 200;
					cComm::String2Charlist((S8*)vd.name_,iname_len,str_name);
					vd.ilen_ = idata_len;
					vd.uc_data_ = (U8*)data;
					v_data.push_back(vd);
				}


				return true;
			}else{
				//std::cout<<"get_view_data empty!"<<std::endl;
			}



		}
		else
			std::cout << "Error calling  get_view_data"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_battery(SBattery &bat)
{
	XmlRpcValue sdata, result;

	sdata = 1;

	if (client_)
	{
		if(execute("get_battery", sdata, result)){

			if (result.size()  > 3)
			{
				std::string str_time_ = std::string(result[0]);
				cComm::ConvertToNum(bat.time_stamp_,str_time_);
				bat.voltage_ = double(result[1]);
				bat.percent_ = double(result[2]);
				bat.charge_current_ = double(result[3]);
				bat.run_current_ = double(result[4]);
				bat.set_contactor_out_ = int(result[5]);
				bat.get_contactor_in_ = int(result[6]);

				return true;
			}else{
				//std::cout << "get_battery no refresh!!"<< std::endl;
				return false;
			}


			
		}
		else
			std::cout << "Error calling get_battery \n";
	}
	return false;
}

bool xml_rpc_client::set_bt_contact(const int &bt_contact)
{
	XmlRpcValue sdata, result;

	sdata[0] = bt_contact;

	if (client_)
	{

		if(execute("set_bt_contact", sdata, result)){

		
			std::cout << "set_bt_contact:"<< sdata[0] << std::endl;
			return true;
		}
		else
			std::cout << "Error calling set_bt_contact \n";
	}
	return false;
}

bool xml_rpc_client::get_special_loc_conpos(SPOS_CONFIDENCE &con_pos)
{
	memset( &con_pos , 0 , sizeof(SPOS_CONFIDENCE));

	XmlRpcValue sdata, result;

	sdata[0] = 1;

	if (client_)
	{

		if(execute("get_special_loc_conpos", sdata, result)){
		
			if ( result.size() > 4){

				con_pos.pos_.x_ = (double)result[0];
				con_pos.pos_.y_ = (double)result[1];
				con_pos.pos_.th_ = (double)result[2];

				con_pos.confidence_.b_amcl_confidence_ = (int)result[3];
				con_pos.confidence_.amcl_confidence_ = (double)result[4];
			}
			std::cout<<"con_pos xya:"<<con_pos.pos_.x_<<" "<<con_pos.pos_.y_<<" "<<con_pos.pos_.th_<<std::endl;
			std::cout<<"con b:"<<int(con_pos.confidence_.b_amcl_confidence_)<<" conf:"<<con_pos.confidence_.amcl_confidence_<<std::endl;


			return true;
		}
		else
			std::cout << "Error calling get_special_loc_conpos \n";
	}
	return false;
}

bool xml_rpc_client::get_special_landmark(SWorldLM &wlm)
{
	memset( &wlm , 0 , sizeof(SWorldLM));

	XmlRpcValue sdata, result;

	sdata[0] = 1;

	if (client_)
	{

		if(execute("get_special_landmark", sdata, result)){

			if ( result.size() > 8){

				wlm.robot_in_world_.x_ = (double)result[0];
				wlm.robot_in_world_.y_ = (double)result[1];
				wlm.robot_in_world_.th_ = (double)result[2];

				wlm.landmark_in_robot_.x_ = (double)result[3];
				wlm.landmark_in_robot_.y_ = (double)result[4];
				wlm.landmark_in_robot_.th_ = (double)result[5];

				wlm.landmark_in_world_.x_ = (double)result[6];
				wlm.landmark_in_world_.y_ = (double)result[7];
				wlm.landmark_in_world_.th_ = (double)result[8];

			}
			std::cout<<"robot_in_world_ xya:"<<wlm.robot_in_world_.x_<<" "<<wlm.robot_in_world_.y_<<" "<<wlm.robot_in_world_.th_<<std::endl;
			std::cout<<"landmark_in_robot_ xya:"<<wlm.landmark_in_robot_.x_<<" "<<wlm.landmark_in_robot_.y_<<" "<<wlm.landmark_in_robot_.th_<<std::endl;
			std::cout<<"landmark_in_world_ xya:"<<wlm.landmark_in_world_.x_<<" "<<wlm.landmark_in_world_.y_<<" "<<wlm.landmark_in_world_.th_<<std::endl;

			return true;
		}
		else
			std::cout << "Error calling get_special_landmark \n";
	}
	return false;
}

bool xml_rpc_client::set_sim_init_pos(const SPos &pos)
{
	std::cout<<"set_sim_init_pos:"<<pos.x_<<" "<<pos.y_<<" "<<pos.th_<<std::endl;
	XmlRpcValue sdata, result;

	if (client_)
	{

		sdata[0] = pos.x_;
		sdata[1] = pos.y_;
		sdata[2] = pos.th_;

		if(execute("set_sim_init_pos", sdata, result)){

			if ( int(result) > 0)
			{
				std::cout << "set init pos over:"<< sdata.size() << std::endl;
				return true;
			}else{
				std::cout << "set init pos err:"<< sdata.size() << std::endl;
				return false;
			}

		}
		else
			std::cout << "Error calling set pos"<< std::endl;
	}
	return false;
}
bool xml_rpc_client::execute(const char* method, XmlRpcValue const& params, XmlRpcValue& result){
	
	boost::mutex::scoped_lock lock(mu_rpc_);

	if (client_->execute(method,params,result)){
		return true;
	}
	return false;

}
bool xml_rpc_client::set_pause( bool b_pause )
{
	
	XmlRpcValue sdata, result;

	if (client_)
	{
		if ( b_pause ){
			sdata[0] = int(1);
		}else{
			sdata[0] = int(0);
		}
		std::cout<<"set_pause:"<<int(sdata[0])<<std::endl;

		if(execute("set_pause", sdata, result)){

			int i_res = int(result[0]);
			if ( i_res > 0){
				return true;
			}else{
				return false;
			}
			std::cout << "set_pause! "<<i_res<< std::endl;
		}
		else
			std::cout << "Error calling set_pause"<< std::endl;
	}
	return false;
}

bool xml_rpc_client::get_fork( SAct_Fork &fork_para )
{
	

	XmlRpcValue sdata, result;

	sdata[0] = 1;

	if (client_)
	{

		if(execute("get_fork", sdata, result)){

			if ( result.size() > 8){

				memset( &fork_para , 0 , sizeof(SAct_Fork));

				fork_para.act_base_.node_from_ = (int)result[0];
				fork_para.act_base_.node_to_ = (int)result[1];
				fork_para.act_base_.trig_per_ = (double)result[2];
				fork_para.act_base_.check_per_ = (double)result[3];

				fork_para.act_base_.init_ = (int)result[4];
				fork_para.act_base_.force_done_ = (int)result[5];

				fork_para.act_base_.force_error_ = (int)result[6];
				fork_para.act_base_.redo_ = (int)result[7];

				fork_para.act_data_.level_ = (double)result[8];
				fork_para.act_data_.speed_ = (double)result[9];


			}

			return true;
		}
		else
			std::cout << "Error calling get_fork \n";
	}
	return false;
}

bool xml_rpc_client::get_steering( std::vector<SSteering> &v_st )
{
	
	XmlRpcValue sdata, result;

	sdata[0] = 1;

	SSteering st;
	
	if (client_)
	{

		if(execute("get_steering", sdata, result)){

			if ( result.size() > 0 ){
				v_st.clear();
			}
			for ( int i = 0 ; i < result.size() ; ++i ){
				memset( &st , 0 , sizeof(SSteering));
				st.id_ = (int)result[i]["id"];

				st.pos_.x_ = (double)result[i]["pos_x"];
				st.pos_.y_ = (double)result[i]["pos_y"];
				st.pos_.th_ = (double)result[i]["pos_th"];

				st.max_angle_ = (double)result[i]["max_a"];
				st.min_angle_ = (double)result[i]["min_a"];

				st.zero_angle_ = (double)result[i]["zero_a"];

				st.set_angle_ = (double)result[i]["set_angle"];
				st.set_speed_ = (double)result[i]["set_speed"];

				st.cur_angle_ = (double)result[i]["cur_angle"];
				st.cur_speed_ = (double)result[i]["cur_speed"];

				v_st.push_back(st);
			}

			if (v_st.size() > 0){
				return true;
			}
			
		}
		else
			std::cout << "Error calling get_steering \n";
	}
	return false;
}

bool xml_rpc_client::get_dio_bind(std::map<std::string, SDIO_NM_INDEX> &m_data)
{
	XmlRpcValue sdata, result;

	sdata[0] = 1;

	SDIO_NM_INDEX dio_nm_index;

	if (client_)
	{

		if(execute("get_dio_bind", sdata, result)){

			if ( result.size() > 0 ){
				m_data.clear();
			}
			for ( int i = 0 ; i < result.size() ; ++i ){
				
				dio_nm_index.str_fnc_nm_ = (std::string)result[i]["fnc_nm"];
				dio_nm_index.str_dev_nm_ = (std::string)result[i]["dev_nm"];
				dio_nm_index.str_type_ = (std::string)result[i]["data_type"];

				dio_nm_index.i_dio_index_ = (int)result[i]["data_index"];


				m_data[dio_nm_index.str_fnc_nm_] = dio_nm_index;
			}

			if (m_data.size() > 0){
				return true;
			}

		}
		else
			std::cout << "Error calling get_dio_bind \n";
	}
	return false;
}

bool xml_rpc_client::get_dio_data( std::vector<SDIO_NM_INDEX> &v_data )
{
	XmlRpcValue sdata, result;

	sdata[0] = 1;

	SDIO_NM_INDEX dio_nm_index;

	if (client_)
	{

		if(execute("get_dio_data", sdata, result)){

			if ( result.size() > 0 ){
				v_data.clear();
			}

			for ( int i = 0 ; i < result.size() ; ++i ){

				dio_nm_index.str_fnc_nm_ = (std::string)result[i]["fnc_nm"];
				dio_nm_index.str_value_ = (std::string)result[i]["data"];

				v_data.push_back( dio_nm_index );
			}

			if (v_data.size() > 0){
				return true;
			}
			
		}
		else
			std::cout << "Error calling get_dio_bind \n";
	}
	return false;
}

bool xml_rpc_client::get_qr_code(SQrCode &qr_code)
{
	XmlRpcValue sdata, result;

	sdata[0] = "qrcode";

	memset(&qr_code,0,sizeof(SQrCode));

	if (client_)
	{

		if(execute("get_qr_code", sdata, result)){

			if ( result.size() > 0 ){
				
				std::vector<char> vdata = result[0];
				
				char* data = new char[vdata.size()];
				std::copy(vdata.begin(),vdata.end(),data);
				if (vdata.size() == sizeof(SQrCode)){
					memcpy(&qr_code,data,sizeof(SQrCode));
					return true;
				}
				delete[] data;
				data = 0;
			}
			std::cout<<"Error calling get_qr_code: data error!"<<std::endl;
			return false;

		}
		else
			std::cout << "Error calling get_qr_code \n";
	}
	return false;
}

