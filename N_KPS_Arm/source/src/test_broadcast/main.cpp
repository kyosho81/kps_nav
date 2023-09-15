#include "udp_server.h"
#include <boost/thread/thread.hpp>

#if 1



//设备信息
typedef struct tagDeviceInfo{
	unsigned short	usFunction;					//功能码
	unsigned short	usVersionFlag;				//版本标记
	unsigned int	uiCompanyId;				//企业id
	char			szDeviceSerialNo[24];		//设备序列号
	unsigned short	usServicePort;				//数据服务端口
	char			szExtend[38];				//扩展
}DeviceInfo;

//工作线程参数
typedef struct tagWorkThreadParameter{
	boost::asio::io_service * pIoService;
	UdpLinkServer * pUdpService;
}WorkThreadParameter;

//工作线程函数处理函数
bool g_WorkThreadExit = false;
int  g_nBroastDataSendInteral = 5000;					//广播发送间隔，单位：毫秒
DeviceInfo g_diDeviceInfo = {0};						//设备信息
unsigned int __stdcall WorkThreadFunByDeviceServiceProcess(PVOID pParam)
{
	int nn = 0;
	int nDataSize = sizeof(DeviceInfo);
	WorkThreadParameter *pAllParameter = (WorkThreadParameter *)pParam;
	while(true)
	{
		if(g_WorkThreadExit)
		{
			break;
		}

		//发送数据
		pAllParameter->pUdpService->SendData((char *)&g_diDeviceInfo,nDataSize,true);

		pAllParameter->pIoService->poll();
		for(nn=g_nBroastDataSendInteral;nn>0; nn-=200)
		{
			if(g_WorkThreadExit)
			{
				break;
			}
			Sleep(200);
		}
	}
	return 0;
}

void test_udp_broadcast(void)
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket(io_service);
	boost::asio::ip::udp::endpoint local_endpoint;
	boost::asio::ip::udp::endpoint remote_endpoint;

	socket.open(boost::asio::ip::udp::v4());
	socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
	socket.set_option(boost::asio::socket_base::broadcast(true));
	local_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 9090);
	remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), 9090);

	try {
		socket.bind(local_endpoint);
		socket.send_to(boost::asio::buffer("abc", 3), remote_endpoint);
	} catch (boost::system::system_error e) {
		std::cout << e.what() << std::endl;
	}
}
int main(int argc, char* argv[])
{
	boost::asio::io_service ioService;
	UdpLinkServer usUdpService(9090,true);//true，为广播模式；false，非广播模式
	usUdpService.Start(ioService);
	g_diDeviceInfo.usFunction = 1;
	g_diDeviceInfo.usVersionFlag = 0x0001;
	strcpy(g_diDeviceInfo.szDeviceSerialNo,"ABCDEFG111111111");
	g_diDeviceInfo.usServicePort = 9001;

	WorkThreadParameter wtpWorkThreadParameter;
	wtpWorkThreadParameter.pIoService = &ioService;
	wtpWorkThreadParameter.pUdpService = &usUdpService;
	//开启线程
	boost::thread thrd(WorkThreadFunByDeviceServiceProcess,&wtpWorkThreadParameter);
	//线程poll等待
	thrd.join();
	g_WorkThreadExit = true;

	usUdpService.Stop();
	ioService.stop();
	return 0;
}
#else
// UdpbroastRevicer.cpp : 定义控制台应用程序的入口点。
//Udpbroast Revicer


//设备信息
typedef struct tagDeviceInfo{
	unsigned short	usFunction;					//功能码
	unsigned short	usVersionFlag;				//版本标记
	unsigned int	uiCompanyId;				//企业id
	char			szDeviceSerialNo[24];		//设备序列号
	unsigned short	usServicePort;				//数据服务端口
	char			szExtend[38];				//扩展
}DeviceInfo;

//工作线程函数处理函数
bool g_WorkThreadExit = false;
int  g_nBroastDataSendInteral = 5000;					//广播发送间隔，单位：毫秒
DeviceInfo g_diDeviceInfo = {0};						//设备信息
unsigned int __stdcall WorkThreadFunByDeviceServiceProcess(PVOID pParam)
{
	int nn = 0;
	boost::asio::io_service * pIoService  = (boost::asio::io_service *)pParam;
	while(true)
	{
		if(g_WorkThreadExit)
		{
			break;
		}

		pIoService->poll();
		for(nn=g_nBroastDataSendInteral;nn>0; nn-=200)
		{
			if(g_WorkThreadExit)
			{
				break;
			}
			Sleep(200);
		}
	}
	return 0;
}

