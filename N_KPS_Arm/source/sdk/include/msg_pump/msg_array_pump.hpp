#ifndef _MSG_ARRAY_PUMP_KYOSHO_20180401_
#define _MSG_ARRAY_PUMP_KYOSHO_20180401_


#include <string>
#include <map>
#include <iostream>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include "Comm/buffer_con.hpp"
#include "Comm/Comm.h"

//#include "msg_pump/msg_pump.hpp"

#define ARRAY_BUFFER_SIZE 40960

typedef struct _Spipe_array
{
	char ch_array_nm_[100];
	unsigned int offset_;
	unsigned int len_;

}Spipe_array;


class SArrData_Addr{
public:
	SArrData_Addr(){
		id_ = 0;
		p_list_ = 0 ;
		data_len_  = 0 ;
		b_thread_run_ = 0;
	};
	~SArrData_Addr(){
		if (p_list_)
		{
			delete p_list_;
			p_list_ = 0;
		}

		std::cout<<"SArrData_Addr destruct!"<<std::endl;
	};

	int id_;

	void* p_list_; 
	int data_len_;

	THSafe<int> b_thread_run_;
};

template<U32 ARRAY_BUF_SIZE>
class msg_array{

public:

	msg_array():head_(0),rear_(0),offset_(0),total_size_(0){
		memset(msg_data_,0,sizeof(unsigned char)*ARRAY_BUF_SIZE);
		memset(msg_pipe_,0,sizeof(Spipe_array)*ARRAY_BUF_SIZE);
	};
	~msg_array(){

	};

	typedef enum{ARRAY_TH_IDLE,ARRAY_TH_RUN,ARRAY_TH_STOP} eArray_th_sta;

	bool empty(){
		if (total_size_ == 0){
			return true;
		}else{
			return false;
		}

	};
	bool full(unsigned int in){
		if ( (total_size_ + in) <= ARRAY_BUF_SIZE){
			return false;
		}else{
			return true;
		}

	};

