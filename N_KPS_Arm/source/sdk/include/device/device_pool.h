#ifndef _DEVICE_POOL_WANGHONGTAO_20180401_
#define _DEVICE_POOL_WANGHONGTAO_20180401_

#include <string>
#include <map>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "device/device_para.h"
//#include "device/device_lms1xx.h"

class device_base;
class device_para;

class device_pool
{
public:

	device_pool();
	~device_pool();

	bool create_sick_1xx( const std::string &name, const std::string &para );
	bool create_laser_rp( const std::string &name, const std::string &para );
	bool create_laser_tim( const std::string &name, const std::string &para );
	bool create_laser_sim( const std::string &name, const std::string &para );

	bool create_laser(const std::string str_laser_type, std::string para);
	bool create_laser( const Laser_type &type, std::string para );

	
	bool create_chassis( const std::string &name, const std::string &para );
	bool create_rion_imu(const std::string &name, const std::string &para);
	bool create_remote(const std::string &name, const std::string &para);
	bool create_433_key(const std::string &name, const std::string &para);
	bool create_amcl(const std::string &name, const std::string &para);
	void create_data_server(const std::string &name, const std::string &para);
	void create_dynamic_para(const std::string &name,const std::string &para);
	bool create_log_play(const std::string &name,const std::string &para);
	bool create_reflector_sim(const std::string &name,const std::string &para);
	bool create_reflector_loc(const std::string &name,const std::string &para);
	bool create_laser_matcher( const std::string &name, const std::string &para );
	bool create_log_bag( const std::string &name, const std::string &para );
	//bool create_dio( const std::string &name, const std::string &para );
	bool create_dynamic_loc( const std::string &name, const std::string &para );

	void pub_all_device();
	bool destruct_all();

	void destruct_laser();

	SLaser_para get_laser_para(const bool &b_reflash = false);
	SMap_para get_map_para();

	bool set_dev_para(std::string str_dev_name, std::string str_para);

protected:

private:
	bool destruct(const std::string &name);
	
	bool add_new_device(std::string name , device_base* p_dev_base);
	std::map< std::string , device_base* > m_all_device_;

	
	device_para* get_all_device_para();
	
	device_base* get_dev(std::string str_dev_name);

	device_para* all_device_para_;
};


typedef boost::serialization::singleton<device_pool> Singleton_Device_Pool;

#endif//_DEVICE_POOL_WANGHONGTAO_20180401_