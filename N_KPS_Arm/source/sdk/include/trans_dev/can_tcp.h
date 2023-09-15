#ifndef _CAN_TCP_KYOSHO_20110903_
#define _CAN_TCP_KYOSHO_20110903_


#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "canalyst2/controlcan.h"
#include "trans_dev/can_base.h"

class cTransferDevice;

class can_tcp : public can_base
{
public:
	can_tcp();
	~can_tcp();

	bool send(U32 can_index, SCanframe data, U8 send_type);
	bool read(U32 can_index, std::vector<SCanframe> &frame_list);

protected:
private:


	bool open_device();
	bool close_device();

	bool get_baud_rate( U8 &i_baud, S32 baud_rate);

	bool get_frame(UData_buffer<U8,1024> &cmd_buffer, U8* p_data,int ilen);
	pattern_thread th_run_;
	bool th_read();

	cTransferDevice* p_tcp_;

	U8 cmd_baud_rate_[13];
	U8 cmd_send_[13];

	U8 cmd_read_[10240];
	UData_buffer<U8,1024> cmd_buffer_;
};



#endif //_CAN_TCP_KYOSHO_20110903_
