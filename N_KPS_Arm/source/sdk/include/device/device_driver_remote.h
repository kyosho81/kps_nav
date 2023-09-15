#ifndef _DEVICE_DRIVER_REMOTE_WANGHONGTAO_20180401_
#define _DEVICE_DRIVER_REMOTE_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"

#include "device/device_driver.h"


typedef struct _SRemote_key{

	U8 key1_;
	U8 key2_;
	U8 key3_;
	U16 new_ad1_;
	U16 new_ad2_;
	S32 sequence_;

}SRemote_key;


class device_driver_remote : device_driver {

public:

	device_driver_remote();
	~device_driver_remote();



//from parent
public:

	
private:

	bool toErr(U16 err_code);
	bool onInit();
	void onSpinOnce();

	bool setPara( std::string name , std::string value );
	
	void init_state_machine();
	
	bool check_crc(U8* data,int len);

	SRemote_key remote_data_;
	bool parse_key(U8* data,int len);
	bool parse_ad1(U8* data,int len);
	bool parse_ad2(U8* data,int len);
	

//static 
private:

	
	
};


#endif //_DEVICE_DRIVER_REMOTE_WANGHONGTAO_20180401_