#ifndef _DEVICE_REFLECTOR_LOCATION_WANGHONGTAO_20191205_
#define _DEVICE_REFLECTOR_LOCATION_WANGHONGTAO_20191205_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"
#include "pf/merge_tf.h"

#include "device/device_laser.h"


class device_reflector_loc : device_base
{
public:

	device_reflector_loc();
	~device_reflector_loc();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

	bool fnc_init();

private:
	
	bool onInit();
	
	bool toErr(U16 err_code);

	


private:
	void init_call_back();
	bool update_odom( const SOdomSpeed& new_odom );
	bool s_call_back_reflector(const SReflector &ref);
	bool s_init_pos( const SInit_Pos &pos );
	bool s_set_map_cmd(const SCmd &map_cmd);
	bool s_update_confidence(const SAMCL_CONFIDENCE &amcl_confidence);
	bool s_call_back_amcl( const SPos &amcl_pos );
	bool update_ref_forbidden( const SRefForbidden &rf );

	int sub_id_odom_;
	int sub_id_reflector_;
	int sub_id_estimate_;
	int sub_id_set_map_cmd_;
	int sub_id_amcl_confidence_;
	int sub_id_amcl_;

	THSafe<SOdomSpeed> th_odom_;
	CSBuffer<SReflector,1> cur_ref_list_;
	SReflector data_;
	SPos global_ref_pos_;

	//hyper location ,merge odom and amcl
	merge_tf location_tf_;
	bool b_merge_odom_;
	void publish_pos(SPos pos);
	bool filter_pos_jump(SPos &pos);
	THSafe<SPos> th_amcl_pos_;
	THSafe<SAMCL_CONFIDENCE> th_amcl_conf_;
	F32 max_jump_dis_;
	bool b_check_ref_amcl_pos_;
	F32 ref_confidence_;
	F32 ref_conf_max_error_;

	void set_map_cmd(const std::string &str_map_cmd);
	bool get_map_cmd(std::string &str_cmd );

	
	boost::mutex m_reset_map_;
	std::string str_map_cmd_;

	//when payload on agv, forbidden reflector to make observed value save as unload
private:
	//<forbidden_ref_start_angle,forbidden_ref_end_angle> ccw dir
	THSafe<SRefForbidden> th_ref_forbidden_;
	bool get_used_rf(SRefForbidden &rf);
	bool filter_forbidden(SReflector &data);
	bool filter_trailing(SReflector &data);
private:
	bool b_pub_ref_laser_pos_;
	bool b_filter_trailing_;
};

#endif//_DEVICE_REFLECTOR_LOCATION_WANGHONGTAO_20191205_
