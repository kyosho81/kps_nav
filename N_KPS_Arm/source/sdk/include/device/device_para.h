#ifndef _DEVICE_PARA_WANGHONGTAO_20180401_
#define _DEVICE_PARA_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/TimerDiff.h"
#include "Comm/buffer_con.hpp"

#include "device/device_base.h"

typedef struct _SMap_para 
{
	std::string map_path_;
	std::string map_name_;
	std::string current_map_;
	std::vector<std::string> m_map_list_;

}SMap_para;


class device_para : device_base
{
public:

	device_para();
	virtual ~device_para();

	SLaser_para get_laser_para();
	SMap_para get_map_para();
	

	bool onInit();

protected:
	//void pub_laser(const SLaser &laser);

	virtual bool setPara( std::string name , std::string value );
	
	bool fnc_recovery();
	bool toErr(U16 err_code);



private:

	bool fnc_init();
	bool fnc_run() ;
	
	
	void load_para();
	void load_laser_para();
	void load_map_para();

	THSafe<SLaser_para> laser_para_;
	THSafe<SMap_para> map_para_;

protected:


};

#endif //_DEVICE_PARA_WANGHONGTAO_20180401_