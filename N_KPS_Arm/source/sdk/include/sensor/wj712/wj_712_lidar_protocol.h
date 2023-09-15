#ifndef WJ_712_LIDAR_PROTOCOL_H
#define WJ_712_LIDAR_PROTOCOL_H
#include <iostream>
#include "string.h"
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

//#include <ros/ros.h>
//#include <visualization_msgs/Marker.h>
//#include <sensor_msgs/LaserScan.h>
//#include <nav_msgs/Odometry.h>
//#include <tf/transform_broadcaster.h>
//#include <dynamic_reconfigure/server.h>
//#include <wj_712_lidar/wj_712_lidarConfig.h>
using namespace std ;
namespace wj_lidar
{
  #define MAX_LENGTH_DATA_PROCESS 40000
  typedef struct TagDataCache
  {
    char m_acdata[MAX_LENGTH_DATA_PROCESS];
    unsigned int m_u32in;
    unsigned int m_u32out;
  }DataCache;
  class wj_712_lidar_protocol
  {
  public:
    wj_712_lidar_protocol();
    bool dataProcess(const char *data,const int reclen);
    bool protocl(const char *data,const int len);
    bool OnRecvProcess(char *data, int len);
    bool checkXor(char *recvbuf, int recvlen);
    void send_scan(const char *data,const int len);
//     ros::NodeHandle nh;
//     ros::Publisher scan_pub;
//     ros::Publisher odom_pub;
//     sensor_msgs::LaserScan scan;
//     nav_msgs::Odometry odom;
    bool setConfig(bool b_wj712_7200);
	void bind_pub( boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data);

  private:
    char        data_[MAX_LENGTH_DATA_PROCESS];
    DataCache   m_sdata;
//    wj_712_lidar::wj_712_lidarConfig config_;
    int m_n32PreFrameNo;
    float scandata[7200];
    float scanintensity[7200];
    double positionx;
    double positiony;
    double positionphi;
    bool positionvalid;
    int freq_scan;
    int resizeNum;

	boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data_;

  };
}
#endif // WJ_712_LIDAR_PROTOCOL_H
