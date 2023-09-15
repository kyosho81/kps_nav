#ifndef _DEVICE_433_KEY_WANGHONGTAO_20180401_
#define _DEVICE_433_KEY_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "key2speed.h"
#include "device_base.h"



class device_433_key : device_base {

public:

	device_433_key();
	~device_433_key();


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
	typedef enum{HEAD,CODE,LEN,DATA_0,DATA_1,CRC0,CRC1} State;
	State sta_;

	void setKey();

	U8 data_[7];
	U32 key_forward_;
	U32 key_backward_;
	U32 key_left_;
	U32 key_right_;
	U32 key_stop_;
	U32 key_begin_;
	U32 key_emergency_;
	U32 key_nop_;
	bool b_run_;

	void cal_speed();
	int continue_set_speed_zero_;

	SSpeed set_speed_;

	F32 tar_vx_;
	F32 tar_vy_;
	F32 tar_vw_;

	cTimerDiff dt_;
	F32 fdt_;
};


#endif //_DEVICE_433_KEY_WANGHONGTAO_20180401_