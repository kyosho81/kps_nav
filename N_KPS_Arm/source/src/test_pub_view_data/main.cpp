
#include <signal.h>

#include "Comm/TimerDiff.h"
#include "robot/Geometry.h"

#include "interpro_shared/sh_pool.hpp"


bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}

bool call_pipe(std::string name,U8* data,U32 len){

	std::cout<<"sub data name:"<<name<<std::endl;
	
	KPS::s_view_data view_data;
	
	if(view_data.ParseFromArray(data,len)){
		std::cout<<view_data.name()<<" shape_type "<<int(view_data.shape_type());
		for( int i = 0 ; i < view_data.point().size() ; ++i){
			std::cout<<" pos "<<i<<" "<<view_data.point(i).x()<<" "<<view_data.point(i).y()<<" "<<std::endl;
		}

		for( int i = 0 ; i < view_data.pos().size() ; ++i){
			std::cout<<" pos "<<i<<" "<<view_data.pos(i).x()<<" "<<view_data.pos(i).y()<<" "<<view_data.pos(i).th()<<std::endl;
		}

		return true;
	}
	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	REG_POOL(argv);

//	test_msg_pool(argc,argv);
// 	shared_pipe_seg<40960> sh_pipe("aa");
// 	sh_pipe.init();
	if (argc == 1){


		boost::function<bool (std::string name,U8* data,U32 len)> fnc;
		fnc = boost::bind(&call_pipe,_1,_2,_3);
		std::string str_sub_pipe = pub_view_data::sub_view_pipe(fnc);

		while(b_run){

			SLEEP(1000);
		}

		END_PIPE_SH_POOL(str_sub_pipe);

	}else{
		SPos pos;
		SVec point;
		pos.x_ = 1.0;
		pos.y_ = -2.0;
		pos.th_ = Deg2Rad(30);
		for ( int i = 0 ; i < 100 ; ++i ){
			pos.x_ += 0.1;
			pub_view_data::pub("loc_pos",pos);
			SLEEP(1000);
		}
		
// 		std::string name = "map";
// 		U8* data = new U8[PIPE_BUFFER_SIZE];
// 		U32 len = PIPE_BUFFER_SIZE;
// 		memset(data,0xaa,PIPE_BUFFER_SIZE);
// 
// 		for (int i = 0 ; i < 1000; ++i)
// 		{
// 			memset(data,i,PIPE_BUFFER_SIZE);
// 			//std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;
// 			std::cout<<"pub pipe name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<i<<std::endl;
// 			if(!PUB_PIPE_SH_POOL("map", "odom", data,100 )){
// 				std::cout<<"pub_sh_msg(odom) err!"<<std::endl;
// 			}
// 			SLEEP(10);
// 		}
	}


}

