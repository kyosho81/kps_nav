

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

#include "Comm.h"

#include "trans_dev.h"
#include "serial_port.h"
#include "tcp_client.h"
#include "tcp_server.h"

using namespace boost::posix_time;
using namespace boost::gregorian;

mTransferDeviceP cTransferDevice::m_mTransferDeviceP;
int cTransferDevice::id_all_ = 0;
//Manage<cTransferDevice> cTransferDevice::list_;

int cTransferDevice::m_bufSize = BUF_MAX_SIZE;
//int cTransferDevice::id_all_ = 0;

int cConnPara::SERIALPORT = 1;
int cConnPara::NETWORK = 2;
int cConnPara::TCPCLIENT = 3;
int cConnPara::TCPSERVER = 4;
int cConnPara::UPD = 5;
//********************************************************************

//*********************************************************************
cConnPara::cConnPara()
{
 	m_iType = SERIALPORT;
 
#ifdef _WIN32
 	sDeviceName = "\\\\.\\COM1"; //
#else
	sDeviceName = "/dev/ttyUSB0"; //
#endif
	b_rs485 = false;
 	nBaud=57600;      //
 
 	chParity= 'N';   //
 	nDataBits=8;  //
 	nStopBits=1;  //
 
 	iAdd=6;      //
 
 	iDefSample = 1;  //
 	iTimeout=80;     //
 	//	byTimeoutMax=1;  //
 	lReflash = 100; //
	//tcp client
 	m_nNetType = cConnPara::TCPCLIENT;  //
 	m_nLocalPort = 2001; //
	m_nRemoteIP = "192.168.2.100";  //
	m_nRemotePort = 2000;//
	//tcp server
	n_listen_port = 2011; //

}
//********************************************************************

//*********************************************************************
cConnPara::~cConnPara()
{

}
//********************************************************************

//*********************************************************************
bool cConnPara::CheckConn(const cConnPara& ConnPara)
{
	if (m_iType ==  ConnPara.m_iType)
	{
		if (m_iType == cConnPara::SERIALPORT )
		{	
			if ((sDeviceName == ConnPara.sDeviceName) && (nBaud == ConnPara.nBaud) && (chParity == ConnPara.chParity) && (nDataBits == ConnPara.nDataBits) && (nStopBits == ConnPara.nStopBits))
			{
				return true;
			}
		}
		if (m_iType == cConnPara::NETWORK )
		{
			if (m_nNetType == cConnPara::TCPCLIENT)
			{
				if (m_nLocalPort == ConnPara.m_nLocalPort) 	
				{
					if (m_nRemoteIP == ConnPara.m_nRemoteIP)
					{
						if (m_nRemotePort == ConnPara.m_nRemotePort)
						{
							return true;
						}
					}
					
				}
			}
			if (m_nNetType == cConnPara::TCPSERVER)
			{
				if (n_listen_port ==  ConnPara.n_listen_port)
				{
					return true;
				}
			}
 			
		}
	}
	return false;
}

bool cConnPara::CanCreate( const cConnPara& ConnPara )
{
	if (m_iType ==  ConnPara.m_iType)
	{
		if (m_iType == cConnPara::SERIALPORT )
		{	
			if ( sDeviceName == ConnPara.sDeviceName ){
				if((nBaud == ConnPara.nBaud) && (chParity == ConnPara.chParity) && (nDataBits == ConnPara.nDataBits) && (nStopBits == ConnPara.nStopBits))
				{
					assert(false);  //
					return false;
				}
				else
				{
					return false;
				}
			}
		}
		if (m_iType == cConnPara::NETWORK )
		{
			if (m_nNetType == cConnPara::TCPCLIENT)
			{
				if ((m_nLocalPort == ConnPara.m_nLocalPort) && (m_nRemoteIP == ConnPara.m_nRemoteIP) &&(m_nRemotePort == ConnPara.m_nRemotePort))
				{
					assert(false);  //
					return false;
				}
				else{
					return true;
				}
			}
			if (m_nNetType == cConnPara::TCPSERVER)
			{
				if (n_listen_port == ConnPara.n_listen_port)
				{
					assert(false);  //
					return false;
				}
				else{
					return true;
				}
			}
			
		}
	}
	return true;
}
void cConnPara::setDeviceName(std::string nm){
	
#ifdef _WIN32
	sDeviceName = "\\\\.\\";
	sDeviceName += nm;
#else
	sDeviceName = "/dev/";
	sDeviceName += nm;
#endif
}

