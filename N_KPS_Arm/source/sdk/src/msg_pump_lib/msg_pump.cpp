#include <string.h>
#include <iostream>

#include "Geometry.h"
#include "Comm.h"
#include "msg_pump/msg_pump.hpp"

msg_pump::mDataMap msg_pump::all_data_map_;
int msg_pump::sub_msg_id = 0;
boost::mutex msg_pump::mu_all_data_map_;

msg_pump::msg_pump()
{

}

msg_pump::~msg_pump()
{

}

