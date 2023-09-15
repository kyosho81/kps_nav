#ifndef _MSG_SHARED_POOL_WANGHONGTAO_2020_09_24_
#define _MSG_SHARED_POOL_WANGHONGTAO_2020_09_24_

#include <fstream>
#include <map>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>

#include "interpro_shared/shared_msg.hpp"
#include "interpro_shared/shared_multimap.hpp"

class msg_shared_pool
{
public:
	msg_shared_pool();
	~msg_shared_pool();

	static void init(const std::string &str_nm ,bool b_create = false){
		nm_ = str_nm;
		g_sh_multimap_.init(b_create);

		std::cout<<"shared msg init!"<<std::endl;
	};
	static void init(char *argv[] ,bool b_create = false){
		nm_ = argv[0];
		nm_ = cComm::Get_FileName(nm_);

		g_sh_multimap_.init(b_create);

		std::cout<<"shared msg init!"<<std::endl;
	};
	static void reset(){
		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);

		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it ){
			bip::shared_memory_object::remove((*it).c_str());
			std::cout<<"remove shared msg:"<<*it<<std::endl;
		}
		
		g_sh_multimap_.reset();
	};
	static void print_all_msg(){
		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);
		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it){
			std::cout<<*it<<std::endl;
		}
	
	};

	template<typename T>
	static bool pub_sh_msg(std::string msg_name,const T &data){
		
		bool b_send_one = false;
		
		std::vector<std::string> vres;

		get_gm_shared_msg_gnm( vres, msg_name);
		if (vres.size() < 1)
		{
			std::cout<<"shared msg pub err! no sub "<<msg_name<<std::endl;
			return false;
		}
		

		std::vector<std::string>::iterator it = vres.begin();
		for ( ; it != vres.end() ; ++it ){
		
			void* local_ptr = getMsgDataPtr(*it);
			//local process thread no reg ptr
			if (!local_ptr){
				//try open shared ptr
				local_ptr = getMsgDataSh<T>(*it);
			}
			if (!local_ptr)
			{
				continue;
			}

			shared_msg<T>* sh_msg_container = static_cast<shared_msg<T>*>(local_ptr);
			if (sh_msg_container->getPtr()->get_th_status() == sh_msg_queue<T>::MSG_TH_RUN )
			{
				sh_msg_container->put(data);
				b_send_one = true;
			}else{
				//sub msg process is close
				std::cout<<"sub msg process closed!!!!!!!!!!!!!!!"<<std::endl;
				m_global_shared_data_ptr_.erase(*it);
			}
		}
		return b_send_one;
	};

	template<typename T>
	static std::string sub_sh_msg(std::string msg_name,boost::function<bool( const T &t)> fnc){
		
		std::string msg_global_name = get_sub_name(msg_name);
		
		void* local_ptr = getMsgDataPtr(msg_global_name);
		if (!local_ptr)
		{
			local_ptr = createMsgDataPtr<T>( msg_name, msg_global_name);
		}
		shared_msg<T>* sh_msg_container = static_cast<shared_msg<T>*>(local_ptr);

		boost::thread th(boost::bind(&msg_shared_pool::sub_thread<T>,sh_msg_container,fnc));

		return msg_global_name;
	};

	template<typename T>
	static void end_sub_msg(const std::string &msg_global_name){

		//remove from shared msg first,pub will no happen
		erase_gm_shared_msg_gnm(msg_global_name);

		void* local_ptr = getMsgDataPtr(msg_global_name);
		if(local_ptr){


			shared_msg<T>* t_ptr = static_cast<shared_msg<T>*>(local_ptr);
			std::cout<<"main thread end sub msg 1111"<<std::endl;

			t_ptr->end_msg_wait();
			
			std::cout<<"main thread wait sub thread over!!!!!33333"<<std::endl;
			
			//remove from local msg map
			m_global_shared_data_ptr_.erase(msg_global_name);
			//destruct shared msg
			SDelete(t_ptr);
			
			if(!bip::shared_memory_object::remove(msg_global_name.c_str())){
				assert(false);
			}
		}
		
	};

protected:
private:
	// sub msg global name, every thread can create one message list
	static std::string get_sub_name(const std::string &str_msg_name){

		std::stringstream ss;
		ss<<nm_<<"_"<<boost::this_thread::get_id()<<"_"<<str_msg_name;
		return ss.str();

	};
	static std::string nm_;

	//
	template<typename T>
	static void sub_thread(shared_msg<T>* sh_msg_container,boost::function<bool( const T &t)> fnc){
		assert(sh_msg_container);
		sh_msg_queue<T>* msg_ptr = sh_msg_container->getPtr();
		msg_ptr->set_th_status(sh_msg_queue<T>::MSG_TH_RUN);
		std::cout<<"begin sub_thread"<<std::endl;

		T tmp;

		while( 1 ){

			if (sh_msg_container->get(tmp))
			{
				if(!fnc(tmp)){
					std::cout<<"sub fnc return false,break sub thread"<<std::endl;
					break;
				}
			}else{
				break;
			}
		}
		std::cout<<"sub thread break loop and set msg queue IDLE !2222"<<std::endl;
		msg_ptr->set_th_status(sh_msg_queue<T>::MSG_TH_IDLE);
		

	};

private:
	//create shared msg , and make init(remove history)
	template<typename T>
	static void* createMsgDataPtr(const std::string &msg_name, const std::string &str_global_nm){
		shared_msg<T>* sh_msg_container = new shared_msg<T>(str_global_nm);
		sh_msg_container->init();
		void* p = (void*)sh_msg_container;
		//insert into local msg map
		m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(str_global_nm,p) );
		//insert into shared msg map
		insert_gm_shared_msg_gnm(msg_name,str_global_nm);

		return p;
	};
	
	static void* getMsgDataPtr(const std::string &str_global_nm){
		std::map<std::string,void*>::iterator it = m_global_shared_data_ptr_.find(str_global_nm);
		if (it != m_global_shared_data_ptr_.end())
		{
			return it->second;
		}
		return 0;

	};
	//open shared msg ,just open
	template<typename T>
	static void* getMsgDataSh(const std::string &str_global_nm){
		void* p = 0;
		shared_msg<T>* sm_ptr = new shared_msg<T>(str_global_nm);
		if (sm_ptr->open())
		{

			if (sm_ptr->getPtr()->get_th_status() == sh_msg_queue<T>::MSG_TH_RUN)
			{
				p = (void*)sm_ptr;
				m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(str_global_nm,p) );

			}else{
				std::cout<<"str_global_nm state err! no run:"<<str_global_nm<<std::endl;
			}
			
		}
		return p;
	};

	static std::map<std::string,void*> m_global_shared_data_ptr_;

	////////////////////////////////////////
	static void insert_gm_shared_msg_gnm( const std::string &msg_name , const std::string &str_global_nm){

		g_sh_multimap_.insert(msg_name,str_global_nm);

	};

	static bool erase_gm_shared_msg_gnm(const std::string &str_global_nm){

		return g_sh_multimap_.erase_value(str_global_nm);
	};
	static void get_gm_shared_msg_gnm(std::vector<std::string> &vres,const std::string &msg_name){
		
		vres.clear();

		g_sh_multimap_.get_res(vres,msg_name);

	};

	static sh_multimap g_sh_multimap_;
};

// std::map<std::string,void*> msg_shared_pool::m_global_shared_data_ptr_;
// sh_multimap msg_shared_pool::g_sh_multimap_("core_shared_msg_list");
// std::string msg_shared_pool::nm_;


#endif//_MSG_SHARED_POOL_WANGHONGTAO_2020_09_24_
