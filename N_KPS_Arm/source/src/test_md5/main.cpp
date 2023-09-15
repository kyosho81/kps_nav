
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
#include "popen.h"
#include "Comm/tollage.h"
#include "encryption/keygen.h"
#include "movement/speed_smooth.h"

// #define TG_AMCL   "amcl"    //"tollage"
// #define TG_FIX_MV "fix_mv"  //"tollage_fix_contrl"
// #define TG_DY_MV  "dy_mv"   //"tollage_dynamic_contrl"
// #define TG_DY_LOC "dy_loc"  //"tollage_dynamic_loc
// #define TG_CH_MUT "ch_mut"  //"tollage_chassis_mut"


void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	


	return;
}
int main(int argc, char* argv[]){

	std::cout<<"tollage cmd: \n "<<std::endl;
	
    std::cout<<"localization   :./test_md5 603506db5b13d698b09a591e800306b9 "<<KG_AMCL<<std::endl;
	std::cout<<"fix control    :./test_md5 603506db5b13d698b09a591e800306b9 "<<KG_MV_FIX<<std::endl;
	std::cout<<"dynamic control:./test_md5 603506db5b13d698b09a591e800306b9 "<<KG_MV_DY<<std::endl;
	std::cout<<"dynamic loc    :./test_md5 603506db5b13d698b09a591e800306b9 "<<KG_DY_LOC<<std::endl;
	std::cout<<"chassis multi  :./test_md5 603506db5b13d698b09a591e800306b9 "<<KG_CHASSIS_MUT<<std::endl;
//	std::ofstream of("acc3.txt",std::ios::binary | std::ios::trunc);
//	MyRand rd;
//	F32 current = 0;
//	int set = 100;
//#if 0
//	for (int i = 0 ; i < 50; ++i ){
//
//// 		if( set == 100){
//// 			set = -200;
//// 		}else{
//// 			set = 100;
//// 		}
//		set = rd.randInt(-10,20);
//		set *= 10;
//		int index = 0;
//		while( fabs(current - set) > 0.01){
//			current = Acc::CalAcc(0.5,current,0.1,0.5,set);
//			of<<index++<<" "<<set<<" "<<current<<std::endl;
//		}
//
//	}
//#else
//	speed_smooth spsm;
//	F32 sv = 100 ;
//	F32 cv = 0;
//	F32 acc = 0;
//	int index = 0;
//
//	for ( int i = 0 ; i < 100 ; ++i )
//	{
//		spsm.sm(sv,cv,acc);
//		of<<index++<<" "<<acc<<" "<<cv<<std::endl;
//	}
//
//	for ( int i = 0 ; i < 100 ; ++i )
//	{
//		spsm.sm(-sv,cv,acc);
//		of<<index++<<" "<<acc<<" "<<cv<<std::endl;
//	}
//
//#endif
//
//	of.flush();
//	of.close();
//	return 0;
	

	std::string str ="bcd92e32fa25adb6d18448f73396eae0";
// 	typedef enum{
// 		t_amcl = 0,
// 		t_dynamic_contrl = 1,
// 		t_fix_contrl = 2,
// 		t_dynamic_contrl = 1,
// 	}e_tollage_type;

//	e_tollage_type tt;
//	tt = t_amcl;
	std::string str_type = "";
	if(argc > 2){
		str = argv[1];

		str_type = argv[2];

	}else if(argc > 1){

		str = argv[1];
		str_type = KG_AMCL;
	}

	tollage tl;

	if ( str_type == KG_AMCL ){
		tl.set_fun_location();
	}else if ( str_type == KG_MV_FIX ){
		tl.set_fun_fix_path();
	}else if ( str_type == KG_MV_DY ){
		tl.set_fun_dynamic_path();
	}else if ( str_type == KG_DY_LOC ){
		tl.set_fun_dynamic_loc();
	}else if ( str_type == KG_CHASSIS_MUT ){
		tl.set_fun_chassis_mut();
	}else{
		std::cout<<"error reg type!!"<<str_type<<std::endl;
		return 0;
	}

	std::string str_res = tl.md5(str + tl.get_noods());

	//bool b = tl.check(str);
	std::cout<<"hack:"<<str_res<<std::endl;

	::system("pause");
	//tl.check(str,true);
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
