#ifndef _DEVICE_WJ718MINI_KYOSHO_20221027_
#define _DEVICE_WJ718MINI_KYOSHO_20221027_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex2.h"
#include "device/device_laser.h"
#include "trans_dev/trans_dev.h"

#include "sensor/wj718mini/vanjee_718mini_lidar_protocol.h"
//#include "sensor/wj719/wj719_driver.h"

class device_wj718mini : protected device_laser
{
public:

	device_wj718mini();
	~device_wj718mini();

protected:

	bool setPara( std::string name , std::string value );

	
	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	
private:
	void init_filter();
	void fill_pub_data();

	void pub_laser_ex(SLaser_Ex &laser_ex);
	void pub_ref(SReflector &laser_ref);
	void pub_laser_ex_ref(SLaser_Ex_Ref &laser_ex_ref);

	void pub_amcl_laser(float * range, float * intensity, int d_size);

	SReflector laser_ref_;
	SLaser_Ex_Ref laser_ex_ref_;

	laser_filter_ex filter_;
	//SLaser_Ex filter_min_range_;
	void filter_para_reset();
	F32 laser_amcl_resolution_;
	int laser_start_index_;
	int laser_step_;

	bool b_pub_laser_ex_;
	bool b_pub_laser_ex_ref_;
	bool b_pub_ref_;
	bool b_pub_amcl_ref_;

	int scan_frequency_ ;
	int samples_per_scan_ ;

private:
	//driver
// 	wj719_driver* p_wj719_driver_;
// 	int i_last_cnt_;
// 	int i_err_cnt_;
// 	THSafe<int> th_sig_cnt_;
	wj_lidar::Vanjee718MiniLidarProtocol *protocol_net_;

	bool init_transfer_device();

	cTransferDevice* pTransferDevice_;
	cConnPara conn_para_;

	bool       connected_;
	U8* res_;
	int ilen_;

	cTimerDiff dt_;
	U8 XOR_check(U8 *Buf,U8 start,U8 end,U8 len);

private:
	std::ofstream foo_;
	bool save_rec(unsigned char* pReceiveData,int iLen);
};

#endif//_DEVICE_WJ719_KYOSHO_20221027_