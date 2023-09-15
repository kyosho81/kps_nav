#ifndef _SCAN_MAP_CONVER_KYOSHO_20200224
#define _SCAN_MAP_CONVER_KYOSHO_20200224

#include <map>

#include "gmapping/scanmatcher/smmap.h"

#include "RobotStruct.h"
#include "robot/k_means.h"
#include "quadtree/QuadTree.h"

class GridMap;

namespace GMapping{
	class ScanMatcher;
}

class scan_map_conver
{
public:
	scan_map_conver();
	~scan_map_conver();

	void init_new_grid_map();
	bool add_scan2map(const SLaser &scan , const SPos &odom,const float &dx,const float &dy);
	bool save_map(std::string str_save_file_);
	bool save_map(GridMap* &p_map);

protected:
private:

	//SlamGMapping* g_slam_;
	GMapping::ScanMatcher* p_matcher_;
	GMapping::ScanMatcherMap* p_smap_;
	bool  b_first_scan_;
	int i_last_map_size_x_;
	int i_last_map_size_y_;
};

#endif//_SCAN_MAP_CONVER_KYOSHO_20200224
