#ifndef _CHASSIS_DRIVER_BASE_WANGHONGTAO_2015_09_17_
#define _CHASSIS_DRIVER_BASE_WANGHONGTAO_2015_09_17_

#include "MyDefine.h"
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"

class Driver_base
{
public:
	Driver_base();
	~Driver_base();

	
	bool init(std::string para);
	virtual void close_driver() = 0;
	virtual bool reset();

	//set speed RPM
	virtual void setRPM(int id,F32 v) = 0;
	virtual F32 getSpeed( int id ) = 0;

	//percent of wheel turn angle 360 deg = 100%
	virtual F32 getDiffAngle(int id) = 0;
	virtual F32 getDiffAngle(int id,const S32 &pos);

	//set angle (rad)
	virtual void setAngle(int id,F32 rad_angle);
	virtual F32 getAngle(int id);
	virtual void setTargetAngle(int id,F32 rad_angle);

	virtual void setAmclPos(const SPos &pos);
	virtual bool getAmclPos(SPos &pos);

	//set customized para
	virtual void setPara(std::string name ,std::string value) = 0 ;

	void set_dio(const SDI &dio);

	void set_Ref_pos(const SPOS_CONFIDENCE &confidence_pos);
	void set_dy_pos(const SPOS_CONFIDENCE &confidence_pos);
protected://init transfer device , set para


	virtual bool open_transfer_device() = 0;
	virtual bool init_driver() = 0;
	virtual bool reset_driver();

	//THSafe<SPos> amcl_pos_;
	SBuffer<SPos> ls_amcl_pos_;

	boost::mutex mu_dio_;
	SDI extern_dio_;						 //extern io
	THSafe<SPOS_CONFIDENCE> conf_ref_pos_;
	SBuffer<SPos> ls_dynamic_pos_;
};


#endif//_CHASSIS_DRIVER_BASE_WANGHONGTAO_2015_09_17_
