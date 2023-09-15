#ifndef _TRAFFIC_CONTROL_WANGHONGTAO_20220303_
#define _TRAFFIC_CONTROL_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "Comm/pattern_thread.h"
#include "movement/task_path.h"
#include "dispatching/seg_path_against.h"

class GridMap;


class agv_show_data
{
public:
	agv_show_data(){};
	~agv_show_data(){};

	int i_agv_id_;
	std::vector<SVec> v_shape_;
	std::list<SOdomSpeed> l_path_;
	SPos amcl_pos_;

protected:

private:
};

class traffic_agv_data
{
public:
	traffic_agv_data();
	~traffic_agv_data();

	void init(int i_id);
	void set_priority( int i_priority );
	bool set_robot_shape(std::vector<SVec> v_robot_shape);
	bool set_run_path(std::list<SPathData> &v_run_path);
	
	void set_agv_current_pos( SPos pos);
	SPos get_agv_current_pos();

	bool update_path();
	//should run after update_path
	int get_spath_seg(std::vector<SPathData> &v_seg_path);

	std::list< std::list<SOdomSpeed>::iterator > temp_path_;
	std::list<SOdomSpeed> earse_p_;
	std::list<SOdomSpeed> extern_p_;

	int get_global_shape(std::vector<SPos> &v_shape_gp);
	int get_global_shape(std::vector<SPos> &v_shape_gp, SPos global_pos );
	int get_shape(std::vector<SVec> &v_shape);
	int get_run_path(std::list<SOdomSpeed> &l_path);

	void err_clear_data();

	bool b_pause_;
protected:
private:
	int i_id_;
	int i_priority_;

	SPos agv_current_pos_;
	//robot shape
private:
	std::vector<SVec> v_shape_;
	std::vector<VecPosition> v_shape_point_;

private:
	
	//task path
private:
	task_path task_path_;
	
};

class tc_body_line_data
{
public:
	tc_body_line_data(){
		i_subordinate_ = 0;
		i_superior_ = 0;
		ctl_type_ = ECTL_LINE_BODY;

	};
	~tc_body_line_data(){};

	int i_subordinate_;
	int i_superior_;

	typedef enum{
		ECTL_LINE_BODY = 0,
		ECTL_LINE_LINE_SAME = 1,
		ECTL_LINE_LINE_AGAINST = 2
	}ECTL_TYPE;

	ECTL_TYPE ctl_type_;
protected:
private:
};

class tc_body_line_mch
{
public:
	tc_body_line_mch(){};
	~tc_body_line_mch(){};

	void set_line_match_body(int i_subordinate,int i_superior){
		tc_body_line_data tc_data;
		tc_data.ctl_type_ = tc_body_line_data::ECTL_LINE_BODY;
		tc_data.i_subordinate_ = i_subordinate;
		tc_data.i_superior_ = i_superior;

		l_mch_.push_back(tc_data);
	};

	void set_line_line_same(int i_subordinate,int i_superior){
		tc_body_line_data tc_data;
		tc_data.ctl_type_ = tc_body_line_data::ECTL_LINE_LINE_SAME;
		tc_data.i_subordinate_ = i_subordinate;
		tc_data.i_superior_ = i_superior;

		l_mch_.push_back(tc_data);
	};
	void set_line_line_against(int i_subordinate,int i_superior){
		tc_body_line_data tc_data;
		tc_data.ctl_type_ = tc_body_line_data::ECTL_LINE_LINE_AGAINST;
		tc_data.i_subordinate_ = i_subordinate;
		tc_data.i_superior_ = i_superior;

		l_mch_.push_back(tc_data);
	};

	std::list<tc_body_line_data> get_line_body(){
		std::list<tc_body_line_data> l_res;
		auto it = l_mch_.begin();
		for ( ; it != l_mch_.end() ; ++it ){
			if ( it->ctl_type_ == tc_body_line_data::ECTL_LINE_BODY){
				l_res.push_back(*it);
			}
		}
		return l_res;
	};
	std::list<tc_body_line_data> get_line_against(){
		std::list<tc_body_line_data> l_res;
		auto it = l_mch_.begin();
		for ( ; it != l_mch_.end() ; ++it ){
			if ( it->ctl_type_ == tc_body_line_data::ECTL_LINE_LINE_AGAINST){
				l_res.push_back(*it);
			}
		}
		return l_res;
	};
	std::list<tc_body_line_data> get_line(){
		std::list<tc_body_line_data> l_res;
		auto it = l_mch_.begin();
		for ( ; it != l_mch_.end() ; ++it ){
			if ( (it->ctl_type_ == tc_body_line_data::ECTL_LINE_LINE_AGAINST)
				|| (it->ctl_type_ == tc_body_line_data::ECTL_LINE_LINE_SAME)){
				l_res.push_back(*it);
			}
		}
		return l_res;
	};
	void clear(){
		l_mch_.clear();
	};
protected:
private:
	std::list<tc_body_line_data> l_mch_;
};


