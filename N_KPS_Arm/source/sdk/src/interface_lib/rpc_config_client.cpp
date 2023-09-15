#include "math.h"
#include "Comm.h"
#include "Geometry.h"

#include "Comm/file.h"

#include "interface/rpc_config_client.h"

rpc_config_client::rpc_config_client()
:client_(0)
{

}
rpc_config_client::~rpc_config_client(){
	if (client_){
		client_->close();
	}
	
}

void rpc_config_client::init( std::string ip, int port )
{

	client_ =  new XmlRpc::XmlRpcClient(ip.c_str(),port);
}


bool rpc_config_client::get_configs(std::string &str_value ,const std::string &str_name)
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{
		sdata[0] = str_name;
		if (client_->execute("get_para", sdata, result)){
			std::string str;
			if (result.size()  > 0)
			{
				str = std::string(result[0]);
			}
			str = cComm::trim(str);
			if ( str.length() < 1)
			{
				std::cout << "get_para err name:"<< str_name <<" value:"<< str_value << std::endl;
				return false;
			}else{
				str_value = str;
				std::cout << "get_para name:"<< str_name <<" value:"<< str_value << std::endl;
				return true;
			}

			
		}
		else{
			std::cout << "Error calling get_para "<<str_name<<std::endl;
		}
	}else{
		std::cout << "!!!!!!!!!!!!Error calling get_para client "<<str_name<<std::endl;
		//assert(false);
	}
	return false;
}

bool rpc_config_client::get_config_list(std::vector<std::string> &v_res)
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{
		
		if (client_->execute("get_para_list", sdata, result)){

			for ( int i = 0 ; i < result.size() ; ++i ){
				v_res.push_back(std::string(result[i]));
			}
			
			return true;
		}
		else
			std::cout << "Error calling get_para_list \n";
	}
	return false;
}

bool rpc_config_client::set_config( const std::string &str_type ,const std::string &str_name , const std::string &str_value)
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{
		sdata[0] = str_type;
		sdata[1] = str_name;
		sdata[2] = str_value;

		if (client_->execute("set_para", sdata, result)){

			if (result.size()  > 0)
			{
				if (int(result[0]) <= 0)
				{
					std::cout << "set_para error name:"<< str_name <<" value:"<< str_value << std::endl;
					return false;
				}
			}


			std::cout << "set_para name:"<< str_name <<" value:"<< str_value << std::endl;
			return true;
		}
		else
			std::cout << "Error calling set_para \n";
	}
	return false;
}

bool rpc_config_client::set_config(const std::string &str_name , const std::string &str_value)
{
	return set_config("string",str_name,str_value);
}

bool rpc_config_client::set_config(const std::string &str_name , const double &d_value)
{
	U8* u_d = new U8[sizeof(double)];
	memset(u_d,0,sizeof(double));
	memcpy(u_d,&d_value,sizeof(double));
	std::string str_value = cComm::ByteToHexString(u_d,sizeof(double));
	delete[] u_d;
	u_d = 0;
	std::string str_type = typeid(double).name();
	return set_config( str_type, str_name, str_value);
}
bool rpc_config_client::set_config(const std::string &str_name , const float &f_value)
{
	U8* f_d = new U8[sizeof(float)];
	memset(f_d,0,sizeof(float));
	memcpy(f_d,&f_value,sizeof(float));
	std::string str_value = cComm::ByteToHexString(f_d,sizeof(float));
	delete[] f_d;
	f_d = 0;
	std::string str_type = typeid(float).name();
	return set_config( str_type, str_name, str_value);
}
bool rpc_config_client::set_config(const std::string &str_name , const int &i_value)
{
	U8* i_d = new U8[sizeof(int)];
	memset(i_d,0,sizeof(int));
	memcpy(i_d,&i_value,sizeof(int));
	std::string str_value = cComm::ByteToHexString(i_d,sizeof(int));
	delete[] i_d;
	i_d = 0;
	std::string str_type = typeid(int).name();
	return set_config( str_type, str_name, str_value);
}

bool rpc_config_client::get_whole_config( std::string &str_value ,const std::string &str_name )
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{
		sdata[0] = str_name;
		if (client_->execute("get_whole_para", sdata, result)){

			if (result.size()  > 0)
			{
				str_value = std::string(result[0]);
			}


			std::cout << "get_whole_config name:"<< str_name <<" value:"<< str_value << std::endl;
			return true;
		}
		else
			std::cout << "Error calling get_whole_config \n";
	}
	return false;
}

bool rpc_config_client::init_whole_config( const std::string &str_whole_para )
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{

		sdata[0] = str_whole_para;

		if (client_->execute("init_whole_config", sdata, result)){

			if (result.size()  > 0)
			{
				if (int(result[0]) <= 0)
				{
					std::cout << "init_whole_config error value:"<< str_whole_para << std::endl;
					return false;
				}
			}


			std::cout << "init_whole_config value:"<< str_whole_para << std::endl;
			return true;
		}
		else
			std::cout << "Error calling init_whole_config \n";
	}
	return false;
}

bool rpc_config_client::set_whole_config(const std::string &str_name , std::string &str_value)
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{

		sdata[0] = str_name;
		sdata[1] = str_value;

		if (client_->execute("set_whole_config", sdata, result)){

			if (result.size()  > 0)
			{
				if (int(result[0]) <= 0)
				{
					std::cout << "init_whole_config error value:"<< str_name << std::endl;
					return false;
				}
			}


			std::cout << "init_whole_config value:"<< str_name << std::endl;
			return true;
		}
		else
			std::cout << "Error calling set_whole_config \n";
	}
	return false;
}

bool rpc_config_client::save()
{
	XmlRpc::XmlRpcValue sdata, result;
	boost::mutex::scoped_lock lock(mu_);
	if (client_)
	{

		if (client_->execute("save_config", sdata, result)){

			if (result.size()  > 0)
			{
				if (int(result[0]) <= 0)
				{
					std::cout << "save_config error " << std::endl;
					return false;
				}
			}


			std::cout << "save_config " << std::endl;
			return true;
		}
		else
			std::cout << "Error calling save_config \n";
	}
	return false;
}


