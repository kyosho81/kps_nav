#ifndef _DEVICE_CHASSIS_WANGHONGTAO_20180401_
#define _DEVICE_CHASSIS_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/TimerDiff.h"
#include "amcl_tf.h"

#include "device/cmd2speed.h"
#include "device/chassis_speed.h"

#include "device/device_base.h"

class Chassis_base;
class Driver_base;

class device_chassis : device_base
{
public:

	device_chassis();
	virtual ~device_chassis();


protected:
	//void pub_laser(const SLaser &laser);

	bool setPara( std::string name , std::string value );
	
	bool fnc_recovery();
	bool onInit();
	bool toErr(U16 err_code) ;

	std::string pub_name_;


private:

	bool fnc_init();
	bool fnc_run() ;

	int  id_sub_speed_;
	bool set_speed(const SSpeed& speed);
	void pub_odom( const SOdomSpeed &odom );
	void init_chassis(Chassis_base* &base,Driver_base* &driver);
	void init_call_back();

	int sub_id_remote_;
	bool set_remote_speed(const SSpeed& speed);
	bool call_back_speed_cmd(const SCmd &scmd);
	//odom pos
private:

	Chassis_base* bchassis ;
	Driver_base* bdriver;

protected:


	SBuffer<SSpeed> set_speed_;
	SBuffer<SSpeed> set_remote_speed_;
	chassis_speed chassis_speed_priority_;

private://bind odom amcl pos
	bool update_init_pos(const SInit_Pos &pos);
	bool s_call_back_amcl(const SPos &amcl_pos);
	bool s_call_back_ref_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool s_call_back_dy_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool s_call_back_imu( const SIMURION &imu);

	std::string chassis_type_;

	amcl_tf tf_odom_amcl_;
	SOdomSpeed odom_speed_;
	boost::mutex mu_odom_amcl_;
	int sub_id_estimate_ ;
	int sub_id_amcl_;
	int sub_id_ref_loc_;
	int sub_id_dynamic_loc_;
	int sub_id_imu_;

	cmd2speed cmd2speed_;
};

#endif //_DEVICE_CHASSIS_WANGHONGTAO_20180401_