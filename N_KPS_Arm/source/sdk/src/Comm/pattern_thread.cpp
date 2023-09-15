#include "math.h"
#include "Comm/Comm.h"
#include "Comm/pattern_thread.h"


pattern_thread::pattern_thread()
{
	th_b_run_ = false;
}

pattern_thread::~pattern_thread()
{
	destory_thread();
}

void pattern_thread::bind_func(boost::function<bool ()> fnc){
	fnc_run_ = fnc;
}
void pattern_thread::run_thread(boost::function<bool ()> fnc)
{
	fnc_run_ = fnc;
	boost::thread(boost::bind(&pattern_thread::th_run,this));
}


bool pattern_thread::destory_thread()
{
	if (th_b_run_() == false)
	{
		return true;
	}

	th_b_run_ = false;
	for ( int i = 0 ; i < 1000 ; ++i )
	{
		if(th_over_sig_.size() > 0 ){
			std::cout<<"pattern_thread::destory_thread over!!"<<std::endl;
			return true;
		}else{
			SLEEP(200);
			std::cout<<"pattern_thread::destory_thread waitting!!"<<std::endl;
		}

	}
	return false;
}

void pattern_thread::th_run()
{
	th_b_run_ = true;
	th_over_sig_.clear();

	std::cout<<"pattern_thread::th_run() id:"<<boost::this_thread::get_id()<<std::endl;

	while(th_b_run_()){
		if(fnc_run_){
			if(!fnc_run_()){
				std::cout<<"pattern_thread::th_run client run cancel!"<<std::endl;
				th_b_run_ = false;
			}
		}else{
			th_b_run_ = false;
		}
	}
	th_over_sig_.put(0);
	std::cout<<"pattern_thread::th_run() over thread id:"<<boost::this_thread::get_id()<<std::endl;
}
