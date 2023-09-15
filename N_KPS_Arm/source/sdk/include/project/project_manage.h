#ifndef _PROJECT_MANAGE_KYOSHO_20150906_
#define _PROJECT_MANAGE_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>


#include "project/project.h"


class project_manage
{
public:
	project_manage();
	~project_manage();

	std::string get_current_project_nm();
	std::string get_project_nm(const std::string pro_nm);

	project* open_pro(const std::string &pro_nm);
	project* open_pro_from_reflector(const std::string &reflector_nm);
	bool load_reflector(const std::string &pro_nm, const std::string &reflector_nm);
	bool save_pro(const std::string &pro_nm);
	project* get_pro(const std::string pro_nm);
	void set_map(const std::string pro_nm,const std::string str_map_name);
	void set_map(const std::string pro_nm,GridMap* p_map);
	GridMap* get_raw_map(const std::string pro_nm);
	GridMap* get_global_map(const std::string pro_nm);
	
	std::string create_range(const std::string pro_nm);
	void remove_range(const std::string pro_nm, const std::string str_range_name);
	void set_range( const std::string pro_nm,const std::string str_range_name,std::vector<Sxy> &v_list );
	int get_range_nm(const std::string pro_nm, std::vector<std::string> &v_list);
	int get_range(const std::string pro_nm, const std::string range_nm, std::vector<Sxy> &v_list , SPos &pos );
	int get_all_range(const std::string pro_nm,std::vector<std::vector<Sxy>> &v_all_range);
	protobuf_range* get_range(const std::string pro_nm, const std::string range_nm);
	protobuf_range* get_next_range(const std::string pro_nm, const std::string &str_name);
	
