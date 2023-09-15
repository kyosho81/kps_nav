#include "../Comm/Comm.h"
#include "trans_dev/trans_dev.h"

#include "trans_dev/can_tcp.h"

can_tcp::can_tcp()
{
	cmd_baud_rate_[0] = 0x10;
	cmd_baud_rate_[1] = 0x00;
	cmd_baud_rate_[2] = 0x00;
	cmd_baud_rate_[3] = 0x08;
	cmd_baud_rate_[4] = 0x01;
	cmd_baud_rate_[5] = 0x02;
	cmd_baud_rate_[6] = 0x01;
	cmd_baud_rate_[7] = 0x01;
	cmd_baud_rate_[8] = 0x00;
	cmd_baud_rate_[9] = 0x05;//250k
	cmd_baud_rate_[10] = 0x00;
	cmd_baud_rate_[11] = 0x00;
	cmd_baud_rate_[12] = 0x00;

	
	memset(&cmd_send_,0,13);
	memset(&cmd_read_,0,10240);

	p_tcp_ = 0;
}

can_tcp::~can_tcp()
{
	close_device();
}

bool can_tcp::open_device()
{
	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = "192.168.1.10";
	conn_para.m_nRemotePort = 4001;


	p_tcp_ = cTransferDevice::GetInstance(conn_para);

	if (p_tcp_)
	{
		while(!p_tcp_->m_Status.IsOpen()){
			SLEEP(100);
			std::cout<<"wait tcp can open !!!"<<std::endl;
		}
		
	}


	if(!get_baud_rate( cmd_baud_rate_[9] , baud_rate_)){
		std::cout<<"tcp can baud rate error!"<<baud_rate_<<std::endl;
		return false;
	}
	cmd_baud_rate_[5] = 0x02;
	cmd_baud_rate_[6] = 0x01;
	U8 ch_read[100] = {0};
	int ilen = 0;
	//set baud rate
	p_tcp_->WriteData(cmd_baud_rate_,13);
	p_tcp_->ReadData(ch_read,ilen,13,1000);


	//set enable
	cmd_baud_rate_[5] = 0x0b;
	cmd_baud_rate_[6] = 0x03;
	p_tcp_->WriteData(cmd_baud_rate_,13);
	p_tcp_->ReadData(ch_read,ilen,13,1000);

	th_run_.run_thread(boost::bind(&can_tcp::th_read,this));

	return true;
}

bool can_tcp::close_device()
{

	th_run_.destory_thread();

	if (p_tcp_){
		cConnPara para;
		p_tcp_->GetPara(para);
		if(cTransferDevice::DelInstance(para)){
			p_tcp_ = 0;
		}
	}
	
	
	return true;
}

bool can_tcp::get_baud_rate( U8 &i_baud, S32 baud_rate)
{

 	if(baud_rate == 125000){
 		i_baud = 7;
 	}
 	else if(baud_rate == 250000){
 		i_baud = 5;
 	}
 	else if(baud_rate == 500000){
 		i_baud = 3;
 	}
 	else if(baud_rate == 800000){
 		i_baud = 1;
 	}
 	else if(baud_rate == 1000000){
 		i_baud = 0;
 	}else{
 		return false;
 	}
	return true;
}
bool can_tcp::get_frame(UData_buffer<U8,1024> &cmd_buffer, U8* p_data,int ilen){

	if (!cmd_buffer.put( p_data,ilen)){
		cmd_buffer.clear_data();
		return false;
	}


	char cmd[1024]={0};
	int icmd = 0;
	while ( cmd_buffer.size() > 12){
		if(cmd_buffer.get( (U8*)&cmd, 13)){
			SCanframe frame;
			frame.len_ = cmd[0];
			U8* p = (U8*)&(frame.can_id_);
			p[3] = cmd[1];
			p[2] = cmd[2];
			p[1] = cmd[3];
			p[0] = cmd[4];

			memcpy(frame.data_, cmd + 5, 8);
			if (frame.len_ == 8){
				if (check_rec_can_id(frame.can_id_)){
					can0_list_.put(frame);

					if (fnc_call_back_){
						fnc_call_back_(frame);
					}
				}
			}
		}
		
	}
	return true;
}
bool can_tcp::th_read()
{
	int ilen = 0;
	p_tcp_->ReadData(cmd_read_,ilen,13,10);
	get_frame(cmd_buffer_, cmd_read_, ilen);
	

	SLEEP(20);

	return true;
}
bool can_tcp::send(U32 can_index, SCanframe data, U8 send_type){
	
	
	cmd_send_[0] = data.len_;
	U8* p = (U8*)&(data.can_id_);
	cmd_send_[1] = p[3];
	cmd_send_[2] = p[2];
	cmd_send_[3] = p[1];
	cmd_send_[4] = p[0];

	memcpy(cmd_send_ + 5,data.data_,8);

	p_tcp_->WriteData(cmd_send_,13);

	return true;
}
bool can_tcp::read(U32 can_index, std::vector<SCanframe> &frame_list){

	frame_list.clear();
	if ( can_index == 0 ){
		SCanframe frame;
		while( can0_list_.size() > 0){
			can0_list_.get(frame);
			frame_list.push_back(frame);
		}
		if (frame_list.size() > 0){
			return true;
		}
	}
	return false;
}
