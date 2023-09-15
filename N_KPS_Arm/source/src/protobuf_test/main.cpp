
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Comm.h"
#include "protobuf_msg/user.pb.h"
#include "protobuf_msg/map.pb.h"

// #include "interprocess/mu_shared_range.hpp"
// #include "interprocess/shared_range.hpp"
#include "interprocess/shared_pool.hpp"

using namespace Test;
using namespace std;

using namespace KPS;

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

using namespace Test;

int main(int argc, char* argv[]){

// 	mp_map_test mmap;
 	char ch[10] = {0};
// 
// 	std::cout<<"mmap size:"<<mmap.ByteSize()<<std::endl;
// 	mmap.add_data((void*)&ch,1);
// 	std::cout<<"mmap size:"<<mmap.ByteSize()<<std::endl;
// 	mmap.add_data((void*)&ch,1);
// 	std::cout<<"mmap size:"<<mmap.ByteSize()<<std::endl;
// 	mmap.add_data((void*)&ch,2);
// 	std::cout<<"mmap size:"<<mmap.ByteSize()<<std::endl;
// 	mmap.add_data((void*)&ch,2);
// 	std::cout<<"mmap size:"<<mmap.ByteSize()<<std::endl;

	return 0;

	std::fstream fs2_(".//pro_log//2018-9-5-0-40-27.proto",std::ios::in | std::ios::binary);
	if (!fs2_.is_open())
	{
		return 1;
	}
	std::stringstream ss;
	std::string str;
	if (!std::getline(fs2_,str))
	{
		fs2_>>str;
		return 1;
	}
	return 0;
	init_shared_pool(argv);
	
	
	userninfo user1;
	user1.set_name("yaoyuan");
	user1.set_mail("123456789@qq.com");
	user1.set_time("2014-9-7");
	user1.set_status("test");

	fstream outPuts;
	outPuts.open("./users",ios::out | ios::trunc | ios::binary);
	if(!user1.SerializePartialToOstream(&outPuts))
	{
		cerr<<"写用户信息失败"<<endl;
		return-1;
	}
	outPuts.close();

	userninfo user2;
	fstream inPuts;
	inPuts.open("./users",ios::in | ios::binary);
	if(!user2.ParseFromIstream(&inPuts))
	{
		cerr<<"Failed to parse user info!"<<endl;
		return-1;
	}
	cout<<"user name:"<<user2.name()<<endl;
	cout<<"user mail:"<<user2.mail()<<endl;
	cout<<"user time:"<<user2.time()<<endl;
	cout<<"user status:"<<user2.status()<<endl;

	inPuts.close();

	system("pause");
	return 0;
}
