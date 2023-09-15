#ifndef _PROTOBUF_BASE_WANGHONGTAO_20211230_
#define _PROTOBUF_BASE_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/id_factory.h"
#include "scene/item_define.h"
#include "protobuf_msg/base.pb.h"

class GridMap;

class protobuf_base{


public:

	protobuf_base();
	virtual ~protobuf_base();

	std::string get_uuid();
	
	
	virtual void init() = 0;
	virtual void update_cmd(std::string str_cmd);

	void set_id();
	void set_id(const int &id);
	int get_id();
	
	void set_pos(const F32 &x,const F32 &y);
	void set_pos(const F32 &x,const F32 &y,const F32 &th);
	void get_pos(F32 &x, F32 &y, F32 &th) ;
	void get_pos(SPos &pos) ;
	bool get_bind_pos(SPos &pos);

	void set_color(const std::string &str_color);
	std::string get_color();

	void add_group(const std::string &str_group_name);
	int get_group(std::vector<std::string> &v_gp);
	void set_group(const std::vector<std::string> &v_gp);

	void set_creatation_time();
	void set_creatation_time(const std::string &str_creatation_name);
	std::string get_creatation_time();

	void set_destruct_time();

	void set_describe( const std::string &str_des);
	std::string get_describe();

	boost::mutex mu_data_;

	std::string get_type();
	int get_bind_node_id();
	bool set_orientation(F32 deg_angle);
	bool orientation(F32 &deg_angle);
	int get_bind_action(std::list<KPS::mp_bind_action> &l_bind_action);


	std::string get_pallet_uuid();
	void clear_pallet();

	virtual bool set_assign( int i_agv_id ){//unexpected
		return false;
	};
	int get_assigned_agv();
	virtual std::string get_status(){return "";};

	int release_role(int i_agv_id);
	
	virtual int set_occupy(int i_agv_id);
	virtual bool set_free(int i_agv_id);

	void set_priority( int i_priority );
	int get_priority();
	bool occupyed();
	virtual bool enabled();

	std::string get_cargo_type();
	std::string get_pallet_type();

	int no_corss_node( std::vector<int> &v_res );

	std::string get_para();
	std::string get_type_id();

private:

	virtual bool proto2byte(char* &data,int &len) = 0;
	virtual bool byte2proto(char* const data,const int len) = 0;


public:

	virtual std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data ) = 0;

	
protected:
	void init_base(bool b_bind_node = true);
	bool init_action();//some one do not every one
	bool init_bind_io();//some one do not every one

	std::string str_uuid_;
	void init_uuid();

	std::string str_type_;

	KPS::mp_item_base* p_base_data_;

	std::string get_base_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	std::string get_bind_node_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	std::string get_action_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	std::string get_io_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data);

	int update_base_data(std::string str_group, std::string str_name , std::string str_data);
	int update_bind_node_data(std::string str_group, std::string str_name , std::string str_data);
	int update_action_data(std::string str_group, std::string str_name , std::string str_data);
	int update_bind_io(std::string str_group, std::string str_name ,std::string str_data);
	
	bool b_enable_;
	bool b_occupy_;
	int i_assign_agv_id_;
	std::string str_error_msg_;


public:

	void set_row_col(int i_row, int i_col);
	void set_rows_cols(int i_rows, int i_cols);
	void bind_node(int id , F32 angle);
	void bind_ori(F32 angle);

	int area();
	int row();
	int col();
	bool matrix();
};

#endif//_PROTOBUF_BASE_WANGHONGTAO_20211230_
