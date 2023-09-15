#ifndef _SH_PIPE_LIST_WANGHONGTAO_2020_08_25_
#define _SH_PIPE_LIST_WANGHONGTAO_2020_08_25_


#include <iostream>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "Comm/MyDefine.h"


typedef struct _Spipe_msg
{
	char ch_pipe_nm_[100];
	U32 offset_;
	U32 len_;

}Spipe_msg;

template<U32 PIPE_BUFFER_SIZE>
class sh_pipe_list{

public:

	sh_pipe_list():head_(0),rear_(0),offset_(0),total_size_(0){
		memset(msg_data_,0,sizeof(U8)*PIPE_BUFFER_SIZE);
		memset(msg_pipe_,0,sizeof(Spipe_msg)*PIPE_BUFFER_SIZE);
	};
	~sh_pipe_list(){

	};

	typedef enum{PIPE_TH_IDLE,PIPE_TH_RUN,PIPE_TH_STOP} ePipe_th_sta;

	bool empty(){
		if (total_size_ == 0){
			return true;
		}else{
			return false;
		}

	};
	bool full(U32 in){
		if ( (total_size_ + in) <= PIPE_BUFFER_SIZE){
			return false;
		}else{
			return true;
		}

	};
	
	bool push_back(std::string name,U8* data,U32 len,bool wait_full){
		if (len > PIPE_BUFFER_SIZE)
		{
			std::cout<<"shared pipe buffer max size is "<<PIPE_BUFFER_SIZE<<" now:"<<len<<std::endl;
			return false;
		}
		
		U32 name_len = name.length();
		
		if ((name_len < 1) || ( name_len > 99) || (!data) || (!len) )
		{
			//name len err!
			return false;
		}
		
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mu);

		while ( full(len))
		{
			if(wait_full){
				std::cout<<"shared pipe buffer full,  wait now !"<<std::endl;
				cond_put.wait(lock);
			}else{
				//pipe list full pop one!;
				pop_one();
				std::cout<<"shared pipe buffer full,  force drop !"<<std::endl;
			}

			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
			if (e_th_run_ != PIPE_TH_RUN)
			{
				std::cout<<"sub pipe thread pop break;"<<std::endl;
				return false;
			}

		}

		Spipe_msg &pipe(msg_pipe_[rear_]);
		name.copy(pipe.ch_pipe_nm_,name_len,0);
		pipe.offset_ = offset_;
		pipe.len_ = len;

		
		if ( (offset_ + pipe.len_ )>= PIPE_BUFFER_SIZE)
		{
			//separate msg into 2 seg
			memcpy(msg_data_ + offset_,data,PIPE_BUFFER_SIZE - pipe.offset_);
			memcpy(msg_data_,data + (PIPE_BUFFER_SIZE - pipe.offset_),pipe.len_ - (PIPE_BUFFER_SIZE - pipe.offset_));
					
		}else{
			memcpy(msg_data_ + offset_,data,len);
		}
		
		offset_ += pipe.len_;
		offset_ = offset_ % PIPE_BUFFER_SIZE;

		total_size_ += pipe.len_;
		
		rear_ = (++rear_) % PIPE_BUFFER_SIZE;
		
		cond_get.notify_one();

		return true;
	};
	bool pop_front(std::string &name,U8* data,U32 &len){
		
		if(!data){
			std::cout<<"shared pipe msg pop_front err: data ptr == 0!"<<std::endl;
			return false;
		}
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mu);

		while (empty())
		{
			cond_get.wait(lock);

			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
			if (e_th_run_ != PIPE_TH_RUN)
			{
				std::cout<<"sub pipe thread pop break;"<<std::endl;
				return false;
			}
		}
		memset(data,0,len);

		Spipe_msg &pipe(msg_pipe_[head_]);
		name = pipe.ch_pipe_nm_;
		
		if ((pipe.offset_ + pipe.len_) >=PIPE_BUFFER_SIZE)
		{
			//separate data into 2 seg
			len = PIPE_BUFFER_SIZE - pipe.offset_ ;
			memcpy(data,msg_data_ + pipe.offset_,len);
			memcpy(data + len,msg_data_,pipe.len_ - len);
			memset(msg_data_ + pipe.offset_,0xff,len);
			memset(msg_data_,0xff,pipe.len_ - len);
			len = pipe.len_;


		}else{
			memcpy(data,msg_data_ + pipe.offset_,pipe.len_);
			memset(msg_data_ + pipe.offset_,0xff,pipe.len_);
			len = pipe.len_;
		
		}	
		memset(&pipe,0,sizeof(Spipe_msg));
		total_size_ -= len;

		head_ = (++head_) % PIPE_BUFFER_SIZE;

		cond_put.notify_one();

		return true;
	};
	void end_wait(){
		while (1)
		{
			{
				boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
				e_th_run_ = PIPE_TH_STOP;
			}

			cond_get.notify_one();
			cond_put.notify_one();
			std::cout<<"sub pipe thread end_wait"<<std::endl;
			SLEEP(20);

			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
			if (e_th_run_ == PIPE_TH_IDLE)
			{
				break;
			}


		}


	};
	ePipe_th_sta get_th_status(){
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
		return (ePipe_th_sta)e_th_run_;
	};
	void set_th_status( const ePipe_th_sta &sta ){
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
		e_th_run_ = sta;
	};
private:
	
	char msg_data_[PIPE_BUFFER_SIZE];
	Spipe_msg msg_pipe_[PIPE_BUFFER_SIZE];
	
	U32 head_;
	U32 rear_;
	U32 offset_;
	U32 total_size_;

	boost::interprocess::interprocess_mutex mu;
	boost::interprocess::interprocess_condition cond_get;
	boost::interprocess::interprocess_condition cond_put;

	//end thread used
	int e_th_run_;
	boost::interprocess::interprocess_mutex mu_status;
	

	void pop_one(){


		Spipe_msg &pipe(msg_pipe_[head_]);

		int len = 0;
		if ((pipe.offset_ + pipe.len_) >=PIPE_BUFFER_SIZE)
		{
			len = PIPE_BUFFER_SIZE - pipe.offset_ ;

			memset(msg_data_ + pipe.offset_,0xff,len);
			memset(msg_data_,0xff,pipe.len_ - len);
			len = pipe.len_;


		}else{

			memset(msg_data_ + pipe.offset_,0xff,pipe.len_);
			len = pipe.len_;

		}
		memset(&pipe,0,sizeof(Spipe_msg));
		total_size_ -= len;

		head_ = (++head_) % PIPE_BUFFER_SIZE;
	};
};
#endif//_SH_PIPE_LIST_WANGHONGTAO_2020_08_25_
