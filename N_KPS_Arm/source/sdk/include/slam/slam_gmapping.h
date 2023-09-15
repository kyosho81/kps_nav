#ifndef _SLAM_GMAPPING_KYOSHO_20191120_
#define _SLAM_GMAPPING_KYOSHO_20191120_
/*
 * slam_gmapping
 * Copyright (c) 2008, Willow Garage, Inc.
 *
 * THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE
 * COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE"). THE WORK IS PROTECTED BY
 * COPYRIGHT AND/OR OTHER APPLICABLE LAW. ANY USE OF THE WORK OTHER THAN AS
 * AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 * 
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO
 * BE BOUND BY THE TERMS OF THIS LICENSE. THE LICENSOR GRANTS YOU THE RIGHTS
 * CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND
 * CONDITIONS.
 *
 */

/* Author: Brian Gerkey */

//#include "ros/ros.h"
//#include "sensor_msgs/LaserScan.h"
//#include "std_msgs/Float64.h"
//#include "nav_msgs/GetMap.h"
//#include "tf/transform_listener.h"
//#include "tf/transform_broadcaster.h"
//#include "message_filters/subscriber.h"
//#include "tf/message_filter.h"

#include "gmapping/gridfastslam/gridslamprocessor.h"
#include "gmapping/sensor/sensor_base/sensor.h"

#include <boost/thread.hpp>

//#include "RobotStruct.h"
#include "slam_tf.h"
#include "robot/process_bar.h"
#include "bag/bag.h"
#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"

class GridMap;

class SlamGMapping
{
  public:
    SlamGMapping();
    SlamGMapping(unsigned long int seed, unsigned long int max_duration_buffer);
    ~SlamGMapping();

    void init();
    void startLiveSlam();
	void bind_pub_bar(boost::function<void(SProcess_Bar &pro_bar)> fnc);
  
    bool laserCallback(const SLaser &scan ,const SPos &odom,const float &dx,const float &dy);



	int save_map(std::string path);
	int save_calib_map(std::list<std::pair<U32,SPos>> &v_stamp_cal_odom ,std::string path);
	int get_calib_scan(std::list<std::pair<U32,SPos>> &v_stamp_cal_odom);
	void save_to_gridmap( GridMap* g_map );
	bool save_Scanmap_byCalibOdom(std::string path,std::vector<SPUB_BAG_EX*> &v_calib_odom_log); 
	bool save_Pgmmap_byCalibOdom(std::string path,std::vector<SPUB_BAG_EX*> &v_calib_odom_log); 

	//for save pgm map
	bool init_para( const SLaser &scan );

  private:
    //ros::NodeHandle node_;
    //ros::Publisher entropy_publisher_;
    //ros::Publisher sst_;
    //ros::Publisher sstm_;
    //ros::ServiceServer ss_;
    //tf::TransformListener tf_;
    //message_filters::Subscriber<sensor_msgs::LaserScan>* scan_filter_sub_;
    //tf::MessageFilter<sensor_msgs::LaserScan>* scan_filter_;
    //tf::TransformBroadcaster* tfB_;

    GMapping::GridSlamProcessor* gsp_;
    GMapping::RangeSensor* gsp_laser_;
    // The angles in the laser, going from -x to x (adjustment is made to get the laser between
    // symmetrical bounds as that's what gmapping expects)
    std::vector<double> laser_angles_;
    // The pose, in the original laser frame, of the corresponding centered laser with z facing up
    //tf::Stamped<tf::Pose> centered_laser_pose_;
    // Depending on the order of the elements in the scan and the orientation of the scan frame,
    // We might need to change the order of the scan
    bool do_reverse_range_;
    unsigned int gsp_laser_beam_count_;
    GMapping::OdometrySensor* gsp_odom_;

    bool got_first_scan_;

    bool got_map_;
    //nav_msgs::GetMap::Response map_;

