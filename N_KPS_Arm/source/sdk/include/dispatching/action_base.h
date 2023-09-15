#ifndef _ACTION_BASE_WANGHONGTAO_20220303_
#define _ACTION_BASE_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "dispatching/schedule_interface.h"
#include "action/action_def.h"

class action_base
{
public:
	action_base(){
		i_cur_node_id_ = -1;
		i_last_node_id_ = -1;
		i_next_node_id_ = -1;
		f_trigger_ = 0;
		f_tri_edge_per_ = 0; //(0 ~ 1.0) percent
		f_chk_edge_per_ = 0; //(0 ~ 1.0) percent
		//first state shoule download
		atc_state_ = ACTION_DOWNLOAD;
	};
	~action_base(){};
	
	void set_action_name(std::string str_name);

	virtual bool decode_para(std::string str_para);
	std::string incode_para();

	virtual void print() = 0;
	void print_base(){
		std::cout<<i_cur_node_id_<<" "<<i_last_node_id_<<" "<<i_next_node_id_<<" "<< f_trigger_ << std::endl;
		int i_node_from;
		int i_node_to;
		F32 per = get_tri_edge( i_node_from, i_node_to);
		std::cout<<i_node_from<<" "<<i_node_to<<" "<<per<<std::endl;
	};

	F32 get_tri_edge(int &i_node_from,int &i_node_to){
		if(f_trigger_< 0){
			i_node_from = i_last_node_id_;
			i_node_to = i_cur_node_id_;
			return f_tri_edge_per_;
			
		}else{
			i_node_from = i_cur_node_id_;
			i_node_to = i_next_node_id_;
			return f_tri_edge_per_;
		}
	}
	int i_cur_node_id_;
	int i_last_node_id_;
	int i_next_node_id_;

	F32 f_trigger_;

	F32 f_tri_edge_per_;
	F32 f_chk_edge_per_;

	std::string get_action_type(){
		return str_action_type_;
	};
public:
	typedef enum{
		ACTION_DOWNLOAD = 0,
		ACTION_CHACK_DOWN = 1,
		ACTION_DONE = 2,
		ACTION_ERROR = 3,
	}ACTION_STA;

	ACTION_STA atc_state_;

	boost::function<int()> fnc_callback_;
	virtual int do_on_server(){
		std::cout<<"action type:"<<str_action_type_<<" do_on_server error!"<<std::endl;
		return false;
	};

protected:
	virtual bool check_para(std::string str_name,std::string str_para) = 0;
	std::string get_para(std::string str_name);
	void set_base_para();

	std::string str_action_type_;
	std::map<std::string,std::string> m_para_;
};

class action_path : action_base
{
public:
	action_path(){
		str_action_type_ = ACT_PATH;
		f_path_speed_ = 0.2;
	};
	~action_path(){};

	std::vector<SPathData> get_run_path();

protected:
private:
	bool decode_para(std::string str_para);
	int create_run_path();
	bool check_para(std::string str_name,std::string str_para){
		return true;
	};
	void print(){
		std::cout<<"Path action:";
		print_base();
		std::cout<<i_ori_<<" : ";
		
		auto it = v_node_.begin();
		for (; it != v_node_.end() ; ++it ){
			std::cout<<*it<<" ";
		}
		std::cout<<std::endl;
		
	};
	int i_ori_;
	std::vector<int> v_node_;
	std::vector<SPathData> seg_path_;
	F32 f_path_speed_;

	
};
class action_fork : action_base
{
public:
	action_fork(){
		str_action_type_ = ACT_FORK;
		m_para_["speed"] = "0.8";
	};
	~action_fork(){};

	std::string get_fork_para();

protected:
private:
	
	bool check_para(std::string str_name,std::string str_para){
		if ( str_name == "level"){
			return true;
		}else if ( str_name == "speed"){
			return true;
		}
		return false;
	};
	void print(){

		std::cout<<"Fork action:";
		print_base();
		std::cout<<"level"<<m_para_["level"]<<std::endl;
	};

	
};
class action_ref_fb : action_base
{
public:
	action_ref_fb(){
		str_action_type_ = ACT_REF_FB;
		m_para_["enable"] = "0";
		m_para_["forbidden_begin"] = "0";
		m_para_["forbidden_end"] = "0";
	};
	~action_ref_fb(){};

	std::string get_fb_para();

protected:
private:

	bool check_para(std::string str_name,std::string str_para){
		if ( str_name == "enable"){
			return true;
		}else if ( str_name == "forbidden_begin"){
			return true;
		}else if ( str_name == "forbidden_end"){
			return true;
		}
		return false;
	};
	void print(){

		std::cout<<"reflector forbidden action:";
		print_base();
		std::cout<<"enable"<<m_para_["enable"]<<std::endl;
		std::cout<<"forbidden_begin"<<m_para_["forbidden_begin"]<<std::endl;
		std::cout<<"forbidden_end"<<m_para_["forbidden_end"]<<std::endl;
	};


};
class action_task_act : action_base
{
public:
	action_task_act(){
		str_action_type_ = ACT_TASK;
	};
	~action_task_act(){};

