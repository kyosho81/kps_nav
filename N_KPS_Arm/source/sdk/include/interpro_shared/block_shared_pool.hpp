#ifndef _BLOCK_SHARED_POOL_WANGHONGTAO_2020_09_24_
#define _BLOCK_SHARED_POOL_WANGHONGTAO_2020_09_24_

#include <fstream>
#include <map>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>

#include "interpro_shared/shared_block.hpp"
#include "interpro_shared/shared_multimap.hpp"


class block_shared_pool
{
public:
	block_shared_pool();
	~block_shared_pool();

	static void init(const std::string &str_nm ,bool b_create = false){
		
		g_sh_multimap_.init(b_create);

		std::cout<<"shared pool block init!"<<std::endl;
	};
	static void init(char *argv[] ,bool b_create = false){

		g_sh_multimap_.init(b_create);

		std::cout<<"shared pool block init!"<<std::endl;
	};
	static void reset(){

		std::vector<std::string> v_res;
		g_sh_multimap_.get_all(v_res);

		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it ){
			bip::shared_memory_object::remove((*it).c_str());
			std::cout<<"remove shared pool block:"<<*it<<std::endl;
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
	static shared_block* Reg_sh_range(std::string sh_name,U32 dsize){ 

		std::cout<<"core create shared block:"<<sh_name<<" size:"<<dsize<<std::endl;

		shared_block* sr = new shared_block(sh_name,dsize);
		if( sr->init() ){
			//insert into local msg map
			m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(sh_name,(void*)sr) );
			//insert into shared msg map
			insert_gm_shared_msg_gnm(sh_name,sh_name);

			return sr;
		}

		SDelete(sr);

		return 0;

	};

	static shared_block* get_sh_range(const std::string &sh_name){
		
		
		std::map<std::string,void*>::iterator it = m_global_shared_data_ptr_.find(sh_name);
		if (it != m_global_shared_data_ptr_.end())
		{
			return (shared_block*)it->second;
		}else{

			std::vector<std::string> vres;
			get_gm_shared_msg_gnm(vres,sh_name);
			
			if (vres.size() < 1){
				std::cout<<"core get shared block err:"<<sh_name<<" check Reg_sh_range"<<std::endl;
				return 0;
			}else{
				shared_block* sr = new shared_block(sh_name,0);
				if( sr->open()){

					m_global_shared_data_ptr_.insert( std::map<std::string,void*>::value_type(sh_name,(void*)sr) );

					return sr;
				}else{
					return 0;
				}
			}
			
		}
	};
	static bool set_block_data(const std::string &sh_name,U8* in,U32 offset,U32 &len){
		shared_block* sh_block = get_sh_range(sh_name);
		if (sh_block){
			return sh_block->write(in,offset,len);
		}
		return false;
	};
	static bool get_block_data(const std::string &sh_name,U8* out,U32 offset,U32 &len){
		shared_block* sh_block = get_sh_range(sh_name);
		if (sh_block){
			return sh_block->read(out,offset,len);
		}
		return false;
	};
protected:


private:
	

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




#endif//_BLOCK_SHARED_POOL_WANGHONGTAO_2020_09_24_
