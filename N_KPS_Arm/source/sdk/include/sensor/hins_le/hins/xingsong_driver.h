/*********************************************************************
 *
 * Software License Agreement ()
 *
 *  Copyright (c) 2020, HINS, Inc.
 *  All rights reserved.
 *
 * Author: Hu Liankui
 * Create Date: 8/9/2020
 *********************************************************************/

/**
 * @brief 兴颂激光雷达驱动
 */

#pragma once
//#include "ros/ros.h"
#include "hins_le/hins/laser_data_receiver.h"
#include <set>
#include "hins_le/laserdll.h"
// #include "laserlib.h"
namespace hins
{

  class XingSongDriver;
  typedef std::shared_ptr<XingSongDriver> XingSongDriverHdr;

  class XingSongDriver
  {
  public:
    XingSongDriver(const ConnectionAddress &conn_info, XingSongLaserParam param);
    XingSongDriver(const ConnectionAddress &conn_info, XingSongLaserParam param, ShadowsFilterParam shadows_filter_param, DisturbFilterParam disturb_filter_param);
    ~XingSongDriver();

    bool StartCapturingTCP();
    class LASERDLLSHARED_EXPORT laser_share_export;
    ScanData GetFullScan();
    
    bool Connect()
    {
      return data_receiver_ptr_->Connect();
    }

    bool IsConnected()
    {
      return data_receiver_ptr_->IsConnected();
    }

    void Disconnect()
    {
      data_receiver_ptr_->Disconnect();
    }

    std::array<unsigned char, 12> GenerateParamCommand(XingSongLaserParam param)
    {
      return data_receiver_ptr_->GenerateParamCommand(param);
    }

    int SyncWrite(const std::array<unsigned char, 12> command)
    {
      return data_receiver_ptr_->SyncWrite(command);
    }

    short int GetLaserSteadyTime()
    {
      return data_receiver_ptr_->GetLaserSteadyTime();
    }

    int SendAreaCommand()
    {
      // std::cout << "SendAreaCommand." << std::endl;
      return data_receiver_ptr_->SyncWrite(get_area_data_command_);
    }

    void SetAreaCommand(HSGetAreaDataPackage command);
    int GetBlockValue()
    {
      return data_receiver_ptr_->GetBlockValue();
    }
    int GetResponseChannel()
    {
      return now_channel_;
    }

    void RefreshChannel()
    {
      now_channel_ = data_receiver_ptr_->GetResponsChannel();
    }

    bool GetBlock1Value()
    {
        return block1_;
    }

    bool GetBlock2Value()
    {
        return block2_;
    }

    bool GetBlock3Value()
    {
        return block3_;
    }
  void DisturbFilter(ScanData& scan_data, DisturbFilterParam disturb_param);

  private:
	bool b_run_;
    void RunMain();
    void ShadowsFilterInit(int scan_num);
    void ShadowsFilter(ScanData& data, int scan_num);
    short int CRCVerify(std::array<unsigned char,18> *command, int len);

  private:
    DisturbFilterParam disturb_filter_param_;
    ShadowsFilterParam shadows_filter_param_;
    ConnectionAddress conn_info_;
    XingSongLaserParam laser_param;
    LaserDataReceiverPtr data_receiver_ptr_;
    //std::thread guard_thread_;
    std::vector<float> shadows_filter_threshold_min_;
    std::vector<float> shadows_filter_threshold_max_;
    set<int> shadows_del_index_;
    set<int> disturb_del_index_;
    std::array<uint8_t, 18> get_area_data_command_;
    bool area_data_flag_;
    uint16_t have_block_;
    uint8_t now_channel_;
    bool block1_;
    bool block2_;
    bool block3_;
    bool block_enable_;                        //
  };


}
