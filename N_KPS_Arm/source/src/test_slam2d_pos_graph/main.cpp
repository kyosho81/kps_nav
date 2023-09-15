#include "Comm.h"
#include "Geometry.h"
#include "TimerDiff.h"

#include "RobotStruct.h"

//#include "linux_driver/mmem.h"

#include "interprocess_core/reg_msg.h"
#include "interprocess/shared_pool.hpp"

#include "g2o_slam/slam2d_pos_graph.h"

using namespace g2o;
using namespace g2o::slam2d;

int main(int argc, char *argv[])
{
  
    std::string str_file_name = "./log.bag";
    if (argc > 1)
    {
	str_file_name = "./";
	str_file_name += argv[1];
    }
    std::cout<<"load bag:"<<str_file_name<<std::endl;
    
    g2o_slam2d g_slam2d;
    g_slam2d.init(0.25,0,0.001,0.001);
    g_slam2d.optimize(str_file_name);
    
    return 0;
}
