#include "tcp_client.h"

cTCPClient::cTCPClient(void)
{
	m_sock = NULL;
	m_endpoint = NULL;
}

cTCPClient::~cTCPClient(void)
{
	if (m_sock != NULL)
	{
		boost::system::error_code errorcode;
		m_sock->shutdown(ip::tcp::socket::shutdown_both, errorcode);
		m_sock->close();
		delete m_sock;
		m_sock = NULL;
	}
	if (m_endpoint != NULL)
	{
		delete m_endpoint;
		m_endpoint = NULL;
	}
}

bool cTCPClient::Open()
{
try
{
	if (m_sock != NULL)
	{
		boost::system::error_code errorcode;
		m_sock->shutdown(ip::tcp::socket::shutdown_both, errorcode);
		m_sock->close();

		delete m_sock;
		m_sock = NULL;
	}
	if (m_endpoint != NULL)
	{
		delete m_endpoint;
		m_endpoint = NULL;
	}

	m_sock = new ip::tcp::socket(m_ios);
	m_endpoint = new ip::tcp::endpoint(ip::address::from_string(m_ConnPara.m_nRemoteIP),m_ConnPara.m_nRemotePort);
	m_sock->connect(*m_endpoint);

	return true;
}
catch (std::exception &e)
{
	return false;
}
}

bool cTCPClient::Close()
{
	if (m_sock != NULL)
	{
		boost::system::error_code errorcode;

		m_sock->shutdown(ip::tcp::socket::shutdown_both, errorcode);
		m_sock->close();

		delete m_sock;
		m_sock = NULL;
	}
	if (m_endpoint != NULL)
	{
		delete m_endpoint;
		m_endpoint = NULL;
	}

	cTransferDevice::Close();
	return true;
}

void cTCPClient::Read()
{
	if(m_sock){
		m_sock->async_read_some(buffer(m_szReadTemp,m_bufSize),
			boost::bind(&cTransferDevice::read_callback,(cTransferDevice*)this,
			boost::asio::placeholders::error,   boost::asio::placeholders::bytes_transferred));
	}
}

bool cTCPClient::Write()
{
 	size_t len = m_sock->write_some(buffer(m_szWriteBuffer,m_nWriteBufferSize));
 	if (m_nWriteBufferSize == len)
 	{
 		return true;
 	}
 	else
	{
		return false;
	}
}

