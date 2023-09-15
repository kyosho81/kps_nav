#ifndef LIDAR_STRUCT_TYPE_H
#define LIDAR_STRUCT_TYPE_H
#include <string>
namespace wj_lidar
{
    struct lidar_base_struct_type
    {
        std::string lidar_ip;
        int lidar_port;
        double angle_min;
        double angle_max;
        double range_min;
        double range_max;
        std::string frame_id;
        std::string topic_name;
    };



    struct lidar_base_struct_type_v1:lidar_base_struct_type
    {
        int line1;
        double line1_angle_min;
        double line1_angle_max;
        std::string line1_frame_id;
        std::string line1_topic_name;

        int line2;
        double line2_angle_min;
        double line2_angle_max;
        std::string line2_frame_id;
        std::string line2_topic_name;

        int line3;
        double line3_angle_min;
        double line3_angle_max;
        std::string line3_frame_id;
        std::string line3_topic_name;

        int line4;
        double line4_angle_min;
        double line4_angle_max;
        std::string line4_frame_id;
        std::string line4_topic_name;
    };
}
#endif