
#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/shared_pipe.hpp"
#include "interpro_shared/pipe_shared_pool.hpp"

#include "Comm/configs.h"
#include "Comm/rpc_config_server.h"

//using namespace boost::interprocess;

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}

bool call_pipe(std::string name,U8* data,U32 len){
	std::cout<<"sub pipe name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<cComm::ByteToHexString(data,len)<<std::endl;
	return true;
}
void th_get1(){
	int i = 0;
	while (1){
		GET_CONFIG(i,"c");
		std::cout<<"get1:"<<i<<std::endl;
	}
	
}
void th_get2(){
	int i = 0;
	while (1){
		GET_CONFIG(i,"c");
		std::cout<<"get2:"<<i<<std::endl;
	}
}
int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	rpc_config_server rpc_cfg;
	rpc_cfg.init();

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

	boost::thread th1(boost::bind(&th_get1));
	boost::thread th2(boost::bind(&th_get2));

	while(1){
		SLEEP(1000);
	}
}

