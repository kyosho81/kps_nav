#ifndef _REFLECTED_PILLAR_KYOSHO_20191120_
#define _REFLECTED_PILLAR_KYOSHO_20191120_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "device/amcl_tf.h"
#include "least squares_pos_tf.h"

#include "quadtree/QuadTree.h"

class protobuf_reflector;

class reflected_pillar_loc
{
public:
	reflected_pillar_loc();
	~reflected_pillar_loc();

	void init();
	void init(std::vector<SReflectorPos> &v_ref_pos);

	int load_reflected_map( std::vector<SReflectorPos> &v_ref_pos, const std::string &reflected_map);

	void init_dynamic();

	//insert reflector and cal ref reflector dis
	void insert(std::map<int,protobuf_reflector*> &m_reflector_list);

	bool dynamic_insert(SPUB_BAG_EX &pub_bag_ex);
	
	eDEV_ERR_CODE reflector_loc( SPos &pos,const SReflector &cur_ref_list, F32 &ref_confidence);

	int get_sim_laser_data( SReflector &cur_ref_list , SPos pos);
	void debug_print();
	//int get_mapping_reflector(std::vector<SVec> &reflector_list);
	
	SPos ref_laser_pos_;

protected:
private:
	

	
	///////////all function and data used for laser base reflector
	bool cal_reflector_pair( SReflector cur_ref_list);
	SVec get_local_reflector(const int &id);
	F32 get_another_edge_reflector(int &an_id,const int &id);
	//reflector select to cal location
	bool destruct_reflector_list();
	//reflector load from file
	std::map<int,protobuf_reflector*> m_reflector_list_;

	std::map< int,SVec > m_cur_ref_list_;
	std::multimap< F32, SPair_SVec> mt_ref_dis_;
	std::map<int,int> m_selected_ref_list_;
	int i_selected_edge_count_;
	
	void bind_local_ref_with_global(const int &local_id, const int &f_global_id, const int &t_global_id);
	//     int local id <int global id, int count>
	std::map<int,std::map<int,int>> m_match_in_local_;
	///////////all function and data used for laser base reflector


	///////////all function and data used for global base reflector
	int find_dis(std::multimap<F32, std::pair<protobuf_reflector *, protobuf_reflector *>> &pair_list,const F32 &dis);
	void add_match_in_global(const std::multimap<F32, std::pair<protobuf_reflector *, protobuf_reflector *>> &pair_list, const int &l_ref_from,const int &l_ref_to);
	bool selected_in_global_map(const int &id);
	// int global id <int local id , int count>
	std::map<int,std::map<int,int>> m_match_in_global_;
	///////////all function and data used for global base reflector

	bool reflector_selected(const int &id);
	bool edge_point_selected(const int &p_from,const int &p_to);
	void set_select_edge();
	bool select_edge_for_search();
	

	void bind_global_ref_with_local(const int &global_id, const int &f_local_id, const int &t_local_id);
	//void get_ref_id_list(std::map<int,int> &m_ref_id_list, const std::multimap<F32, std::pair<protobuf_reflector *, protobuf_reflector *>> &pair_list);
	int match_edge_in_global(std::vector<std::pair<SVec,SVec>> &v_pp_pairs);
	F32 cal_ref_confidence(const std::vector<std::pair<SVec,SVec>> &v_pp_pairs, const SPos &pos);

	bool get_max_probility_match(std::multimap<int, std::pair<int, int>> &mt_anchor,std::multimap<int, std::pair<int, int>> &mt_sort_tmp);
	//protobuf_reflector* get_protobuf_ref2(const int &id);
	protobuf_reflector* get_list_ref(const int &id);
	//protobuf_reflector* get_list_ref_dynamic(const int &id);
	bool check_g_l(const int &gf_id,const int &gt_id,const int &lf_id,const int &lt_id);
	bool try_match(const std::vector<std::pair<int, int>> &m_anchor);
	bool set_anchor(std::map<int,int> &m_anchor, const int &g_ref_id, const int &l_ref_id);
	void set_merge(std::vector< std::vector< std::pair<int,int> >> &v_merge_cmn,std::multimap< int, std::pair<int,int>>::iterator it_begin,std::multimap< int, std::pair<int,int>>::iterator it_end,const int &i_min_size);
	int make_local_global_bind(std::vector<std::pair<int, int>> &v_match_res);
	
	SPos laser2loc(const SPos& laser_pos);
	SPos laser2loc(const SPos& laser_pos,const SPos& laser_diff);
private:

	bool del_reflector_pair( protobuf_reflector* ref1,protobuf_reflector* ref2);
	void insert_reflector_pair(const F32 &dis, protobuf_reflector* ref1,protobuf_reflector* ref2);
	F32 dis_reflector_pair(protobuf_reflector* ref_1,protobuf_reflector* ref_2);
	std::multimap<protobuf_reflector*,protobuf_reflector*> mt_reflector_pair_;
	std::multimap<F32,std::pair< protobuf_reflector*,protobuf_reflector* >> mt_reflector_dis_;
	QuadTree<protobuf_reflector*>* qtree_;

	F32 tolerance_k_;
	F32 max_laser_radii_;
	F32 max_laser_sim_radii_;
	int max_ref_count_;
	SPos laser_diff_;

private:
	void init_c_nm_map();
	int get_c_nm(const int &n);
	int c_nm(const int &n ,const int &m);
	
	
	std::map<int,int> m_c_nm_;

	least_squares_pos_tf LS_;
// mapping ref
private:
	eDEV_ERR_CODE dynamic_reflector_loc( SPos &pos, const SPos &laser_diff, SReflector cur_ref_list);
	int reflector_existed(F32 &p_x ,F32 &p_y);
	int insert_scan_ref(SPos pos ,F32 dx, F32 dy,SReflector &laser_reflector);
	
	void drop_not_in_global_map(SPos &pos, const SPos &laser_diff,SReflector &cur_ref_list);
	//void insert_scan_ref(SPUB_BAG_EX &pub_bag_ex);
	//std::map<int,protobuf_reflector*> m_reflector_map_;
	bool b_first_bag_;
	amcl_tf tf_odom_refloc_;
	bool b_calib_odom_;

	

};

typedef boost::serialization::singleton<reflected_pillar_loc> Singleton_Reflected_Pillar;

#endif//_REFLECTED_PILLAR_KYOSHO_20191120_
