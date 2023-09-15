#ifndef _SPECIAL_LOCALIZATION_BASE_KYOSHO_20210704_
#define _SPECIAL_LOCALIZATION_BASE_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "pf/merge_tf.h"



class special_loc_base
{
public:
	special_loc_base();
	~special_loc_base();

	bool init();
	void bind_landmark_world();

	void bind_pub_pos(boost::function< void( SWorldLM wlm , SPOS_CONFIDENCE con_pos )> fnc);
	
	boost::function< bool(const SLaser& laser)> fnc_show_laser_;

	typedef enum{
		RUNTIME = 0,
		PLAYBACK = 1,
		DEVICE = 2
	}SL_SUB_TYPE;

protected:
	virtual bool init_special(){return false;};

	virtual bool init_sensor_diff() = 0;
	virtual bool init_sub_msg();
	virtual bool sm_robot_in_loc_ori( SPos &pos ) = 0;
	virtual void set_loc_odom(SOdomSpeedEx odom_ex){};

	void set_sm_loc(SPos pos );
	

	SL_SUB_TYPE sub_type_;

	THSafe<bool> th_set_bind_;
	SWorldLM wlm_bind_;
	SBuffer<SPos> v_amcl_pos_;
	merge_tf location_tf_;

protected:
	std::map<std::string,std::string> m_para_;
	virtual bool parse_para(std::string str_name, std::string str_para);

private:

	bool update_odom(const SOdomSpeed &odomspeed);
	bool update_amcl_pos(const SPos &amcl_pos);
	bool update_runtime_para(const SPara &rt_para);
	
	THSafe<SOdomSpeedEx> th_odom_ex_;
	//SBuffer<SOdomSpeedEx> v_sub_odom_;
	//THSafe<SPos> th_robot_in_landmark_;

	boost::function< void( SWorldLM wlm , SPOS_CONFIDENCE con_pos )> fnc_wlm_;

	int sub_id_odom_;
	int sub_id_amcl_;

};


#endif//_SPECIAL_LOCALIZATION_BASE_KYOSHO_20210704_
