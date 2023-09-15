#ifndef _DEVICE_BAG_WANGHONGTAO_20180401_
#define _DEVICE_BAG_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/TimerDiff.h"

#include "device/device_base.h"

class device_bag : device_base
{
public:

	device_bag();
	virtual ~device_bag();

protected:
	//void pub_laser(const SLaser &laser);

	virtual bool setPara( std::string name , std::string value );
	
	bool fnc_recovery();
	bool toErr(U16 err_code);


private:

	bool fnc_init();
	bool fnc_run() ;
	bool onInit();


	void init_call_back();
	

	int sub_id_laser_;
	int sub_id_odom_;
	int sub_id_estimate_;

	
protected:


};

#endif //_DEVICE_BAG_WANGHONGTAO_20180401_