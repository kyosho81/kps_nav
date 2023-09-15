#include "trans_dev/trans_dev.h"
#include "Comm/Comm.h"

#include "trans_dev/modbus_tcp.h"

modbus_tcp_clt::modbus_tcp_clt(void)
{
	cComm::load();

	trans_ = 0;
	index_.data_ = 0;
	memset(&u_head_,0,sizeof(u_head_));
	memset(&read_body_,0,sizeof(SREADBODY));
	memset(&write_body_,0,sizeof(SWRITEBODY));
}

modbus_tcp_clt::~modbus_tcp_clt(void)
{
	cConnPara conn_para;
	trans_->GetPara(conn_para);
	cTransferDevice::DelInstance(conn_para);
	trans_ = 0;
}

bool modbus_tcp_clt::init(std::string str_ip, int i_port)
{
	u_head_.s_head.index_.data_ = 0;
	u_head_.s_head.proto_.data_ = 0;
	u_head_.s_head.length_.data_ = 0;
	u_head_.s_head.address_ = 0xff;

	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = str_ip;
	conn_para.m_nRemotePort = i_port;

	trans_ = cTransferDevice::GetInstance(conn_para);

	//if (sport_->Init(port_,115200))
	U32 wait = 20;
	if (trans_ )
	{
		while(wait--){

			if (trans_->m_Status.IsOpen())
			{
				std::cout<<"modbus tcp open ok:"<<str_ip<<" port:"<<i_port<<std::endl;
				return true;
			}

			SLEEP(100);
		}


	}
	std::cout<<"modbus tcp open error:"<<str_ip<<" port:"<<i_port<<std::endl;
	return false;
}

bool modbus_tcp_clt::read_coil( SDI &sdi,U16 add, U16 count)
{
	memset(&sdi,0,sizeof(SDI));
	
	index_.data_++;
	u_head_.s_head.index_.byte_[0] = index_.byte_[1];
	u_head_.s_head.index_.byte_[1] = index_.byte_[0];
	
	u_16_.data_ = 6;
	u_head_.s_head.length_.byte_[0] = u_16_.byte_[1];
	u_head_.s_head.length_.byte_[1] = u_16_.byte_[0];
	
	//set func add count
	read_body_.fnc_ = 0x01;
	u_16_.data_ = add;
	read_body_.address_[0] = u_16_.byte_[1];
	read_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = count;
	read_body_.count_[0] = u_16_.byte_[1];
	read_body_.count_[1] = u_16_.byte_[0];

	U8 data[12] = {0};
	memcpy(data, u_head_.byte_head_,7 );
	memcpy(data + 7, &read_body_,5 );

	trans_->WriteData(data,12);
	U8 rdata[40] = {0}; 
	int ibit_len = (count % 8) > 0 ? 1 : 0 ;
	ibit_len += count / 8;
	int ilen = ibit_len + 9;
	trans_->ReadData(rdata,ilen,ilen,1000);

	//length error
	if (ilen < 8){
		return false;
	}
	//length error
	if ( (rdata[5] + 7 -1) != ilen){
		return false;
	}

	assert(count <= MAX_DI);

	for ( int i = 0 ; i < count ; ++i){
		int index = i / 8 ;
		U8 data = rdata[ 9 + index];

		sdi.di_[i] = cComm::GetBit(data,i % 8);
		sdi.id_[i] = i;
		sdi.used_++;
	}

	return true;
}

bool modbus_tcp_clt::read_holding_reg(SAI &sai, U16 add, U16 count)
{
	memset(&sai,0,sizeof(SAI));

	index_.data_++;
	u_head_.s_head.index_.byte_[0] = index_.byte_[1];
	u_head_.s_head.index_.byte_[1] = index_.byte_[0];

	u_16_.data_ = 6;
	u_head_.s_head.length_.byte_[0] = u_16_.byte_[1];
	u_head_.s_head.length_.byte_[1] = u_16_.byte_[0];

	//set func add count
	read_body_.fnc_ = 0x03;
	u_16_.data_ = add;
	read_body_.address_[0] = u_16_.byte_[1];
	read_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = count;
	read_body_.count_[0] = u_16_.byte_[1];
	read_body_.count_[1] = u_16_.byte_[0];

	U8 data[12] = {0};
	memcpy(data, u_head_.byte_head_,7 );
	memcpy(data + 7, &read_body_,5 );

	trans_->WriteData(data,12);
	U8 rdata[40] = {0}; 
	int ilen = 9 + count*2;
	trans_->ReadData(rdata,ilen,ilen,1000);

	//length error
	if (ilen < 8){
		return false;
	}
	//length error
	if ( (rdata[5] + 7 - 1) != ilen){
		return false;
	}

	//address back error
	if (rdata[7] != add ){
		return false;
	}

	for ( int i = 0 ; i < count ; ++i){

		sai.id_[i] = i;
		sai.used_++;

		uni_16 u16_data;
		u16_data.byte_[0] = rdata[ 9 + i*2 + 1 ];
		u16_data.byte_[1] = rdata[ 9 + i*2 + 0 ];
		sai.ai_[i] = u16_data.data_;
	}

	return true;
}

