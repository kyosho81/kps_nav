#ifndef _SHARED_MULTIMAP2_WANGHONGTAO_2020_08_25_
#define _SHARED_MULTIMAP2_WANGHONGTAO_2020_08_25_

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>

#include "Comm/Comm.h"

//using namespace boost::interprocess;
namespace bip = boost::interprocess;

//Typedefs of allocators and containers
typedef bip::managed_shared_memory::segment_manager                       segment_manager_t;
typedef bip::allocator<void, segment_manager_t>                           void_allocator;
typedef bip::allocator<int, segment_manager_t>                            int_allocator;
typedef bip::vector<int, int_allocator>                                   int_vector;
typedef bip::allocator<int_vector, segment_manager_t>                     int_vector_allocator;
typedef bip::vector<int_vector, int_vector_allocator>                     int_vector_vector;
typedef bip::allocator<char, segment_manager_t>                           char_allocator;
typedef bip::basic_string<char, std::char_traits<char>, char_allocator>   char_string;

class complex_data
{
public:
	int               id_;
	int               status_;  // 0 idle 1 new 2 run 3 stop
	char_string       char_string_;
	int_vector_vector int_vector_vector_;

	typedef enum{SH_MUL_MAP_IDLE,SH_MUL_MAP_NEW,SH_MUL_MAP_RUN,SH_MUL_MAP_STOP} eSh_mul_map_sta;

public:
	//Since void_allocator is convertible to any other allocator<T>, we can simplify
	//the initialization taking just one allocator for all inner containers.
	complex_data(int status, const char *name, const void_allocator &void_alloc)
		: status_(status), char_string_(name, void_alloc), int_vector_vector_(void_alloc)
	{

	};
	//Other members...
};

//Definition of the multimap holding a string as key and complex_data as mapped type
typedef std::pair<const char_string, complex_data>                      map_value_type;
typedef std::pair<char_string, complex_data>                            movable_to_map_value_type;
typedef bip::allocator<map_value_type, segment_manager_t>                    map_value_type_allocator;
typedef bip::multimap< char_string, complex_data
	, std::less<char_string>, map_value_type_allocator>          complex_map_type;

typedef bip::multimap< char_string, complex_data
	, std::less<char_string>, map_value_type_allocator>::iterator complex_map_type_iter;

class sh_multimap{

public:

	sh_multimap(const std::string &str_sh_name)//:bip_mu_(bip::create_only,std::string(str_sh_name + "_mu").c_str())
	{
		bip_mu_ = 0;
		str_sh_name_ = str_sh_name;
		str_sh_map_name_ = str_sh_name_ + "_map";
		//bip_mu_.unlock();
	};
	~sh_multimap(){};

	void init( const bool &b_create){
		if(b_create){

			bip::named_mutex::remove(std::string(str_sh_name_ + "_mu").c_str());
			bip_mu_ = new bip::named_mutex(bip::create_only,std::string(str_sh_name_ + "_mu").c_str());

			bip::shared_memory_object::remove(str_sh_name_.c_str());
			seg_ptr_ = new bip::managed_shared_memory(bip::create_only,str_sh_name_.c_str(),65536);
			//An allocator convertible to any allocator<T, segment_manager_t> type
			p_alloc_inst_ = new void_allocator(seg_ptr_->get_segment_manager());
			mymap_ = seg_ptr_->construct<complex_map_type>
				//(object name), (first ctor parameter, second ctor parameter)
				(str_sh_map_name_.c_str())(std::less<char_string>(), *p_alloc_inst_);
		}else{
			bip_mu_ = new bip::named_mutex(bip::open_only,std::string(str_sh_name_ + "_mu").c_str());
			seg_ptr_ =  new bip::managed_shared_memory(bip::open_only,str_sh_name_.c_str());
			p_alloc_inst_ = new void_allocator(seg_ptr_->get_segment_manager());
			mymap_ = seg_ptr_->find<complex_map_type>(str_sh_map_name_.c_str()).first;
		}
	};
	void insert( const std::string &msg_name, const std::string &str_global_nm){
		
		boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(*bip_mu_);

		char_string  key_object(*p_alloc_inst_);
		key_object = msg_name.c_str();
		complex_data mapped_object(int(complex_data::SH_MUL_MAP_NEW), str_global_nm.c_str(), *p_alloc_inst_);
		map_value_type value(key_object, mapped_object);
		//Modify values and insert them in the multimap

		mymap_->insert(value);
		std::cout<<"insert shared multimap key:"<<msg_name<<" value:"<<str_global_nm<<std::endl;
	};
	
	bool erase_value(const std::string &str_global_nm){
		boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(*bip_mu_);
		for ( complex_map_type::iterator it = mymap_->begin() ; it != mymap_->end() ; ++it){
			if ( it->second.char_string_.c_str() == str_global_nm  ){
				mymap_->erase(it);
				return true;
				break;

			}
			
		}
		return false;
	}
	int get_res(std::vector<std::string> &vres,const std::string &msg_name){

		boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(*bip_mu_);

		char_string  key_object(*p_alloc_inst_);
		key_object = msg_name.c_str();
		std::pair<complex_map_type::iterator,complex_map_type::iterator> ret;

		ret = mymap_->equal_range(key_object);
		for ( complex_map_type::iterator it = ret.first ; it != ret.second ; ++it){
			vres.push_back(it->second.char_string_.c_str());
			//std::cout<<"get shared multimap key:"<<msg_name<<" value:"<<it->second.char_string_.c_str()<<std::endl;
		}
		return vres.size();

		//complex_map_type::iterator it = mymap_->find(key_object);
		//vres.push_back(it->second.char_string_.c_str());
	};
	void get_all(std::vector<std::string> &vres){
		boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(*bip_mu_);
		complex_map_type::iterator it = mymap_->begin();
		for ( ; it != mymap_->end() ; ++it){
			vres.push_back(it->second.char_string_.c_str());
		}
		
	};
	
	void reset(){
		bip::shared_memory_object::remove(str_sh_name_.c_str());

	};
private:

	bip::managed_shared_memory* seg_ptr_;
	complex_map_type* mymap_;
	void_allocator* p_alloc_inst_;

	std::string str_sh_name_;
	std::string str_sh_map_name_;
	
	bip::named_mutex* bip_mu_;
};
#endif//_SHARED_MULTIMAP2_WANGHONGTAO_2020_08_25_
