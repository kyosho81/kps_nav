#include "trans_dev/pinger.h"
#include "trans_dev/traceroute.h"
#include "Comm/Comm.h"

#include "encryption/Base64.h"
#include "encryption/keygen.h"
#include "encryption/key_client.h"

int main(void){

#if 0
	std::string str_key = "a123456";
	Base64Encrypt enc( str_key.c_str(), str_key.length() );
	std::string str_enc = enc.GetString();
	std::cout<<"len:"<<str_enc.length()<<" sn:"<<str_enc<<std::endl;
	Base64Decrypt dec(str_enc.c_str(),str_enc.length());
	std::string str_dec = dec.GetString();

	keygen kg;
	std::string str = kg.init_token();
	std::cout<<"len:"<<str.length()<<" sn:"<<str<<std::endl;
	if( kg.check_token(str)){
		std::cout<<"token ok!"<<std::endl;
	}else{
		std::cout<<"token error!"<<std::endl;
	}
	#endif

	KEY_CLIENT.init();

	::system("pause");

	return 0;
}