static void WINAPI BroastDeviceInfoRecvDataCallback(const boost::system::error_code& error,char *pData,int nDataLength,char *pPeerIp,unsigned short usPeerPort,DWORD dwUserData1,DWORD dwUserData2)
{
	SYSTEMTIME sm;
	GetLocalTime(&sm);
	char szInfo[256] = {0};
	DeviceInfo *pDeviceInfo = (DeviceInfo *)pData;
	sprintf(szInfo,"%s %s:%d time:%04d-%02d-%0d %02d:%02d:%02d\n",pDeviceInfo->szDeviceSerialNo,pPeerIp,usPeerPort,sm.wYear,sm.wMonth,sm.wDay,sm.wHour,sm.wMinute,sm.wSecond);
	printf(szInfo);
}

int main(int argc, char* argv[])
{
	boost::asio::io_service ioService;
	UdpLinkServer usUdpService(9090,false);
	usUdpService.SetRecvDataCallback(true,BroastDeviceInfoRecvDataCallback,0,0);
	usUdpService.Start(ioService);

	//开启线程
	boost::thread thrd(WorkThreadFunByDeviceServiceProcess,&ioService);
	//线程poll等待
	thrd.join();
	g_WorkThreadExit = true;

	usUdpService.Stop();
	ioService.stop();
	return 0;
}


#endif

#if 0

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost;
using asio::ip::udp;
using system::error_code;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

class udp_server; // forward declaration

struct udp_session : enable_shared_from_this<udp_session> {

	udp_session(udp_server* server) : server_(server) {}

	void handle_request(const error_code& error);

	void handle_sent(const error_code& ec, std::size_t) {
		// here response has been sent
		if (ec) {
			std::cout << "Error sending response to " << remote_endpoint_ << ": " << ec.message() << "\n";
		}
	}

	udp::endpoint remote_endpoint_;
	array<char, 100> recv_buffer_;
	std::string message;
	udp_server* server_;
};

class udp_server
{
	typedef shared_ptr<udp_session> shared_session;
public:
	udp_server(asio::io_service& io_service)
		: socket_(io_service, udp::endpoint(udp::v4(), 1313)), 
		strand_(io_service)
	{
		receive_session();
	}

private:
	void receive_session()
	{
		// our session to hold the buffer + endpoint
		auto session = make_shared<udp_session>(this);

		socket_.async_receive_from(
			asio::buffer(session->recv_buffer_), 
			session->remote_endpoint_,
			strand_.wrap(
			bind(&udp_server::handle_receive, this,
			session, // keep-alive of buffer/endpoint
			asio::placeholders::error,
			asio::placeholders::bytes_transferred)));
	}

	void handle_receive(shared_session session, const error_code& ec, std::size_t /*bytes_transferred*/) {
		// now, handle the current session on any available pool thread
		socket_.get_io_service().post(bind(&udp_session::handle_request, session, ec));

		// immediately accept new datagrams
		receive_session();
	}

	void enqueue_response(shared_session const& session) {
		socket_.async_send_to(asio::buffer(session->message), session->remote_endpoint_,
			strand_.wrap(bind(&udp_session::handle_sent, 
			session, // keep-alive of buffer/endpoint
			asio::placeholders::error,
			asio::placeholders::bytes_transferred)));
	}

	udp::socket  socket_;
	asio::strand strand_;

	friend struct udp_session;
};

void udp_session::handle_request(const error_code& error)
{
	if (!error || error == asio::error::message_size)
	{
		message = make_daytime_string(); // let's assume this might be slow

		// let the server coordinate actual IO
		server_->enqueue_response(shared_from_this());
	}
}

int main()
{
	try {
		asio::io_service io_service;
		udp_server server(io_service);

		thread_group group;
		for (unsigned i = 0; i < thread::hardware_concurrency(); ++i)
			group.create_thread(bind(&asio::io_service::run, ref(io_service)));

		group.join_all();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
#endif