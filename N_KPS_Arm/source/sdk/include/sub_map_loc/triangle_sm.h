#ifndef _SUB_MAP_LOCALIZATION_KYOSHO_20210704_
#define _SUB_MAP_LOCALIZATION_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/tf_2d_server.h"

class triangle_sm
{
public:
	triangle_sm();
	~triangle_sm();

	void init(F32 edge_len,F32 angle_deg);
	void set_laser_in_base_link( F32 x, F32 y , F32 th );
	bool cal_triangle_pos(SPos &pos ,const std::vector<SLine2P> &ln );
	bool cal_triangle_in_base_link(SPos &pos , const std::vector<SLine2P> &ln);
	SPos tf_robot_in_triangle( const SPos &pos);

	
protected:
private:
	bool check_close( const SVec &p1,const SVec &p2);
	bool check_seg_closeto( SPos &pos, const SLine2P &ln1,const SLine2P &ln2);
		 
	bool intersect(SPos &pos, const SVec &l1p1,const SVec &l2p1 ,const SVec &l1p2,const SVec &l2p2 );
	bool check_angle( F32 &angle_deg , const SVec &l1p1,const SVec &l2p1 ,const SVec &l1p2,const SVec &l2p2 );

	F32 edge_len_;
	F32 edge_tolerance_;
	F32 angle_deg_;
	F32 angle_tolerance_deg_;

	tf_2d_server tf_;
};


#endif//_SUB_MAP_LOCALIZATION_KYOSHO_20210704_
