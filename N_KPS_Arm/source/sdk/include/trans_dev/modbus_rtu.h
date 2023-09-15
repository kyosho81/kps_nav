#ifndef _MODBUS_RTU_CLIENT_KYOSHO_20110904_
#define _MODBUS_RTU_CLIENT_KYOSHO_20110904_


#include "robot/RobotStruct.h"
#include "trans_dev.h"

class cTransferDevice;

class modbus_rtu
{


public:


	modbus_rtu(void);
	~modbus_rtu(void);

	bool init(std::string str_port);

	bool read_coil( SDI &sdi, U16 add, U16 count);//0x01
	bool read_holding_reg(SAI &sai, U16 add, U16 count); //0x03


	bool write_mut_coil( U16 add ,SDO sdo ); //0x0f
	bool write_mut_reg(U16 add, SAO sao );//0x10

private:
	union uni_16{
		U8 byte_[2];
		U16 data_;
	} u_16_;

	

	cTransferDevice* trans_;
	
	

	typedef struct _SREADBODY
	{
		U8 dev_;
		U8 fnc_;
		U8 address_[2];
		U8 count_[2];

	}SREADBODY;
	SREADBODY read_body_;

	typedef struct _SWRITEBODY
	{
		U8 dev_;
		U8 fnc_;
		U8 address_[2];
		U8 count_[2];
		U8 byte_cnt_;
		U8 data_[100];
	}SWRITEBODY;
	SWRITEBODY write_body_;

	uni_16 index_;
};
#endif //_MODBUS_RTU_CLIENT_KYOSHO_20110904_
