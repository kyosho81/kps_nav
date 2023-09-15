

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#include <stdlib.h>
#include "Comm/Rand.hpp"

#include "trans_dev.h"
#include "Comm.h"
#include "interface/interface_def.h"

#include <iostream>
#include <fstream>

bool brun = true;
#define  LEN_MAX 1024

void shutdown(int sig)
{

	std::cout<<"shutdown process"<<std::endl;

	brun = false;
	return;
}

void test_get_map(U8* read,int &ilen){

	un_U16 cmd_temp;
	cmd_temp.udata_ = CMD_GET_MAP;
	read[0] = cmd_temp.ch_data_[0];
	read[1] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = CMD_HEAD_CRC;
	read[2] = cmd_temp.ch_data_[0];
	read[3] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = cComm::CRC16(read,4);
	read[4] = cmd_temp.ch_data_[0];
	read[5] = cmd_temp.ch_data_[1];
	ilen = CMD_HEAD_CRC;

}

void test_get_status(U8* read,int &ilen)
{
	un_U16 cmd_temp;
	cmd_temp.udata_ = CMD_GET_STATUS;
	read[0] = cmd_temp.ch_data_[0];
	read[1] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = CMD_HEAD_CRC;
	read[2] = cmd_temp.ch_data_[0];
	read[3] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = cComm::CRC16(read,4);
	read[4] = cmd_temp.ch_data_[0];
	read[5] = cmd_temp.ch_data_[1];
	ilen = CMD_HEAD_CRC;
}
void test_get_pos(U8* read,int &ilen){

	un_U16 cmd_temp;
	cmd_temp.udata_ = CMD_GET_POS;
	read[0] = cmd_temp.ch_data_[0];
	read[1] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = CMD_HEAD_CRC;
	read[2] = cmd_temp.ch_data_[0];
	read[3] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = cComm::CRC16(read,4);
	read[4] = cmd_temp.ch_data_[0];
	read[5] = cmd_temp.ch_data_[1];
	ilen = CMD_HEAD_CRC;

}
void test_init_pos(U8* read,int &ilen,const F32 &x,const F32 &y,const F32 &a)
{
	un_U16 cmd_temp;
	cmd_temp.udata_ = CMD_INIT_POS;
	read[0] = cmd_temp.ch_data_[0];
	read[1] = cmd_temp.ch_data_[1];

	cmd_temp.udata_ = INIT_POS_LEN;
	read[2] = cmd_temp.ch_data_[0];
	read[3] = cmd_temp.ch_data_[1];

	memcpy(read + 4 , &x, sizeof(F32));
	memcpy(read + 8 , &y, sizeof(F32));
	memcpy(read + 12 , &a, sizeof(F32));

	cmd_temp.udata_ = cComm::CRC16(read,16);
	read[16] = cmd_temp.ch_data_[0];
	read[17] = cmd_temp.ch_data_[1];
	ilen = INIT_POS_LEN;
}
void test_set_map(U8* read,int &ilen,const std::string &str_map)
{
	un_U16 cmd_temp;
	cmd_temp.udata_ = CMD_INIT_MAP;
	read[0] = cmd_temp.ch_data_[0];
	read[1] = cmd_temp.ch_data_[1];


	int ilen_map = str_map.length();
	ilen = ilen_map + CMD_HEAD_CRC ;

	cmd_temp.udata_ = ilen;
	read[2] = cmd_temp.ch_data_[0];
	read[3] = cmd_temp.ch_data_[1];

	memcpy(read + 4 , str_map.c_str() ,ilen_map);

	cmd_temp.udata_ = cComm::CRC16( read,ilen_map + 4);
	read[ilen_map + 4] = cmd_temp.ch_data_[0];
	read[ilen_map + 5] = cmd_temp.ch_data_[1];
	
}
int main(int argc, char *argv[])
{
	

	std::string strPort = "COM2";
	std::cout<<"serial port :"<<strPort<<std::endl;

	int ibaud = 115200;
	std::cout<<"serial port baud:"<<ibaud<<std::endl;

	cConnPara conn_para2;
	conn_para2.m_iType = cConnPara::SERIALPORT;
	conn_para2.setDeviceName(strPort);
	conn_para2.nBaud = ibaud;
	conn_para2.chParity = 'N';
	conn_para2.nDataBits = 8;
	conn_para2.nStopBits = 1;
	conn_para2.b_rs485 = false;

	cTransferDevice* pSerialPort = cTransferDevice::GetInstance(conn_para2);

	if (pSerialPort)
	{
		while(!pSerialPort->m_Status.IsOpen()){
			 SLEEP(100);
			 std::cout<<"port open err!"<<std::endl;
		}
	}


	U8 read[LEN_MAX] = {0};
	int len = 0;


	//test_get_map(read,len);
	

	while(brun){

		if(!pSerialPort->m_Status.IsOpen()){
			break;
		}
		std::string str = "";
		
		std::getline(std::cin,str);

		if( "l" == str ){
			test_get_map(read,len);
			pSerialPort->WriteData(read,len);
			len = 0;
			pSerialPort->ReadData(read,len,300,1000);
			U8* data = new U8[len - 5];
			memset(data,0,len-5);
			memcpy(data,read + 4 , len -6);
			std::string str_map = (char*)data;
			std::cout<<"map list:"<<str_map<<std::endl;
		}else if( "s" == str ){
			test_get_status(read,len);
			pSerialPort->WriteData(read,len);
			len = 0;
			pSerialPort->ReadData(read,len,300,1000);
			if (len == 6)
			{
				std::cout<<"init err no amcl status!"<<std::endl;
			}else{
				int idev = (len - 6) / 3;
				std::map<int,SPubDevStatus> m_dev;
				SPubDevStatus dev;
				for ( int i = 0 ; i < idev ; ++i )
				{
					
					dev.dev_status_.device_id_ =  *(read + 4 + i*3 + 0);
					dev.dev_status_.status_ =  *(read + 4 + i*3 + 1);
					dev.dev_status_.err_code_ =  *(read + 4 + i*3 + 2);
					m_dev[dev.dev_status_.device_id_] = dev;
				}
				std::map<int,SPubDevStatus>::iterator it = m_dev.find(3);
				if ( it != m_dev.end() )
				{
					SPubDevStatus &dev2(it->second);
					std::cout<<"amcl dev id:"<<int(dev2.dev_status_.device_id_)<<" status:"<<int(dev2.dev_status_.status_)<<" errcode:"<<int(dev2.dev_status_.err_code_)<<std::endl;
				}
				

			}
			
		}else if( "p" == str ){
			test_get_pos(read,len);
			pSerialPort->WriteData(read,len);
			len = 0;
			pSerialPort->ReadData(read,len,CMD_HEAD_CRC + 12,1000);
			if (len == 6)
			{
				std::cout<<"init err no amcl status!"<<std::endl;
			}else{
				F32 x = 0 ; 
				F32 y = 0 ;
				F32 a = 0 ;
				memcpy(&x,read + 4 ,sizeof(F32) );
				memcpy(&y,read + 8 ,sizeof(F32) );
				memcpy(&a,read + 12 ,sizeof(F32) );
				std::cout<<"robot pos x:"<<x<<" y:"<<y<<" a:"<<a<<std::endl;
			}
		}else{
			std::vector<std::string> vlist;
			cComm::SplitString(str," ",vlist);

			if (vlist.size() == 4)
			{
				if( vlist[0] == "i"){
					F32 x = 0;
					F32 y = 0;
					F32 a = 0;
					cComm::ConvertToNum(x,vlist[1]);
					cComm::ConvertToNum(y,vlist[2]);
					cComm::ConvertToNum(a,vlist[3]);
					test_init_pos(read,len,x,y,a);
					pSerialPort->WriteData(read,len);
					len = 0;
					pSerialPort->ReadData(read,len,6,1000);
					std::cout<<"init pos rec:"<<cComm::ByteToHexString(read,len)<<std::endl;
				} 

			}else if (vlist.size() == 2)
			{
				if( vlist[0] == "m"){
					test_set_map(read,len,vlist[1]);
					pSerialPort->WriteData(read,len);
					len = 0;
					pSerialPort->ReadData(read,len,6,1000);
					std::cout<<"set map rec:"<<cComm::ByteToHexString(read,len)<<std::endl;
				}
			}
		}

// 		U8 send[26] ;
// 		U32 slen = 26;
// 		for (int i = 0 ; i < slen ; ++i)
// 		{
// 			send[i] = i ;
// 		}
// 		pSerialPort->WriteData(send,slen);
// 		std::cout<<"send 26:"<<cComm::ByteToHexString(send,slen)<<std::endl;
// 
// 		U8 rec[100] = {0};
// 		int rlen = 0;
// 		pSerialPort->ReadData(rec,rlen,26,1000);
// 
// 		if (rlen > 0)
// 		{
// 			std::cout<<"rec:"<<cComm::ByteToHexString(rec,rlen)<<std::endl;
// 
// 		}else{
// 			//SLEEP(500);
// 			std::cout<<"no data read!"<<std::endl;
// 			continue;
// 		}



	}
}
