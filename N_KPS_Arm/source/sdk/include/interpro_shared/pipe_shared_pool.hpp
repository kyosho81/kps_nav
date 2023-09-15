#ifndef _PIPE_SHARED_POOL_KYOSHO_2020_09_24_
#define _PIPE_SHARED_POOL_KYOSHO_2020_09_24_

#include <fstream>
#include <map>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>

#include "interpro_shared/shared_pipe.hpp"
#include "interpro_shared/shared_multimap.hpp"

#define PIPE_BUFFER_SIZE 40960

class pipe_shared_pool
{
public:
	pipe_shared_pool();
	~pipe_shared_pool();

	static void init(const std::string &str_nm ,bool b_create = false){
		nm_ = str_nm;
		g_sh_multimap_.init(b_create);

		std::cout<<"shared pipe init!"<<std::endl;
	};
	static void init(char *argv[] ,bool b_create = false){
		nm_ = argv[0];
		nm_ = cComm::Get_FileName(nm_);

		g_sh_multimap_.init(b_create);

		std::cout<<"shared pipe init!"<<std::endl;
	};
	static void reset(){
		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);

		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it ){
			bip::shared_memory_object::remove((*it).c_str());
			std::cout<<"remove shared pipe:"<<*it<<std::endl;
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

	static bool push_back(const std::string &pipe_name,const std::string &data_name,U8* data,U32 len,bool wait_full = true){

		bool b_send_one = false;
		
		std::vector<std::string> vres;

		get_gm_shared_msg_gnm( vres, pipe_name);
		if (vres.size() < 1)
		{
			std::cout<<"shared pipe sub nothing! pipe name:"<<pipe_name<<std::endl;
			return false;
		}
		

		std::vector<std::string>::iterator it = vres.begin();
		for ( ; it != vres.end() ; ++it ){
		
			void* local_ptr = getMsgDataPtr(*it);
			//local process thread no reg ptr
			if (!local_ptr){
				//try open shared ptr
				local_ptr = getMsgDataSh(*it);
			}
			if (!local_ptr)
			{
				continue;
			}

			shared_pipe_seg<PIPE_BUFFER_SIZE>* sh_pipe_container = static_cast<shared_pipe_seg<PIPE_BUFFER_SIZE>*>(local_ptr);
			if (sh_pipe_container->getPtr()->get_th_status() == sh_pipe_list<PIPE_BUFFER_SIZE>::PIPE_TH_RUN )
			{
				sh_pipe_container->push_back( data_name, data, len, wait_full);
				b_send_one = true;
			}else{
				std::cout<<"sub pipe process closed!!!!!!!!!!!!!!!"<<std::endl;
				m_global_shared_data_ptr_.erase(*it);
			}
		}
		return b_send_one;
	};
	static std::string sub_pipe(const std::string &pipe_name,boost::function<bool (std::string name,U8* data,U32 len)> fnc ){
			
		std::string msg_global_name = get_sub_name(pipe_name);
		
		void* local_ptr = getMsgDataPtr(msg_global_name);
		if (!local_ptr){
			local_ptr = createMsgDataPtr( pipe_name, msg_global_name);
		}

		shared_pipe_seg<PIPE_BUFFER_SIZE>* sh_pipe_container = static_cast<shared_pipe_seg<PIPE_BUFFER_SIZE>*>(local_ptr);

		std::cout<<"create pipe sub thread:"<<pipe_name<<std::endl;
		boost::thread th(boost::bind(&pipe_shared_pool::sub_pipe_thread,sh_pipe_container,fnc));

		return msg_global_name;
	};

	static void end_sub_msg(const std::string &msg_global_name){

		//remove from shared msg first,pub will no happen
		erase_gm_shared_msg_gnm(msg_global_name);

		void* local_ptr = getMsgDataPtr(msg_global_name);
		if(local_ptr){

			shared_pipe_seg<PIPE_BUFFER_SIZE>* sh_pipe_container = static_cast<shared_pipe_seg<PIPE_BUFFER_SIZE>*>(local_ptr);

			std::cout<<"main thread end sub pipe 1111"<<std::endl;

			sh_pipe_container->end_msg_wait();
			
			std::cout<<"main thread wait sub pipe over!!!!!33333"<<std::endl;
			
			//remove from local msg map
			m_global_shared_data_ptr_.erase(msg_global_name);
			//destruct shared msg
			SDelete(sh_pipe_container);
			
			bip::shared_memory_object::remove(msg_global_name.c_str());
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
	static void sub_pipe_thread(shared_pipe_seg<PIPE_BUFFER_SIZE>* sh_pipe_container,boost::function<bool( std::string name,U8* data,U32 len )> fnc){

		assert(sh_pipe_container);
		sh_pipe_list<PIPE_BUFFER_SIZE>* pipe_ptr = sh_pipe_container->getPtr();
		pipe_ptr->set_th_status(sh_pipe_list<PIPE_BUFFER_SIZE>::PIPE_TH_RUN);
		std::cout<<"begin pipe sub_thread"<<std::endl;

		std::string name;
		U8* data = new U8[PIPE_BUFFER_SIZE];
		U32 len = PIPE_BUFFER_SIZE;

		while( 1 ){

			if(pipe_ptr->pop_front(name,data,len)){
				if(!fnc(name,data,len)){
					std::cout<<"sub pipe fnc return false,break sub thread"<<std::endl;
					break;
				}
			}else{
				break;
			}
			

		}
		std::cout<<"sub thread break loop and set msg queue IDLE !2222"<<std::endl;
		pipe_ptr->set_th_status(sh_pipe_list<PIPE_BUFFER_SIZE>::PIPE_TH_IDLE);
		

	};

private:
	//create shared pipe , and make init(remove history)

	static void* createMsgDataPtr(const std::string &pipe_name, const std::string &str_global_nm){
		shared_pipe_seg<PIPE_BUFFER_SIZE>* sh_pipe_container = new shared_pipe_seg<PIPE_BUFFER_SIZE>(str_global_nm);
		sh_pipe_container->init();
		void* p = (void*)sh_pipe_container;
		//insert into local msg map
		m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(str_global_nm,p) );
		//insert into shared msg map
		insert_gm_shared_msg_gnm(pipe_name,str_global_nm);

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
	//open shared pipe ,just open

	static void* getMsgDataSh(const std::string &str_global_nm){
		void* p = 0;
		shared_pipe_seg<PIPE_BUFFER_SIZE>* pipe_ptr = new shared_pipe_seg<PIPE_BUFFER_SIZE>(str_global_nm);
		if (pipe_ptr->open())
		{

			//if (pipe_ptr->getPtr()->get_th_status() == sh_pipe_list<PIPE_BUFFER_SIZE>::MSG_TH_RUN)
			{
				p = (void*)pipe_ptr;
				m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(str_global_nm,p) );

			}
// 			else{
// 				std::cout<<"str_global_nm state err! no run:"<<str_global_nm<<std::endl;
// 			}
			
		}
		return p;
	};

	static std::map<std::string,void*> m_global_shared_data_ptr_;

	////////////////////////////////////////
	static void insert_gm_shared_msg_gnm( const std::string &msg_name , const std::string &str_global_nm){

		g_sh_multimap_.insert(msg_name,str_global_nm);
		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);

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

#endif//_PIPE_SHARED_POOL_KYOSHO_2020_09_24_
