
#include <stdlib.h>
#include "Comm/Rand.hpp"

#include "trans_dev.h"
#include "Comm.h"
#include <iostream>
#include <fstream>

//
#include "Comm/TimerDiff.h"
#include "trans_dev/can_base.h"
#include "trans_dev/canalyst2.h"
#include "trans_dev/can_tcp.h"
#include "trans_dev/can_socket.h"

int main(int argc, char *argv[])
{
	std::string str_can_type = "can_tcp";
	if (argc > 1){
		str_can_type = argv[1];
	}

	can_base* p_can = 0;
	
	if (str_can_type == "canalyst2"){
		p_can = new canalyst2();
	}else if (str_can_type == "can_tcp"){
		p_can = new can_tcp();
	}else if (str_can_type == "can_socket"){
		p_can = new can_socket();
	}
	
	p_can->init();

	cTimerDiff dt;
	while(1){
	


		std::vector<SCanframe> v_frame;
		p_can->read(0,v_frame);
		auto it = v_frame.begin();
		for ( ; it != v_frame.end() ; ++it ){
			SCanframe &frame(*it);
			std::cout<<"id:"<<frame.can_id_<<" len:"<<frame.len_<<" "<<std::hex;
			for ( int i = 0 ; i < frame.len_ ; ++i ){
				std::cout<<int(frame.data_[i])<<" ";
			}
			std::cout<<std::endl;
		}
		//std::cout<<"-------"<<std::endl;

		SCanframe frame;
		memset(&frame,0,sizeof(SCanframe));
		frame.can_id_= 0x181;
		frame.len_ = 8;
		for ( int i = 0 ; i < frame.len_ ; ++i ){
			frame.data_[i] = i;
		}
		p_can->send(0,frame,1);
		std::cout<<"send data:"<<cComm::ByteToHexString(frame.data_,8)<<std::endl;
	


		dt.ms_loop(1000);
	}
}

