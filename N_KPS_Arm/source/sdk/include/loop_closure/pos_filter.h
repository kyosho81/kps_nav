#ifndef _POS_FILTER_KYOSHO_20200224
#define _POS_FILTER_KYOSHO_20200224

#include <map>

#include "RobotStruct.h"
#include "robot/k_means.h"
#include "quadtree/QuadTree.h"
#include "buffer_con.hpp"

class GridMap;
class filter2D_template;

class pos_filter
{
public:
	pos_filter();
	~pos_filter();


	void init(GridMap* p_map = 0);

	void add_probability_pos(std::vector<SPos> &v_pos);
	//return confidence
	F32 get_pro_pos( SPos &pos , std::vector<STriangle> &v_probability_pos);

protected:
private:

	bool check_pos_available(const SPos &robot_pos);
	void check_k_para(const float &fx, const float &fy );
	bool b_first_data_;
//cluster pos
	k_means kmeans_;
	int cluster_k_;
	QuadTree<int>* qtree_;
	F32 max_cluster_dis_;
	void cluster_pos();
	void up_date();
	//when old point is close to new point
	bool check_old_pos_avaliable( const float &fx, const float &fy );


	F32 confidence_;
	CSBuffer<SPos,1> final_pos_;
	SPos cal_pos( const std::vector<std::vector<point>::iterator> &v_max_pos);
	std::vector<STriangle> v_probability_pos_;

	int i_remove_;
	//std::list<std::map<int,std::list<point>>> l_his_point_;

	///////////amcl map where robot in EMPTY place  
	void load_test_map(const std::string &map_name);
	GridMap* amcl_shared_map_;
	///////////probability map where is robot place on
	GridMap* probability_map_;
	filter2D_template* p_f2d_;
	F32 robot_pos_inf_;
	int i_clear_0_127_;
};

#endif//_POS_FILTER_KYOSHO_20200224
