#ifndef _DEVICE_IMU_RION_WANGHONGTAO_20191201_
#define _DEVICE_IMU_RION_WANGHONGTAO_20191201_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "trans_dev/trans_dev.h"

class device_imu_rion : device_base
{
public:

	device_imu_rion();
	~device_imu_rion();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();
	
	bool fnc_init();

	bool fnc_recovery();

	bool fnc_to_err();

private:
	
	bool onInit();
	bool toErr(U16 err_code);


	
private:
	void init_call_back();
	bool s_init_pos(const SInit_Pos &pos );
	int sub_id_estimate_;


private:

	void connect( std::string port );

	void disconnect();



	bool connected_;
	cTransferDevice* pTransDevice_;
	cConnPara conn_para_;

private:
	typedef enum{
		EIMU_HEAD,
		EIMU_LEN,
		EIMU_ADD,
		EIMU_CMD,
		EIMU_W1,
		EIMU_W2,
		EIMU_W3,
		EIMU_ACC1,
		EIMU_ACC2,
		EIMU_ACC3,
		EIMU_YAW1,
		EIMU_YAW2,
		EIMU_YAW3,
		EIMU_CRC
	}eIMU_sm;

	eIMU_sm sm_;
	//dot decimal point position 100=0.01 10=0.001
	F32 tobcd( U8* data, int ilen, F32 dot);
	void parse();
	void state_machine(U8 data);
	unsigned char* buf_all_;
	//CSBuffer<SIMURION,10> real_imu_;

	U8 ch_data[20];
	U8 crc8_;
};

#endif//_DEVICE_IMU_RION_WANGHONGTAO_20191201_