std::string cConnPara::getDeviceName()
{
	return sDeviceName;
}

cTransferDevice::cTransferDevice(void)
{
	m_Status.SetClose();

	m_lReadBuffer.Init(BUF_MAX_SIZE);
	m_szReadTemp = new unsigned char[BUF_MAX_SIZE];
	m_szWriteBuffer = new unsigned char[BUF_MAX_SIZE];
	memset(m_szReadTemp,0,BUF_MAX_SIZE);
	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = 0;
	
	m_iInstanceCount = 0;

	m_threadRun = NULL;

	m_btime_out = false;

	th_run_ = false;
}

cTransferDevice::~cTransferDevice(void)
{
//	Close();
	delete m_threadRun;
	m_threadRun = NULL;

	std::cout<<"cTransferDevice destory!"<<std::endl;
}
cTransferDevice* cTransferDevice::GetInstance(const cConnPara& ConnPara )
{
	
	cTransferDevice* pTransferDevice = NULL;
	//
  	mTransferDeviceP::const_iterator  cit = m_mTransferDeviceP.begin();
  	for (;cit!= m_mTransferDeviceP.end();++cit)
  	{
  		pTransferDevice = cit->second;
  		if (pTransferDevice->m_ConnPara.CheckConn(ConnPara))
  		{

			//LOGS_INFO("TransferDevice")<<"GetExistInstance:"<<pTransferDevice->m_ConnPara.nCommNO;
			std::cout<<"TransferDevice GetExistInstance:"<<pTransferDevice->m_ConnPara.getDeviceName()<<std::endl;
			pTransferDevice->m_iInstanceCount++;
  			return pTransferDevice;
  		}
  	}
	//
	cit = m_mTransferDeviceP.begin();
	for (;cit!= m_mTransferDeviceP.end();++cit)
	{
		pTransferDevice = cit->second;
		if (!pTransferDevice->m_ConnPara.CanCreate(ConnPara))
		{
			std::cout<<"TransferDevice Para Error:"<<pTransferDevice->m_ConnPara.getDeviceName()<<std::endl;
			//LOGS_WARN("TransferDevice")<<"Para Error:"<<pTransferDevice->m_ConnPara.nCommNO;
			pTransferDevice = NULL;
			return pTransferDevice;
		}
	}

  
  	if (ConnPara.m_iType == cConnPara::SERIALPORT)
  	{
  		typedef mTransferDeviceP::value_type vType;
  
  		int iIndex = m_mTransferDeviceP.size();
		pTransferDevice = (cTransferDevice*)new cSerialPort();
		assert(pTransferDevice != NULL);
  		if(!pTransferDevice->Init(ConnPara))
  		{
  			delete pTransferDevice;
  			pTransferDevice = NULL;
  			return NULL;
  		}
		pTransferDevice->m_iInstanceCount = 1;
  		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
  		
  		return pTransferDevice;
  	}
  	if ((ConnPara.m_iType == cConnPara::NETWORK) && (ConnPara.m_nNetType == cConnPara::TCPCLIENT))
  	{
  		typedef mTransferDeviceP::value_type vType;
  		
  		int iIndex = m_mTransferDeviceP.size();
  		pTransferDevice = (cTransferDevice*)new cTCPClient();
  		if(!pTransferDevice->Init(ConnPara))
  		{
  			delete pTransferDevice;
  			pTransferDevice = NULL;
  			return NULL;
  		}
		pTransferDevice->m_iInstanceCount = 1;
  		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
 		return pTransferDevice;
 	}

	if ((ConnPara.m_iType == cConnPara::NETWORK) && (ConnPara.m_nNetType == cConnPara::TCPSERVER))
	{
		typedef mTransferDeviceP::value_type vType;

		int iIndex = m_mTransferDeviceP.size();
		pTransferDevice = (cTransferDevice*)new cTCP_Server();
		if(!pTransferDevice->Init(ConnPara))
		{
			delete pTransferDevice;
			pTransferDevice = NULL;
			return NULL;
		}
		pTransferDevice->m_iInstanceCount = 1;
		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
		return pTransferDevice;
	}
 
 	return NULL;
}


