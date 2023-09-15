#ifndef _DEVICE_DRIVER_WANGHONGTAO_20180401_
#define _DEVICE_DRIVER_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "device_base.h"
//use for data conver
typedef enum{

	CMD_TYPE_DATA_U8,
	CMD_TYPE_DATA_U16,
	CMD_TYPE_DATA_U32,
	CMD_TYPE_DATA_S8,
	CMD_TYPE_DATA_S16,
	CMD_TYPE_DATA_S32,
	CMD_TYPE_DATA_F32

}eCmd_DataType;
//switch state machine check function
typedef enum{

	CMD_TYPE_HEAD,
	CMD_TYPE_CMD,
	CMD_TYPE_DATA,
	CMD_TYPE_CRC

}eCmd_Index_Type;

typedef struct _StateMechine_it 
{
	U8 index_;

	eCmd_DataType data_type_;
	eCmd_Index_Type cmd_index_;

	U8 data_index_;
	U8 data_cmp_;   //use for check data

	U8* data_;
	S16 len_;
	bool b_do_crc_;
	boost::function<bool( U8* data ,int len )> fnc_parse_;
	boost::function<bool( U8* data ,int len )> fnc_crc_;

}StateMechine_it;


// class TransferData{
// 
// public:
// 	TransferData(){};
// 	~TransferData(){};
// 	
// 	U8* data_;
// 	S32 data_len_;
// };

class device_driver : device_base {

public:

	device_driver();
	~device_driver();

	int get_driver_id();
	


//from parent
private:
	bool fnc_init();
	

protected:
	virtual bool setPara( std::string name , std::string value );

	virtual void init_state_machine() = 0;
	void clear_state_machine();
	virtual bool toErr(U16 err_code);
	virtual bool onInit() = 0;
	virtual bool fnc_run();
	virtual void onSpinOnce();
	std::map<int,StateMechine_it> cmd_state_mechine_;
	std::map<int,StateMechine_it>::iterator current_state_;

	bool parse_ste_mechine(U8 data);
	cTransferDevice *pTransferDevice_;

private:

	int driver_id_;

	
	bool init_transfer_device();
	bool fnc_recovery() ;

	cConnPara conn_para_;
	bool      b_is_can_bus_;
	int       i_can_baud_;
	bool       connected_;
	

	
	

	std::vector<std::map<int,StateMechine_it>::iterator> l_parse_it_;
	
	UData_buffer<U8,102400> cmd_buffer_;

//static 
private:

	static int max_driver_id_;
	static int get_all_driver_id();
	

};


#endif //_DEVICE_DRIVER_WANGHONGTAO_20180401_