
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <signal.h>

#include "Comm/Comm.h"
#include "log/log_client.h"
#include "log/log_server.h"

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	//brun = false;
	
	SLEEP(500);

	return;
}

#define CLIENT 1
#if CLIENT 
int main(int argc, char* argv[]){
	
	::signal(SIGINT, shutdown);
	RPC_CONFIG_CLIENT_INIT("127.0.0.1");
	TCP_LOG.init(argc,argv);
	std::string str_prc_name = argv[0];
	for ( int i = 0 ;  i < 1000 ; ++i)
	{
		TCP_LOG_INFO<<"tcp log test main:"<<i;
		SLEEP(100);
	}
	TCP_LOG.destroy();

	system("pause");
}
#else
int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	TCP_LOG_SERVER.init_listen();
	SLEEP(100);

	for ( int i = 0 ; i < 3 ; ++i)
	{

		TCP_LOG_SERVER.run_once();
	}
	TCP_LOG_SERVER.destruct();
}
#endif