    //ros::Duration map_update_interval_;
    //tf::Transform map_to_odom_;
    boost::mutex map_to_odom_mutex_;
    boost::mutex map_mutex_;

    int laser_count_;
    int throttle_scans_;

    //boost::thread* transform_thread_;

    std::string base_frame_;
    std::string laser_frame_;
    std::string map_frame_;
    std::string odom_frame_;

    //void updateMap(const sensor_msgs::LaserScan& scan);
    //void updateMap(const SLaser &scan);
	void save(std::string path,const GMapping::ScanMatcherMap &smap);
	int updateMap(std::string path,const bool &b_ret_calb_odom = false);
	int save_scan_map(std::string path,const bool &b_ret_calb_odom = false);
	int get_calb_stamp_odom(std::list<std::pair<U32,SPos>> &v_stamp_cal_odom);

	//bool getOdomPose(GMapping::OrientedPoint& gmap_pose, const ros::Time& t);
    bool getOdomPose(GMapping::OrientedPoint& gmap_pose , const U32 stamp);
	
	//bool initMapper(const sensor_msgs::LaserScan& scan);
    bool initMapper(const SLaser &scan);
    //bool addScan(const sensor_msgs::LaserScan& scan, GMapping::OrientedPoint& gmap_pose);
    bool addScan(const SLaser &scan , GMapping::OrientedPoint& gmap_pose);
    double computePoseEntropy();
	
	std::string init_scan_log(const std::string &path);
	std::string init_scan_ex_log(const std::string &path);
	void rscan2laserscan( SPROTOBUF_BAG &pbag ,const GMapping::OrientedPoint& p,const GMapping::OrientedPoint& o, const double* readings);
	void rscan2laserscan( SBAG &bag ,const GMapping::OrientedPoint& p,const GMapping::OrientedPoint& o, const double* readings);
	
	// Parameters used by GMapping
    double maxRange_;
    double maxUrange_;
    double maxrange_;
    double minimum_score_;
    double sigma_;
    int kernelSize_;
    double lstep_;
    double astep_;
    int iterations_;
    double lsigma_;
    double ogain_;
    int lskip_;
    double srr_;
    double srt_;
    double str_;
    double stt_;
    double linearUpdate_;
    double angularUpdate_;
    double temporalUpdate_;
    double resampleThreshold_;
    int particles_;
    double xmin_;
    double ymin_;
    double xmax_;
    double ymax_;
    double delta_;
    double occ_thresh_;
    double llsamplerange_;
    double llsamplestep_;
    double lasamplerange_;
    double lasamplestep_;
    
    //ros::NodeHandle private_nh_;
    
    unsigned long int seed_;
    
    double transform_publish_period_;
    double tf_delay_;

	//  use for arm
	void save_png(std::string path,const GMapping::ScanMatcherMap &smap);
	
	//save optimize scan for loopclosure
	bool b_save_bag_;
	//cbag optimize_bag_;
	protobuf_bag pbag_;
	protobuf_bag_ex pbag_ex_;
	//SLaser_para laser_para_;

private:

	slam_tf mtf_;
	SPos odom_;

	F32 entropy_;
	U32 last_map_update_;
	U32 map_update_interval_;
	//GridMap* mp_;

	unsigned char* img_buf_;
	
	//process_bar
private:
	process_bar pro_bar_;
	boost::function<void(SProcess_Bar &pro_bar)> fnc_pub_pro_;
	void pub_process(const std::string &str_nm,const int &icurrent,const int &imax);
	
private://cal gmapping entropy
	bool cal_odom_amcl_entropy(GMapping::OrientedPoint& p,const GMapping::OrientedPoint& o);
	
	GMapping::OrientedPoint lp_;
	GMapping::OrientedPoint lo_;
	bool b_first_scan_;

	std::list<std::pair<U32,SPos>> v_stamp_cal_odom_;
};
#endif//_SLAM_GMAPPING_KYOSHO_20191120_