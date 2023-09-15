#ifndef _RPC_CONFIG_SERVER_WANGHONGTAO_KYOSHO_20200912_
#define _RPC_CONFIG_SERVER_WANGHONGTAO_KYOSHO_20200912_

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
#include "XmlRpc.h"


class get_para : public XmlRpc::XmlRpcServerMethod
{
public:

	get_para(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_para", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		int nArgs = params.size();
		if(nArgs == 1){

			std::string name = params[0];

			std::string value ;
			if(!GET_CONFIG(value,name)){
				result[0] = "";
				std::cout<<"get_para err name:"<<name<<" value:"<<value<<std::endl;
			}else{
				result[0] = value;
				std::cout<<"get_para name:"<<name<<" value:"<<value<<std::endl;
			}

			
		}else{
			result[0] = "";
		}

	};
};

class get_whole_para : public XmlRpc::XmlRpcServerMethod
{
public:

	get_whole_para(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_whole_para", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = "";

		int nArgs = params.size();
		if(nArgs == 1){

			std::string name = params[0];

			std::string value ;
			if(GET_WHOLE_CONFIG(value,name)){
				result[0] = value;
				std::cout<<"get_whole_para name:"<<name<<" value:"<<value<<std::endl;
			}else{
				std::cout<<"get_whole_para err name:"<<name<<std::endl;
			}

			
		}

	};
};
class init_whole_config : public XmlRpc::XmlRpcServerMethod
{
public:

	init_whole_config(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("init_whole_config", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);

		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			if(INIT_WHOLE_CONFIG(str)){
				result[0] = int(1);
				std::cout<<"set_whole_para value:"<<str<<std::endl;
			}else{
				std::cout<<"set_whole_para err name:"<<str<<std::endl;
			}


		}

	};
};
class set_whole_config : public XmlRpc::XmlRpcServerMethod
{
public:

	set_whole_config(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_whole_config", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);

		int nArgs = params.size();
		if(nArgs == 2){

			std::string str_name = params[0];
			std::string str_value = params[1];
//			
			if( SET_WHOLE_CONFIG( str_name, str_value) ){
				result[0] = int(1);
				std::cout<<"set_whole_para value:"<<str_name<<" value:"<<str_value<<std::endl;
			}else{
				std::cout<<"set_whole_para err name:"<<" value:"<<str_value<<std::endl;
			}



		}

	};
};
class get_para_list : public XmlRpc::XmlRpcServerMethod
{
public:

	get_para_list(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_para_list", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		//result[0] = "";
		std::vector<std::string> v_list;
		GET_LIST(v_list);

		int index = 0;
		std::vector<std::string>::iterator it = v_list.begin();
		for ( ; it != v_list.end() ; ++it ){
			result[index++] = *it;
		}
		
	};
};
class set_para : public XmlRpc::XmlRpcServerMethod
{
public:

	set_para(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_para", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		result[0] = 0;
		if ( params.size() > 2)
		{
			std::string str_type = std::string(params[0]);
			std::string str_name = std::string(params[1]);
			std::string str_value = std::string(params[2]);

			if ( "string" == str_type){
				if(SET_SCONFIG(str_name,str_value)){
					result[0] = 1;
				}
			}else if( typeid(int).name() == str_type ){
				int i_data = 0;
				int ilen = sizeof(int);
				U8* p_data = (U8*)&i_data;
				cComm::HexStringToByte(p_data,ilen,str_value);
				assert(ilen == sizeof(int));

				if(SET_CONFIG(str_name,i_data)){
					result[0] = 1;
				}
			}else if( typeid(float).name() == str_type ){
				float f_data = 0;
				int ilen = sizeof(float);
				U8* p_data = (U8*)&f_data;
				cComm::HexStringToByte(p_data,ilen,str_value);
				assert(ilen == sizeof(float));

				if(SET_CONFIG(str_name,f_data)){
					result[0] = 1;
				}
			}else if( typeid(double).name() == str_type ){
				double d_data = 0;
				int ilen = sizeof(double);
				U8* p_data = (U8*)&d_data;
				cComm::HexStringToByte(p_data,ilen,str_value);
				assert(ilen == sizeof(double));

				if(SET_CONFIG(str_name,d_data)){
					result[0] = 1;
				}
			}
		}else{
			result[0] = -1;
		}



	};
};

class save_config : public XmlRpc::XmlRpcServerMethod
{
public:

	save_config(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("save_config", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);

	
		if( SAVE_CONFIG(".//cfg//kps_config.cfg")){
			result[0] = int(1);
			std::cout<<"save_config ok"<<std::endl;
		}else{
			std::cout<<"save_config err "<<std::endl;
		}

	}

	
};
class rpc_config_server
{
public:

	rpc_config_server();
	~rpc_config_server();

	bool init();
	void destruct();

protected:
private:

	int load_cfg();
	bool load_cfg(const std::string &str_cfg_file);
	
	std::string str_config_path_;
	//rpc
private:

	void init_s();
	void th_rpc_(void);
	
	XmlRpc::XmlRpcServer s_;

	get_para* get_para_;
	get_para_list* get_para_list_;
	set_para* set_para_;
	get_whole_para* get_whole_para_;
	init_whole_config* init_whole_config_;
	set_whole_config* set_whole_config_;
	save_config* save_config_;
};

#endif //_RPC_CONFIG_SERVER_WANGHONGTAO_KYOSHO_20200912_
