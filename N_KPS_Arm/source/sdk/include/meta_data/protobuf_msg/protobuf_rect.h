#ifndef _PROTOBUF_RECT_WANGHONGTAO_20151230_
#define _PROTOBUF_RECT_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "meta_data/meta_data.h"


#include "protobuf_msg/rect.pb.h"

class GridMap;

class protobuf_rect {


public:

	protobuf_rect();
	~protobuf_rect();


	void set_name(const std::string str_nm);
	std::string get_name();
	

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_rect_region proto_rect_;

	void set_pos(F32 pos_x, F32 pos_y);
	void set_pos(F32 pos_x, F32 pos_y, F32 pos_th);
	void set_rect( F32 width , F32 length , F32 height = .0 );
	void set_pallet_type(std::string str_pallet_uuid);
	void set_pallet_rect( F32 width , F32 length , F32 height = .0 );
	void set_spacing( F32 col_spacing, F32 row_spacing);
	
	void get_pos(F32 &pos_x, F32 &pos_y, F32 &pos_th);
	void get_rect( F32 &width , F32 &length );
	void get_pallet_rect( F32 &width , F32 &length );
	int get_pallet_lt(std::vector<Sxy> &v_anchor);
	int get_anchor(std::vector< std::vector<Sxy>> &v_xy);
	int get_anchor_world(std::vector< std::vector<Sxy>> &v_xy);

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

public:
	static int max_id_;

private:

	void cal_row_para();
	void cal_col_para();
	void cal_anchor();

	int i_rows_;
	int i_cols_;
	F32 col_left_;
	F32 row_top_;
	F32 col_width_;
	F32 row_width_;

	std::vector< std::vector<Sxy>> v_xy_;
};

#endif//_PROTOBUF_RANGE_WANGHONGTAO_20151230_
