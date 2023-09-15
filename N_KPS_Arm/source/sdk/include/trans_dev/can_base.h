#ifndef _CAN_DEVICE_BASE_KYOSHO_20110903_
#define _CAN_DEVICE_BASE_KYOSHO_20110903_


#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Comm/buffer_con.hpp"
#include "Comm/pattern_thread.h"

class can_base
{
public:
	can_base();
	~can_base();

	bool init( S32 baud_rate = 500000 );
	virtual bool reset_driver();

	bool bind_rec(boost::function<int(const SCanframe &frame )> fnc_call_back);

	virtual bool send(U32 can_index, SCanframe data, U8 send_type) = 0;
	virtual bool send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type);
	virtual bool read(U32 can_index, std::vector<SCanframe> &frame_list) = 0;
	
	bool set_rec_can_id(std::string str_can_id);
	void set_rec_can_id(std::map<U32,int> m_can_id);
	int get_rec_can_id(std::map<U32,int> &m_can_id );

protected:

	
	bool check_rec_can_id( U32 i_can_id );
	
	std::map<U32,int> m_can_id_;

	virtual bool open_device() = 0;
	virtual bool close_device() = 0;
	

	CSBuffer<SCanframe,100> can0_list_;
	CSBuffer<SCanframe,100> can1_list_;

	S32 baud_rate_;

	boost::function<int(const SCanframe &frame )> fnc_call_back_;


};



#endif //_CAN_DEVICE_BASE_KYOSHO_20110903_
