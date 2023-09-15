#ifndef VANJEE_718H_LIDAR_PROTOCOL_H
#define VANJEE_718H_LIDAR_PROTOCOL_H

#include "vanjee_abstract_protocol.h"
#include <vanjee_mini_lidar/vanjee_718h_lidarConfig.h>

namespace vanjee_lidar
{
    class Vanjee718HLidarProtocol : public VanjeeAbstractProtocol
    {
    public:
        Vanjee718HLidarProtocol();
        ~Vanjee718HLidarProtocol();
        bool protocl(unsigned char *data, const int len);
        // void sendScan(const char *data,const int len);
        bool setConfig(vanjee_mini_lidar::vanjee_718h_lidarConfig &new_config, uint32_t level);
        bool heartstate_;

    private:
        vanjee_mini_lidar::vanjee_718h_lidarConfig config_;
        unsigned int pre_frame_no_;
        std::set<int> received_package_no_;
        float scan_data_[1440];
        float scan_intensity_[1440];
        int index_start_;
        int index_end_;
    };

}
#endif
