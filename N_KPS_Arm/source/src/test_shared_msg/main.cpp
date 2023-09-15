/*
#if 0
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interprocess/msg_shared_pool.hpp"

typedef struct {
	U8 a[1000000];
	int i;
} tp_big;

std::string str_sub_msg ;
void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	

	msg_shared_pool::end_sub_msg<int>(str_sub_msg);

	return;
}
bool call_back_odom(const tp_big &tp ){
	std::cout<<"sub odom:"<<cTimerDiff::total_ms() <<" "<<tp.i<<std::endl;

	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	msg_shared_pool::init(argv);

	while (1)
	{
		boost::function<bool(const tp_big&)> fnc;
		fnc = boost::bind(call_back_odom,_1);
		str_sub_msg = msg_shared_pool::sub_sh_msg("odom",fnc);

		msg_shared_pool::end_sub_msg<tp_big>(str_sub_msg);
	}
	
	

	for (int i = 0 ; i < 1000; ++i){
		tp_big tpp;
		tpp.i = i;
		msg_shared_pool::pub_sh_msg("odom",tpp);
		std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;
	}

	
	Config::getConfig()
	system("pause");

	return 0;
}

//#include <memory>
//
//template<class T>
//class user_defined_allocator : public std::allocator<T>
//{
//public:
//	typedef std::allocator<T> base_type;
//
//	// 必须要重新定义，否则容器如 list, set, map 使用时作用域只能到达 std::allocator
//	template<class Other>
//	struct rebind
//	{
//		typedef user_defined_allocator<Other> other;
//	};
//
//	// 构造函数必须实现
//	user_defined_allocator() {}
//
//	user_defined_allocator(user_defined_allocator<T> const&) {}
//
//	user_defined_allocator<T>& operator=(user_defined_allocator<T> const&) { return (*this); }
//
//	// idiom: Coercion by Member Template
//	template<class Other>
//	user_defined_allocator(user_defined_allocator<Other> const&) {}
//
//	// idiom: Coercion by Member Template
//	template<class Other>
//	user_defined_allocator<T>& operator=(user_defined_allocator<Other> const&) { return (*this); }
//
//	// 内存的分配与释放可以实现为自定义的算法，替换函数体即可
//	pointer allocate(size_type count) { return (base_type::allocate(count)); }
//
//	void deallocate(pointer ptr, size_type count) { base_type::deallocate(ptr, count); }
//};


#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace bip = boost::interprocess;
//共享内存上的指针
using ShMemRef = boost::shared_ptr<bip::managed_shared_memory>;
//共享内存分配器
template <typename T> using shm_alloc = bip::allocator<T, bip::managed_shared_memory::segment_manager>;
//共享内存map
template <typename K, typename V> using shared_map = bip::map<K, V, std::less<K>, shm_alloc<std::pair<K const, V> > >;


class Helper
{
public:
	using inner_alloc = shm_alloc<std::pair<int, ShMemRef>>;
	Helper(inner_alloc const& instance) : shm(instance) {}
private:
	int i;
	shared_map<int, ShMemRef> shm;
};

int main()
{
	ShMemRef shmInfo = boost::make_shared<bip::managed_shared_memory>(bip::open_or_create, "Main", 1024);

	using outer_alloc = shm_alloc<std::pair<const int, Helper>>;
	outer_alloc oa_instance(shmInfo->get_segment_manager());

	shared_map<int, Helper>* myHelpers = shmInfo->construct<shared_map<int, Helper>>("Memory")(oa_instance);

	Helper::inner_alloc ia_instance(shmInfo->get_segment_manager());
	Helper helper1(ia_instance), helper2(ia_instance), helper3(ia_instance);
	myHelpers->emplace(1, helper1);
	myHelpers->emplace(2, helper2);
	myHelpers->emplace(3, helper3);
}



#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

#include "Comm/Comm.h"

namespace bip = boost::interprocess;

//共享内存上的指针
#define ShMemRef  boost::shared_ptr<bip::managed_shared_memory>
//共享内存分配器
//template <typename T> using shm_alloc = bip::allocator<T, bip::managed_shared_memory::segment_manager>;
//共享内存map
//template <typename K, typename V> using shared_map = bip::map<K, V, std::less<K>, shm_alloc<std::pair<K const, V> > >;

template <typename K, typename V>
class Helper
{
public:

	Helper( bip::allocator<std::pair<K, V>, bip::managed_shared_memory::segment_manager> const& instance)
		: shm(instance) {

	};

private:
	int i;
	bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> > shm;
	//shared_map<int, ShMemRef> shm;
};

template <typename K, typename V ,int SHARED_SIZE>
class shared_map{
public:
	explicit shared_map(const std::string str_sh_name){

		shmInfo_ = boost::make_shared<bip::managed_shared_memory>(bip::open_or_create, str_sh_name.c_str(), SHARED_SIZE);
		std::string str_alo_name = str_sh_name +"_Memory";
		bip::allocator<std::pair<const K, V>, bip::managed_shared_memory::segment_manager> oa_instance(shmInfo_->get_segment_manager());
		sh_map_ptr_ =  shmInfo_->find_or_construct< bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> >>(str_alo_name.c_str())(oa_instance);
		
	};
	V& operator[] ( K key ){
		return (*sh_map_ptr_)[key];
	};

	int get_all_elm(std::map<K,V> &m_res){
		
		bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> >::iterator it = sh_map_ptr_->begin();
		for ( ; it != sh_map_ptr_->end(); ++it){
			m_res[it->first] = it->second;
		}
		return m_res.size();
	};
	bool find_elm(V &value,const K &key){
		bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> >::iterator it = sh_map_ptr_->find(key);
		if (it != sh_map_ptr_->end())
		{
			value = it->second;
			return true;
		}
		return false;
	};
	int print_all_elm(){
		int i_count = 0;
		bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> >::iterator it = sh_map_ptr_->begin();
		for ( ; it != sh_map_ptr_->end(); ++it){
			std::cout<<"key:"<<it->first<<" v:"<<it->second<<std::endl;
			i_count++;
		}
		return i_count;
	};
private:
	boost::shared_ptr<bip::managed_shared_memory> shmInfo_;
	bip::map< K, V, std::less<K>, bip::allocator< std::pair<K const, V>, bip::managed_shared_memory::segment_manager> >* sh_map_ptr_;

};

//bip::shared_memory_object::remove("Main");
boost::shared_ptr<bip::managed_shared_memory> shmInfo = boost::make_shared<bip::managed_shared_memory>(bip::open_or_create, "Main", 1024);
// 
// 	using outer_alloc = shm_alloc<std::pair<const int, Helper>>;
bip::allocator<std::pair<const int, std::string>, bip::managed_shared_memory::segment_manager> oa_instance(shmInfo->get_segment_manager());
// 	outer_alloc oa_instance(shmInfo->get_segment_manager());

// 	shared_map<int, Helper>* myHelpers = shmInfo->construct<shared_map<int, Helper>>("Memory")(oa_instance);
bip::map< int, std::string, std::less<int>, bip::allocator< std::pair<int const, std::string>, bip::managed_shared_memory::segment_manager> >* myHelpers = 
	shmInfo->find_or_construct< bip::map< int, std::string, std::less<int>, bip::allocator< std::pair<int const, std::string>, bip::managed_shared_memory::segment_manager> >>("Memory")(oa_instance);

bip::allocator<std::pair<int, std::string >, bip::managed_shared_memory::segment_manager> ia_instance(shmInfo->get_segment_manager());
//(*myHelpers)[1] = "aa";
(*myHelpers)[1] = "bb";
std::cout<<"find:"<<(*myHelpers)[1]<<std::endl;

shared_map<int,std::string,1024*100> sm("shared_para");

for (int i = 0 ; i < 100 ; ++i ){
	sm[i] = cComm::ConvertToString(i*10);
	std::cout<<"ssfind:"<<i<<" data:"<<sm[i]<<std::endl;
}

#include "interprocess/msg_shared_pool.hpp"

#include "interpro_shared/shared_map.hpp"
#include "interpro_shared/shared_multimap.hpp"

#include "Comm/TimerDiff.h"

class  _sst
{
public:
	int i;
	float f;
	std::string str;

friend std::ostream& operator<<(std::ostream& out,const _sst &data){
		out<<data.i<<" "<<data.f<<" "<<data.str;
		return out;
	};
};

bool call_back_odom(const int &tp ){
	std::cout<<"sub odom:"<<cTimerDiff::total_ms() <<" "<<tp<<std::endl;

	return true;
}

int main(int argc, char* argv[]){

#if 1
	if(argc> 1){

		msg_shared_pool::reset();
		msg_shared_pool::init(argv);

		boost::function<bool(const int&)> fnc;
		fnc = boost::bind(call_back_odom,_1);
		std::string str_sub_msg = msg_shared_pool::sub_sh_msg("odom",fnc);


		for (int i = 0 ; i < 100; ++i)
		{
			//msg_shared_pool::pub_sh_msg("odom", i );
			
			std::cout<<"count:"<<i<<std::endl;
			msg_shared_pool::print_all_msg();
			SLEEP(1000);
		}
		msg_shared_pool::end_sub_msg<int>(str_sub_msg);
		
	}else{
		//msg_shared_pool::reset();
		msg_shared_pool::init(argv);

// 		boost::function<bool(const int&)> fnc;
// 		fnc = boost::bind(call_back_odom,_1);
// 		std::string str_sub_msg = msg_shared_pool::sub_sh_msg("odom",fnc);


		for (int i = 0 ; i < 100; ++i)
		{
			std::cout<<"count:"<<i<<std::endl;
			msg_shared_pool::print_all_msg();

			msg_shared_pool::pub_sh_msg("odom", i );
			SLEEP(1000);
		}
		//msg_shared_pool::end_sub_msg<int>(str_sub_msg);
	}
	return 0;
#endif
	shared_multimap<std::string,std::string,1024*10> gsh_msg_pair;

	if(argc> 1){
		
		gsh_msg_pair.reset("global_msg_pair");
		gsh_msg_pair.init("global_msg_pair");
		
		while (1)
		{
			std::cout<<"insert data:"<<std::endl;
			std::string str;
			std::cin>>str;
			gsh_msg_pair.insert(str,str + "a1");
			gsh_msg_pair.print_all_elm();
		}
		gsh_msg_pair.insert("aa","a1");
		gsh_msg_pair.insert("aa","a2");
		gsh_msg_pair.insert("aa","a2");
		gsh_msg_pair.insert("aa","a3");
		gsh_msg_pair.insert("bb","a1");
		gsh_msg_pair.print_all_elm();
		gsh_msg_pair.erase_value("a1");
		gsh_msg_pair.print_all_elm();
		system("pause");
	}else{

		gsh_msg_pair.init("global_msg_pair");

		while(1){
			gsh_msg_pair.print_all_elm();
			
			SLEEP(500);
		}

		gsh_msg_pair.insert("bb","a1");
		gsh_msg_pair.print_all_elm();
		std::multimap<std::string,std::string> ml_res;

		gsh_msg_pair.find_elm(ml_res,"aa");
		system("pause");
	}
	return 0;
	//gsh_msg_pair.erase_key("aa");
	gsh_msg_pair.erase_value("a1");
	std::multimap<std::string,std::string> ml_res;

	gsh_msg_pair.find_elm(ml_res,"aa");
	gsh_msg_pair.get_all_elm(ml_res);
	return 0;
	
// 	shared_map<int,_sst,1024*100> smtt("ttt");
// 
// 
// 	for (int i = 0 ; i < 100 ; ++i ){
// 		_sst ts;
// 		ts.i = i;
// 		ts.f = i/100;
// 		ts.str = cComm::ConvertToString(i*10);
// 		smtt[i] = ts;
// 		//std::cout<<"ssfind:"<<i<<" data:"<<smtt[i].i<<" f:"<<smtt[i].f<<" str:"<<smtt[i].str<<std::endl;
// 	}
// 	smtt.print_all_elm();
// 
// 	std::map<int,_sst> m_res;
// 	smtt.get_all_elm(m_res);

	shared_multimap<int,_sst,1024*100> smtt22;
	smtt22.reset("tss");
	smtt22.init("tss");
	std::multimap<int,_sst> mres2;
	_sst ts;
	ts.i = 1;
	ts.f = 0.1;
	ts.str = "12";
	smtt22.insert(1,ts);

	//smtt22.clear();
	smtt22.reset("tss");
	smtt22.init();
	smtt22.insert(1,ts);
	ts.str = "13";
	smtt22.insert(1,ts);
	smtt22.insert(2,ts);
	smtt22.get_all_elm(mres2);
	smtt22.erase_key(1);
	smtt22.get_all_elm(mres2);


}
#endif
*/
#if 0
#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/msg_shared_pool.hpp"
#include "interprocess/shared_pool.hpp"

