#ifndef _SIM_OBSTACLE_WANGHONGTAO_20190501_
#define _SIM_OBSTACLE_WANGHONGTAO_20190501_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/buffer_con.hpp"
#include "RobotStruct.h"
#include "robot/Geometry.h"

typedef struct _SObstacle
{
	int id_;
	SPos pos_;

	std::vector<Sxy> range_list_;

	F32 radius_;
	F32 vx_;
	F32 w_;

} SObstacle;

class sim_obstacle
{
public:
	sim_obstacle();
	~sim_obstacle();

	void set_obs_pos( const int &id, const SPos &pos , const F32 &radius ,const F32& vx, const F32 &w);
	void get_osb_all_range(std::vector<Sxy> &range_list);
	void set_triangle_pos(const int &id, const SPos &pos , F32 edge_line = 0.15, F32 intersection_angle = 100 );
	
	void set_rectangle(const int &id, const SPos &pos , F32 length = 1.2, F32 width = 1.2);

protected:
private:

	void get_obs_range_pos( std::vector<Sxy> &range_list, std::map<int, SObstacle>::iterator it );

	std::map<int,SObstacle> m_obs_;

	void create_line(SObstacle &obs,VecPosition v_begin ,VecPosition v_end);
};

#endif//_SIM_OBSTACLE_WANGHONGTAO_20190501_
