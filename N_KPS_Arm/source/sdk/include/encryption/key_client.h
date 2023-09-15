#ifndef _KEY_CLIENT_KYOSHO_20230303_H
#define _KEY_CLIENT_KYOSHO_20230303_H

#include <string>
#include <vector>
#include <boost/serialization/singleton.hpp>

#include "network.h"
#include "encryption/keygen.h"

#define KEYGEN_TIMEOUT_TG 3600// 60*60 sec
//#define KEYGEN_TIMEOUT_TG 60*10// 60*60 sec

class key_client
{
public:
	key_client();
	~key_client();

	bool init(std::string str_fnc);
	bool check_fuc(std::string str_fnc);

private:
	net_work nw_;
	SCentralController_Info cc_info_;

	void th_activate();
	bool b_run_;

	keygen kg_;

	int get_port(std::string str_fnc);
};

typedef boost::serialization::singleton<key_client> Singleton_key_client;
#define KEY_CLIENT Singleton_key_client::get_mutable_instance()

#endif //_KEY_CLIENT_KYOSHO_20230303_H

