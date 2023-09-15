
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Acc.h"
#include "Comm/Rand.hpp"
#include "Comm.h"

#include "Comm/tollage.h"
#include "Comm/file.h"

#include "project/suro_forbidden_line.h"

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	


	return;
}
int main(int argc, char* argv[]){

	suro_forbidden_line fl;
//	fl.load("D://MyRobot//N_KPS_Arm//doc//it//forbidden_line//10086.map");
//	fl.load("D://MyRobot//N_KPS_Arm//debug_data//20201015//0717.map");
	fl.load("D://MyRobot//N_KPS_Arm//doc//it//20211222//3-dt//3-dt.map");
	//fl.load("./AgvData/zz1016/zz1016.map");
	std::list<SLine2P> l_forbidden_lines;

	fl.get_forbidden_lines(l_forbidden_lines);
	std::cout<<"forbidden line size:"<<l_forbidden_lines.size()<<std::endl;
	return 0;
}



//int main2(int argc, char* argv[]){
//
//
//	int result;
//	if(-1==(result=gethostid()))
//	{
//		printf("gethostid err\n");
//		exit(0);
//	}
//	printf("hosid is :%d\n",result);
//
//
//	//std::::system("ifconfig eth0 | grep "HWaddr" | awk '{print $5}'");
//	std::string str_rec = "" ;
//	system::cmd("ifconfig eth0 | grep ''HWaddr'' | awk '{print $5}'",str_rec);
//	str_rec = cComm::trim_n(str_rec);
//
//
//	std::stringstream ss;
//	ss<<result<<"-"<<str_rec;
//
//
//
//	return 0;
//}
