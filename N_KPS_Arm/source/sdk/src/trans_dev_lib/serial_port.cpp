#if defined(_WINDOWS)
#else
#include <sys/ioctl.h>
#endif

#include "serial_port.h"
#include "Comm.h"


cSerialPort::cSerialPort(void)
{
	m_pSerialPort = NULL;
	sleep_one_byte_per_ms_ = 2;
}

cSerialPort::~cSerialPort(void)
{
	if (m_pSerialPort != NULL)
	{
		delete m_pSerialPort;
		m_pSerialPort = NULL;
	}
	
}

bool cSerialPort::Open(){
try{

	if (m_pSerialPort != NULL)
	{
		std::cout<<"delete serial port"<<std::endl;
		delete m_pSerialPort;
		m_pSerialPort = NULL;
		std::cout<<"delete serial port over!"<<std::endl;
	}

	std::string strComNo;
  	//strComNo = "COM";
	std::cout<<"open port:"<<m_ConnPara.getDeviceName()<<std::endl;

	m_pSerialPort = new boost::asio::serial_port(m_ios ,m_ConnPara.getDeviceName());

	m_pSerialPort->set_option(boost::asio::serial_port::baud_rate(m_ConnPara.nBaud));
	m_pSerialPort->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
	if (m_ConnPara.chParity == 'N')
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
	}
	if (m_ConnPara.chParity == 'O') //��У��
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::odd));
	}
	if (m_ConnPara.chParity == 'E')  //żУ��
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::even));
	}
	
	if (m_ConnPara.nStopBits == 1)
	{
		m_pSerialPort->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
	}else if (m_ConnPara.nStopBits == 2)
	{
		m_pSerialPort->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::two));
	}
	else
	{
		return false;
	}
	m_pSerialPort->set_option(boost::asio::serial_port::character_size(m_ConnPara.nDataBits));
	
	if(m_ConnPara.b_rs485){
		setRTS(false);
	}

	sleep_one_byte_per_ms_ =  m_ConnPara.nBaud / 10;
	sleep_one_byte_per_ms_ = 1000 / sleep_one_byte_per_ms_  ;
	std::cout<<"baud:"<<m_ConnPara.nBaud<<" sleep_one_byte_per_ms_:"<<sleep_one_byte_per_ms_<<std::endl;

#if defined(_WINDOWS)
// 	void* fd = m_pSerialPort->native_handle();
// 	// retrieves information about the communications properties.
// 	LPCOMMPROP	lpCommProp = (LPCOMMPROP)malloc(sizeof(COMMPROP));
// 	lpCommProp->wPacketLength = sizeof(COMMPROP);
// 	GetCommProperties(fd, lpCommProp);
// 	WORD wSize = lpCommProp->wPacketLength;
// 	free(lpCommProp);
// 	lpCommProp = (LPCOMMPROP)malloc(wSize);
// 	lpCommProp->wPacketLength = wSize;
// 	GetCommProperties(fd, lpCommProp);
// 
// 	COMMTIMEOUTS TimeOuts;
// 	//设定读超时
// 	TimeOuts.ReadIntervalTimeout=1000;
// 	TimeOuts.ReadTotalTimeoutMultiplier=500;
// 	TimeOuts.ReadTotalTimeoutConstant=5000;
// 	//设定写超时
// 	TimeOuts.WriteTotalTimeoutMultiplier=500;
// 	TimeOuts.WriteTotalTimeoutConstant=2000;
// 	SetCommTimeouts(fd,&TimeOuts); //设置超时
#endif
	// the maximum size of the driver's internal output buffer
	// is:      lpCommProp->dwMaxTxQueue;
	// maximum size of the driver's internal input buffer
	// is :      lpCommProp->dwMaxRxQueue;

	return true;
}
catch (std::exception &e)
{
	std::cout<<"Serial port open err!"<<std::endl;;
	return false;
}
	
}
void cSerialPort::BaudSleep(int len){

	int isleep = sleep_one_byte_per_ms_ * len + 2;

	//std::cout<<"used for rs485 sleep:"<<isleep<<std::endl;
	SLEEP(isleep);


}
void cSerialPort::setRTS(bool enabled){
#if defined(_WINDOWS)
	
#else

	int fd = m_pSerialPort->native_handle();

	int data = TIOCM_RTS;

//	struct termios options;
//	 if  ( tcgetattr( fd,&options)  !=  0)
//	  {
//		perror("SetupSerial 1");
//		return;
//	  }
//	 options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
//	 options.c_cc[VTIME] = 1; /* 设置超时15 seconds*/
//	 options.c_cc[VMIN] = 26; /* Update the options and do it NOW */
//	 //options.c_lflag &= ~(ICANON | ECHO | ECHOE);
//	 if (tcsetattr(fd,TCSANOW,&options) != 0)
//	    {
//	        perror("SetupSerial 3");
//	        return ;
//	    }


	if (!enabled)
		ioctl(fd, TIOCMBIC, &data);        
	else
		ioctl(fd, TIOCMBIS, &data);
#endif
}

void cSerialPort::setDTR(bool enabled)
{
#if defined(_WINDOWS)
#else
	int fd = m_pSerialPort->native_handle();

	int data = TIOCM_DTR;

//	struct termios options;
// if  ( tcgetattr( fd,&options)  !=  0)
//  {
//	perror("SetupSerial 1");
//	return;
//  }
// options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
// options.c_cc[VMIN] = 26; /* Update the options and do it NOW */
//// options.c_lflag &= ~(ICANON | ECHO | ECHOE);
// if (tcsetattr(fd,TCSANOW,&options) != 0)
//    {
//        perror("SetupSerial 3");
//        return ;
//    }



	if (!enabled)
		ioctl(fd, TIOCMBIC, &data);        // Clears the RTS pin
	else
		ioctl(fd, TIOCMBIS, &data);        // Sets the RTS pin
#endif
}
bool cSerialPort::Close()
{
	SDelete(m_pSerialPort);

	cTransferDevice::Close();
	return true;
}

bool cSerialPort::Write()
{

	if(!m_pSerialPort){
		return false;
	}
	if(m_ConnPara.b_rs485){
		setRTS(true);
	}

	size_t len = m_pSerialPort->write_some(boost::asio::buffer(m_szWriteBuffer,m_nWriteBufferSize));

	if(m_ConnPara.b_rs485){
		BaudSleep(m_nWriteBufferSize);

		setRTS(false);
	}

	if (m_nWriteBufferSize == len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cSerialPort::Read()
{
	if(!m_pSerialPort){
		std::cout<<"err serial port read!"<<std::endl;
		return;
	}

	m_pSerialPort->async_read_some(boost::asio::buffer(m_szReadTemp,m_bufSize), 
		boost::bind(&cTransferDevice::read_callback,(cTransferDevice*)this,  
   		boost::asio::placeholders::error,   boost::asio::placeholders::bytes_transferred)); 
}
