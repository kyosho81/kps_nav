#ifndef _SCAN_MATCH_LASER_ODOM_KYOSHO_20210704_
#define _SCAN_MATCH_LASER_ODOM_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "robot/tf_2d_server.h"
#include "device/amcl_tf.h"
#include "scanmatcher/psm_node.h"

class scan_match_laser
{
public:
	scan_match_laser();
	~scan_match_laser();
	
	void init( F32 laser_dx,F32 laser_dy );
	void set_laser_para(SLaser_para laser_para);

	bool scan_match(SPos &diff, SPos cur_pos, SPos ref_pos, SLaser &cur_laser, SLaser &ref_laser);

protected:
private:

	SLaser_para laser_para_;

	PSMNode psm_node_;

	SPos odom2laser(const SPos& w_pos);
	SPos odom_diff2laser_diff( SPos pos_amcl , SPos pos_ref);
	SPos laser_diff2odom_diff(const SPos& laser_diff);
	bool diff_ok( const SPos &est_pos,const  SPos &match_pos );



	F32 f_match_err_dis_;
	F32 f_match_err_ang_;


private:
	void save_frame(SPos pos, SLaser &cur_laser, SLaser_para &laser_para ,int i_save_state = 0 );

};


#endif//_SCAN_MATCH_LASER_ODOM_KYOSHO_20210704_
