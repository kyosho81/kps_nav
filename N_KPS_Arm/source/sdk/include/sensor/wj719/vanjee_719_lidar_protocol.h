#ifndef VANJEE_719_LIDAR_PROTOCOL_H
#define VANJEE_719_LIDAR_PROTOCOL_H
// #include <ros/ros.h>
// #include <sensor_msgs/LaserScan.h>
#include "vanjee_abstract_protocol.h"

using namespace std;

namespace wj_lidar
{
    #define LIDAR_719_MAX_BANK_BYTE_LENGTH_30HZ 1200
    #define LIDAR_719_MAX_ALL_BYTE_LENGTH_30HZ LIDAR_719_MAX_BANK_BYTE_LENGTH_30HZ * 12

    #define LIDAR_719_MAX_BANK_BYTE_LENGTH_20HZ 1200
    #define LIDAR_719_MAX_ALL_BYTE_LENGTH_20HZ LIDAR_719_MAX_BANK_BYTE_LENGTH_20HZ * 12

    #define LIDAR_719_MAX_BANK_BYTE_LENGTH_10HZ 1200
    #define LIDAR_719_MAX_ALL_BYTE_LENGTH_10HZ LIDAR_719_MAX_BANK_BYTE_LENGTH_10HZ * 36

	#define u_int8_t unsigned char
	#define u_int32_t unsigned int

    class vanjee_719_lidar_protocol : public VanjeeAbstractProtocol
    {
        public:
            vanjee_719_lidar_protocol();
            ~vanjee_719_lidar_protocol();
            bool protocl(unsigned char *data, const int len);
            void protocl_10HZ(unsigned char *data);
            void protocl_20_30HZ(unsigned char *data);
			
			void bind_pub(boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data);

        private:

            int pointcloud_datatype;
            int oldversion;
            int scan_protocols;
            int circle_HZ; //
            float intensity_div;

            int index_start;
            int index_end;
            int resizeNum;
            
            
            float* scan_data;
            float* scan_intensity_data;
    
            //u_int8_t Circle_Frequence_HZ;   // 10hz 20/30HZ
            u_int8_t receive_BankNO;  

            u_int32_t CircleCount;
            //ros::Time timeStamp;

            uint32_t g_n32TimeStampSec; 
            uint32_t g_n32TimeStampSubSec;
            unsigned char* fScandata719;

//             ros::Publisher marker_pub;
//             sensor_msgs::LaserScan scan;
// 
//             ros::Time test_timeStamp;
			boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data_;
    };

}
#endif
