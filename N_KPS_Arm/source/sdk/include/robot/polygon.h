#ifndef _POLYGON_KYOSHO_20161220_
#define _POLYGON_KYOSHO_20161220_

#include <vector>

#include "RobotStruct.h"
#include "Geometry.h"

#define POLYGON_COUNT		1441
#define POLYGON_ANGLE_START 0
#define POLYGON_ANGLE_DIFF  0.25

class polygon
{
public:

	polygon();
	~polygon();
	
	//init robot shape polygon,with CCW point list
	void init_shape(const std::vector<Sxy> &shape);
	void init_shape( const std::string &str_shape );
	void get_range(SLaser& min_range,F32 dx,F32 dy);
//	void get_urg_range(SLaser_Urg& min_range,F32 dx);

protected:
private:
	void clean();
	
// 	F32 angle_;
// 	F32 dis_;
	void create_angle_range();
	bool getCrossLine(Line &ln,VecPosition ray,std::vector<Sxy>::iterator &seg_end);
	bool getCrossLine2(Line &ln,VecPosition ray);
	F32 angle_list_[POLYGON_COUNT];
	F32 range_list_[POLYGON_COUNT];

private:
	void print_shape();
	bool find_ray_in_seg(std::vector<Sxy>::iterator &it_begin,std::vector<Sxy>::iterator &it_end,const VecPosition& ray);
	std::vector<Sxy> shape_list_;

};


#endif//_POLYGON_KYOSHO_20161220_
