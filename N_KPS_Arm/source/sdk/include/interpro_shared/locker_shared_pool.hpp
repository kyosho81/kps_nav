#ifndef _LOCKER_SHARED_POOL_WANGHONGTAO_2020_09_24_
#define _LOCKER_SHARED_POOL_WANGHONGTAO_2020_09_24_

#include <fstream>
#include <map>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>

#include "interpro_shared/shared_locker.hpp"
#include "interpro_shared/shared_multimap.hpp"

class locker_shared_pool
{
public:
	locker_shared_pool();
	~locker_shared_pool();

	static void init(const std::string &str_nm ,bool b_create = false){
	
		g_sh_multimap_.init(b_create);

		std::cout<<"shared locker init!"<<std::endl;
	};
	static void init(char *argv[] ,bool b_create = false){

		g_sh_multimap_.init(b_create);

		std::cout<<"shared locker init!"<<std::endl;
	};
	static void reset(){
		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);

		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it ){
			bip::shared_memory_object::remove((*it).c_str());
			std::cout<<"remove shared locker:"<<*it<<std::endl;
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
	static  bool set_locker( const std::string &share_name ,const bool &b_lock){
		
		shared_locker* lc = reg_locker(share_name);
		if (lc){
			if (b_lock){
				lc->lock();
			}else{
				lc->unlock();
			}
			return true;
		}
		return false;
	};

	static shared_locker* reg_locker(const std::string &share_name){
		//if local thread have get ptr before
		std::map<std::string,shared_locker*>::iterator it = m_global_shared_data_ptr_.find(share_name);
		if (it != m_global_shared_data_ptr_.end())
		{
			return it->second;
		}else{
			std::vector<std::string> vres;
			get_gm_shared_msg_gnm(vres,share_name);
			
			//if shared object didn't create shared locker
			shared_locker* sh_locker = 0;
			if (vres.size() < 1){

				sh_locker = new shared_locker(share_name); 
				sh_locker->init();

				m_global_shared_data_ptr_.insert( std::map<std::string,shared_locker*>::value_type(share_name,sh_locker) );

				insert_gm_shared_msg_gnm(share_name,share_name);

				
			}else{
				//if shared object have been created
				sh_locker = new shared_locker(share_name); 
				sh_locker->open();

				m_global_shared_data_ptr_.insert( std::map<std::string,shared_locker*>::value_type(share_name,sh_locker) );

			}
			return sh_locker;
			
		}

	};

protected:

private:
	

	static std::map<std::string,shared_locker*> m_global_shared_data_ptr_;

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




#endif//_LOCKER_SHARED_POOL_WANGHONGTAO_2020_09_24_
