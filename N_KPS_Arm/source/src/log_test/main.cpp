
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

#include "Log4cppArm.hpp"

int main(int argc, char* argv[]){
	LOG.enableFileLog("ADAM");

	while(1){
		LOGS_WARN("ADAM") << "ADAM WARN : ";
		SLEEP(1000);
	}
	

}