	bool push_back(std::string name,unsigned char* data,unsigned int len,bool wait_full){
		if (len > ARRAY_BUF_SIZE)
		{
			std::cout<<"msg array buffer max size is "<<ARRAY_BUF_SIZE<<" now:"<<len<<std::endl;
			return false;
		}

		unsigned int name_len = name.length();

		if ((name_len < 1) || ( name_len > 99) || (!data) || (!len) )
		{
			//name len err!
			return false;
		}

		boost::mutex::scoped_lock lock(mu);

		while ( full(len))
		{
			if(wait_full){
				std::cout<<"msg array buffer full,  wait now !"<<std::endl;
				cond_put.wait(lock);
			}else{
				//pipe list full pop one!;
				pop_one();
				std::cout<<"msg array buffer full,  force drop !"<<std::endl;
			}

			boost::mutex::scoped_lock lock2(mu_status);
			if (e_th_run_ != ARRAY_TH_RUN)
			{
				std::cout<<"sub msg array thread pop break;"<<std::endl;
				return false;
			}

		}

		Spipe_array &pipe(msg_pipe_[rear_]);
		name.copy(pipe.ch_array_nm_,name_len,0);
		pipe.offset_ = offset_;
		pipe.len_ = len;


		if ( (offset_ + pipe.len_ )>= ARRAY_BUF_SIZE)
		{
			//separate msg into 2 seg
			memcpy(msg_data_ + offset_,data,ARRAY_BUF_SIZE - pipe.offset_);
			memcpy(msg_data_,data + (ARRAY_BUF_SIZE - pipe.offset_),pipe.len_ - (ARRAY_BUF_SIZE - pipe.offset_));

		}else{
			memcpy(msg_data_ + offset_,data,len);
		}

		offset_ += pipe.len_;
		offset_ = offset_ % ARRAY_BUF_SIZE;

		total_size_ += pipe.len_;

		rear_ = (++rear_) % ARRAY_BUF_SIZE;

		cond_get.notify_one();

		return true;
	};
	bool pop_front(std::string &name,unsigned char* data,unsigned int &len){

		if(!data){
			std::cout<<"msg array pop_front err: data ptr == 0!"<<std::endl;
			return false;
		}
		boost::mutex::scoped_lock lock(mu);

		while (empty())
		{
			cond_get.wait(lock);

			boost::mutex::scoped_lock lock2(mu_status);
			if (e_th_run_ != ARRAY_TH_RUN)
			{
				std::cout<<"sub msg array thread pop break;"<<std::endl;
				return false;
			}
		}
		memset(data,0,len);

		Spipe_array &pipe(msg_pipe_[head_]);
		name = pipe.ch_array_nm_;

		if ((pipe.offset_ + pipe.len_) >=ARRAY_BUF_SIZE)
		{
			//separate data into 2 seg
			len = ARRAY_BUF_SIZE - pipe.offset_ ;
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
		memset(&pipe,0,sizeof(Spipe_array));
		total_size_ -= len;

		head_ = (++head_) % ARRAY_BUF_SIZE;

		cond_put.notify_one();

		return true;
	};
	void end_wait(){
		while (1)
		{
			{
				boost::mutex::scoped_lock lock2(mu_status);
				e_th_run_ = ARRAY_TH_STOP;
			}

			cond_get.notify_one();
			cond_put.notify_one();
			std::cout<<"sub msg array thread end_wait"<<std::endl;
			//SLEEP(20);

			boost::mutex::scoped_lock lock2(mu_status);
			if (e_th_run_ == ARRAY_TH_IDLE)
			{
				break;
			}


		}


	};
	eArray_th_sta get_th_status(){
		boost::mutex::scoped_lock lock2(mu_status);
		return (eArray_th_sta)e_th_run_;
	};
	void set_th_status( const eArray_th_sta &sta ){
		boost::mutex::scoped_lock lock2(mu_status);
		e_th_run_ = sta;
	};
private:

	char msg_data_[ARRAY_BUF_SIZE];
	Spipe_array msg_pipe_[ARRAY_BUF_SIZE];

	unsigned int head_;
	unsigned int rear_;
	unsigned int offset_;
	unsigned int total_size_;

	boost::mutex mu;
	boost::condition_variable_any cond_get;
	boost::condition_variable_any cond_put;

	//end thread used
	int e_th_run_;
	boost::mutex mu_status;


	void pop_one(){


		Spipe_array &pipe(msg_pipe_[head_]);

		int len = 0;
		if ((pipe.offset_ + pipe.len_) >=ARRAY_BUF_SIZE)
		{
			len = ARRAY_BUF_SIZE - pipe.offset_ ;

			memset(msg_data_ + pipe.offset_,0xff,len);
			memset(msg_data_,0xff,pipe.len_ - len);
			len = pipe.len_;


		}else{

			memset(msg_data_ + pipe.offset_,0xff,pipe.len_);
			len = pipe.len_;

		}
		memset(&pipe,0,sizeof(Spipe_array));
		total_size_ -= len;

		head_ = (++head_) % ARRAY_BUF_SIZE;
	};
};

class msg_array_pump
{
public:
	msg_array_pump();
	~msg_array_pump();

	static bool pub_msg(const std::string &pipe_name,const std::string &data_name,U8* data,U32 len,bool wait_full = true){

		mDataMap get_match;
		{
			std::pair<mDataMap::iterator, mDataMap::iterator> ret;
			boost::mutex::scoped_lock lock(mu_all_data_map_);
			ret = all_data_map_.equal_range(pipe_name);

			for ( mDataMap::iterator it = ret.first ; it != ret.second ; ++it){
				get_match.insert (mDataMap::value_type(it->first,it->second) );
			}
		}

		for (mDataMap::iterator it = get_match.begin() ; it != get_match.end() ; ++it ){
		
			SArrData_Addr* p_da = it->second;
			
			int data_size = len ;

			if (p_da->b_thread_run_() == 1){
	
				msg_array<ARRAY_BUFFER_SIZE>* p_array = static_cast<msg_array<ARRAY_BUFFER_SIZE>*>(p_da->p_list_);
				p_array->push_back(data_name,data,len,wait_full);
			}

		}
		return true;
	};

	static int sub_msg_id;

	static int get_sub_msg_id(){
		return sub_msg_id++;
	};

