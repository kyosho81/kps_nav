#ifndef _MSG_PUMP_WANGHONGTAO_20180401_
#define _MSG_PUMP_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <iostream>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include "RobotStruct.h"
#include "buffer_con.hpp"
#include "robot/msg_def.h"
#include "Comm/Comm.h"

#define MSG_PUMP_SIZE_LIST_10 (10)

// a predefine size(SIZE) ring buffer  : put over head , if empty get will waiting
template<typename T>
class msg_list
{
private:
	boost::mutex mu;
	boost::condition_variable_any cond_get;

	//boost::circular_buffer<T> buffer_list;
	CrList<T,MSG_PUMP_SIZE_LIST_10> buffer_list;
public:
	explicit msg_list() //: buffer_list(MSG_PUMP_SIZE_LIST_10)
	{
		
	};

	~msg_list(){
		std::cout<<"~msg_list()"<<std::endl;
	};
	size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_list.size();
	};
	void put(T in)
	{

		{
			boost::mutex::scoped_lock lock(mu);
			if (buffer_list.full())
			{
				//buffer_list.pop_front();
				//std::cout << "full !! over head ..." << std::endl;
			}

			buffer_list.push_back(in);

		}
		//std::cout<<"buffer size:"<<buffer_list.size()<<std::endl;
		cond_get.notify_one();

	};
	void get(T &out)
	{
		{
			
			boost::mutex::scoped_lock lock(mu);

			while (buffer_list.empty())
			{
				//std::cout << "empty waiting..." << std::endl;
				cond_get.wait(lock);
			}
			//out = buffer_list.front();
			buffer_list.pop_front(out);

		}

	};
	void clear()
	{
		boost::mutex::scoped_lock lock(mu);
		while(!buffer_list.empty()){
			buffer_list.pop_front();
		}
	};

};


class SData_Addr{
public:
	SData_Addr(){
		id_ = 0;
		p_data_ = 0 ;
		p_list_ = 0 ;
		data_len_  = 0 ;
		b_thread_run_ = 0;
	};
	~SData_Addr(){
		if (p_data_)
		{
			delete[] p_data_;
			p_data_ = 0;
		}
		
		std::cout<<"SData_Addr destruct!"<<std::endl;
	};

	int id_;

	void* p_data_;
	void* p_list_; 
	int data_len_;

	THSafe<int> b_thread_run_;
};

class msg_pump
{
public:
	msg_pump();
	~msg_pump();



	template<typename T>
	static bool pub_msg(std::string msg_name,const T &data){

		
		mDataMap get_match;
		{
			std::pair<mDataMap::iterator, mDataMap::iterator> ret;
			boost::mutex::scoped_lock lock(mu_all_data_map_);
			ret = all_data_map_.equal_range(msg_name);

			for ( mDataMap::iterator it = ret.first ; it != ret.second ; ++it){
				get_match.insert (mDataMap::value_type(it->first,it->second) );
			}
		}

		for (mDataMap::iterator it = get_match.begin() ; it != get_match.end() ; ++it ){
		
			SData_Addr* sdata = it->second;
			int data_size = sizeof( msg_list< T > );
			if(data_size != sdata->data_len_){
				std::cout<<"err pub msg data size err!  "<<msg_name<<std::endl;
				continue;
			}
			
			if (sdata->b_thread_run_() == 1){
				msg_list< T >* ptr = static_cast<msg_list< T >*>(sdata->p_list_);
				ptr->put(data);
			}

		}
		return true;
	};

	static int sub_msg_id;

	static int get_sub_msg_id(){
		return sub_msg_id++;
	};

	template<typename T>
	static int sub_msg(std::string msg_name,boost::function<bool( const T &t)> fnc){

		boost::mutex::scoped_lock lock(mu_all_data_map_);

		int data_size = sizeof( msg_list< T > );
	
		SData_Addr* p_da = new SData_Addr();
		
		p_da->p_data_ = (void*)new char[data_size];
		msg_list< T >* ptr = new (p_da->p_data_) msg_list< T >();
		p_da->p_list_ = (void*)ptr;
		assert(p_da->p_data_ == p_da->p_list_);
		p_da->id_ = get_sub_msg_id();
		p_da->data_len_ = data_size;
		p_da->b_thread_run_ = 1;


		std::cout<<"sub msg id:"<<p_da->id_<<" msg:"<<msg_name<<std::endl;


		all_data_map_.insert (mDataMap::value_type(msg_name,p_da) );


		boost::thread th(boost::bind(&msg_pump::sub_thread<T>,p_da,fnc));

		return p_da->id_;
	};

	template<typename T>
	static void sub_thread(SData_Addr* pda, boost::function<bool( const T &t)> fnc){

		std::cout<<"sub thread id:"<<pda->id_<<std::endl;
		msg_list< T >* pshd = (msg_list< T >*)pda->p_list_;
		

		if( (!pda) || (!pshd)){
			return;
		}
		std::cout<<"sub_thread begin :"<<pda->id_<<std::endl;

		T tmp;
		try  
		{

			while( pda->b_thread_run_()){
				pshd->get(tmp);
				if(!fnc.empty() ){
					
					if (!fnc(tmp))
					{
						break;
					}
					
				}else{
					break;
				}
				boost::this_thread::interruption_point();
			}
			
		} 
		catch (boost::thread_interrupted&) {
		//catch (std::exception& e)  {  
			//std::cout <<"sub_thread err:"<< e.what() << std::endl;  
			std::cout <<"sub_thread err:"<< std::endl;  
		}

		pda->b_thread_run_ = -1;

		std::cout<<"sub thread is end id:"<<pda->id_<<std::endl;
		
	};
	template<typename T>
	static bool end_Sub(const int &id,const T &t){

		//boost::mutex::scoped_lock lock(mu_all_data_map_);
		mu_all_data_map_.lock();

		mDataMap::iterator it = all_data_map_.begin();

		for ( ; it != all_data_map_.end() ; ++it)
		{
			std::cout<<"begin end sub id:"<<it->second->id_<<" msg:"<<it->first<<std::endl;
			SData_Addr* p_da = it->second;
			
			if( id == p_da->id_){
				
				mu_all_data_map_.unlock();

				p_da->b_thread_run_ = 0;
				while( p_da->b_thread_run_() != -1){
					msg_list< T >* ptr = static_cast<msg_list< T >*>(p_da->p_list_);
					ptr->put(T());
					SLEEP(1);
					
				}

				boost::mutex::scoped_lock lock(mu_all_data_map_);
				std::cout<<"over end sub id:"<<it->second->id_<<" msg:"<<it->first<<std::endl;
				all_data_map_.erase(it);
				SDelete(p_da);

				return true;
			}
			
		}
		std::cout<<"end_Sub err id:"<<id<<std::endl;
		mu_all_data_map_.unlock();
		return false;
	};

protected:
private:

	typedef std::multimap<std::string,SData_Addr*> mDataMap;
	static mDataMap all_data_map_;

	static boost::mutex mu_all_data_map_;
};


#endif //_MSG_PUMP_WANGHONGTAO_20180401_