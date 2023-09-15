#ifndef _DISASSEMBLY_ORDER_WANGHONGTAO_20220303_
#define _DISASSEMBLY_ORDER_WANGHONGTAO_20220303_

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
#include "dispatching/order_factory.h"


class search_path_node
{
public:
	search_path_node(){
		i_from_node_ = 0;
		i_to_node_ = 0;
		i_total_path_size_ = 0;

	};
	~search_path_node(){};

	int i_from_node_;
	int i_to_node_;
	int i_total_path_size_;

	F32 f_from_angle_;
	F32 f_to_angle_;

	ORIENTAION ori_;
	std::vector<int> path_;

	std::map<search_path_node*,int> m_next_;

	std::string get_path_para();

protected:
private:
};

class task_flow_data;

class disassembly_order
{
public:
	disassembly_order();
	~disassembly_order();

	std::string disassembly( task_flow_data* tf, order_schedule* p_osch );
	bool disassembly( std::list<order_schedule*> &l_osch , std::multimap<std::string, protobuf_base *> &mm_all_roles );

	
protected:



private:

	void fill_osch( order_schedule* p_osch);
	bool disassembly_path_node(order_schedule &osch);
	bool disassembly_path_node2(order_schedule &osch, std::multimap<std::string, protobuf_base *> &mm_all_roles, std::vector<SEdge_ori> &v_edge_err);

