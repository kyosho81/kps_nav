
#ifndef _RPC_CONFIG_CLIENT_KYOSHO_20201105_H_
#define _RPC_CONFIG_CLIENT_KYOSHO_20201105_H_

#include <vector>
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>
#include "boost/lexical_cast.hpp"
#include <iostream>

#include <RobotStruct.h>

#include "XmlRpc.h"
#include "Comm/PortDef.h"


//using namespace XmlRpc;

class rpc_config_client
{
public:
	rpc_config_client();
	~rpc_config_client();

	void init(std::string ip, int port = RPC_CONFIG_SER_PORT);
	
	bool set_config( const std::string &str_name , const std::string &str_value );
	bool set_config( const std::string &str_name , const double &d_value );
	bool set_config( const std::string &str_name , const float &f_value);
	bool set_config( const std::string &str_name , const int &i_value);

	bool get_configs(std::string &str_value ,const std::string &str_name);
	bool get_whole_config(std::string &str_value ,const std::string &str_name);
	bool set_whole_config(const std::string &str_name , std::string &str_value);
	bool init_whole_config(const std::string &str_whole_para);

	template<typename T>
	bool get_config( T &value ,const std::string &str_name){
		
		std::string str_value;
		
		if (get_configs(str_value,str_name)){
			//cComm::ConvertToNum(value,str_value);
			//value = boost::lexical_cast<T>(str_value.c_str());

			try
			{
				value = boost::lexical_cast<T>(str_value.c_str());
				return true;
			}
			catch (boost::bad_lexical_cast& e)
			{
				std::cout<<"rpc get_config err! str:"<<str_name<<" value:"<<str_value<<std::endl;
				return false;
			}

			return true;
		}
		return false;
	};

	bool get_config_list(std::vector<std::string> &v_res);

	bool save();

private:

	bool set_config( const std::string &str_type ,const std::string &str_name , const std::string &str_value );

	XmlRpc::XmlRpcClient* client_;

	boost::mutex mu_;

};


typedef boost::serialization::singleton<rpc_config_client> Singleton_Rpc_config_client;
#define RPC_CONFIG_CLIENT_INIT(str_ip)  Singleton_Rpc_config_client::get_mutable_instance().init(str_ip)
#define RPC_CONFIG_CLIENT Singleton_Rpc_config_client::get_mutable_instance()
#endif // _RPC_CONFIG_CLIENT_KYOSHO_20201105_H_