	static int sub_msg(std::string msg_name,boost::function<bool( std::string name,U8* data,U32 len )> fnc){

		boost::mutex::scoped_lock lock(mu_all_data_map_);

		int data_size = sizeof( msg_array<ARRAY_BUFFER_SIZE> );
		msg_array<ARRAY_BUFFER_SIZE>* p_array = new msg_array<ARRAY_BUFFER_SIZE>();
		p_array->set_th_status(msg_array<ARRAY_BUFFER_SIZE>::ARRAY_TH_RUN);
		SArrData_Addr* p_da = new SArrData_Addr();
		p_da->p_list_ = (void*)p_array;

		p_da->id_ = get_sub_msg_id();
		p_da->data_len_ = data_size;
		p_da->b_thread_run_ = 1;


		std::cout<<"sub msg id:"<<p_da->id_<<" msg:"<<msg_name<<std::endl;


		all_data_map_.insert (mDataMap::value_type(msg_name,p_da) );


		boost::thread th(boost::bind(&msg_array_pump::sub_thread,p_da,fnc));
		return p_da->id_;

		return 1;
	};


	static void sub_thread(SArrData_Addr* pda, boost::function<bool(std::string name,unsigned char* data,unsigned int len)> fnc){

		std::cout<<"sub thread id:"<<pda->id_<<std::endl;

		msg_array<ARRAY_BUFFER_SIZE>* p_array = static_cast<msg_array<ARRAY_BUFFER_SIZE>*>(pda->p_list_);

		if( (!p_array) ){
			return;
		}
		std::cout<<"sub_thread begin :"<<pda->id_<<std::endl;

		std::string name;
		unsigned char* data = new unsigned char[ARRAY_BUFFER_SIZE];
		unsigned int len = ARRAY_BUFFER_SIZE;

		try  
		{

			while( pda->b_thread_run_()){

				if (p_array->pop_front(name,data,len)){

					if(!fnc.empty() ){

						if (!fnc(name,data,len))
						{
							break;
						}

					}else{
						break;
					}
				}

				
				boost::this_thread::interruption_point();
			}

		} 
		catch (boost::thread_interrupted&) {
			//catch (std::exception& e)  {  
			//std::cout <<"sub_thread err:"<< e.what() << std::endl;  
			std::cout <<"sub_thread err:"<< std::endl;  
		}

		pda->b_thread_run_ = -1;
		SDelete(data);
		std::cout<<"sub thread is end id:"<<pda->id_<<std::endl;

	};

	static bool end_Sub(const int &id){

		//boost::mutex::scoped_lock lock(mu_all_data_map_);
		mu_all_data_map_.lock();

		mDataMap::iterator it = all_data_map_.begin();

		unsigned char t[] = {0};
		for ( ; it != all_data_map_.end() ; ++it)
		{
			std::cout<<"begin end sub id:"<<it->second->id_<<" msg:"<<it->first<<std::endl;
			SArrData_Addr* p_da = it->second;

			if( id == p_da->id_){

				mu_all_data_map_.unlock();

				p_da->b_thread_run_ = 0;
				while( p_da->b_thread_run_() != -1){

					msg_array<ARRAY_BUFFER_SIZE>* p_array = static_cast<msg_array<ARRAY_BUFFER_SIZE>*>(p_da->p_list_);
					//p_array->set_th_status(msg_array<ARRAY_BUFFER_SIZE>::ARRAY_TH_STOP);
					p_array->end_wait();
					//p_array->push_back("end thread",t,1,true);
					SLEEP(1);

				}

				boost::mutex::scoped_lock lock(mu_all_data_map_);
				std::cout<<"over end sub id:"<<it->second->id_<<" msg:"<<it->first<<std::endl;
				all_data_map_.erase(it);
				SDelete(p_da);

				return true;
			}

		}
		std::cout<<"end_Sub err id:"<<id<<std::endl;
		mu_all_data_map_.unlock();
		return false;
	};

protected:
private:

	typedef std::multimap<std::string,SArrData_Addr*> mDataMap;
	static mDataMap all_data_map_;

	static boost::mutex mu_all_data_map_;
};

#endif //_MSG_ARRAY_PUMP_KYOSHO_20180401_