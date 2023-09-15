#ifndef _CFG_WANGHONGTAO_KYOSHO_20200912_
#define _CFG_WANGHONGTAO_KYOSHO_20200912_

#include "interface/rpc_config_client.h"

/**************************************************************************************************
 * class Config
***************************************************************************************************/


class Config
{
public:
	template<typename Type>
	static bool getConfig(std::string name, Type &out)
	{
		return RPC_CONFIG_CLIENT.get_config(out,name);
	};
	static bool getConfig(std::string name, std::string &out)
	{
		return RPC_CONFIG_CLIENT.get_config(out,name);
	};
	template<typename T>
	static bool setConfig(const std::string &name, const T &in)
	{
		return RPC_CONFIG_CLIENT.set_config(name,in);
	};

};


#endif //_CFG_WANGHONGTAO_KYOSHO_20200912_
