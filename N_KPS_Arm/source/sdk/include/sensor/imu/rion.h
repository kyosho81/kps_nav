/*
 * rion.h
 *
 ***************************************************************************/

#ifndef _IMU_RS232_RION_H_
#define _IMU_RS232_RION_H_

#include "buffer_con.hpp"

class cTransferDevice;

class rion_imu
{
public:

	rion_imu();
	~rion_imu();

	
	bool init();
	bool get_imu(SIMURION &data);

protected:
private:

	void connect( std::string port );

	void disconnect();

	
	
	bool connected_;
	cTransferDevice* pTransDevice_;

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
	CSBuffer<SIMURION,10> real_imu_;

	U8 ch_data[20];
	U8 crc8_;
private:
	THSafe<bool> th_over_;
	bool b_run_;
	CSBuffer<int,1> th_state_thread_run_;

	void init_th();
	void th_run();
};



#endif//_IMU_RS232_RION_H_
