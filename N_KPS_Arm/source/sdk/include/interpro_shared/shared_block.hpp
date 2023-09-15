#ifndef _SHARED_BLOCK_WANGHONGTAO_2020_08_27_
#define _SHARED_BLOCK_WANGHONGTAO_2020_08_27_


#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


#include "Comm.h"
#include "interpro_shared/sh_shared_block.hpp"
//#include "interprocess/con_shared_list.hpp"

class shared_block
{
public:
	explicit shared_block(std::string share_name,U32 dsize):share_name_(share_name),dsize_(dsize){
		shm_ = 0;
		region_ = 0;

		ptr_data_ = 0;
		ptr_ = 0;
	};

	~shared_block(){

		SDelete(region_);
		SDelete(shm_);
		
	};

	bool init(){

		SDelete(ptr_);
		SDelete(region_);
		SDelete(shm_);

 		try{

			std::cout<<"core shared block remove:"<<share_name_<<std::endl;
			boost::interprocess::shared_memory_object::remove(share_name_.c_str());

			//Create a shared memory object.
			shm_  = new boost::interprocess::shared_memory_object
				(boost::interprocess::create_only               //only create
				,share_name_.c_str()           //name
				,boost::interprocess::read_write                //read-write mode
				);
			std::cout<<"core shared block create:"<<share_name_<<std::endl;
			//Set size


			U32 total_size = sizeof(msg_block);
			std::cout<<"core shared block size:"<<total_size<<std::endl;
			total_size += dsize_;

			shm_->truncate(total_size);
			std::cout<<"core construct shared block:"<<share_name_<<" size:"<<total_size<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();

			//Construct the shared structure in memory
			ptr_ = new (addr) msg_block();
			ptr_->init(dsize_);
			ptr_data_ = (U8*)addr + sizeof(msg_block);

			std::cout<<"core get shared block ptr:"<<share_name_<<std::endl;

		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core init shared block create err :" << ex.what() << std::endl;

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
			std::cout<<"core shared block open:"<<share_name_<<std::endl;

			//Map the whole shared memory in this process
			region_ = new boost::interprocess::mapped_region
				(*shm_                       //What to map
				,boost::interprocess::read_write //Map it as read-write
				);

			//Get the address of the mapped region
			void * addr       = region_->get_address();
	
			//Construct the shared structure in memory
			ptr_ = static_cast<msg_block*>(addr);

			ptr_data_ = (U8*)addr + sizeof(msg_block);

			std::cout<<"core get shared block ptr:"<<share_name_<<std::endl;

		}
		catch(boost::interprocess::interprocess_exception &ex){

			std::cout<<"core shared block open err :" << ex.what() << std::endl;

			SDelete(ptr_);
			SDelete(region_);
			SDelete(shm_);
			return false;
		}
		return true;
	};


	bool read(U8* out,U32 offset,U32 &len){
		if (!ptr_ && !ptr_data_)
		{
			std::cout<<"core shared block read err! check ptr"<<std::endl;
			return false;
		}

		return ptr_->read(out,offset,len,ptr_data_);

	};
	bool write(U8* in,U32 offset,U32 &len){
		if (!ptr_ && !ptr_data_)
		{
			std::cout<<"core shared block write err! check ptr"<<std::endl;
			return false;
		}
		return ptr_->write(in,offset,len,ptr_data_);

	};

	msg_block* getPtr(){
		return ptr_;
	};
	U8* getDataPtr(){
		return ptr_data_;
	};


private:

	boost::interprocess::shared_memory_object* shm_;
	boost::interprocess::mapped_region* region_;

	msg_block* ptr_;
	U8* ptr_data_;
	U32 dsize_;


	std::string share_name_;
};


#endif//_SHARED_BLOCK_WANGHONGTAO_2020_08_27_
