#ifndef _CONFIGS_WANGHONGTAO_KYOSHO_20200912_
#define _CONFIGS_WANGHONGTAO_KYOSHO_20200912_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include "boost/unordered/unordered_map.hpp"

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"

#define SEPARATE_NAME_VALUE "|"

class config_it
{
public:
	config_it(const std::string &str_name){
		str_name_ = str_name;
		str_data_ = "";
		str_seg_ = "default";

		memset(ch_max_,0,20);
		memset(ch_min_,0,20);
		memset(ch_data_,0,20);

		str_des_ = "";
	};
	config_it(const config_it &c_it);

	~config_it(){};

	friend bool operator>>(std::istream &in, config_it &a){
		

		return false;
	};
	friend std::ostream &operator<<(std::ostream &os, config_it &a){
		std::string str;
		os<<"type"<<SEPARATE_NAME_VALUE<<get_aline_nop(a.type_,a.TYPE_AL_LEN)<<" ";
		os<<"seg"<<SEPARATE_NAME_VALUE<<get_aline_nop(a.get_seg(),a.SEGM_AL_LEN)<<" ";
		std::string str_int_type = typeid(int).name();
		std::string str_float_type = typeid(float).name();
		std::string str_double_type = typeid(double).name();
		str_int_type = match_type(str_int_type);
		str_float_type = match_type(str_float_type);
		str_double_type = match_type(str_double_type);
		
		if ( "string" == a.type_ )
		{
			os<<"data"<<SEPARATE_NAME_VALUE<<get_aline_nop(a.str_data_,a.SDAT_AL_LEN)<<std::endl;
			//os<<"desc:"<<get_aline_nop(a.str_des_,a.DESC_AL_LEN)<<std::endl;

		}else if( str_int_type == a.type_ ){
			int data = 0;
			a.get_value(data);
			os<<"data"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DATA_AL_LEN)<<" ";
			
			a.get_max(data);
			os<<"dmax"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMAX_AL_LEN)<<" ";