	protobuf_reflector* create_reflector(const std::string pro_nm, const SVec &vp);
	void update_reflector(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_reflector(const std::string pro_nm, const int &id);
	int get_reflector(const std::string pro_nm, std::vector<SVec> &ref_list);
	int get_reflector(const std::string pro_nm, std::vector<protobuf_reflector*> &reflector_list);
	protobuf_reflector* get_reflector(const std::string pro_nm, const int &id);
	bool save_reflector_map(const std::string pro_nm,const std::string str_map_name);

	protobuf_lab* create_lab(const std::string pro_nm,const SVec &pos);
	void remove_lab(const std::string pro_nm, const int &id);
	protobuf_lab* get_lab(const std::string pro_nm, const int &id);
	protobuf_lab* get_next_lab(const std::string pro_nm, const int &id);
	void update_lab(const std::string pro_nm, const int &id,const SVec &vp);


	protobuf_node* create_node(const std::string pro_nm,const SVec &pos);
	void remove_node(const std::string pro_nm, const int &id);
	protobuf_node* get_node(const std::string pro_nm, const int &id);
	protobuf_node* get_next_node(const std::string pro_nm, const int &id);
	protobuf_node* get_node_it(const std::string pro_nm,const int &i_pos);
	std::map<int,protobuf_node*> get_node_range(const std::string pro_nm,Sxy topleft,Sxy bottomright);
	int get_node_size(const std::string pro_nm);
	int get_node_list(const std::string pro_nm,std::vector<std::string> &v_comb);
	int get_ref_node(const std::string pro_nm, const int &id , std::vector<std::pair<int ,F32> > &v_ref_node , U8 dir);
	int get_ref_node(const std::string pro_nm, const int &id , std::vector<std::pair<int ,F32> > &v_ref_node);
	int get_ref_edge(const std::string pro_nm, const int &id , std::vector<int> &v_ref_edge_id);
	void update_node(const std::string pro_nm, const int &id,const SVec &vp);
	//void update_node_refnode(const std::string pro_nm, const int &id, const std::vector<int> &v_ref_node_id);
	void update_node_refedge(const std::string pro_nm, const int &id, const std::vector<int> &v_ref_edge_id);
	void add_node_refedge(const std::string pro_nm, const int &id,const int &edge_id);
	
	protobuf_edge* create_edge(const std::string pro_nm,const int &nsrc,const int &ndst);
	void remove_edge(const std::string pro_nm, const int &id);
	protobuf_edge* get_edge(const std::string pro_nm, const int &id);
	protobuf_edge* get_edge(const std::string pro_nm, const int &nsrc,const int &ndst);
	protobuf_edge* get_next_edge(const std::string pro_nm, const int &id);
	void update_edge(const std::string pro_nm, const int &id,const int &ori,const DIRECTION &dir);
	bool check_edge_exist( const std::string pro_nm,const int &nsrc,const int &ndst );

	bool pro_map_setup(const std::string &pro_nm);


	protobuf_cargo_type* create_cargo_type(const std::string pro_nm);
	void update_cargo_type(const std::string pro_nm, const int &id ,const std::string str_cmd);
	void remove_cargo_type(const std::string pro_nm, const int &id);
	protobuf_cargo_type* get_cargo_type(const std::string pro_nm, const int &id);
	protobuf_cargo_type* get_cargo_type_uuid(const std::string pro_nm, const std::string str_uuid);
	protobuf_cargo_type* get_next_cargo_type(const std::string pro_nm, const int &id);
	int get_cargo_type_uuid(const std::string pro_nm,std::vector<std::string> &v_comb);
	bool check_cargo_type_uuid(const std::string pro_nm,std::string str_uuid);

	protobuf_pallet_type* create_pallet_type(const std::string pro_nm);
	void update_pallet_type(const std::string pro_nm, const int &id ,const std::string str_cmd);
	void remove_pallet_type(const std::string pro_nm, const int &id);
	protobuf_pallet_type* get_pallet_type(const std::string pro_nm, const int &id);
	protobuf_pallet_type* get_next_pallet_type(const std::string pro_nm, const int &id);
	int get_pallet_type_uuid(const std::string pro_nm,std::vector<std::string> &v_comb);
	bool check_pallet_type_uuid(const std::string pro_nm,const std::string str_uuid);

	protobuf_pallet* create_pallet(const std::string pro_nm);
	void update_pallet(const std::string pro_nm, const int &id ,const std::string str_cmd);
	void remove_pallet(const std::string pro_nm, const int &id);
	protobuf_pallet* get_pallet(const std::string pro_nm, const int &id);
	protobuf_pallet* get_next_pallet(const std::string pro_nm, const int &id);
	protobuf_pallet* get_pallet_uuid(const std::string pro_nm, const std::string str_uuid);

	protobuf_cargo* create_cargo(const std::string pro_nm);
	void update_cargo(const std::string pro_nm, const int &id ,const std::string str_cmd);
	void remove_cargo(const std::string pro_nm, const int &id);
	protobuf_cargo* get_cargo(const std::string pro_nm, const int &id);
	protobuf_cargo* get_next_cargo(const std::string pro_nm, const int &id);
	protobuf_cargo* get_cargo_uuid(const std::string pro_nm, const std::string str_uuid);


	protobuf_producer* create_producer(const std::string pro_nm,const SVec &pos);
	void update_producer(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_producer(const std::string pro_nm, const int &id);
	protobuf_producer* get_producer(const std::string pro_nm, const int &id);
	protobuf_producer* get_next_producer(const std::string pro_nm, const int &id);

	protobuf_consumer* create_consumer(const std::string pro_nm,const SVec &pos);
	void update_consumer(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_consumer(const std::string pro_nm, const int &id);
	protobuf_consumer* get_consumer(const std::string pro_nm, const int &id);
	protobuf_consumer* get_next_consumer(const std::string pro_nm, const int &id);

	protobuf_processer* create_processer(const std::string pro_nm,const SVec &pos);
	void update_processer(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_processer(const std::string pro_nm, const int &id);
	protobuf_processer* get_processer(const std::string pro_nm, const int &id);
	protobuf_processer* get_next_processer(const std::string pro_nm, const int &id);

	protobuf_storage* create_storage(const std::string pro_nm,const SVec &pos);
	void update_storage(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_storage(const std::string pro_nm, const int &id);
	protobuf_storage* get_storage(const std::string pro_nm, const int &id);
	protobuf_storage* get_next_storage(const std::string pro_nm, const int &id);


	protobuf_charge* create_charge(const std::string pro_nm,const SVec &pos);
	void update_charge(const std::string pro_nm, const int &id,const SVec &vp);
	void remove_charge(const std::string pro_nm, const int &id);
	protobuf_charge* get_charge(const std::string pro_nm, const int &id);
	protobuf_charge* get_next_charge(const std::string pro_nm, const int &id);

	protobuf_action_base* create_action_fork(const std::string pro_nm);
	void update_action_fork(const std::string pro_nm, const int &id ,const std::string str_cmd);
	void remove_action_fork(const std::string pro_nm, const int &id);
	protobuf_action_base* get_action_fork(const std::string pro_nm, const int &id);
	protobuf_action_base* get_action_fork_uuid(const std::string pro_nm, const std::string str_uuid);
	protobuf_action_base* get_next_action_fork(const std::string pro_nm, const int &id);
	int get_action_fork_uuid(const std::string pro_nm,std::vector<std::string> &v_comb);

	protobuf_rect* create_rect(const std::string pro_nm,const SPos &pos);
	void update_rect(const std::string pro_nm, const std::string &str_name,const SPos &pos);
	void remove_rect(const std::string pro_nm, const std::string &str_name);
	protobuf_rect* get_rect(const std::string pro_nm, const std::string &str_name);
	protobuf_rect* get_next_rect(const std::string pro_nm, const std::string &str_name);


	protobuf_qrcode* create_qrcode(const std::string pro_nm,const SPos &pos);
	void update_qrcode(const std::string pro_nm, const int &id,const SVec &vp);
	void update_qrcode(const std::string pro_nm, const int &id,const F32 &angle);
	void remove_qrcode(const std::string pro_nm, const int &id);
	protobuf_qrcode* get_qrcode(const std::string pro_nm, const int &id);
	protobuf_qrcode* get_next_qrcode(const std::string pro_nm, const int &id);
	bool save_qr_map(const std::string pro_nm,const std::string str_map_name);
	bool load_qr_map(const std::string &pro_nm, const std::string &str_map_name);


	protobuf_base* get_role(const std::string &pro_nm, std::string str_name);

private:

	std::map<std::string,project*> project_list_;
	std::string str_current_project_nm_;
};

typedef boost::serialization::singleton<project_manage> Singleton_Project_Manage;
#define PRO_MANAGE Singleton_Project_Manage::get_mutable_instance()
#define CURRENT_PRO Singleton_Project_Manage::get_mutable_instance().get_current_project_nm()
#endif//_PROJECT_MANAGE_KYOSHO_20150906_