	std::string get_para();

protected:
private:

	bool check_para(std::string str_name,std::string str_para){
		
		return true;
	};
	void print(){

		std::cout<<"task_act action:";
		print_base();
		
	};

	std::string str_para_;
};
class action_get_over : action_base
{
public:
	action_get_over(){
		str_action_type_ = ACT_GET_OVER;
	};
	~action_get_over(){};

	
	int do_on_server(){
		if (!fnc_callback_.empty() ){
			return fnc_callback_();
		}
		return false;
	};
protected:
private:

	bool check_para(std::string str_name,std::string str_para){
		
		return false;
	};
	void print(){

		std::cout<<"role get over action:";
		print_base();

	};


};

class action_put_over : action_base
{
public:
	action_put_over(){
		str_action_type_ = ACT_PUT_OVER;
	};
	~action_put_over(){};


	int do_on_server(){
		if (!fnc_callback_.empty() ){
			return fnc_callback_();
		}
		return false;
	};
protected:
private:

	bool check_para(std::string str_name,std::string str_para){

		return false;
	};
	void print(){

		std::cout<<"role put over action:";
		print_base();

	};


};


class action_occupy : action_base
{
public:
	action_occupy(){
		str_action_type_ = ACT_PUT_OCCUPY;
	};
	~action_occupy(){};


	int do_on_server(){
		if (!fnc_callback_.empty() ){
			return fnc_callback_();
		}
		return false;
	};
protected:
private:

	bool check_para(std::string str_name,std::string str_para){

		return false;
	};
	void print(){

		std::cout<<"action_occupy action:";
		print_base();

	};


};
class action_release : action_base
{
public:
	action_release(){
		str_action_type_ = ACT_PUT_RELEASE;
	};
	~action_release(){};


	int do_on_server(){
		if (!fnc_callback_.empty() ){
			return fnc_callback_();
		}
		return false;
	};
protected:
private:

	bool check_para(std::string str_name,std::string str_para){

		return false;
	};
	void print(){

		std::cout<<"action_release action:";
		print_base();

	};


};
// 
// class action_charge_begin : action_base
// {
// public:
// 	action_charge_begin(){
// 		str_action_type_ = ACTION_CHARGE_BEGIN;
// 	};
// 	~action_charge_begin(){};
// 
// 
// 	int do_on_server(){
// 		if (!fnc_callback_.empty() ){
// 			return fnc_callback_();
// 		}
// 		return false;
// 	};
// protected:
// private:
// 
// 	bool check_para(std::string str_name,std::string str_para){
// 
// 		return false;
// 	};
// 	void print(){
// 
// 		std::cout<<"action_charge_begin action:";
// 		print_base();
// 
// 	};
// 
// 
// };
// 
// 
// class action_charge_over : action_base
// {
// public:
// 	action_charge_over(){
// 		str_action_type_ = ACTION_CHARGE_OVER;
// 	};
// 	~action_charge_over(){};
// 
// 
// 	int do_on_server(){
// 		if (!fnc_callback_.empty() ){
// 			return fnc_callback_();
// 		}
// 		return false;
// 	};
// protected:
// private:
// 
// 	bool check_para(std::string str_name,std::string str_para){
// 
// 		return false;
// 	};
// 	void print(){
// 
// 		std::cout<<"action_charge_over action:";
// 		print_base();
// 
// 	};
// 
// 
// };

class action_queue
{
public:
	action_queue();
	~action_queue();

	void insert_act_path(int i_que, std::string str_para);
	void insert_act_fork(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para );
	void insert_act_lift(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para );
	void insert_act_ref_fb(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para );
	void insert_act_charge(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para );
	void insert_act_get_over(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para , boost::function<bool(void)> fnc_callback);
	void insert_act_put_over(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para , boost::function<bool(void)> fnc_callback);
	
	void insert_act_release(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para , boost::function<bool(void)> fnc_callback);
	void insert_act_occupy(int i_que, int i_cur_node_id, int i_last_node_id , int i_next_node_id, F32 f_trigger , std::string str_para , boost::function<bool(void)> fnc_callback);

	void print_all();

	int get_action();



protected:
private:

	void make_trigger_edge_percent(F32 &tri_percent, F32 &chk_percent , int i_node_cur, int i_last_node_id , int i_next_node_id , F32 f_trigger );


	typedef std::multimap<int,action_base*>::iterator M_it;
	typedef std::pair< M_it , M_it > P_it;
	P_it pair_it_;

	//insert by fill
	std::multimap<int,action_base*> mm_act_que_;
	
public:
	//insert by get current do action_queue::do_action
	std::multimap<int , action_base*> mm_ord_doing_act_;
	//insert by current done
	std::multimap<int , action_base*> mm_ord_done_act_;

	int one_act_err_shutdown();
};


#endif//_ACTION_BASE_WANGHONGTAO_20220303_