bool cTransferDevice::Init( const cConnPara& ConnPara )
{
	m_ConnPara = ConnPara;

	m_lReadBuffer.Init(BUF_MAX_SIZE);
	memset(m_szReadTemp,0,BUF_MAX_SIZE);
	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = 0;
	
	id_ = CreateID();

	return BeginThread();
}


bool cTransferDevice::BeginThread()
{
	if (m_threadRun!= NULL)
	{
		delete m_threadRun;
		m_threadRun = NULL;
	}
	while(th_run_){
		std::cout<<"wait thread over!"<<std::endl;
		SLEEP(10);
	};


 	m_threadRun = new boost::thread(boost::bind(&cTransferDevice::ThreadRun,this));
 	if (m_threadRun)
 	{
 		return true;
 	}
 	else
 	{
 		return false;
 	}
}

void cTransferDevice::EndThread()
{
	th_run_ = false;

	if (m_threadRun != NULL)
	{
		std::cout<<"cTransferDevice::EndThread begin"<<std::endl;
		m_ios.stop();
		m_ios.reset();
		SLEEP(10);
		std::cout<<"cTransferDevice::EndThread join"<<std::endl;
		//m_threadRun->interrupt();
		m_threadRun->join();

		delete m_threadRun;
		m_threadRun = NULL;

		
		std::cout<<"trans dev end thread!!"<<std::endl;
	}
	std::cout<<"trans dev end over!"<<std::endl;
}

int cTransferDevice::ThreadRun()
{	
	th_run_ = true;

try{
	while (th_run_)
	{
		if (Open())
		{

			SetOpen();
			Read();
			
			std::cout<<"m_ios.run();"<<std::endl;
			m_ios.run();
			std::cout<<"m_ios.reset();"<<std::endl;
			m_ios.reset();

		//	this_thread::interruption_point();
		}
		std::cout<<"interruption point t"<<std::endl;
		//this_thread::interruption_point();

		std::cout<<" trans dev Reopen"<<std::endl;
		SLEEP(1000);

	}
	std::cout<<"interruption_point 2"<<std::endl;
	//this_thread::interruption_point();
	return 0;
}
catch(thread_interrupted)
{
	cout<<"cTransferDevice thread interrupted"<<endl;
	return -1;
}
}

bool cTransferDevice::WriteData(/*In*/unsigned char* pData,int Len,const bool &b_clear_read)
{

 	if (!m_Status.IsOpen())
 	{
 		std::cout<<"cTransferDevice write data err!!!!!!!"<<std::endl;
 		return false;
 	}
	//m_read_write_Lock.lock();
	//mutex::scoped_lock lock(m_read_write_Lock); for wuhan 20130112
	//cout<<"write"<<endl;
	assert(pData!=NULL);


	if (!pData || Len > BUF_MAX_SIZE)
	{
		std::cout<<"cTransferDevice write data pppppp err!!!!!!!"<<std::endl;
		return false;
	}

	if (b_clear_read)
	{
		m_lReadBuffer.Clear();
	}
	
	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = Len;
	memcpy(m_szWriteBuffer,pData,Len);

	return Write();
}
int cTransferDevice::ReadData( /*Out*/unsigned char* pReceiveData,int& iLen,/*In*/int iReclen,int iTimeout)
{
	assert(pReceiveData != 0);

	if (!m_Status.IsOpen())
	{
		//m_read_write_Lock.unlock();
		return 0;
	}
	
	if (iReclen == -1)
	{
		iReclen = m_lReadBuffer.Size();
	}

	if (iReclen > BUF_MAX_SIZE)
	{
		std::cout<<"buf out:"<<iReclen<<std::endl;
		iReclen = BUF_MAX_SIZE;
	}

	memset(pReceiveData,0,iReclen);
	iLen = 0;

	int len_tmp = 0;

	while(1){

		len_tmp = m_lReadBuffer.Size();
		if ( len_tmp >= iReclen)
		{

			//std::cout<<"read data over"<<std::endl;
			break;
		}

		int i_sleep = 1;
#ifdef _WIN32
		i_sleep = 20;
#endif
		if (iTimeout > 0)
		{
			iTimeout = iTimeout - i_sleep;

			SLEEP(i_sleep);
			//std::cout<<"sleep 1ms"<<std::endl;
		}
		else{
			//std::cout<<"-----------time out"<<std::endl;
			break;
		}
	}
	m_lReadBuffer.Read(pReceiveData,iLen);

	return iLen;

}

