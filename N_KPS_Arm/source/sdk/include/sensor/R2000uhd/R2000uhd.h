/*
 * R2000uhd.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: dl
 */

#ifndef R2000UHD_H_
#define R2000UHD_H_

#include <string>

#include <boost/thread.hpp>


#include "MyDefine.h"
#include "R2000uhd/DataConvert.h"
#include "R2000uhd/SendCommand.h"
#include "buffer_con.hpp"

#include "trans_dev/trans_dev.h"

typedef struct _scanData1 {

	F32 h_distance[8400];
	S32 h_echo[8400];
    F32 h_angle[8400];

} scanData1;


typedef struct _headData{
    U8 magic[2];
    U16 packet_type;
    U32 packet_size;
    U16 header_size;
    U16 scan_number;
    U16 packet_number;
    U64 timestamp_raw;
    U64 timestamp_sync;
    U32 status_flags;
    U32 scan_frequency;
    U16 num_points_scan;
    U16 num_points_packet;
    U16 first_index;
    S32 first_angle;
    S32 angular_increment;
    double angular_increment_real;
    U32 output_status;
    U32 field_status;
}headData;



class R2000uhd {
public:
	R2000uhd();
	virtual ~R2000uhd();

	void disconnect();


	bool isConnected();

	void Laser_Init(const std::string ip);

	void startMeas();
	void stopMeas();

	bool getData(scanData1& data);

	void getLdata(float* ldata,scanData1& data,const int laser_lanmark_R2000_);
	void getBLdata(float* ldata,scanData1& data,const int laser_lanmark_R2000_);
	void getRAll_data(float* ldata,scanData1& data);
	void getRAll_echo(S32* ldata,scanData1& data);
	void getRAll_angle(float* ldata,scanData1& data);

	bool isReadStatus();
	void Set_Laser_Para(const F32 start_angle_,const int laser_lanmark_R2000_,const int laser_R2000_echo_);
	void getEchodata(S32* ldata,scanData1& data,const int laser_lanmark_R2000_);
	void getBEchodata(S32* ldata,scanData1& data,const int laser_lanmark_R2000_);

	void stop_Thread();
	void start_thread();

	void Feed_Watchdog();
	bool isBreakConnect();
//	void Head_Package_Size(void);
	void fetch_data(scanData1&);

private:
	void connect(std::string host, int port = 2111);
	
	void Laser_Init_Para(void);
	void th_run(void);
	void ReConnect_laser();

//	bool Scan_Num_Check(U16 current_num);
	bool Scan_Index_Check(U16 current_index);
	bool Package_Charge(headData &head_,U8 *buffer,scanData1& data);
	void Set_Connect(bool state_);

private:
	THSafe<bool> connected;

	cConnPara conn_para_;
	cTransferDevice* pTrans_;
	int read_data( U8* data, int &ilen , int ineed );
//////
	//bool connected;
	bool debug_print_;
	

	headData m_headData;
	DataConvert m_DataConvert;
	SendCommand m_sendmand;

	S16 m_ReadCount;
	THSafe<bool> IsReadDate;
	bool IsScanRead;
	//bool IsReadDate;
	std::string  laser_ip_;
	int  laser_landmark_exist;
	int  laser_echo_exist;
	S16 receive_cout;

	std::string laser_para_;
	std::string lstart_angle_;
	std::string pack_type_;
private:

	THSafe<bool> thread_run_;
	CSBuffer<int,1> i_over_;

	int conect_ret;
	U16 feed_cout;

	U16 last_scan_index;
	U16 scan_first_index_count;
	bool last_index_check;

	U16 laser_back_cout;

	U32 head_size_cout;
	THSafe<bool> head_break_exit;
	bool laser_head_check;

	THSafe<bool> handle_ready_;
	scanData1 scan_data_;

	U8* p_buffer_;
};

#endif    /* R2000UHD_H_ */

