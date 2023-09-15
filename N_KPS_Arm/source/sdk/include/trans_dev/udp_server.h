#pragma once
 
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
 

#define  UDP_DATA_PACKAGE_MAX_LENGTH		1024
 

//typedef void (CALLBACK *SendDataCallback)(const boost::system::error_code& error,std::size_t bytes_transferred,DWORD dwUserData1,DWORD dwUserData2);
typedef boost::function<void (const boost::system::error_code& error,std::size_t bytes_transferred)> fnc_send;

//typedef void (CALLBACK *RecvDataCallback)(const boost::system::error_code& error,char *pData,int nDataLength,char *pPeerIp,unsigned short usPeerPort,DWORD dwUserData1,DWORD dwUserData2);
typedef boost::function<void (const boost::system::error_code& error,char *pData,int nDataLength,char *pPeerIp,unsigned short usPeerPort)> fnc_rec;

class UdpLinkServer
{
public:
	UdpLinkServer(unsigned short usPort,bool bBroadcast);
	virtual ~UdpLinkServer(void);
 

	typedef boost::function<void* (const boost::system::error_code& error,std::size_t bytes_transferred)>	SendDataCallbackHandler;

	

	void SetRecvDataCallback(bool bAutoRecvData,fnc_rec pfunc);
	fnc_rec fnc_rec_;


	bool Start(boost::asio::io_service& ioService);
 
	//ֹͣ
	int Stop();
 

	int SendDataEx(boost::asio::ip::udp::endpoint endpointRemote,char *pBuffer,int nBufferSize,fnc_send pfunc);
 

	int SendData(char *pBuffer,int nBufferSize,bool bAsync);
 

	boost::asio::ip::udp::endpoint & GetBroadcastEndPoint();
 
	//������ݴ��?�ֶ���
	void handleRecvDataByManual(fnc_rec pfunc );

	void handleSendData(char *pBuffer,int nBufferSize,const boost::system::error_code& error,std::size_t bytes_transferred);
	void handleSendDataInner(fnc_send pfunc,const boost::system::error_code& error,std::size_t bytes_transferred);
	//void handleSendData(boost::shared_ptr<std::string> strMessage,const boost::system::error_code& error,std::size_t bytes_transferred);

	static void SendDataCallbackOuter(const boost::system::error_code& error,std::size_t bytes_transferred);
 
 
protected:

	void RecvDataProcess(fnc_rec pfunc);
	//������ݴ��?�Զ���
	void handleRecvData(const boost::system::error_code& error,std::size_t bytes_transferred,fnc_rec pfunc);
 

	bool IsStop();
 
private:
	boost::asio::ip::udp::socket	*m_sockUdp;										
	boost::asio::ip::udp::endpoint m_endpointRemote;								
	boost::asio::ip::udp::endpoint m_endpointBroadcast;							
	boost::array<char,UDP_DATA_PACKAGE_MAX_LENGTH> m_recvBuf;	
	bool m_bStop;												
	bool  m_bBroadcast;											
	unsigned short m_usPort;									
	bool m_bAutoRecvData;										
	
	bool b_send_over_;
};
