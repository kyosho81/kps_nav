
#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/shared_pipe.hpp"
#include "interpro_shared/pipe_shared_pool.hpp"

#include "Comm/configs.h"
#include "Comm/rpc_config_server.h"
#include "interface/rpc_config_client.h"

//using namespace boost::interprocess;

bool b_run = true;
rpc_config_server rpc_cfg_svr;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;
	rpc_cfg_svr.destruct();

	return;
}

bool call_pipe(std::string name,U8* data,U32 len){
	std::cout<<"sub pipe name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<cComm::ByteToHexString(data,len)<<std::endl;
	return true;
}
void th_get1(){
	int i = 0;

	RPC_CONFIG_CLIENT_INIT("127.0.0.1");
	while (1){
		std::vector<std::string> v_res;
		RPC_CONFIG_CLIENT.get_config_list(v_res);

		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it ){
			std::string str_value;
			RPC_CONFIG_CLIENT.get_config(str_value,*it);
			std::cout<<"name:"<<*it<<" "<<str_value<<std::endl;
		}
		SLEEP(1000);
	}
	
}
void th_get2(){

	

	int i = -3;
	std::string str;
	while (1){
		//std::getline(std::cin,str);
		/*RPC_CONFIG_CLIENT.set_config("dev_laser_ip","192");
		RPC_CONFIG_CLIENT.set_config("dev_laser_dx",double(.125));
		RPC_CONFIG_CLIENT.set_config("dev_laser_dx",float(.125));
		RPC_CONFIG_CLIENT.set_config("dev_laser_s",i);*/
		std::vector<std::string> vres;
		RPC_CONFIG_CLIENT.get_config_list(vres);
		std::vector<std::string>::iterator it = vres.begin();
		for ( ; it != vres.end(); ++it)
		{
			F32 dx = 0;
			Config::getConfig("dev_laser_dx",dx);
			std::cout<<"dev_laser_dx:"<<dx<<std::endl;
			SLEEP(10);
// 			std::string str;
// 			RPC_CONFIG_CLIENT.get_whole_config(str,*it);
// 			config_it c_it("def");
// 			c_it.decode(str);
// 			std::string s = c_it.code();
// 		
// 			RPC_CONFIG_CLIENT.init_whole_config(s);
		}
	}
}
int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	
	//rpc_cfg_svr.init();
	RPC_CONFIG_CLIENT_INIT("127.0.0.1");

	boost::thread th1(boost::bind(&th_get2));

	while(b_run){
		F32 dx = 0;
		Config::getConfig("dev_laser_dx",dx);
		std::cout<<"main dev_laser_dx:"<<dx<<std::endl;
		SLEEP(10);
	}

	return 0;

	int i = 80000000;
	float f = -0.1;
	double d1 = 0.001;
//	Singleton_Configs::get_mutable_instance().init_config("c",2,1,100);
	INIT_CONFIG("c",2,1,100);
	SET_SEG("c","laser");
	INIT_CONFIG("b",2,1,100);
	SET_SEG("b","laser");
	
	INIT_CONFIG("f",f,f,f);
	INIT_CONFIG("d",d1,d1,d1);
	SET_SCONFIG("s","string");
	//SAVE_CONFIG("kps_config.ini");
	LOAD_CONFIG("kps_config.ini");

	return 0;
//	Singleton_Configs::get_mutable_instance().set_config("c",i);
	SET_CONFIG("c",i);
//	Singleton_Configs::get_mutable_instance().set_sconfig("s","string");
	SET_SCONFIG("s","string");

	double d = 0.123;
	INIT_CONFIG("d",2.0,1.0,100.0);
	SET_CONFIG("d",d);

	std::string str="";
	GET_CONFIG(i,"c");
	GET_SCONFIG(str,"s");
	//Singleton_Configs::get_mutable_instance().get_sconfig(str,"s");

// 	boost::thread th1(boost::bind(&th_get1));
// 	boost::thread th2(boost::bind(&th_get2));

	while(1){
		SLEEP(1000);
	}
}

