#ifndef _TRACEROUTE_KYOSHO_20210603_
#define _TRACEROUTE_KYOSHO_20210603_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <istream>
#include <iostream>
#include <ostream>
#include <iomanip>

#include "icmp_header.hpp"
#include "ipv4_header.hpp"


class traceroute
{
public:

	traceroute(boost::asio::io_service& io_service, const char* destination);

private:
	void start_send();
	void start_receive();
	void handle_receive(std::size_t length, boost::system::error_code& ec);

	static unsigned short get_identifier()
	{
#if defined(BOOST_WINDOWS)
		return static_cast<unsigned short>(::GetCurrentProcessId());
#else
		return static_cast<unsigned short>(::getpid());
#endif
	}

	boost::asio::ip::icmp::resolver resolver_;
	boost::asio::ip::icmp::endpoint destination_;
	boost::asio::ip::icmp::socket socket_;
	unsigned short sequence_number_;
	boost::posix_time::ptime time_sent_;
	boost::asio::streambuf reply_buffer_;
	bool reach_dest_host_;
	std::size_t max_hop_;
};


#endif //_TRACEROUTE_KYOSHO_20210603_
