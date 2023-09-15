#ifndef _PINGER_KYOSHO_20210603_
#define _PINGER_KYOSHO_20210603_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <istream>
#include <iostream>
#include <ostream>
#include <iomanip>

#include "icmp_header.hpp"
#include "ipv4_header.hpp"

class pinger
{
public:
	pinger(boost::asio::io_service& io_service, const char* destination, int i_ping_cnt = 2);

	bool ping_ok();

	static unsigned short get_identifier()
	{
#if defined(BOOST_ASIO_WINDOWS)
		return static_cast<unsigned short>(::GetCurrentProcessId());//全局函数，widows api，得到进程id
#else
		return static_cast<unsigned short>(::getpid());//linux
#endif
	};

private:

	void start_send();
	void handle_timeout();
	void start_receive();
	void handle_receive(std::size_t length);

	boost::asio::ip::icmp::resolver resolver_;
	boost::asio::ip::icmp::endpoint destination_;
	boost::asio::ip::icmp::socket socket_;
	boost::asio::deadline_timer timer_;
	unsigned short sequence_number_;
	boost::posix_time::ptime time_sent_;
	boost::asio::streambuf reply_buffer_;
	std::size_t num_replies_;
	int send_num_;
	int i_ping_cnt_;
};

#endif //_PINGER_KYOSHO_20210603_
