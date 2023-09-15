#ifndef _CANALYST2_KYOSHO_20110903_
#define _CANALYST2_KYOSHO_20110903_


#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "canalyst2/controlcan.h"
#include "trans_dev/can_base.h"

class canalyst2 : public can_base
{
public:
	canalyst2();
	~canalyst2();

	bool send(U32 can_index, SCanframe data, U8 send_type);
	bool send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type);
	bool read(U32 can_index, std::vector<SCanframe> &frame_list);

protected:
private:


	bool open_device();
	bool close_device();
	bool reset_driver();

	bool get_baud_rate( U8 &t0 , U8 &t1, S32 baud_rate);

	pattern_thread th_run_;
	bool th_read();

	

	VCI_CAN_OBJ rec_data0_[2100];
	VCI_CAN_OBJ rec_data1_[2100];

	boost::mutex mu_rw_0_;
	boost::mutex mu_rw_1_;
};



#endif //_CAN_DEVICE_BASE_KYOSHO_20110903_
