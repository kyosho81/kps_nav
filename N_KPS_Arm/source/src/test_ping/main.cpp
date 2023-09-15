#include "trans_dev/pinger.h"
#include "trans_dev/traceroute.h"
#include "Comm/Comm.h"

#include "trans_dev/network.h"

int main(int argc, char* argv[])
{
	//netstat -ano|findstr 31287
	net_work nw;
	while(1){
		nw.do_listen();
		SLEEP(1000);
	}

	return 0;

	boost::asio::io_service io_service;
	traceroute p(io_service, "180.101.49.11");
	io_service.run();


	nw.get_active_ip();


	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: ping <host>" << std::endl;
#if !defined(BOOST_ASIO_WINDOWS)
			std::cerr << "(You may need to run this program as root.)" << std::endl;
#endif
			return 1;
		}
		boost::asio::io_service io_service;
		pinger p(io_service, argv[1]);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}
