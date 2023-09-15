#ifndef _VIEW_PARA_KYOSHO_20150906_
#define _VIEW_PARA_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>

#include "MyDefine.h"
#include "RobotStruct.h"

class view_para
{
public:
	view_para(){};
	~view_para(){};

	static F32 get_node_radius();
	static F32 get_node_pen();
	static F32 get_edge_pen();
	static F32 get_edge_dir_dis();
	static F32 get_station_width();
	static F32 get_station_pen();
	static F32 get_qrcode_width();
	static F32 get_qrcode_pen();

	static F32 scale_para_;

	static F32 node_radius_;
	static F32 node_pen_width_;

	static F32 edge_pen_width_;
	static F32 edge_dir_dis_;
	
	static F32 station_width_;
	static F32 station_pan_;

	static F32 qrcode_width_;
	static F32 qrcode_pan_;

protected:
private:
};


#endif//_VIEW_PARA_KYOSHO_20150906_
