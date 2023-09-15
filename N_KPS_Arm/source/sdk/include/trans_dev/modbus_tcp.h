#ifndef _MODBUS_TCP_CLIENT_KYOSHO_20110904_
#define _MODBUS_TCP_CLIENT_KYOSHO_20110904_


#include "robot/RobotStruct.h"
#include "trans_dev.h"

class cTransferDevice;

class modbus_tcp_clt
{


public:


	modbus_tcp_clt(void);
	~modbus_tcp_clt(void);

	bool init(std::string str_ip, int i_port);

	bool read_coil( SDI &sdi, U16 add, U16 count);//0x01
	bool read_holding_reg(SAI &sai, U16 add, U16 count); //0x03


	bool write_mut_coil( U16 add ,SDO sdo ); //0x0f
	bool write_mut_reg(U16 add, SAO sao );//0x10

private:
	union uni_16{
		U8 byte_[2];
		U16 data_;
	} u_16_;

	typedef struct _STCPHEAD
	{
		uni_16 index_;
		uni_16 proto_;
		uni_16 length_;
		U8 address_;

	}SSTCPHEAD;

	cTransferDevice* trans_;
	
	union u_head{
		U8 byte_head_[7];
		SSTCPHEAD  s_head;
	} u_head_;
	


	typedef struct _SREADBODY
	{
		U8 fnc_;
		U8 address_[2];
		U8 count_[2];

	}SREADBODY;
	SREADBODY read_body_;

	typedef struct _SWRITEBODY
	{
		U8 fnc_;
		U8 address_[2];
		U8 count_[2];
		U8 byte_cnt_;
		U8 data_[100];
	}SWRITEBODY;
	SWRITEBODY write_body_;

	uni_16 index_;
};
#endif //_MODBUS_TCP_CLIENT_KYOSHO_20110904_