			a.get_min(data);
			os<<"dmin"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMIN_AL_LEN)<<" ";

			//os<<"desc:"<<get_aline_nop(a.str_des_,a.DESC_AL_LEN)<<" ";

			os<<"dhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_data_,sizeof(int));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"xhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_max_,sizeof(int));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"mhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_min_,sizeof(int));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<std::endl;

		}else if( str_float_type == a.type_ ){
			float data = 0;
			a.get_value(data);
			os<<"data"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DATA_AL_LEN)<<" ";

			a.get_max(data);
			os<<"dmax"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMAX_AL_LEN)<<" ";

			a.get_min(data);
			os<<"dmin"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMIN_AL_LEN)<<" ";

			//os<<"desc:"<<get_aline_nop(a.str_des_,a.DESC_AL_LEN)<<" ";

			os<<"dhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_data_,sizeof(float));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"xhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_max_,sizeof(float));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"mhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_min_,sizeof(float));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<std::endl;

		}else if( str_double_type == a.type_ ){
			double data = 0;
			a.get_value(data);
			os<<"data"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DATA_AL_LEN)<<" ";

			a.get_max(data);
			os<<"dmax"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMAX_AL_LEN)<<" ";

			a.get_min(data);
			os<<"dmin"<<SEPARATE_NAME_VALUE;
			str = cComm::ConvertToString(data);
			os<<get_aline_nop(str,a.DMIN_AL_LEN)<<" ";

			//os<<"desc:"<<get_aline_nop(a.str_des_,a.DESC_AL_LEN)<<" ";

			os<<"dhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_data_,sizeof(double));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"xhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_max_,sizeof(double));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<" ";

			os<<"mhex"<<SEPARATE_NAME_VALUE;
			str = ByteToHexString(a.ch_min_,sizeof(double));
			os<<get_aline_nop(str,a.DHEX_AL_LEN)<<std::endl;
		}

		return os;
	};

	std::string code();

	bool decode(std::string str);

	template<typename T>
	bool set_value( T data){

		T t_max = 0;
		T t_min = 0;

		memcpy( &t_max, ch_max_ ,sizeof(T));
		memcpy( &t_min, ch_min_ ,sizeof(T));
	
		if( !cComm::RangeIt<T>(data,t_min,t_max) ){
			return false;
		}

		memset( ch_data_,0,20);
		memcpy( ch_data_, &data ,sizeof(T));

		type_ = typeid(data).name();
		type_ = match_type(type_);

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<"type:"<<type_<<" set_value:"<<data;
		//std::cout<<"set type value:"<<ss.str()<<std::endl;
		str_des_ = ss.str();
		str_data_ = cComm::ConvertToString(data);
		//std::cout<<ss.str()<<std::endl;
		return true;
	};
	//template specialization

	bool set_value(std::string str){
		str_data_ = cComm::trim_n(str);
		str_data_ = cComm::trim_cr(str_data_);

		type_ = "string";

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<"type:"<<type_<<" set_str:"<<str;
		str_des_ = ss.str();

		return true;
	};

	template<typename T>
	bool get_value(T &data){

		memcpy( &data, ch_data_ ,sizeof(T));
		
		return true;
	};


	bool get_value(std::string &data){
		data = str_data_;
		return true;
	};

	template<typename T>
	void set_max(const T &data){
		memset(ch_max_,0,20);
		memcpy(ch_max_ , &data, sizeof(T));

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<" set_max:"<<data;
		str_des_ = ss.str();

	};
	template<typename T>
	T get_max(T &data){
		data = 0;

		memcpy( &data, ch_max_ ,sizeof(T));

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<" get_max:"<<data;
		str_des_ = ss.str();

		return data;
	};
	template<typename T>
	void set_min(const T &data){
		memset(ch_min_,0,20);
		memcpy(ch_min_ , &data, sizeof(T));

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<"type:"<<type_<<" set_min:"<<data;
		str_des_ = ss.str();

	};

	template<typename T>
	T get_min(T &data){
		data = 0;

		memcpy( &data, ch_min_ ,sizeof(T));

		std::stringstream ss;
		ss<<cTimerDiff::get_now()<<" get_min:"<<data;
		str_des_ = ss.str();

		return data;

	};
	std::string get_name(){
		return str_name_;
	};
	std::string get_al_name(){
		return get_aline_nop(str_name_,NAME_AL_LEN);
	};
	void set_seg(const std::string &str_seg){
		str_seg_ = str_seg;
	};
	std::string get_seg(){
		return str_seg_;
	};
	std::string get_type(){
		return type_;
	};
	static bool split_name_value(std::string &name,std::string &value , const std::string &str){
		name = "";
		value = "";

		std::vector<std::string> v_res;
		cComm::SplitString(str,SEPARATE_NAME_VALUE,v_res);
		if (v_res.size() > 1)
		{
			name = v_res[0];
			value = v_res[1];
			return true;
		}
		return false;
	};
	static std::string match_type(const std::string str_type){
		if("i" == str_type){
			return "int";
		}else if("f" == str_type){
			return "float";
		}else if("d" == str_type){
			return "doblue";
		}else{
			std::cout<<"match_type:"<<str_type<<std::endl;
			return str_type;
		}
	};

protected:
private:
	std::string str_name_;
	std::string type_;
	std::string str_data_;
	std::string str_seg_;

	U8 ch_max_[20];
	U8 ch_min_[20];
	U8 ch_data_[20];
// 	std::string str_max_;
// 	std::string str_min_;
	std::string str_des_;

	static std::string get_aline_nop(std::string str,int aline_len){
		if ( str.length() >= aline_len )
		{
			return str;
		}else{
			aline_len = aline_len - str.length();
			for (int i = 0 ; i < aline_len ; ++i ){
				str += " ";
			}
		}
		return str;
	};

	static std::string ByteToHexString( U8* pData,
		S32 iLen )
	{
		std::string strTmp;
		std::string s;
		char chTmp[8] = {0};
		for(S32 i = 0; i<iLen ;++i)
		{
			sprintf(chTmp, "%02X-", pData[i]);

			strTmp += chTmp;
		}
		return strTmp;
	}
public:
	static const int NAME_AL_LEN = 38;
	static const int TYPE_AL_LEN = 6;
	static const int SEGM_AL_LEN = 10;
	static const int DESC_AL_LEN = 50;
	static const int SDAT_AL_LEN = 50;
	static const int DATA_AL_LEN = 20;
	static const int DMAX_AL_LEN = 20;
	static const int DMIN_AL_LEN = 20;
	static const int DHEX_AL_LEN = 20;
};

class configs
{
public:
	configs();
	~configs();

	bool load(const std::string &str_file, const bool &b_merge = false);
	bool save(const std::string &str_file);

