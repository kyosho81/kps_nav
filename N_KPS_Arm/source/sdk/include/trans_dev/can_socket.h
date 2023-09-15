#ifndef _CAN_SOCKET_KYOSHO_20110903_
#define _CAN_SOCKET_KYOSHO_20110903_


#include <iostream>
#include <string>
#include <map>
#include <vector>


#include "trans_dev/can_base.h"

#ifndef WIN32

#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <aio.h>
#include <signal.h>
#endif

class cTransferDevice;

class can_socket : public can_base
{
public:
	can_socket();
	~can_socket();

	bool send(U32 can_index, SCanframe data, U8 send_type);
	bool send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type);
	bool read(U32 can_index, std::vector<SCanframe> &frame_list);

	
protected:
private:
	void fnc_read(SCanframe frame);

	bool open_device();
	bool close_device();

	int sock_;
	U8* rec_;
	//CSBuffer<SCanframe,100> can0_list_;
	static boost::mutex mu_rec_;
	static std::map<int,boost::function<void(SCanframe)>> m_fnc_;
#ifdef WIN32
	void read_callback(int sigval);
#else
	static void read_callback(sigval_t sigval);

	struct aiocb m_aiocb_;

#endif
};



#endif //_CAN_SOCKET_KYOSHO_20110903_
