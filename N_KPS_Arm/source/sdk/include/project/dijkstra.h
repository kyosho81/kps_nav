#ifndef _DIJKSTRA_KYOSHO_2019_09_17_
#define _DIJKSTRA_KYOSHO_2019_09_17_

#include "robot/Geometry.h"
#include "robot/RobotStruct.h"


class dijkstar
{
public:
	dijkstar();
	~dijkstar();

	void add_unreachable( std::multimap<int,SEdge_ori> &mm_unreachable);
	void add_unreachable( const int &start_node_id, const int &end_node_id , ORIENTAION ori );
	bool unreachable( const int &start_node_id, const int &end_node_id , U8 ori_all  );
	void clear_unreachable();

	int search( std::list<int> &l_path, const int &start_node_id, const int &end_node_id , U8 ori = 0xff );

protected:
private:

	int start_node_id_;
	int end_node_id_;

	bool check_in_close_list(const int &id);
	int get_min_dis_node();
		
	bool update_dis(const int &id,F32 dis,const int &from_id);
	void sort_min_dis();
	F32 get_dis(const int &id);

	int find_path(std::list<int> &l_path);
	void print_debug();
 
	//pair first dis; last nod id;
	typedef std::pair< F32 , int > T_dis_head;
	//map < node id , T_dis_head >
	std::map< int , T_dis_head> m_id_dis_map_;
	//sort by dis increase
	std::list< std::map< int , T_dis_head>::iterator > l_it_map_; 
	//close list  
	std::map<int,int> close_list_;

private:
	
	//unreachable edge
	std::multimap<int,SEdge_ori> mm_unreachable_;
};


#endif//_DIJKSTRA_KYOSHO_2019_09_17_