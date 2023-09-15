#include <assert.h>

#include "Comm/PortDef.h"
#include "Comm/configs.h"

#include "interface/rpc_config_server.h"

rpc_config_server::rpc_config_server()
{
	str_config_path_ = ".//cfg//";
	get_para_ = 0;
	get_para_list_ = 0;
	set_para_ = 0;
	get_whole_para_ = 0;
	init_whole_config_ = 0;
	set_whole_config_ = 0;
	save_config_ = 0;
}

rpc_config_server::~rpc_config_server()
{
	SDelete(get_para_);
	SDelete(get_para_list_);
	SDelete(set_para_);
	SDelete(get_whole_para_);
	SDelete(init_whole_config_);
	SDelete(set_whole_config_);
	SDelete(save_config_);
}

int rpc_config_server::load_cfg()
{
	std::vector<std::string> v_file;
	cComm::Find_files(str_config_path_,"*.cfg",v_file);
	std::vector<std::string>::iterator it = v_file.begin();
	for ( ; it != v_file.end() ; ++it ){
		std::cout<<"load cfg:"<<*it<<std::endl;
		load_cfg(*it);
	}

	return v_file.size();
}

bool rpc_config_server::load_cfg(const std::string &str_cfg_file)
{
	return LOAD_CONFIG(str_cfg_file);
}

bool rpc_config_server::init()
{
	load_cfg();
	std::cout<<"load cfg over!"<<std::endl;

	init_s();

	//XmlRpc::setVerbosity(0);

	if (s_.bindAndListen(RPC_CONFIG_SER_PORT))
	{
		// Enable introspection
		s_.enableIntrospection(true);
		// Wait for requests indefinitely
		boost::thread th(boost::bind(&rpc_config_server::th_rpc_,this));
	}else{
		std::cout<<"cfg rpc server init err !!!!port:"<<RPC_CONFIG_SER_PORT<<std::endl;
		return false;
	}
	return true;
}
void rpc_config_server::th_rpc_(void){

	std::cout<<"rpc_config_server thread run!"<<std::endl;
	s_.work(-1.0);
	std::cout<<"rpc_config_server thread end!"<<std::endl;
}

void rpc_config_server::destruct()
{
	s_.close();
}

void rpc_config_server::init_s()
{
	get_para_ = new get_para(&s_);
	get_para_list_ = new get_para_list(&s_);
	set_para_ = new set_para(&s_);
	get_whole_para_ = new get_whole_para(&s_);
	init_whole_config_ = new init_whole_config(&s_);
	set_whole_config_ = new set_whole_config(&s_);
	save_config_ = new save_config(&s_);
}
