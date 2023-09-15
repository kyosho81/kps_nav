
#ifndef _KH_INTERFACE_DEF_2019_10_22_H_
#define _KH_INTERFACE_DEF_2019_10_22_H_

#define INIT_POS_LEN 18

#define GET_MAP_LEN  6
#define GET_STATUS_LEN  6
#define GET_POS_LEN  6

#define CMD_INIT_POS 1
#define CMD_INIT_MAP 2
#define CMD_GET_MAP  3
#define CMD_GET_STATUS 4
#define CMD_GET_POS 5

#define CMD_HEAD_CRC 6

#define CMD_ERR_NONE 0
#define CMD_ERR_CRC 1
#define CMD_ERR_XMLRPC 2
#define CMD_ERR_INIT_POS 3
#define CMD_ERR_INIT_MAP 4

typedef union{
	U8 ch_data_[2];
	U16 udata_;
}un_U16; 

typedef union{
	U8 ch_data_[4];
	F32 fdata_;
}un_F32;

#endif//_KH_INTERFACE_DEF_2019_10_22_H_