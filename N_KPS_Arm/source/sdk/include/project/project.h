#ifndef _PROJECT_KYOSHO_20150906_
#define _PROJECT_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

#include "protobuf_msg/protobuf_map.h"
#include "protobuf_msg/protobuf_path.h"
#include "protobuf_msg/protobuf_range.h"
#include "protobuf_msg/protobuf_reflector.h"
#include "protobuf_msg/protobuf_lab.h"
#include "protobuf_msg/protobuf_node.h"
#include "protobuf_msg/protobuf_edge.h"
#include "protobuf_msg/protobuf_cargo_type.h"
#include "protobuf_msg/protobuf_pallet_type.h"
#include "protobuf_msg/protobuf_pallet.h"
#include "protobuf_msg/protobuf_cargo.h"
#include "protobuf_msg/protobuf_producer.h"
#include "protobuf_msg/protobuf_consumer.h"
#include "protobuf_msg/protobuf_action_base.h"
#include "protobuf_msg/protobuf_processer.h"
#include "protobuf_msg/protobuf_storage.h"
#include "protobuf_msg/protobuf_station.h"
#include "protobuf_msg/protobuf_charge.h"
#include "protobuf_msg/protobuf_rect.h"
#include "protobuf_msg/protobuf_qrcode.h"

class GridMap;

#define AMCL_MAP "amcl_map"
#define GLOBAL_MAP "global_map"

class project
{
public:

	project();
	~project();

//	void set_pro_name(std::string str_pro_name);

	void set_map(std::string str_map_name);
	void set_map(GridMap* p_map);
	
	GridMap* get_raw_map();
	GridMap* get_amcl_map();
	GridMap* get_global_map();

	int get_range_name_list(std::vector<std::string> &v_name_list);
	std::string create_range();
	void remove_range(const std::string str_name);

	void set_range( std::string str_name , std::vector<Sxy> &v_list );
	void set_range_start_pos( std::string str_name , const SPos &pos );

	int get_range( std::string str_name, std::vector<Sxy> &v_list, SPos &pos);
	int get_all_range( std::vector<std::vector<Sxy>> &v_all_range );
	protobuf_range* get_range( std::string str_name);
	protobuf_range* get_next_range(const std::string &str_name);

	int get_path_name_list(std::vector<std::string> &v_name_list);
	void add_path( std::string str_name , std::vector<SOdomSpeed> &v_list);
	int get_path( std::string str_name , std::vector<SOdomSpeed> &v_list);

	int add_reflector(const SVec &pos);
	int add_reflector(const SVec &pos,const std::vector<std::pair<int,F32>> &reflector_list);
	int get_reflector(const int &id, std::vector<std::pair<int,F32>> &reflector_list);
	int get_reflector_all(std::vector<SReflectorPos> &v_ref_pos);
	protobuf_reflector* get_reflector(const int &id);
	protobuf_reflector* get_next_reflector(const int &id, std::vector<std::pair<int,F32>> &reflector_list);
	void remove_reflector(const int &id);

	int add_lab(const SVec &pos,const std::string str_nm);
	protobuf_lab* get_lab(const int &id);
	protobuf_lab* get_next_lab(const int &id);
	void remove_lab(const int &id);

	int add_node(const SVec &pos);
//	int add_node(const SVec &pos,const std::vector<int> &v_ref_edge_id);
	protobuf_node* get_node(const int &id);
	protobuf_node* get_next_node(const int &id);
	protobuf_node* get_node_it(const int &i_pos);
	int get_node_size();
	int get_node_list( std::vector<std::string> &v_comb );
	std::map<int,protobuf_node*> get_node_range( Sxy topleft,Sxy bottomright );
	void remove_node(const int &id);
	bool set_node_ref_edge(const int &id,const int &ref_edge_id);
	bool remove_node_ref_edge(const int &id,const int &ref_edge_id);
	int get_ref_edge(const int &id , std::vector<int> &v_ref_edge);
	bool pos_in_range(VecPosition vec ,const std::vector<Sxy> &v_range_list);

	int add_edge(const int &nsrc,const int &ndst);
	protobuf_edge* get_edge(const int &id);
	protobuf_edge* get_edge(const int &nsrc,const int &ndst);
	protobuf_edge* get_next_edge(const int &id);
	void remove_edge(const int &id);
	bool check_edge_exist(const int &nsrc,const int &ndst);
	

	int add_cargo_type();
	protobuf_cargo_type* get_cargo_type(const int &id);
	protobuf_cargo_type* get_cargo_type_uuid(const std::string str_uuid);
	protobuf_cargo_type* get_next_cargo_type(const int &id);
	void remove_cargo_type(const int &id);
	int  get_cargo_type_uuid(std::vector<std::string> &v_comb);
	bool check_cargo_type_uuid(std::string str_uuid);

	int add_pallet_type();
	protobuf_pallet_type* get_pallet_type(const int &id);
	protobuf_pallet_type* get_next_pallet_type(const int &id);
	void remove_pallet_type(const int &id);
	int  get_pallet_type_uuid(std::vector<std::string> &v_comb);
	bool check_pallet_type_uuid(std::string str_uuid);

	int add_pallet();
	protobuf_pallet* get_pallet(const int &id);
	protobuf_pallet* get_pallet_uuid(const std::string str_uuid);
	protobuf_pallet* get_next_pallet(const int &id);
	void remove_pallet(const int &id);

	int add_cargo();
	protobuf_cargo* get_cargo(const int &id);
	protobuf_cargo* get_cargo_uuid(const std::string str_uuid);
	protobuf_cargo* get_next_cargo(const int &id);
	void remove_cargo(const int &id);

	int add_producer(const SVec &pos);
	protobuf_producer* get_producer(const int &id);
	protobuf_producer* get_next_producer(const int &id);
	void remove_producer(const int &id);

