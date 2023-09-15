#ifndef _DEVICE_REMOTE_WANGHONGTAO_20180401_
#define _DEVICE_REMOTE_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "key2speed.h"
#include "device_base.h"



class device_remote : device_base {

public:

	device_remote();
	~device_remote();


//from parent
private:
	bool fnc_init();
	bool onInit();
	bool setPara( std::string name , std::string value );
	bool toErr(U16 err_code);
	bool fnc_run();
	bool fnc_recovery() ;

private:

	
	bool init_transfer_device();


	cTransferDevice* pTransferDevice_;
	cConnPara conn_para_;
	
	bool       connected_;

private:
	void state_mathine( U8 data );
	typedef enum{HEAD,KEY,AD1_0,AD1_1,AD2_0,AD2_1,CRC0,CRC1} State;
	State sta_;

	void setKey();
	void setAd();
	

	U8 key_;
	U16 ad_1;
	U16 ad_2;

	SRemote_data data_;
	key2speed key2speed_;

	void cal_speed();
	int continue_set_speed_zero_;

	F32 vx_;
	F32 vw_;
};


#endif //_DEVICE_REMOTE_WANGHONGTAO_20180401_