#ifndef _SHARED_MSG_WANGHONGTAO_2020_08_27_
#define _SHARED_MSG_WANGHONGTAO_2020_08_27_


#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


#include "Comm.h"
#include "interpro_shared/sh_msg_queue.hpp"
//#include "interprocess/con_shared_list.hpp"

template<typename T>
class shared_msg
{
public:
	explicit shared_msg(std::string share_name):share_name_(share_name){
		shm_ = 0;
		region_ = 0;
		ptr_ = 0;
	};

	~shared_msg(){

		SDelete(region_);
		SDelete(shm_);
		
	};

	bool init(){
		SDelete(ptr_);
		SDelete(region_);
		SDelete(shm_);

 		try{

			std::cout<<"core shared msg remove:"<<share_name_<<std::endl;
			boost::interprocess::shared_memory_object::remove(share_name_.c_str());

			//Create a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::create_only               //only create
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);
			std::cout<<"core shared msg create:"<<share_name_<<std::endl;
			//Set size

			std::cout<<"msg struct size:"<<sizeof(sh_msg_queue<T>)<<std::endl;
			shm_->truncate(sizeof(sh_msg_queue<T>));
			std::cout<<"msg construct shared:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();

			//Construct the shared structure in memory
			ptr_ = new (addr) sh_msg_queue<T>();
			


		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared msg err :" << ex.what() << std::endl;

			SDelete(ptr_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};

	bool open(){
		SDelete(ptr_);
		SDelete(region_);
		SDelete(shm_);

		try{

			//open a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::open_only               //only open
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);
			std::cout<<"core shared msg open:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();
	
			//Construct the shared structure in memory
			ptr_ = static_cast<sh_msg_queue<T>*>(addr);


		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared msg err :" << ex.what() << std::endl;

			SDelete(ptr_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};

// 	void destruct(){
// 
// 		//SDelete(ptr_);
// 		SDelete(region_);
// 		SDelete(shm_);
// 
// 		std::cout<<"thread destruct shared msg remove:"<<share_name_<<std::endl;
// 		boost::interprocess::shared_memory_object::remove(share_name_.c_str());
// 	}

	bool put(const T &in){
		if (!ptr_)
		{
			std::cout<<"shared msg put err: check ptr"<<std::endl;
			return false;
		}

		return ptr_->push_back(in);

	};
	bool get(T &out){
		if (!ptr_)
		{
			std::cout<<"shared msg get err: check ptr"<<std::endl;
			return false;
		}
		return ptr_->pop_front(out);
	};
	sh_msg_queue<T>* getPtr(){
		return ptr_;
	};
	void end_msg_wait(){
		ptr_->end_wait();
	};

private:

	boost::interprocess::shared_memory_object* shm_;
	boost::interprocess::mapped_region* region_;

	sh_msg_queue<T>* ptr_;
	
	std::string share_name_;
};


#endif//_SHARED_MSG_WANGHONGTAO_2020_08_27_
