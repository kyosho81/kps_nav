
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include "Comm/Comm.h"
#include "Comm/data_time.h"


int main(int argc, char* argv[]){
	

	data_time data_t;
	std::cout<<data_t.set_begin()<<std::endl;
	SLEEP(20);
	std::cout<<data_t.set_end()<<std::endl;
	std::cout<<data_t.get_diff_ms()<<std::endl;

	return 0;
}
