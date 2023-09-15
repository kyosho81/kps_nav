#ifndef _SEPARATE_BLOCK_20210309_H
#define _SEPARATE_BLOCK_20210309_H

//#include "quadtree/QuadTree.h"
#include "octomap/octomap.h"
#include "robot/Geometry.h"
#include "robot/RobotStruct.h"

#include "octomap/octomap.h"
#include "robot/Geometry.h"

#include "area.h"

namespace octomap {
	class OcTree;
}


class separate_block
{
public:
	separate_block();
	~separate_block();

	
	void init(GridMap* p_forbidden_map,GridMap* p_global_map);
	int do_separate_block(std::vector< std::list<SPos> > &l_block_list , const std::list<SPos> &l_block);
	int do_separate_block(std::list<area> &l_area_list, const std::list<SPos> &l_block);
	
	std::list<std::pair<Sxy,Sxy>> get_sep_line();
protected:
private:

	GridMap* p_forbidden_map_;
	GridMap* p_global_map_;

	void init_map(const std::list<SPos> &l_block);
	std::map<int,SPos> m_id_pos_;

	void init_qt_tree();
	octomap::OcTree* octree_;

	void search_choke_point();
	void create_separate_block(std::vector< std::list<SPos> > &l_block_list);
	void create_separate_block(std::list<area> &l_area_list);

	std::list<std::pair<int,int>> vp_choke_point_;
	int i_min_id_diff_;
	F32 f_choke_dis_;

	
};

#endif // _SEPARATE_BLOCK_20210309_H
