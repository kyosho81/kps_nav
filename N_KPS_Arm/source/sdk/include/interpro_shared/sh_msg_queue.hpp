#ifndef _SHARED_MSG_LIST_WANGHONGTAO_2020_08_24_
#define _SHARED_MSG_LIST_WANGHONGTAO_2020_08_24_


#include <iostream>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <boost/interprocess/sync/interprocess_condition.hpp>


#define BUFFER_SIZE 10

template<typename T>
class sh_msg_queue{

public:

	sh_msg_queue():head_(0),rear_(0),deap_(0){

	};
	~sh_msg_queue(){
	};

	typedef enum{MSG_TH_IDLE,MSG_TH_RUN,MSG_TH_STOP} eMsg_th_sta;

	bool empty(){
		if (deap_ == 0)
		{
			return true;
		}else{
			return false;
		}

	};
	bool full(){
		if (deap_ == BUFFER_SIZE)
		{
			return true;
		}else{
			return false;
		}

	};

	bool push_back(const T &in){
		bool bfull = false;
		{
			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mu);

			bfull = full();
			if (bfull)
			{
				//std::cout<<"is full egnore:"<<msg_list_[head_]<<std::endl;
				head_ = (++head_) % BUFFER_SIZE;
				deap_--;
			}

			msg_list_[rear_] = in;
			rear_ = (++rear_) % BUFFER_SIZE;
			deap_++;
		}
		cond_get.notify_one();
		assert(deap_ < (BUFFER_SIZE+1));

		return bfull;
	};
	bool pop_front(T &in){
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mu);

		while (empty())
		{
			//std::cout << "empty waiting..." << std::endl;
			cond_get.wait(lock);
			
			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
			if (e_th_run_ != MSG_TH_RUN)
			{
				std::cout<<"sub thread pop break;"<<std::endl;
				return false;
			}
			
			//std::cout << "empty waiting over ..." << std::endl;
		}

		in = msg_list_[head_];
		//std::cout<<"pop index:"<<head_<<std::endl;

		head_ = (++head_) % BUFFER_SIZE;
		deap_--;
		
		return true;
	};
	void end_wait(){
		while (1)
		{
			{
				boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
				e_th_run_ = MSG_TH_STOP;
			}
			
			cond_get.notify_one();
			std::cout<<"sub thread end_wait"<<std::endl;
			SLEEP(20);

			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
			if (e_th_run_ == MSG_TH_IDLE)
			{
				break;
			}
			
			
		}
		
		
	};
	eMsg_th_sta get_th_status(){
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
		return (eMsg_th_sta)e_th_run_;
	};
	void set_th_status( const eMsg_th_sta &sta ){
		boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock2(mu_status);
		e_th_run_ = sta;
	};
	

private:
	T msg_list_[BUFFER_SIZE];
	int head_;
	int rear_;
	int deap_;
	

	boost::interprocess::interprocess_mutex mu;
	boost::interprocess::interprocess_condition cond_get;

	//end thread used
	int e_th_run_;
	boost::interprocess::interprocess_mutex mu_status;
	
};
#endif//_SHARED_MSG_LIST_WANGHONGTAO_2020_08_24_