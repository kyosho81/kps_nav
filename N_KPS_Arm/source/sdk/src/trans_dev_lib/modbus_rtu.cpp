#include "trans_dev/trans_dev.h"
#include "Comm/Comm.h"

#include "trans_dev/modbus_rtu.h"

modbus_rtu::modbus_rtu(void)
{
	cComm::load();

	trans_ = 0;

	memset(&read_body_,0,sizeof(SREADBODY));
	memset(&write_body_,0,sizeof(SWRITEBODY));
}

modbus_rtu::~modbus_rtu(void)
{
	cConnPara conn_para;
	trans_->GetPara(conn_para);
	cTransferDevice::DelInstance(conn_para);
	trans_ = 0;
}

bool modbus_rtu::init(std::string str_port)
{
	

	cConnPara conn_para;
	conn_para.m_iType = cConnPara::SERIALPORT ;
	//conn_para_.setDeviceName("ttyUSB0");
	conn_para.setDeviceName(str_port);
	conn_para.nBaud = 115200;
	conn_para.chParity = 'N';
	conn_para.nDataBits = 8;
	conn_para.nStopBits = 1;

	read_body_.dev_ = 0x01;
	write_body_.dev_ = 0x01;

	trans_ = cTransferDevice::GetInstance(conn_para);

	//if (sport_->Init(port_,115200))
	U32 wait = 20;
	if (trans_ )
	{
		while(wait--){

			if (trans_->m_Status.IsOpen())
			{
				std::cout<<"modbus tcp open ok:"<<conn_para.getDeviceName()<<std::endl;
				return true;
			}

			SLEEP(100);
		}


	}
	std::cout<<"modbus rtu open com error:"<<conn_para.getDeviceName()<<std::endl;
	return false;
}

bool modbus_rtu::read_coil( SDI &sdi,U16 add, U16 count)
{
	memset(&sdi,0,sizeof(SDI));
	
	read_body_.fnc_ = 0x01;
	u_16_.data_ = add;
	read_body_.address_[0] = u_16_.byte_[1];
	read_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = count;
	read_body_.count_[0] = u_16_.byte_[1];
	read_body_.count_[1] = u_16_.byte_[0];

	U8 data[8] = {0};
	memcpy(data, &read_body_,6 );
	u_16_.data_ = cComm::CRC16(data,6);
	data[6] = u_16_.byte_[0];
	data[7] = u_16_.byte_[1];
	trans_->WriteData(data,8);


	U8 rdata[40] = {0}; 
	int ibit_len = (count % 8) > 0 ? 1 : 0 ;
	ibit_len += count / 8;
	int ilen = ibit_len + 5;
	trans_->ReadData(rdata,ilen,ilen,1000);
	

	//length error
	if (ilen < 5){
		return false;
	}
	//length error
	if ( (rdata[2] + 5) != ilen){
		return false;
	}

	for ( int i = 0 ; i < count ; ++i){
		int index = i / 8 ;
		U8 data = rdata[ 3 + index];

		sdi.di_[i] = cComm::GetBit(data,i % 8);
		sdi.id_[i] = i;
		sdi.used_++;
	}


	return true;
}

bool modbus_rtu::read_holding_reg(SAI &sai, U16 add, U16 count)
{
	memset(&sai,0,sizeof(SAI));



	return true;
}

bool modbus_rtu::write_mut_coil(U16 add ,SDO sdo)
{
	write_body_.fnc_ = 0x0f;
	u_16_.data_ = add;
	write_body_.address_[0] = u_16_.byte_[1];
	write_body_.address_[1] = u_16_.byte_[0];
	u_16_.data_ = sdo.used_;
	write_body_.count_[0] = u_16_.byte_[1];
	write_body_.count_[1] = u_16_.byte_[0];

	write_body_.byte_cnt_= (sdo.used_ % 8) > 0 ? 1 : 0 ;
	write_body_.byte_cnt_ += sdo.used_ / 8;


	for ( int i = 0 ; i < sdo.used_ ; ++i){
		int index = i / 8 ;
		assert(index < write_body_.byte_cnt_ );
		U8 &tmp = write_body_.data_[ index ];
		if (sdo.do_[i]){
			tmp |= 1<<(i % 8 );
		}else{
			tmp &= ~(1<<(i % 8 ));
		}

	}

	U8 data[100] = {0};
	int i_len = 6 + write_body_.byte_cnt_;
	memcpy(data, &write_body_, i_len);
	u_16_.data_ = cComm::CRC16(data,i_len);
	data[i_len + 0] = u_16_.byte_[0];
	data[i_len + 1] = u_16_.byte_[1];

	trans_->WriteData(data, i_len + 2 );
	
	U8 rdata[40] = {0}; 
	int ilen = 0 ;
	trans_->ReadData(rdata,ilen,5,1000);

	if (ilen == 5){
		return true;
	}
	return false;
}

bool modbus_rtu::write_mut_reg(U16 add, SAO sao)
{
	
	return false;
}