bool modbus_tcp_clt::write_mut_coil(U16 add ,SDO sdo)
{
	if (sdo.used_ == 0 ){
		return false;
	}

	index_.data_++;
	u_head_.s_head.index_ = index_;
	

	//set func add count
	memset(&write_body_,0,sizeof(SWRITEBODY));
	write_body_.fnc_ = 0x0f;
	u_16_.data_ = add;
	write_body_.address_[0] = u_16_.byte_[1];
	write_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = sdo.used_;
	write_body_.count_[0] = u_16_.byte_[1];
	write_body_.count_[1] = u_16_.byte_[0];

	write_body_.byte_cnt_= (sdo.used_ % 8) > 0 ? 1 : 0 ;
	write_body_.byte_cnt_ += sdo.used_ / 8;

	int i_max_index = -1;

	for ( int i = 0 ; i < sdo.used_ ; ++i){

		int index = (sdo.id_[i]);
		if (i_max_index < index){
			i_max_index = index;
		}
		index /= 8;
		//assert(index < write_body_.byte_cnt_ );
		U8 &tmp = write_body_.data_[ index ];
		if (sdo.do_[i]){
			tmp |= 1<<(i % 8 );
		}else{
			tmp &= ~(1<<(i % 8 ));
		}
		
	}


	write_body_.byte_cnt_= (i_max_index % 8) > 0 ? 1 : 0 ;
	write_body_.byte_cnt_ += i_max_index / 8;

	u_16_.data_ =  7 + write_body_.byte_cnt_;
	u_head_.s_head.length_.byte_[0] = u_16_.byte_[1];
	u_head_.s_head.length_.byte_[1] = u_16_.byte_[0];

	U8 data[100] = {0};

	memcpy(data, u_head_.byte_head_,7 );
	memcpy(data + 7, &write_body_, 6 + write_body_.byte_cnt_);


	trans_->WriteData(data, 7 + 6 + write_body_.byte_cnt_);
	U8 rdata[40] = {0}; 
	int ilen = 0 ;
	trans_->ReadData(rdata,ilen,14,1000);

	if (ilen == 14){
		return true;
	}
	return false;
}

bool modbus_tcp_clt::write_mut_reg(U16 add, SAO sao)
{
	index_.data_++;
	u_head_.s_head.index_ = index_;


	//set func add count
	memset(&write_body_,0,sizeof(SWRITEBODY));
	write_body_.fnc_ = 0x10;
	u_16_.data_ = add;
	write_body_.address_[0] = u_16_.byte_[1];
	write_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = sao.used_;
	write_body_.count_[0] = u_16_.byte_[1];
	write_body_.count_[1] = u_16_.byte_[0];

	write_body_.byte_cnt_= sao.used_*2;

	
	for ( int i = 0 ; i < sao.used_ ; ++i){
		
		uni_16 u16_data;
		u16_data.data_ = sao.ao_[i];
		
		write_body_.data_[ i*2 + 0 ] = u16_data.byte_[1];
		write_body_.data_[ i*2 + 1 ] = u16_data.byte_[0];

	}
	u_16_.data_ =  7 + write_body_.byte_cnt_;
	u_head_.s_head.length_.byte_[0] = u_16_.byte_[1];
	u_head_.s_head.length_.byte_[1] = u_16_.byte_[0];
	
	
	U8 data[100] = {0};
	memcpy(data, u_head_.byte_head_,7 );
	memcpy(data + 7, &write_body_, 6 + write_body_.byte_cnt_);


	trans_->WriteData(data, 7 + 6 + write_body_.byte_cnt_);
	U8 rdata[40] = {0}; 
	int ilen = 0 ;
	trans_->ReadData(rdata,ilen,12,1000);

	if (ilen == 12){
		return true;
	}
	return false;
}
