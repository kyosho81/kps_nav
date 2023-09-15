#include <iostream>
#include <boost/exception/all.hpp>
#include "trans_dev/udp_server.h"

UdpLinkServer::UdpLinkServer(unsigned short usPort,bool bBroadcast)
{
	m_bStop = false;
	m_bBroadcast = bBroadcast;
	m_usPort = usPort;
	m_sockUdp = NULL;
	m_bAutoRecvData = true;

}
 
UdpLinkServer::~UdpLinkServer(void)
{
	if(m_sockUdp != NULL)
	{
		m_sockUdp->close();
		delete m_sockUdp;
		m_sockUdp = NULL;
	}
}
 

//开始
bool UdpLinkServer::Start(boost::asio::io_service& ioService)
{
	try
	{
		if(m_bBroadcast)
		{
			//广播
			m_sockUdp = new boost::asio::ip::udp::socket(ioService,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),0));
			m_sockUdp->set_option(boost::asio::socket_base::reuse_address(true));
			m_sockUdp->set_option(boost::asio::socket_base::broadcast(true));
			m_endpointBroadcast = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), m_usPort);
		}
		else
		{
			m_sockUdp = new boost::asio::ip::udp::socket(ioService,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),m_usPort));
			if(!m_sockUdp->is_open())
			{
				//端口被占用
				return false;
			}
			m_sockUdp->set_option(boost::asio::socket_base::reuse_address(true));
		}
	
	}
	catch (boost::exception& e)
	{
		std::cerr << boost::diagnostic_information(e);
		return false;
	}
 
    m_bStop = false;
	if(m_bAutoRecvData)
	{
		RecvDataProcess(fnc_rec_);
	}
	return true;
}
 
//停止
int UdpLinkServer::Stop()
{
	m_bStop = true;
 
	return 0;
}
 
//是否停止服务
bool UdpLinkServer::IsStop()
{
	return m_bStop;
}
 
//获取广播端点
boost::asio::ip::udp::endpoint & UdpLinkServer::GetBroadcastEndPoint()
{
	return m_endpointBroadcast;
}
 
void UdpLinkServer::SendDataCallbackOuter(const boost::system::error_code& error,std::size_t bytes_transferred)
{
	int i = 0;
}
 
//发送数据
int UdpLinkServer::SendDataEx(boost::asio::ip::udp::endpoint endpointRemote,char *pBuffer,int nBufferSize,fnc_send pfunc)
{
	m_sockUdp->async_send_to(boost::asio::buffer(pBuffer,nBufferSize),endpointRemote,boost::bind(&UdpLinkServer::handleSendDataInner,this,pfunc,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
 
	return 0;
}
 
//发送数据
int UdpLinkServer::SendData(char *pBuffer,int nBufferSize,bool bAsync)
{
	if(!m_bBroadcast)
	{
		if(bAsync)
		{
			b_send_over_ = false;
			//异步发送
			m_sockUdp->async_send_to(boost::asio::buffer(pBuffer,nBufferSize),m_endpointRemote,boost::bind(&UdpLinkServer::handleSendData,this,pBuffer,nBufferSize,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			//同步发送
			m_sockUdp->send_to(boost::asio::buffer(pBuffer,nBufferSize),m_endpointRemote);
		}
	}
	else
	{
		//广播
		if(bAsync)
		{
			b_send_over_ = false;
			//异步发送
			m_sockUdp->async_send_to(boost::asio::buffer(pBuffer,nBufferSize),m_endpointBroadcast,boost::bind(&UdpLinkServer::handleSendData,this,pBuffer,nBufferSize,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			//同步发送
			m_sockUdp->send_to(boost::asio::buffer(pBuffer,nBufferSize),m_endpointBroadcast);
		}
	}
 
	return 0;
}
 
//接收数据
void UdpLinkServer::RecvDataProcess(fnc_rec pfunc)
{
	//异步接收数据
	m_sockUdp->async_receive_from(boost::asio::buffer(m_recvBuf),
		m_endpointRemote,
		boost::bind(&UdpLinkServer::handleRecvData,this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred,
		pfunc)
		);
}
 
//接收数据处理（手动），就进入本函数响应处理
void UdpLinkServer::handleRecvDataByManual(fnc_rec pfunc)
{
	if(IsStop())
		return;
 
	//下一次接收
	RecvDataProcess(pfunc);
}
 
//当收到客户端数据时，就进入本函数响应处理  
void UdpLinkServer::handleRecvData(const boost::system::error_code& error,std::size_t bytes_transferred,fnc_rec pfunc)
{
	if(IsStop())
		return;
 
	//如果没有出错
	if(!error || error==boost::asio::error::message_size)
	{
		if(bytes_transferred > UDP_DATA_PACKAGE_MAX_LENGTH)
		{
			//超过最大数据长度
			return;
		}
 
		/*
		//打印接收的内容
		char szTmp[UDP_DATA_PACKAGE_MAX_LENGTH] = {0};
		memcpy(szTmp,m_recvBuf.data(),bytes_transferred);
		printf("%s\n",szTmp);
		//boost::shared_ptr<std::string> strMessage(new std::string("aaaaaa"));
		//SendData((char *)strMessage.data(),strMessage.size());
		std::string strMessage = "aaaaaaaaaa";
		SendDataEx(m_endpointRemote,(char *)strMessage.data(),strMessage.size(),SendDataCallbackOuter,(int)this,0);
		*/
 
		//回调数据
		if(pfunc)
		{
			pfunc(error,m_recvBuf.data(),bytes_transferred,(char *)m_endpointRemote.address().to_string().c_str(),m_endpointRemote.port());
		}
 
		//下一次接收
		RecvDataProcess(pfunc);
	}
	else
	{
		//出错
		if(pfunc != NULL)
		{
			//pfunc(error,NULL,bytes_transferred,NULL,0,dwUserData1,dwUserData2);
		}
	}
}
 
//当发送数据给客户端成功之后响应。  
void UdpLinkServer::handleSendData(char *pBuffer,int nBufferSize,const boost::system::error_code& error,std::size_t bytes_transferred)
{
	b_send_over_ = true;
	std::cout<<"async send over!"<<std::endl;
}
void UdpLinkServer::handleSendDataInner(fnc_send pfunc,const boost::system::error_code& error,std::size_t bytes_transferred)
{
	if(error)
	{
		//打印错误信息
		printf("%s", boost::system::system_error(error).what());
	}
	if(pfunc != 0)
	{
		pfunc(error,bytes_transferred);
	}
	int n = 0;
}

void UdpLinkServer::SetRecvDataCallback(bool bAutoRecvData,fnc_rec pfunc)
{
	m_bAutoRecvData = bAutoRecvData;
	fnc_rec_ = pfunc;
}

/*
void UdpLinkServer::handleSendData(boost::shared_ptr<std::string> strMessage,const boost::system::error_code& error,std::size_t bytes_transferred)
{
	 int n = 0;
}
*/
