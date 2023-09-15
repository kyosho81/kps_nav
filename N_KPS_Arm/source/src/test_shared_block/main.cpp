
#include <signal.h>

#include "Comm/TimerDiff.h"
// #include "interpro_shared/shared_pipe.hpp"
// #include "interpro_shared/block_shared_pool.hpp"
#include "interpro_shared/sh_pool.hpp"

//using namespace boost::interprocess;

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}


int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	
//	test_msg_pool(argc,argv);
// 	shared_pipe_seg<40960> sh_pipe("aa");
// 	sh_pipe.init();
#define MA "ma"

	U8 data[10];
	for ( int i = 0 ; i < 10; ++i ){
		data[i] = i;
	}
	if (argc == 1){

		block_shared_pool::init(argv,true);

		REG_BLOCK_SH_POOL(MA,10);

		//shared_block* sh_b = block_shared_pool::get_sh_range(MA);

		for ( int i = 0; i < 100 ; ++i){
		
			U32 ilen = 10;
			SET_BLOCK_SH_POOL(MA,data,0,ilen);
			data[9] = i;
			SLEEP(1000);
			std::cout<<"write"<<cComm::ByteToHexString(data,10)<<std::endl;
		}

	}else {

		block_shared_pool::init(argv);

		shared_block* sh_b = block_shared_pool::get_sh_range(MA);

		for( int i = 0 ; i < 1000; ++i ){
			U32 ilen = 10;
			sh_b->read(data,0,ilen);
			std::cout<<"read:"<<cComm::ByteToHexString(data,ilen)<<std::endl;
			SLEEP(500);
		}
	} 


}

