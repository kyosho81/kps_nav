#include "trans_dev/traceroute.h"

#if defined(BOOST_WINDOWS)
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif
 
traceroute::traceroute(boost::asio::io_service& io_service, const char* destination)
	: resolver_(io_service), socket_(io_service, boost::asio::ip::icmp::v4()),
	sequence_number_(0), max_hop_(30)
{
	boost::asio::ip::icmp::resolver::query query(boost::asio::ip::icmp::v4(), destination, "");
	destination_ = *resolver_.resolve(query);

	std::cout << "\nTracing route to " << destination
		<< " [" << destination_.address().to_string() << "]"
		<< " with a maximum of " << max_hop_ << " hops.\n" << std::endl;

#if defined(BOOST_WINDOWS)
	int timeout = 5000;
	if( setsockopt(socket_.native(), SOL_SOCKET, SO_RCVTIMEO,
		(const char*)&timeout, sizeof(timeout)))
	{
		std::cout << "RCVTIMEO not set properly." << std::endl;
		throw std::runtime_error("RCVTIMEO not set properly");
	}
#else
	struct timeval tv;
	tv.tv_sec  = 5;
	tv.tv_usec = 0;
	if( setsockopt(socket_.native_handle() , SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		std::cout << "RCVTIMEO not set properly." << std::endl;
		throw std::runtime_error("RCVTIMEO not set properly");
	}
#endif

	reach_dest_host_ = false;
	int ttl = 1;
	while (!reach_dest_host_ && max_hop_--)
	{
		const boost::asio::ip::unicast::hops option(ttl);
		socket_.set_option(option);

		boost::asio::ip::unicast::hops op;
		socket_.get_option(op);
		if( ttl !=  op.value() )
		{
			std::cout << "TTL not set properly. Should be "
				<< ttl << " but was set to "
				<< op.value() << '.' << std::endl;
			throw std::runtime_error("TTL not set properly");
		}

		std::cout << std::setw(3) << ttl << std::flush;
		start_send();
		start_receive();

		ttl++;
	}//while
}

void traceroute::start_send()
{
	std::string body("\"Hello!\" from Asio ping.");

	// Create an ICMP header for an echo request.
	icmp_header echo_request;
	echo_request.type(icmp_header::echo_request);
	echo_request.code(0);
	echo_request.identifier(get_identifier());
	echo_request.sequence_number(++sequence_number_);
	compute_checksum(echo_request, body.begin(), body.end());

	// Encode the request packet.
	boost::asio::streambuf request_buffer;
	std::ostream os(&request_buffer);
	os << echo_request << body;

	// Send the request.
	time_sent_ = boost::posix_time::microsec_clock::universal_time();
	socket_.send_to(request_buffer.data(), destination_);
}


void traceroute::start_receive()
{
	// Discard any data already in the buffer.
	reply_buffer_.consume(reply_buffer_.size());

	// Wait for a reply. We prepare the buffer to receive up to 64KB.
	boost::system::error_code ec;
	boost::asio::socket_base::message_flags flags = 0;
	size_t len = socket_.receive(reply_buffer_.prepare(65536), flags, ec);

	handle_receive(len, ec);
}

void traceroute::handle_receive(std::size_t length, boost::system::error_code& ec)
{
	// The actual number of bytes received is committed to the buffer so that we
	// can extract it using a std::istream object.
	reply_buffer_.commit(length);

	// Decode the reply packet.
	std::istream is(&reply_buffer_);
	ipv4_header ipv4_hdr;
	is >> ipv4_hdr;

	if(ec)
	{
		std::cout << std::setw(9) << '*' << '\t' << "Request timed out." << std::endl;
		return;
	}

	boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
	long long dwRoundTripTime = (now - time_sent_).total_milliseconds();

	if(dwRoundTripTime)
	{
		std::cout << std::setw(6) << dwRoundTripTime << " ms"  << std::flush;
	}
	else
	{
		std::cout << std::setw(6) << "<1" << " ms" << std::flush;
	}
#if defined(_WINDOWS)
	Sleep(2000);
#else
	usleep(2000*1000);
#endif

	std::cout << '\t' << ipv4_hdr.source_address() << std::endl;

	// Print out some information about the reply packet.
	if( ipv4_hdr.source_address().to_string() == destination_.address().to_string() )
	{
		reach_dest_host_ = true;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "traceroute sucess!" << std::endl;

		icmp_header icmp_hdr;
		is >> icmp_hdr;

		if (is && icmp_hdr.type() == icmp_header::echo_reply
			&& icmp_hdr.identifier() == get_identifier()
			&& icmp_hdr.sequence_number() == sequence_number_)
		{
			// Print out some information about the reply packet.
			std::cout << length - ipv4_hdr.header_length()
				<< " bytes from " << ipv4_hdr.source_address()
				<< ": icmp_seq=" << icmp_hdr.sequence_number()
				<< ", ttl=" << ipv4_hdr.time_to_live()
				<< ", time=" << dwRoundTripTime << " ms"
				<< std::endl;
		}
	}
}