class traffic_control
{
public:
	traffic_control();
	~traffic_control();

		
	void init();
	bool do_traffic_control();
	void set_data(std::map<int,SAGV_Info> m_agv_status,std::map<int,SRobot_Inf> &m_robot_inf,std::map<int,std::list<SPathData>> &m_run_path,std::map<int,std::vector<SVec>> m_robot_shape);
	std::string get_global_map();
	std::map<int,agv_show_data> get_agv_raw_show();

	int check_pause_loop();
	
	bool remove_data( int i_agv_id );

protected:
private:
	boost::mutex mu_data_;
// 	std::map<int, SAGV_Info> m_agv_status_;
// 	std::map<int, SRobot_Inf> m_robot_inf_;
// 	std::map<int,std::list<SPathData>> m_run_path_;
// 	std::map<int,std::vector<SVec>> m_robot_shape;

	pattern_thread pattern_thread_;

private:
	bool agv_registed(int i_id );
	bool agv_registed(std::map<int,traffic_agv_data*>::iterator &it, int i_id );
	bool insert_agv_data();
	std::map<int,traffic_agv_data*> m_traffic_raw_data_;

private:
	//agv body 
	std::string str_traffic_body_map_;
	GridMap* global_body_map_;

	bool check_body_shape();

	bool insert_body_collision(int i_subordinate,int i_superior);
	std::multimap<int,int> mm_body_collision_;

	int print_pause_agv();
	//control list 
	void insert_control_list(int i_subordinate,int i_superior,std::string str_reason);
	//int : agv id which is controlled
	//std::map<int, (: superior to control subordinate) ,int>
	std::map< int, std::multimap<int,std::string> > m_control_list_;
	bool check_agv_controlled(int i_agv_id);

	bool get_check_run_agv();
	std::map<int,traffic_agv_data*> m_traffic_run_data_;
	//std::map<int,traffic_agv_data*> m_traffic_path_collision_;

	//draw ex_robot shape for path is arc
	void draw_ex_shape();
	//check check path match body
	void check_path_match_body();
	//check against seg path
	void check_seg_path_against();

	////////////////////////////////////////////////////////////

	


	

	void check_run_priority();
	tc_body_line_mch tc_mch_;

	//check_agv_path_match_path
	//return line match line same direction or  against 
	void check_agv_path_match_path();

	//find_body_on_another_path_both:
	// 1 path against should pause
	// 2 path same dir continue
	void find_body_on_another_path_both();
	void remove_against_body(std::list<tc_body_line_data> &l_line_body, std::list<tc_body_line_data> &l_line);


	bool line_against( int &i_subordinate , int &i_superior ) ;
	bool line_against( int &i_subordinate , int &i_superior , std::list<std::list<SOdomSpeed>::iterator> path_x , std::list<std::list<SOdomSpeed>::iterator> path_y ) ;

private:
	S8 get_global_body_map( F32 fx , F32 fy );
	S8 get_global_body_map2(F32 fx , F32 fy);
	//set controlled
	//set release
private:
	std::map<int,int> m_ctl_state_;
	int check_agv_pause(  int i_agv_id , bool b_pause );

	

	void set_agv_controlled();
	bool have_seg_pause(int i_subordinate,int i_superior);
	bool have_seg_pause(int i_subordinate);

private://seg path
	seg_path_against seg_path_against_;

private:
	typedef std::multimap<int,int>::iterator MPL_IT;
	
	bool filter_pause_each(std::multimap<int,int>  &m_pl);
	int pause_each(std::multimap<int,int> m_pl);
	bool exist_pause(int i_subordinate , int i_superior, std::multimap<int,int> &m_pl);
	std::multimap<int,int> m_pasue_each_;
	std::multimap<int,int> m_pasue_loop_;
	std::map<int,int> m_pasue_loop_agv_;

	int unfasten_pasue_loop();

};


typedef boost::serialization::singleton<traffic_control> Singleton_Traffic_Control;
#define TRAFFIC_CONTROL Singleton_Traffic_Control::get_mutable_instance()

#endif//_TRAFFIC_CONTROL_WANGHONGTAO_20220303_
