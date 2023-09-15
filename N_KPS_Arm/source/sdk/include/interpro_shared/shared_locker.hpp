#ifndef _SHARED_LOCKER_WANGHONGTAO_2020_08_27_
#define _SHARED_LOCKER_WANGHONGTAO_2020_08_27_


#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


#include "Comm.h"

class shared_locker
{
public:
	explicit shared_locker(std::string share_name):share_name_(share_name){
		
		shm_ = 0;
		region_ = 0;

		mu_lock_ = 0;
	};

	~shared_locker(){

		SDelete(region_);
		SDelete(shm_);
		
	};

	bool init(){

		SDelete(mu_lock_);

		SDelete(region_);
		SDelete(shm_);

 		try{

			std::cout<<"core shared locker remove:"<<share_name_<<std::endl;
			boost::interprocess::shared_memory_object::remove(share_name_.c_str());

			//Create a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::create_only               //only create
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);

			std::cout<<"core shared locker create:"<<share_name_<<std::endl;
			//Set size

			U32 total_size = sizeof(boost::interprocess::interprocess_mutex);
			std::cout<<"core shared locker size:"<<total_size<<std::endl;

			shm_->truncate(total_size);
			std::cout<<"core shared locker construct :"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();

			//Construct the shared structure in memory
			mu_lock_ = new (addr) boost::interprocess::interprocess_mutex();

		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared locker create err :" << ex.what() << std::endl;

			SDelete(mu_lock_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};

	bool open(){
		SDelete(mu_lock_);
		SDelete(region_);
		SDelete(shm_);

		try{

			//open a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::open_only               //only open
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);
			std::cout<<"core shared locker open:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();
	
			//Obtain a pointer to the shared structure  
			mu_lock_ = static_cast<boost::interprocess::interprocess_mutex*>(addr);

			std::cout<<"client get shared locker ptr:"<<share_name_<<std::endl;
		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared locker open err :" << ex.what() << std::endl;

			SDelete(mu_lock_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};

	void lock(){
		if (mu_lock_){
			mu_lock_->lock();
		}
	};

	void unlock(){
		if (mu_lock_){
			mu_lock_->unlock();
		}
	};

private:

	boost::interprocess::shared_memory_object* shm_;
	boost::interprocess::mapped_region* region_;

	boost::interprocess::interprocess_mutex* mu_lock_;

	std::string share_name_;
};


#endif//_SHARED_LOCKER_WANGHONGTAO_2020_08_27_
