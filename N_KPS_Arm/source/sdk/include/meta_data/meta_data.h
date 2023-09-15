#ifndef META_DATA_20121101_
#define META_DATA_20121101_

#include <map>
#include <fstream>
#include "boost/unordered/unordered_map.hpp"

#include "MyDefine.h"
#include "Comm/Comm.h"
#include "robot/RobotStruct.h"
#include "meta_data/group_data.h"

#define ID_MIN 0
#define ID_MAX 99999

typedef enum{
  	META_BOOL,
 	META_I,
 	META_F,
 	META_STR,
	META_ENUM,
	META_POINT,
	META_POS,
	META_RANGE,
	META_COLOR,
	META_MT_SEL,
	META_COMB
}META_TYPE;



class SSMetaData
{
public:
	SSMetaData();
	~SSMetaData();

	META_TYPE mt_type_;

	std::string str_para_name_;
	std::string str_describe_;

	template<typename T>
	bool get_data(T &d){
		return cComm::ConvertToNum(d,str_data_);
	};
	bool get_data(std::string &str){
		str = str_data_;
		return true;
	};
	template<typename T>
	bool get_max(T &d){
		return cComm::ConvertToNum(d,str_max_);
	};
	template<typename T>
	bool get_min(T &d){
		return cComm::ConvertToNum(d,str_min_);
	};

	template<typename T>
	void set_data(T d){
		str_data_ = cComm::ConvertToString(d);
	};

	template<typename T>
	void set_max(T d){
		str_max_ = cComm::ConvertToString(d);
	};
	template<typename T>
	void set_min(T d){
		str_min_ = cComm::ConvertToString(d);
	};
	void set_read_only(bool b_read_only){
		b_read_only_ = b_read_only;
	};
	bool get_read_only(){
		return b_read_only_;
	};
	void set_list(const std::vector<std::string> &str_list){
		str_list_ = str_list;
	};
	std::vector<std::string> get_list(){
		return str_list_;
	};
protected:
private:

	std::string str_data_;
	std::string str_max_;
	std::string str_min_;
	std::vector<std::string> str_list_;

	bool b_read_only_;
};


class meta_base
{
public:
	meta_base();
	virtual ~meta_base();

	
	std::string name(){
		return group_name_;
	};

	void add_meta_data(std::string para_name,const SSMetaData &mt_data){
		auto it =  find_para(para_name);
		if ( it == m_data_.end() ){
			//new para
			m_data_.push_back(std::make_pair(para_name,mt_data));
		}else{
			it->second = mt_data;
		}
	};

	int get_data( std::vector< std::pair<std::string,SSMetaData> > &m_data){

		m_data = m_data_;
		return m_data_.size();
	};

	bool set_data( const std::string &str_data ){
		return set_data("data",str_data);
	};
	bool set_data( const std::string & str_name , const std::string &str_data){
		auto it = find_para(str_name);
		if ( it != m_data_.end()){
			it->second.set_data(str_data);
			return true;
		}else{
			return false;
		}
	};

	template<typename T>
	bool set_max( const std::string & str_name , const T &t){
		auto it = find_para(str_name);
		if ( it != m_data_.end()){
			it->second.set_max(t);
			return true;
		}else{
		return false;
		}
	};
	template<typename T>
	bool set_min( const std::string & str_name , const T &t){
		auto it = find_para(str_name);
		if ( it != m_data_.end()){
			it->second.set_min(t);
			return true;
		}else{
			return false;
		}
	};

	bool set_read_only( const std::string & str_name , bool b_read_only){
		auto it = find_para(str_name);
		if ( it != m_data_.end()){
			it->second.set_read_only(b_read_only);
			return true;
		}else{
			return false;
		}
	};
protected:

	virtual void init_type() = 0;

	std::vector< std::pair<std::string,SSMetaData> > m_data_;
	std::string group_name_;
	META_TYPE mt_type_;

private:
	std::vector< std::pair<std::string,SSMetaData> >::iterator find_para(std::string para_name){
		auto it = m_data_.begin();
		for ( ; it != m_data_.end() ; ++it ){
			if ( it->first == para_name ){
				return it;
			}
		}
		return m_data_.end();
	};
	

};
class meta_bool : public meta_base
{
public:
	meta_bool(){};
	~meta_bool(){};

	void init( const std::string &para_name, S32 i_data);

protected:
private:
	void init_type();
};

class meta_int : public meta_base
{
public:
	meta_int(){};
	~meta_int(){};

	void init( const std::string &para_name, S32 i_data);

protected:
private:
	void init_type();
};

class meta_double : public meta_base
{
public:
	meta_double(){};
	~meta_double(){};

	void init( const std::string &para_name, F64 f_data);

protected:
private:
	void init_type();
};

class meta_enum : public meta_base
{
public:
	meta_enum(){};
	~meta_enum(){};

	void init( const std::string &para_name, S32 i_data ,const std::vector<std::string> &str_list );

protected:
private:
	void init_type();
};

class meta_comb : public meta_base
{
public:
	meta_comb(){};
	~meta_comb(){};

	void init( const std::string &para_name, std::string str_data ,const std::vector<std::string> &str_list );

protected:
private:
	void init_type();
};
// 
// 
// class meta_float : public meta_base
// {
// public:
// 	meta_float(){
// 		SSMetaData mt_data;
// 		mt_data.mt_type_ = META_TYPE::META_F;
// 		mt_data.set_data("");
// 		mt_data.str_describe_ = "";
// 		mt_data.str_name_ = "float";
// 		m_data_["data"] = mt_data;
// 	
// 	};
// 	~meta_float(){};
// 
// 	
// protected:
// 
// };

class meta_point : public meta_base
{
public:
	meta_point(){};
	~meta_point(){};

	void init( const std::string &group_name, F64 x , F64 y );

private:

	void init_type();

};
class meta_pos : public meta_base
 {
 public:
	 meta_pos(){};
	 ~meta_pos(){};

	 void init( const std::string &group_name, F64 x , F64 y , F64 th);

 private:

	 void init_type();

};

class meta_mt_select : public meta_base
{
public:
	meta_mt_select(){};
	~meta_mt_select(){};

	void init( const std::string &group_name, std::string str_sel ,const std::vector<std::string> &str_list );

protected:
private:
	void init_type();
};

class meta_color : public meta_base
{
public:
	meta_color(){};
	~meta_color(){};

	void init( const std::string &para_name, std::string str_color);

protected:
private:
	void init_type();
};



class meta_str : public meta_base
{
public:
	meta_str(){};
	~meta_str(){};

	void init( const std::string &para_name, std::string str_data);

protected:
private:
	void init_type();
};
// 
// class meta_range : public meta_base
// {
// public:
// 	meta_range(){};
// 	~meta_range(){};
// 
// 
// private:
// 
// 	std::map<int,meta_point> m_pt_;
// 
// };

#endif //META_DATA_20121101_
