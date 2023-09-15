#ifndef _PROTOBUF_QRCODE_WANGHONGTAO_20230319_
#define _PROTOBUF_QRCODE_WANGHONGTAO_20230319_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "meta_data/meta_data.h"

class GridMap;

class protobuf_qrcode {


public:

	protobuf_qrcode();
	~protobuf_qrcode();


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	void set_uuid();
	void set_uuid(U32 i_id);
	U32 get_uuid();

	void set_pos( F32 pos_x, F32 pos_y);
	void set_pos(F32 pos_x, F32 pos_y, F32 pos_th);
	void set_angle( F32 angle);
	void get_pos(F32 &pos_x, F32 &pos_y, F32 &pos_th);

	void set_des(std::string str_des);
	std::string get_des();

	void set_time_stemp(U64 time_stemp);

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);
	

public:
	static int max_id_;

private:

	SQrCode qr_code_;

};







#endif//_PROTOBUF_QRCODE_WANGHONGTAO_20230319_
