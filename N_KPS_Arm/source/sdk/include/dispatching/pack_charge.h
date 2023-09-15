#ifndef _PACK_CHARGE_WANGHONGTAO_20220303_
#define _PACK_CHARGE_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "dispatching/schedule_interface.h"
#include "dispatching/action_base.h"
#include "Comm/data_time.h"


class base_station
{
public:
	base_station();
	~base_station();

	void bind_node(int i_node_id);
	void set_pos(F32 fx,F32 fy);
	void set_direction(F32 fth);

	bool occupyed();
	void set_occupt(int i_agv_id);

protected:
	
	SPos pos_;
	int bind_node_;

	int occupy_agv_id_;

private:
};

class pack_station : public base_station
{
public:
	pack_station();
	~pack_station();

protected:
private:
};


class pack_charge
{
public:
	pack_charge();
	~pack_charge();

	//load pach and charge pos
	bool init();

protected:
private:
	
};


#endif//_PACK_CHARGE_WANGHONGTAO_20220303_