	int add_consumer(const SVec &pos);
	protobuf_consumer* get_consumer(const int &id);
	protobuf_consumer* get_next_consumer(const int &id);
	void remove_consumer(const int &id);

	int add_processer(const SVec &pos);
	protobuf_processer* get_processer(const int &id);
	protobuf_processer* get_next_processer(const int &id);
	void remove_processer(const int &id);

	int add_storage(const SVec &pos);
	protobuf_storage* get_storage(const int &id);
	protobuf_storage* get_next_storage(const int &id);
	void remove_storage(const int &id);

	int add_charge(const SVec &pos);
	protobuf_charge* get_charge(const int &id);
	protobuf_charge* get_next_charge(const int &id);
	void remove_charge(const int &id);

	int add_action_fork();
	protobuf_action_base* get_action_fork(const int &id);
	protobuf_action_base* get_action_fork_uuid(const std::string str_uuid);
	protobuf_action_base* get_next_action_fork(const int &id);
	void remove_action_fork(const int &id);
	int  get_action_fork_uuid(std::vector<std::string> &v_comb);


	std::string add_rect();
	protobuf_rect* get_rect(const std::string &str_name);
	protobuf_rect* get_next_rect(const std::string &str_name);
	void remove_rect(const std::string &str_name); 


	int add_qr_code(const SVec &pos,const std::string str_des);
	protobuf_qrcode* get_qr_code(const int &id);
	protobuf_qrcode* get_next_qr_code(const int &id);
	void remove_qr_code(const int &id);


	bool save(std::string str_pro);
	bool load(std::string str_pro);
	bool open_from_reflector( std::string str_ref );
	bool load_from_reflector( std::string str_ref );
	bool save_reflector_map( std::string str_ref_map );

	bool load_from_qr( std::string str_qr_name );
	bool save_qr_map( std::string str_qr_map );
	int get_qr_all(std::vector<SQrCode> &v_qr_code);

	void print_all_range();
	void print_all_path();
	void print_all_reflector();

	bool map_setup();

	protobuf_base* get_role(std::string str_name);

protected:
private:
	
	void write_data(std::ofstream &off, char* ch_data,int ilen);
	void read_data(std::ifstream &iff, char* &ch_data,int &ilen);

	protobuf_map raw_map_;
	protobuf_map amcl_map_;
	protobuf_map global_map_;

	int i_max_range_id_;
	int i_max_path_id_;
	std::map<std::string,protobuf_range*> m_rangle_list_;
	std::map<std::string,protobuf_path*> m_path_list_;
	std::map<int,protobuf_reflector*> m_reflector_list_;
	std::map<int,protobuf_lab*> m_lab_list_;
	std::map<int,protobuf_node*> m_node_list_;
	std::map<int,protobuf_edge*> m_edge_list_;
	std::map<int,protobuf_cargo_type*> m_cargo_type_list_;
	std::map<int,protobuf_pallet_type*> m_pallet_type_list_;
	std::map<int,protobuf_pallet*> m_pallet_list_;
	std::map<int,protobuf_cargo*> m_cargo_list_;
	std::map<int,protobuf_producer*> m_producer_list_;
	std::map<int,protobuf_consumer*> m_consumer_list_;
	std::map<int,protobuf_processer*> m_processer_list_;
	std::map<int,protobuf_storage*> m_storage_list_;
	std::map<int,protobuf_charge*> m_charge_list_;
	std::map<int,protobuf_action_base*> m_action_list_;
	std::map<std::string,protobuf_rect*> m_rect_list_;
	std::map<int,protobuf_qrcode*> m_qr_list_;

	float amcl_map_inf_;
	float global_map_inf_;

	//std::string str_map_path_;
	void save_raw_map(std::ofstream &off);
	void load_raw_map(std::ifstream &iff);

	void save_amcl_map(std::ofstream &off);
	void load_amcl_map(std::ifstream &iff);

	void save_global_map(std::ofstream &off);
	void load_global_map(std::ifstream &iff);

	void save_range(std::ofstream &off);
	void load_range(std::ifstream &iff);
	void clear_range();

	void save_path(std::ofstream &off);
	void load_path(std::ifstream &iff);
	void clear_path();

	void save_reflector(std::ofstream &off);
	void load_reflector(std::ifstream &iff);
	void clear_reflector();

	void save_lab(std::ofstream &off);
	void load_lab(std::ifstream &iff);
	void clear_lab();

	void save_node(std::ofstream &off);
	void load_node(std::ifstream &iff);
	void clear_node();

	void save_edge(std::ofstream &off);
	void load_edge(std::ifstream &iff);
	void clear_edge();

	void save_cargo_type(std::ofstream &off);
	void load_cargo_type(std::ifstream &iff);
	void clear_cargo_type();

	void save_pallet_type(std::ofstream &off);
	void load_pallet_type(std::ifstream &iff);
	void clear_pallet_type();

	void save_producer(std::ofstream &off);
	void load_producer(std::ifstream &iff);
	void clear_producer();

	void save_consumer(std::ofstream &off);
	void load_consumer(std::ifstream &iff);
	void clear_consumer();

	void save_processer(std::ofstream &off);
	void load_processer(std::ifstream &iff);
	void clear_processer();

	void save_storage(std::ofstream &off);
	void load_storage(std::ifstream &iff);
	void clear_storage();

	void save_charge(std::ofstream &off);
	void load_charge(std::ifstream &iff);
	void clear_charge();

	void save_qrcode(std::ofstream &off);
	void load_qrcode(std::ifstream &iff);
	void clear_qrcode();

private:
	bool b_set_map_;
//	std::string str_pro_name_;
};

#endif//_PROJECT_KYOSHO_20150906_