	template<typename T>
	bool get_config( T &data , const std::string &str_para_name){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = (it->second);
			return ct->get_value(data);
		}
		return false;
	};
	bool get_config( std::string &str_data , const std::string &str_para_name){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = (it->second);
			return ct->get_value(str_data);
		}
		return false;
	};
	bool get_whole_config( std::string &str_data , const std::string &str_para_name){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = (it->second);
			
			str_data = ct->code();
			return true;
		}
		return false;
	};
	
	bool get_sconfig( std::string &str , const std::string &str_para_name){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = (it->second);
			return ct->get_value(str);
		}
		return false;
	};


	template<typename T>
	bool set_config(const std::string &str_para_name, const T &data){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = (it->second);
			return ct->set_value(data);

		}

		return false;
	};
	bool init_config(const std::string str_decode);

	bool init_config(config_it &c_it);

	template<typename T>
	bool init_config(const std::string &str_para_name, const T &data, const T &min, const T &max){
		boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = ( it->second );
			ct->set_min<T>(min);
			ct->set_max<T>(max);
			return ct->set_value(data);
		}

		config_it* c = new config_it(str_para_name);
		c->set_min<T>(min);
		c->set_max<T>(max);
		if( c->set_value(data)){
			m_all_paras_[str_para_name] = c;
			l_all_paras_.push_back(c);

			return true;
		}else{
			return false;
		}
		

		
	};
	bool set_seg(const std::string &str_para_name, const std::string &str_seg);

	bool set_sconfig(const std::string &str_para_name, const std::string &data){
		boost::unordered_map<std::string, config_it* >::iterator it = m_all_paras_.find(str_para_name);
		if ( it != m_all_paras_.end()){
			config_it* ct = ( it->second );
			return ct->set_value(data);
		}

		config_it* c = new config_it(str_para_name);
		if( c->set_value(data)){
			m_all_paras_[str_para_name] = c;
			l_all_paras_.push_back(c);
		}
		

		return false;
	};
	int get_para_list( std::vector<std::string> &v_list){
		v_list.clear();
		std::list<config_it*>::iterator it = l_all_paras_.begin();
		for ( ; it != l_all_paras_.end() ; ++it ){
			v_list.push_back((*it)->get_name());
		}
		return v_list.size();
	};
	bool set_whole_config(const std::string &str_para_name,const std::string str_decode);

protected:
private:
	std::string get_uni_key(const std::string &str_seg_name ,const std::string &str_para_name){
		std::string str_key = str_seg_name + "_" + str_para_name;
		if (m_all_paras_.find(str_key) != m_all_paras_.end())
		{
			return "";
		}
		return str_key;
	};
	
	
	boost::unordered_map<std::string, config_it*> m_all_paras_;
	std::list<config_it*> l_all_paras_;
	std::multimap<std::string,config_it*> mt_seg_paras_;

	std::multimap<std::string,config_it*>::iterator get_seg_para_it( const std::string &str_name);
	//std::map<std::string, config_it> m_all_paras_;
};
typedef boost::serialization::singleton<configs> Singleton_Configs;
#define INIT_CONFIG(str_para_name,data,min,max ) Singleton_Configs::get_mutable_instance().init_config(str_para_name,data,min,max) 
#define SET_CONFIG(str_para_name,data ) Singleton_Configs::get_mutable_instance().set_config(str_para_name,data) 
#define SET_SCONFIG(str_para_name,str ) Singleton_Configs::get_mutable_instance().set_sconfig(str_para_name,str) 
#define GET_CONFIG(data ,str_para_name ) Singleton_Configs::get_mutable_instance().get_config(data,str_para_name)
#define GET_SCONFIG(str ,str_para_name ) Singleton_Configs::get_mutable_instance().get_sconfig(str,str_para_name)
#define SET_SEG( str_para_name , str_seg ) Singleton_Configs::get_mutable_instance().set_seg(str_para_name,str_seg)
#define GET_LIST( v_para_list ) Singleton_Configs::get_mutable_instance().get_para_list(v_para_list)
#define GET_WHOLE_CONFIG(data ,str_para_name ) Singleton_Configs::get_mutable_instance().get_whole_config(data,str_para_name)
#define INIT_WHOLE_CONFIG(str_whole_para ) Singleton_Configs::get_mutable_instance().init_config(str_whole_para)
#define SET_WHOLE_CONFIG( str_para_name, str_whole_para ) Singleton_Configs::get_mutable_instance().set_whole_config(str_para_name,str_whole_para)

#define SAVE_CONFIG(str_file_name ) Singleton_Configs::get_mutable_instance().save(str_file_name)
#define LOAD_CONFIG(str_file_name ) Singleton_Configs::get_mutable_instance().load(str_file_name)

#endif //_CONFIGS_WANGHONGTAO_KYOSHO_20200912_
