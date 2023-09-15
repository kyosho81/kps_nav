#ifndef _PATH_SEARCH_KYOSHO_2022_02_24_
#define _PATH_SEARCH_KYOSHO_2022_02_24_

#include <boost/serialization/singleton.hpp>

#include "robot/Geometry.h"
#include "robot/RobotStruct.h"


class path_search
{
public:
	path_search();
	~path_search();

	void add_unreachable( const int &start_node_id, const int &end_node_id , ORIENTAION ori );
	void clear_unreachable();

	int search( const int &start_node_id, const int &end_node_id , const F32 &start_anlge, const F32 &end_anlge );
	int search( const int &start_node_id, const int &end_node_id , const F32 &start_anlge);
	int search(const int &start_node_id, const int &end_node_id);

	int get_path(std::list<int> &l_path);
	int get_path_ori(std::list<int> &l_path);
	int get_path( ORIENTAION ori, std::list<int> &l_path);
	int get_all_path( std::multimap<ORIENTAION, std::vector<int>> &mt_path );

	static ORIENTAION get_motion_ori(F32 path_ori_rad,F32 agv_ori_rad);
	VecPosition get_node_pos(const int &node_id);

protected:
private:
	bool init_start_ori(const int &start_node_id,F32 start_anlge);
	std::map<ORIENTAION,int> m_start_ori_;

	bool init_end_ori(const int &end_node_id, F32 end_anlge);
	std::map<ORIENTAION,int> m_end_ori_;

	int get_start_ref(ORIENTAION ori);
	int get_end_ref(ORIENTAION ori);

	
	std::multimap<ORIENTAION,std::vector<int>> mt_path_; 

	bool check_path_ori(const int &start_node_id, const int &end_node_id , ORIENTAION ori);
	int search_hyper( std::multimap<ORIENTAION,std::vector<int>> &mt_path, const int &start_node_id, const int &end_node_id , const F32 &start_anlge, const F32 &end_anlge );

private:
	bool check_exist_unreach(const int &start_node_id, const int &end_node_id , ORIENTAION ori);
	std::multimap<int,SEdge_ori> m_fnode_unreach_;
	//std::map<int,SEdge_ori> m_tnode_edge_;
};

typedef boost::serialization::singleton<path_search> Singleton_Path_Search;
#define PATH_SEARCH Singleton_Path_Search::get_mutable_instance()

#endif//_PATH_SEARCH_KYOSHO_2022_02_24_