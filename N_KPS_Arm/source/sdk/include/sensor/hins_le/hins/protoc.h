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

#pragma once

#include <array>
#include <vector>
#include "pavo/sys_types.h"

namespace hins {

#define kMaxDistance 61000
#define kMaxIntensity 30000
#define IntensityThreshold 5000

struct ScanData
{
  //
  std::vector<uint32_t> distance_data;
  
  //
  std::vector<uint32_t> amplitude_data;

  //

  unsigned int time_increment;
  
};

struct ShadowsFilterParam
{
  float min_angle;
  float max_angle;
  int neighbors;            //
  int window;               //
  int shadows_filter_level; 
  int traverse_step;          //
};

struct XingSongLaserParam
{
  std::string run_state;
  bool change_flag;                           //
  std::string measure_frequency_kHz;
  std::string spin_frequency_Hz;
  std::string sampling_size_per_position;
  std::string noise_filter_level;
  bool block_enable;                        //
};

#pragma pack(1)

struct XSPackageHeader
{
  char head[4];
  unsigned short start_angle;      //
  unsigned short end_angle;        //
  unsigned short data_size;        //
  unsigned short data_position;    // 
  unsigned short measure_size;     //
  unsigned short time;             //
};

struct HSGetAreaDataPackage 
{
  unsigned char mode;                 //
  unsigned char channel;            // 
  short int angle;
  short int speed;
  short int channel_group;
};

struct HSAreaDataPackage 
{
  char head[5];
  unsigned char channel;                     //
  unsigned char input_status;           // 
  unsigned char output;                 //
  unsigned char led_status;          // 
  unsigned short error_status;      //
  char other[10];
  unsigned short check;                // 
};

struct DisturbFilterParam
{
  uint32_t threshold;
  int range;
  bool disturb_filter_enable;
};




#pragma pack()


}