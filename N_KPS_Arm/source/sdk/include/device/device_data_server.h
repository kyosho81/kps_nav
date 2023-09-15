#ifndef _DEVICE_DATA_SERVER_WANGHONGTAO_20180401_
#define _DEVICE_DATA_SERVER_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/TimerDiff.h"

#include "device/device_trans_pub.h"

#include "device/device_base.h"


class device_data_server : device_base
{
public:

	device_data_server();
	virtual ~device_data_server();
	bool onInit();

protected:
	//void pub_laser(const SLaser &laser);

	virtual bool setPara( std::string name , std::string value );
	
	bool fnc_recovery();
	bool toErr(U16 err_code);


private:

	bool fnc_init();
	bool fnc_run() ;



	void init_call_back();
	

	device_trans_pub trans_pub_;

	int sub_id_laser_;
	int sub_id_odom_;
	int sub_id_amcl_;
	int sub_id_particle_;
	int sub_id_reflector_;
	int sub_id_ref_loc_;
	int sub_id_dynamic_loc_;

	int sub_id_laser_ex_;
	int sub_id_laser_ex_ref_;
	int sub_id_laser_ex_cab_;
	int sub_id_amcl_confidence_;

protected:

	

};

#endif //_DEVICE_DATA_SERVER_WANGHONGTAO_20180401_