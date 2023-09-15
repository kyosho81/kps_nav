
#include <signal.h>


#include <iostream>
#include <fstream>
//#include <unistd.h>

#include <string>
#include <cassert>
#include <windows.h>

#include "Comm/TimerDiff.h"

#include "msg_pump/msg_array_pump.hpp"


bool brun = true; 
#if 0
msg_array ma;

void th_sub(){

	std::vector<long long> v_dt;

	for ( int i = 0 ; i < 2000; ++i ){
		unsigned char ch[12] = {0};
		std::string str;
		unsigned int ilen = 12;

		if ( !ma.pop_front(str,ch,ilen)){
			Sleep(100);
			continue;
		}
		//std::cout<<"pop name:"<<str<<" ";
		int index = 0;
		long long lt = 0;
		memcpy(&index,ch,sizeof(int));
		memcpy(&lt,ch + sizeof(int),sizeof(long long));

		long long lt_sub = cTimerDiff::total_ms();
		
		//std::cout<<"index:"<<index<<std::endl;
		//std::cout<<" pub:"<<lt<<std::endl;
		//std::cout<<" sub:"<<lt_sub<<std::endl;
		//std::cout<<" dt:"<< (lt_sub - lt) <<std::endl;

		v_dt.push_back( lt_sub - lt);
		if ( (i ==199) && ma.empty()){
			break;
		}
	}
	auto it = v_dt.begin();

	for ( ; it != v_dt.end() ; ++it ){
		
		std::cout<<"dt:"<<*it<<std::endl;
	}
	std::cout<<"thread over!"<<std::endl;
}

int main(int argc, char *argv[])
{
	ma.set_th_status(msg_array::ARRAY_TH_RUN);

	boost::thread th(th_sub);

	for ( int i = 0 ;  i < 200 ; ++i ){
		unsigned char ch[12] = {0};
		memcpy(ch,&i,sizeof(int));
		long long lt = cTimerDiff::total_ms();
		memcpy(ch + sizeof(int),&lt,sizeof(long long));
		ma.push_back("pub",ch,12,false);
		
		std::cout<<"pub data:"<<lt<<std::endl;
		Sleep(10);
	}
	
	Sleep(1000000);
	return 0;
}
#endif

bool sub_data(std::string name, U8 * data, U32 len){

	std::string str = cComm::ByteToHexString(data,len);
	std::cout<<"name1:"<<name<<" "<<str<<std::endl;
	return true;
}
bool sub_data1(std::string name, U8 * data, U32 len){

	std::string str = cComm::ByteToHexString(data,len);
	std::cout<<"name2:"<<name<<" "<<str<<std::endl;
	return true;
}


int main(int argc, char *argv[])
{
	boost::function<bool( std::string name, U8 * data, U32 len )> fnc;
	fnc = boost::bind(&sub_data,_1,_2,_3);
	msg_array_pump::sub_msg("a",fnc);

	fnc = boost::bind(&sub_data1,_1,_2,_3);
	msg_array_pump::sub_msg("a",fnc);

	unsigned char ch[12] = {0};
	for ( int i = 0 ; i < 12 ; ++i ){
		ch[i] = i;
	}

	for (int i = 0 ; i < 100 ; ++i ){
		ch[0] = i;
		msg_array_pump::pub_msg("a","p1",ch,12);
	}
	SLEEP(1000000);
}