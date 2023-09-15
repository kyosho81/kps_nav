

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
#include <iostream>
#include <fstream>

U8 rec[1024000] = {0};

#if 1
int main(int argc, char *argv[])
{
	cConnPara conn_para2;
	conn_para2.m_iType = cConnPara::NETWORK;
	conn_para2.m_nNetType = cConnPara::TCPCLIENT;
	conn_para2.m_nRemoteIP = "192.168.1.100";
	conn_para2.m_nRemotePort = 2110;
// 	conn_para2.m_nRemoteIP = "127.0.0.1";
// 	conn_para2.m_nRemotePort = 502;

	cTransferDevice* pSerialPort = cTransferDevice::GetInstance(conn_para2);

	if (pSerialPort)
	{
		while(!pSerialPort->m_Status.IsOpen()){
			SLEEP(100);
			std::cout<<"port open err!"<<std::endl;
		}
	}

	while(1){

// 		U8 send[26] ;
// 		U32 slen = 26;
// 		for (int i = 0 ; i < slen ; ++i)
// 		{
// 			send[i] = i ;
// 		}
// 		pSerialPort->WriteData(send,slen);
// 		std::cout<<"send 26:"<<cComm::ByteToHexString(send,slen)<<std::endl;

		
		int rlen = 0;
		pSerialPort->ReadData(rec,rlen,1024000,30);

		if (rlen > 0)
		{
			//std::cout<<"rec:"<<cComm::ByteToHexString(rec,rlen)<<std::endl;

		}else{
			//SLEEP(500);
			std::cout<<"no data read!"<<std::endl;
			continue;
		}



	}
}


#else

int main(int argc, char *argv[])
{

	std::string strPort = "ttyAMA0";
	std::cout<<"please input port: (def ttyAMA0)";
	std::cin>>strPort;
	std::cout<<"serial port :"<<strPort<<std::endl;

	int ibaud = 115200;
	std::cout<<"please input baud: (def 115200)";
	std::cin>>ibaud;
	std::cout<<"serial port baud:"<<ibaud<<std::endl;

	cConnPara conn_para2;
	conn_para2.m_iType = cConnPara::SERIALPORT;
	conn_para2.setDeviceName(strPort);
	conn_para2.nBaud = ibaud;
	conn_para2.chParity = 'N';
	conn_para2.nDataBits = 8;
	conn_para2.nStopBits = 1;
	conn_para2.b_rs485 = false;

	std::cout<<"open port init begin !!"<<std::endl;

	cTransferDevice* pSerialPort = cTransferDevice::GetInstance(conn_para2);
	
	std::cout<<"open port init over!!"<<std::endl;

	if (pSerialPort)
	{
		while(!pSerialPort->m_Status.IsOpen()){
			 SLEEP(100);
			 std::cout<<"port open err!"<<std::endl;
		}
	}
	std::cout<<"open port ok!!"<<std::endl;

	while(pSerialPort->m_Status.IsOpen()){

		U8 send[26] ;
		U32 slen = 26;
		for (int i = 0 ; i < slen ; ++i)
		{
			send[i] = i ;
		}
		pSerialPort->WriteData(send,slen);
		std::cout<<"send 26:"<<cComm::ByteToHexString(send,slen)<<std::endl;

		U8 rec[100] = {0};
		int rlen = 0;
		pSerialPort->ReadData(rec,rlen,26,1000);

		if (rlen > 0)
		{
			std::cout<<"rec:"<<cComm::ByteToHexString(rec,rlen)<<std::endl;

		}else{
			//SLEEP(500);
			std::cout<<"no data read!"<<std::endl;
			continue;
		}



	}
}
#endif
