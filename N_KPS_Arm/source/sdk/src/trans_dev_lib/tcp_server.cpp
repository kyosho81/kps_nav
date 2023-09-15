#include "tcp_server.h"
#include "../Comm/Comm.h"

cTCP_Server::cTCP_Server(void)
{

	acceptor_ = NULL;
}

cTCP_Server::~cTCP_Server(void)
{
}

bool cTCP_Server::Open()
{

	return Start();
	//return true;
}

bool cTCP_Server::Close()
{
	p_sock_->close();
	std::cout<<"cTCP_Server::Close() begin!"<<std::endl;
	if (acceptor_)
	{
		delete acceptor_;
		acceptor_ = NULL;
	}
// 	if (sock_)
// 	{
// 		delete sock_;
// 		sock_ = NULL;
// 	}
	std::cout<<"cTCP_Server::Close() end!"<<std::endl;
	cTransferDevice::Close();
	return true;
}

void cTCP_Server::Read()
{
// 	if (m_Status.IsOpen())
// 	{
	try {
		p_sock_->async_read_some(buffer(m_szReadTemp,m_bufSize), boost::bind(
			&cTransferDevice::read_callback,(cTransferDevice*)this,
			boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	} catch (std::exception& e) {
		m_Status.SetClose();
		std::cout<<"TCP Svr close conn port = "<< p_sock_->local_endpoint().port()<<std::endl;
	}
// 	}
// 	else
// 	{
// 		cout<<"read err"<<endl;
// 	}
	
}

bool cTCP_Server::Write()
{
	try {
		if (!p_sock_->is_open())
			return 0;

		int total = 0;
		
		while (total < m_nWriteBufferSize) {
			int tmpLength = m_nWriteBufferSize - total > m_nWriteBufferSize ? m_nWriteBufferSize : m_nWriteBufferSize - total;

			size_t sz = p_sock_->write_some(buffer(m_szWriteBuffer + total,
				tmpLength));

			total += sz;
			//cout<<"sendData : length  = "<<tmpLength<<endl;
		}
		assert(total == m_nWriteBufferSize);
		//delete[] data;
		return true;
	} catch (std::exception& e) {
		m_Status.SetClose();
		std::cout<<"TCP Svr close conn port = "<< p_sock_->local_endpoint().port()<<std::endl;
		return false;
	}
}

bool cTCP_Server::Start()//接收异步连接，连接发生时Accept_handler被调用
{
	try
	{
		if (acceptor_)
		{
			delete acceptor_;
			acceptor_ = NULL;
		}


		if (!acceptor_)
		{
			acceptor_ = new ip::tcp::acceptor(m_ios,ip::tcp::endpoint(ip::tcp::v4(),m_ConnPara.n_listen_port));
		}

		
		sock_pt s(new ip::tcp::socket(m_ios));
		p_sock_ = s;
		acceptor_->accept(*p_sock_);
		cout<<"tcp serv >> client connect"<<endl;

		return true;
	}
	catch (std::exception &e)
	{
		m_Status.SetClose();
		std::cout<<"TCP tcp::acceptor port err: "<< m_ConnPara.n_listen_port<<std::endl;

		return false;;
	}
// 	if ( (p_sock_) && (acceptor_))
// 	{
// 		acceptor_->async_accept(*p_sock_,bind(&cTCP_Server::Accept_handler,this,placeholders::error));
// 	}
	
}
// void cTCP_Server::Accept_handler(const system::error_code& ec)
// {
// 	if (ec) //检测错误代码
// 	{
// 		Start(); //再次启动异步连接
// 		m_Status.SetClose();
// 		return;
// 	}
// 	else
// 	{
// 		
// 		// 	sock_->async_read_some(buffer(m_szReadTemp,m_bufSize), boost::bind(
// 		// 		&cTransferDevice::read_callback,(cTransferDevice*)this,
// 		// 		placeholders::error,placeholders::bytes_transferred));
// 		Read();
// 		m_Status.SetOpen();
// 		
// 		LOGS("TCP Server")<<"client:"<<p_sock_->remote_endpoint().address();
// 		
// 		//Start(); //再次启动异步连接
// 	}
// 	
// }
//重载函数，异步连接，需要accept后为有效
