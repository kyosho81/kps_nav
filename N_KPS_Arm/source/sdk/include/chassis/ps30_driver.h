#ifndef _CHASSIS_PS30_DRIVER_20190911_H_
#define _CHASSIS_PS30_DRIVER_20190911_H_

#include "Comm/buffer_con.hpp"
#include "driver_base.h"
#include "trans_dev.h"

class cTransferDevice;

class ps30_driver : Driver_base
{
public:
	ps30_driver();
	~ps30_driver();


protected:

private://virtual

	void setPara(std::string name ,std::string value);
	bool open_transfer_device();
	bool init_driver();
	void close_driver();

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);
	F32 getDiffAngle(int id);

 	void setAngle(int id,F32 rad_angle);
 	F32 getAngle(int id);

private:
	void SendData( U8* s_data,U16 len );
	void ReadData( U8* r_data,int &len,int need );

	bool Sendspeed();
	void Readspeedodmo();

private:
	cConnPara conn_para_;
	cTransferDevice* pTrans_;
	std::string strIP_;
	std::string port_;

	F32 S_Vx_;
	F32 S_Vy_;
	F32 S_Vw_;

	F32 C_vx_;
	F32 C_vy_;
	F32 C_vw_;
// 	F32 X_;
// 	F32 Y_;
// 	F32 W_;
	F32 X_last_;
	F32 Y_last_;
	F32 W_last_;
	double X_dete_;
	double Y_dete_;
	double W_dete_;
	
	bool first_read_;

	F32 ms_communicate_;

	bool b_run_;
	void th_run();
	THSafe<SOdomSpeed> th_odom_;
	THSafe<SPos> th_pos_;
};



#endif//_CHASSIS_PS30_DRIVER_20190911_H_