//using namespace boost::interprocess;

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}

bool call_back_odom(const int &tp ){
	std::cout<<"sub odom:"<<cTimerDiff::total_ms() <<" "<<tp<<std::endl;

	return true;
}
// int test_sh_msg(int argc, char* argv[]){
// 	if (argc > 1)
// 	{
// 		shared_msg<int> sm("aa");
// 		sm.init();
// 
// 		sh_msg_queue<int>* msg_ptr = sm.getPtr();
//		msg_ptr->set_th_status(sh_msg_queue<int>::MSG_TH_RUN);
// 
// 		sh_msg_queue<int>::eMsg_th_sta sta = msg_ptr->get_th_status();
// 		std::cout<<"sta:"<<int(sta)<<std::endl;
// 
// 		for (int i = 0 ; i < 1000 ; ++i){
// 			sm.put(i);
// 			SLEEP(1000);
// 		}
// 	}else{
// 		shared_msg<int> sm("aa");
// 		sm.open();
// 
// 		sh_msg_queue<int>* msg_ptr = sm.getPtr();
		//msg_ptr->set_th_status(msg_queue<int>::MSG_TH_RUN);
// 		sh_msg_queue<int>::eMsg_th_sta sta;
// 		while(1){
// 			int i = 0 ;
// 			sm.get(i);
// 			sta = msg_ptr->get_th_status();
// 			std::cout<<"aa:"<<i<<" sta:"<<int(sta)<<std::endl;
// 		}
// 	}
// 	return 0;
// }