	void print_osch(const order_schedule &osch);
	void print_spirit_path(std::list<spirit_path> &l_path_array);

	
private:
	//std::list<int> l_path_;
	int disassembly_get_ff(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_get_fb(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_put_ff(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_put_fb(std::list<spirit_path> &l_path_array, one_task &one_t);

	int disassembly_get_sf(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_put_sf(std::list<spirit_path> &l_path_array, one_task &one_t);

	int disassembly_get(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_put(std::list<spirit_path> &l_path_array, one_task &one_t);

	int disassembly_pack(std::list<spirit_path> &l_path_array, one_task &one_t);
	int disassembly_charge(std::list<spirit_path> &l_path_array, one_task &one_t);

	std::list<spirit_path> l_path_array_;

	int get_bind_action( protobuf_base* p_base , std::string type , std::list<KPS::mp_bind_action> &l_bind_action);
	int get_turn_id( std::vector<int> &v_turn_id, protobuf_base* p_base);

	spirit_path create_spirit_path( std::list<int> &l_path , std::list<KPS::mp_bind_action> l_bind_action);
	
	
	std::list<spirit_path> create_spirit_path( std::list<search_path_node> l_sel_path , std::list<KPS::mp_bind_action> l_bind_action);
	spirit_path create_spirit_path( search_path_node path );
	void fill_path_action(spirit_path &spath,std::list<KPS::mp_bind_action> &l_bind_action);

	int bind_action_on_node( spirit_path &spath, std::list<KPS::mp_bind_action> l_bind_action);
	bool bind_unload_fork_lev(spirit_path &spath, int i_id_diff = 1);
	bool bind_loadling_fork_lev(spirit_path &spath, int i_id_diff = 1);

	bool bind_get_fork_over(spirit_path &spath, int i_id_diff = 0);
	bool bind_get_fork_before(spirit_path &spath, int i_id_diff = 1);
	bool bind_put_fork_over(spirit_path &spath, int i_id_diff = 0);
	bool bind_put_fork_before(spirit_path &spath, int i_id_diff = 1);
	
	bool bind_get_role_over(spirit_path &spath, int i_id_diff = -1);
	bool bind_put_role_over(spirit_path &spath, int i_id_diff = -1);

	bool bind_occupy(spirit_path &spath);
	bool bind_release(spirit_path &spath);
	bool bind_charge_begin(spirit_path &spath);
	bool bind_charge_over(spirit_path &spath);

	ORIENTAION get_motion_ori(int i_node_1 , int i_node_2 , F32 f_agv_ori);
	F32 get_motion_angle(int i_node_1 , int i_node_2 );

	std::vector<F32> create_quater_angle(int i_node_1,int i_node_2);
	bool create_path_comb( std::vector< std::list<std::pair<int,F32>>> &v_path_comb, int i_node_1,int i_node_2,std::vector<int> v_comb_1, std::vector<int> v_comb_2,F32 f_angle_1,F32 f_angle_2);
	int select_path( std::list<search_path_node> &l_sel_path , std::vector< std::list<std::pair<int,F32>>> &v_path_comb , std::vector<int> &v_node_err, std::vector<SEdge_ori> &v_edge_err);

	int create_all_path( std::multimap<int,std::list<search_path_node>> &m_res_path , std::vector< std::list<std::pair<int,F32>>> &v_path_comb , std::vector<int> &v_node_err, std::vector<SEdge_ori> &v_edge_err);
	bool match_path(std::list<search_path_node> &l_sel_path, task_flow_data* tf);
	bool get_path_by_reqact( std::multimap<int,std::list<search_path_node>> &m_res_path , std::vector<std::string> v_req_stage);
	
	bool check_path_suitable(std::multimap<int,std::list<search_path_node>> &m_res_path, std::vector<std::list<search_path_node>> v_seg_path);
	void check_path_dir(std::multimap<int,std::list<search_path_node>> &m_res_path,float f_from_angle, float f_to_angle);
	void check_path_error(std::multimap<int,std::list<search_path_node>> &m_res_path, std::vector<int> &v_node_err,  std::vector<SEdge_ori> &v_edge_err);
	bool node_err(std::list<search_path_node> &seg_path, std::vector<int> &v_node_err);
	bool edge_err(std::list<search_path_node> &seg_path, std::vector<SEdge_ori> &v_edge_err);
	bool get_next_sn( std::multimap<int,search_path_node> &mt_seg, search_path_node* p_next, int i_deep );
	//std::vector< std::list<std::pair<int,F32>>> v_path_comb_; 

	//task flow ref
private:
	protobuf_base* get_close_role( int i_cur_node_id, F32 f_cur_angle );
	int get_nocross_node(protobuf_base* p_get_role, protobuf_base* p_release_role);

	bool match_tf_mvseg(std::map<std::string,std::list<search_path_node>::iterator> m_path_mv_seg, std::vector<std::string> v_req_stage);
	std::vector<int> v_nocross_node_;
	std::vector<SEdge_ori> v_edge_err_;

	void get_path_segnm(std::map<std::string,std::list<search_path_node>::iterator > &m_path_mv_seg, std::list<search_path_node> &l_sel_path);
	bool filter_path(std::list<search_path_node> &l_sel_path , std::vector<std::string> v_req_stage);
	
	int disassembly_pack_charge(order_schedule* p_osch, bool b_charge);
	bool search_pack_charge_path(std::list<search_path_node> &v_seg_path ,order_schedule* p_osch);
	bool search_path(std::list<search_path_node> &v_seg_path, order_schedule* p_osch, task_flow_data* tf, std::string str_stage_nm);


	int get_stage_required(std::vector<std::string> &v_req_stage, std::string str_stage_nm, task_flow_data* tf );
	std::list<KPS::mp_bind_action> fnc_bind_role(std::list<KPS::mp_bind_action> &l_bind_act_src, std::list<KPS::mp_bind_action> &l_bind_act_des, std::string str_act_type);
	bool get_bind_act(KPS::mp_bind_action &kbact, std::list<KPS::mp_bind_action> &l_bind_act, std::string str_get_put, std::string str_mv_seg, std::string str_act_type);
	bool get_bind_act(KPS::mp_bind_action &kbact, std::list<KPS::mp_bind_action> &l_bind_act,spirit_action &sact);
	std::vector<int> cov_path(std::string str_path);
	bool cal_path_para(spirit_action &sact, std::vector<int> &vi_path);

	std::string create_acts(act_list &acts,task_flow_data* tf ,std::list<search_path_node> &v_get_path, std::list<search_path_node> &v_put_path);
	bool fill_act_para(act_list &acts,task_flow_data* tf ,std::list<KPS::mp_bind_action> l_bind_release_act, std::list<KPS::mp_bind_action> l_bind_from_act, std::list<KPS::mp_bind_action> l_bind_to_act);
	bool chk_act( order_schedule* p_osch );

	std::string code_acts(act_list &acts);
	
	//bool decode_acts(act_list &acts,std::string str_code);


};

typedef boost::serialization::singleton<disassembly_order> Singleton_Disassembly_Order;
#define DISASSEMBLY_ORDER Singleton_Disassembly_Order::get_mutable_instance()

#endif//_DISASSEMBLY_ORDER_WANGHONGTAO_20220303_
