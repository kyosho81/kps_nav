#ifndef _SHARED_PIPE_SEG_WANGHONGTAO_2020_09_22_
#define _SHARED_PIPE_SEG_WANGHONGTAO_2020_09_22_


#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


#include "Comm.h"
#include "interpro_shared/sh_pipe_list.hpp"

template<U32 PIPE_BUFFER_SIZE>
class shared_pipe_seg
{
public:
	explicit shared_pipe_seg(std::string share_name):share_name_(share_name){
		shm_ = 0;
		region_ = 0;
		ptr_ = 0;
	};

	~shared_pipe_seg(){

		SDelete(region_);
		SDelete(shm_);
		
	};
	

	bool init(){
		SDelete(ptr_);
		SDelete(region_);
		SDelete(shm_);

 		try{

			std::cout<<"core shared pipe remove:"<<share_name_<<std::endl;
			boost::interprocess::shared_memory_object::remove(share_name_.c_str());

			//Create a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::create_only               //only create
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);
			std::cout<<"core shared pipe create:"<<share_name_<<std::endl;
			//Set size

			std::cout<<"pipe struct size:"<<sizeof(sh_pipe_list<PIPE_BUFFER_SIZE>)<<std::endl;
			shm_->truncate(sizeof(sh_pipe_list<PIPE_BUFFER_SIZE>));
			std::cout<<"sh pipe construct shared:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();

			//Construct the shared structure in memory
			ptr_ = new (addr) sh_pipe_list<PIPE_BUFFER_SIZE>();


		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared pipe create err :" << ex.what() << std::endl;

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
			std::cout<<"core shared pipe open:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();
	
			//Construct the shared structure in memory
			ptr_ = static_cast<sh_pipe_list<PIPE_BUFFER_SIZE>*>(addr);


		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared pipe open err :" << ex.what() << std::endl;

			SDelete(ptr_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};


	void push_back(std::string name,U8* data,U32 len,bool wait_full = true){
		if (ptr_)
		{
			ptr_->push_back(name,data,len,wait_full);
		}

	};
	void pop_front(std::string &name,U8* data,U32 &len){
		if (ptr_)
		{
			ptr_->pop_front(name,data,len);
		}

	};
	sh_pipe_list<PIPE_BUFFER_SIZE>* getPtr(){
		return ptr_;
	};
	void end_msg_wait(){
		ptr_->end_wait();
	};

private:

	boost::interprocess::shared_memory_object* shm_;
	boost::interprocess::mapped_region* region_;

	sh_pipe_list<PIPE_BUFFER_SIZE>* ptr_;
	
	std::string share_name_;
};

#endif//_SHARED_PIPE_SEG_WANGHONGTAO_2020_09_22_
