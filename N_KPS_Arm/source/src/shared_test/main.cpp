
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Comm.h"
#include "TimerDiff.h"
#include "RobotStruct.h"
#include "PolarScanMatch.h"

// #include "interprocess/mu_shared_range.hpp"
// #include "interprocess/shared_range.hpp"
#include "interprocess/shared_pool.hpp"


void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	//brun = false;
	shared_pool::destructor();
	SLEEP(500);

	exit(0);

	return;
}

void init_shared_pool(char *argv[]){

	shared_pool::init(argv);
	std::cout<<"shared test init call back"<<std::endl;
}
int main(int argc, char* argv[]){

	init_shared_pool(argv);
	
	U32 len = 8;
	U8* data = new U8[len];
	//memset(data,8,len);
	
	
	if (argc > 1)
	{
		data[0] = 1;
		data[1] = 2;
		data[2] = 3;
		data[3] = 4;
		data[4] = 5;
		data[5] = 6;
		data[6] = 7;
		data[7] = 8;

		for (int i = 0 ; i < len ; ++i)
		{
			U32 rlen = 1;
			shared_pool::Shared_Range_Write("global_cost_map",data+i,i,rlen);
			std::cout<<"write data:"<<i<<" value:"<<int(data[i])<<std::endl;
			//SLEEP(20);
		}
	}else{
		memset(data,8,len);

		while(1){

			//shared_pool::Shared_Range_Read("global_cost_map",data,0,len);

			std::cout<<"data len:"<<len<<" d:"<<cComm::ByteToHexString(data,len)<<std::endl;
		}	
		
	}
	//

	

	return 0;
}
//int main2(int argc, char* argv[]){
//
//	if (argc == 1)
//	{
//		shared_range sr("local cost map",100);
//		sr.init(true);
//
//		U32 len = 10;
//		U8* data = new U8[len];
//		for (int i = 0 ; i < 1000 ; ++i)
//		{
//			memset(data,i%10,len);
//			sr.write(data,10*(i%10),len);
//			std::cout<<"reg thread alive"<<i<<std::endl;
//			SLEEP(20);
//		}
//
//		if (data)
//		{
//			delete[] data;
//			data = 0;
//		}
//
//	}
//	else{
//		shared_range sr("local cost map",100);
//		sr.init();
//
//		U32 len = 100;
//		U8* data = new U8[len];
//		int i = 0;
//		while(1){
//			sr.read(data,0,len);
//			std::cout<<"data:"<<i++<<std::endl;
//		}
//
//	}
//
//	return 0;
//
//
//}