int test_msg_pool(int argc, char* argv[]){
	if (argc > 1)
	{
		msg_shared_pool::init(argv);

		boost::function<bool(const int&)> fnc;
		fnc = boost::bind(call_back_odom,_1);
		std::string str_sub_msg = msg_shared_pool::sub_sh_msg("odom",fnc);

// 			for (int i = 0 ; i < 100; ++i)
// 			{
// 				std::cout<<"count:"<<i<<std::endl;
// 
// 				msg_shared_pool::pub_sh_msg("odom", i );
// 				SLEEP(1000);
// 			}
		while(b_run){

			SLEEP(1000);
		}

		msg_shared_pool::end_sub_msg<int>(str_sub_msg);


		
	}else{
		msg_shared_pool::init(argv);

		for (int i = 0 ; i < 100; ++i)
		{
			std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;

			if(!msg_shared_pool::pub_sh_msg("odom", i )){
				std::cout<<"pub_sh_msg(odom) err!"<<std::endl;
			}
			if(!b_run)
				break;
			SLEEP(100);
		}
	}

	return 0;

}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

//	test_msg_pool(argc,argv);
	shared_pool::init(argv);

	if (argc > 1)
	{
		//amcl
		boost::function<void(  const int &amcl_pos )> fnc_amcl;
		fnc_amcl = boost::bind(call_back_odom,_1);
		shared_pool::Subscribe(shared_pool::name(),"odom",fnc_amcl);

		while(b_run){
			SLEEP(1000);
		}


	}else{
		for (int i = 0 ; i < 100 ; ++i ){
			std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;
			shared_pool::Publish(shared_pool::name(),"odom",i);

			SLEEP(100);
		}
		
	}

	shared_pool::destructor();
	return 0;

	if(argc > 1){

	
		//Remove shared memory on construction and destruction
		struct shm_remove
		{
			shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
			//~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
		} remover;
		//根据具体情况确实是否需要对内存数据进行remove操作。本文的写进程和读进程是分开的，所以保留缓存中的数据。

		//   //Create shared memory
		bip::managed_shared_memory segment(bip::create_only,"MySharedMemory",65536);


		//write------begin-----------
		//An allocator convertible to any allocator<T, segment_manager_t> type
		void_allocator alloc_inst (segment.get_segment_manager());
		//Construct the shared memory map and fill it
		complex_map_type *mymap = segment.construct<complex_map_type>
			//(object name), (first ctor parameter, second ctor parameter)
			("MyMap")(std::less<char_string>(), alloc_inst);

		for(int i = 0; i < 50; ++i)
		{
			//Both key(string) and value(complex_data) need an allocator in their constructors
			char_string  key_object(alloc_inst);
			std::string temp = "key" + boost::lexical_cast< std::string >(i);
			key_object=temp.c_str();
			temp = "default_name_" + boost::lexical_cast<std::string>(i);
			complex_data mapped_object(i, temp.c_str(), alloc_inst);
			map_value_type value(key_object, mapped_object);
			//Modify values and insert them in the map
			mymap->insert(value);
		}
		//write------end-----------
		return 0;
	}else{

		//read------begin------
		//Find the vector using the c-string name
		bip::managed_shared_memory segment(bip::open_only,"MySharedMemory");
		complex_map_type *myvector = segment.find<complex_map_type>("MyMap").first;
		complex_map_type_iter iter;

		//print the result
		std::cout<<"size of map="<<myvector->size()<<std::endl;

		for (iter = myvector->begin(); iter != myvector->end(); ++iter)
		{
			std::cout <<"key:"<< iter->first <<std::endl;
			std::cout<<"value:"<<iter->second.id_<<","<<iter->second.char_string_<<std::endl;
		}
		//write------end-------
	}
}
#endif

#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/sh_pool.hpp"

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}
bool call_back_odom(const int &tp ){
	std::cout<<"sub odom:"<<cTimerDiff::total_ms() <<" "<<tp<<std::endl;

	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	

	if(argc == 1){

		msg_shared_pool::init(argv);

		boost::function<bool(const int&)> fnc;
		fnc = boost::bind(call_back_odom,_1);
		std::string str_sub_msg = SUB_MSG_SH_POOL("odom",fnc);

		//while(b_run){

			SLEEP(10000);
		//}
		//msg_shared_pool::destroy(str_sub_msg);
		END_MSG_SH_POOL(int,str_sub_msg);
	}else{

		msg_shared_pool::init(argv);

		for (int i = 0 ; i < 100; ++i)
		{
			std::cout<<"count:"<<i<<std::endl;

			PUB_MSG_SH_POOL("odom", i );
			SLEEP(1000);
		}
	}
	

	return 0;
}