bool cTransferDevice::Close()
{	
	m_Status.SetClose();
	EndThread();
	SLEEP(500);
	return true;
}
bool cTransferDevice::Write()
{
	assert(false);
	return false;
}

void cTransferDevice::Read()
{
	assert(false);
}

void cTransferDevice::read_callback( const boost::system::error_code& error, std::size_t bytes_transferred)
{   
	//mutex::scoped_lock lock(m_readlock);
	if (m_Status.IsClose())
	{
		return;
	}
 	if (error )   
 	{     // No data was read!
		m_Status.SetClose();
		std::cout<<"trans dev callback err "<<boost::system::system_error(error).what()<<std::endl;
		return;   
 	} 


	m_lReadBuffer.Write(m_szReadTemp,bytes_transferred);
	//std::cout<<"read data:"<<bytes_transferred<<std::endl;
	Read();
 } 
void cTransferDevice::wait_callback( const boost::system::error_code& error) 
{  
	
	//Close();

} 

bool cTransferDevice::DelInstance(const cConnPara& ConnPara)
{
	cTransferDevice* pTransferDevice = NULL;
	mTransferDeviceP::iterator  it = m_mTransferDeviceP.begin();
	for (;it != m_mTransferDeviceP.end(); )
	{
		pTransferDevice = it->second;
		if (pTransferDevice->m_ConnPara.CheckConn(ConnPara))
		{
			pTransferDevice->m_iInstanceCount--;
			if (pTransferDevice->m_iInstanceCount <=0)
			{
				pTransferDevice->Close();
				delete it->second;
				it->second = NULL;
				m_mTransferDeviceP.erase(it++);
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			++it;
		}
	}
	return false;
}
cTransferDevice* cTransferDevice::GetInstance( int id )
{
	cTransferDevice* tf = cTransferDevice::GetNextDevice();
	
	while (tf)
	{
		if (tf->ID() == id)
		{
			return tf;
		}
		
		tf = cTransferDevice::GetNextDevice(tf);
	}
	return NULL;
}
cTransferDevice* cTransferDevice::GetNextDevice( cTransferDevice* pTransfer )
{
	mTransferDeviceP::iterator it;
	if (!pTransfer)
	{
		it = m_mTransferDeviceP.begin();
		
	}
	else{
		it = m_mTransferDeviceP.find(pTransfer->ID());
		it++;
	}
	if (it != m_mTransferDeviceP.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}
void cTransferDevice::SetOpen()
{
	m_Status.SetOpen();
}
// 
// int cTransferDevice::CreateID()
// {
// 	return id_all_++;
// }
// 
// int cTransferDevice::tID()
// {
// 	return id_;
// }
void cTransferDevice::GetPara( cConnPara& ConnPara )
{
	ConnPara = m_ConnPara;
}

bool cTransferDevice::Open()
{
	return false;
}

int cTransferDevice::CreateID()
{
	return id_all_++;
}

int cTransferDevice::ID()
{
	return id_;
}
