#ifndef _POS_SEARCH_KYOSHO_20221116_
#define _POS_SEARCH_KYOSHO_20221116_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "robot/RobotStruct.h"
#include "device/amcl_tf.h"
#include "Comm/pattern_thread.h"


#include "quadtree/QuadTree.h"


typedef struct _STree_Node
{
	SPos pos_;
	void* p_data_;

}STree_Node;

class pos_search
{
public:
	pos_search();
	~pos_search();

	bool init();
	bool insert_pos(SPos pos, void* p_data);
	int get_in_range( std::vector<STree_Node> &v_res, SPos target_pos );

protected:
private:
	F32 f_find_range_;// find range around pos rect box
	F32 f_angle_range_;// find angle diff in (rad)
	QuadTree<STree_Node>* qtree_;

private:
	bool check_angle( F32 search_a, F32 target_a );
	bool check_target_rect( SPos search_pos,  SPos target_pos );

	F32 f_dis2xaxle_;
	F32 f_dis2yaxle_;
};

#endif//_POS_SEARCH_KYOSHO_20221116_
