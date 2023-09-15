#include "Comm/TimerDiff.h"
#include "sensor/pavo/pavo_driver.h"

#include <fstream>


#define COMP_NODES (36000)
#define CIRCLE_ANGLE (27000.0)
#define START_ANGLE (4500)

#define DEG2RAD(x) ((x)*M_PI/180.)

using namespace pavo;
pavo::pavo_driver *drv = NULL;

int main(){
  std::vector<pavo_response_scan_t> scan_vec;
//   if(!switch_active_mode)
//   {     
//           drv = new pavo::pavo_driver();
//   }
//   else
//   {     
//           drv = new pavo::pavo_driver(host_ip,host_port);
//   }
  std::string lidar_ip = "192.168.0.100";
  int lidar_port = 2368;
  int host_port = 2368;
  drv = new pavo::pavo_driver();
  drv->pavo_open(lidar_ip, lidar_port);
  
  double scan_duration;
  drv->enable_motor(true);
  /*uint sn,pn;
  drv->get_device_sn(sn);
  drv->get_device_pn(pn);
  std::cout<<std::hex<<sn<<" "<< pn<<std::endl;*/
  
//   if(!enable_motor)
//   {
//           pid_t kill_num;
//           kill_num  =getppid();
//           kill(kill_num,4);
//           return 0;
//   }
  int motor_speed = 15;
  int merge_coef = 4;
  int method = 0;
  std::cout<<"motor_speed: %d"<<(int)motor_speed<<std::endl;
  std::cout<<"merge_coef: %d"<<(int)merge_coef<<std::endl;

  if(method == 0 || method == 1 || method == 2 || method == 3)
  {
	drv->enable_tail_filter(method);
        if(method>0)
	std::cout<<"success to eliminate the tail by using method: %d"<<(int)method<<std::endl;
  }
  else{
	std::cout<<"false to set tail filter!"<<std::endl;
        return 0;	
  }

  if(drv->set_motor_speed(motor_speed)){  //设置为15Hz  
  //if(drv.set_motor_speed(15)){  //设置为15Hz  
	  std::cout<<"success to set speed!"<<std::endl;  
  }else{
	  std::cout<<"false to set speed!"<<std::endl;    
          return -1;
  }

  if(drv->set_merge_coef(merge_coef)){  //设置1点合并,分辨率是0.12°  2 0.24° 4 0.48°
  //if(drv.set_merge_coef(4)){  //设置1点合并,分辨率是0.12° 
	  std::cout<<"success to set merge!"<<std::endl; 
  }else{
	  std::cout<<"false to set merge!"<<std::endl;     
          return -1;
  } 

  F32 sleep_rate =  1000.0/15;

  cTimerDiff dt;
  SLaser laser_data;
  memset(&laser_data,0,sizeof(SLaser));
  laser_data.range_max_ = 20.0;
  laser_data.range_min_ = 0.10;
  laser_data.resolution_ = 0.48;
  laser_data.start_angle_ = -135.0;
 
  //ros::Rate rate(15); 
  int count = 0;
  while(1){
      try
      { 
        dt.Begin();
        drv->get_scanned_data(scan_vec);
		F32 td = dt.End() / 1e-6;
        count = scan_vec.size();
		
		laser_data.stamp_++;

		int index = 0;
		std::vector<pavo_response_scan_t>::iterator it = scan_vec.begin();
		for ( ; it != scan_vec.end() ; ++it ){
			pavo_response_scan_t &ldata(*it);

			laser_data.data_[index] = 0.002*ldata.distance;
			laser_data.seg_[index] = ldata.intensity;
			if((laser_data.data_[index] < laser_data.range_max_) && (laser_data.data_[index] > laser_data.range_min_)){
				laser_data.used_++;
			}
			
			if (index >= LASER_COUNT)
			{
				break;
			}
		}
		
//         end_scan_time = ros::Time::now();
//         scan_duration = (end_scan_time - start_scan_time).toSec();
        //publish_msg(&scan_pub, scan_vec,start_scan_time, scan_duration,frame_id,inverted,angle_min,angle_max,min_range,max_range,method,switch_active_mode);
        dt.ms_loop(sleep_rate);
      }
      catch(std::exception ex)
      {
          std::cerr << "exception: " << ex.what() << std::endl;
      }
  }
  delete drv;
}