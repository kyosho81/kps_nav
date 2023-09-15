#include <string.h>
#include <iostream>

#include "Geometry.h"
#include "Comm.h"
#include "msg_pump/msg_array_pump.hpp"

msg_array_pump::mDataMap msg_array_pump::all_data_map_;
int msg_array_pump::sub_msg_id = 0;
boost::mutex msg_array_pump::mu_all_data_map_;

msg_array_pump::msg_array_pump()
{

}

msg_array_pump::~msg_array_pump()
{

}

