#ifndef _LINDE_CRC16_KYOSHO_2023_07_26_H_
#define _LINDE_CRC16_KYOSHO_2023_07_26_H_

#include "MyDefine.h"

class linde_crc16{
public:
  linde_crc16(){};
  ~linde_crc16(){};

  static bool cal_crc16( U16 &crc_value, U8* src, U32 len );
  static bool chk_crc16( U8* src, U32 len);
};

#endif//_LINDE_CRC16_KYOSHO_2023_07_26_H_
