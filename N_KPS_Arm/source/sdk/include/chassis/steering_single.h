#ifndef _STEERING_SINGLE_KYOSHO_2022_
#define _STEERING_SINGLE_KYOSHO_2022_

#include "MyDefine.h"
#include "TimerDiff.h"
#include "robot/Geometry.h"

class steeing_single
{
public:

	steeing_single();
	~steeing_single();

	bool cal_resolv( F32 &angle, F32 &speed, F32 v , F32 w);
	bool cal_fusion( F32 &dx, F32 &dy, F32 &da, F32 &cur_angle , F32 cur_ds , F32 runtime_x, F32 runtime_y ,F32 runtime_a);
	void set_max_min_angle(F32 max_a ,F32 min_a);
	void set_pos( SPos base_link );
	void set_pos(F32 base_link_x, F32 base_link_y, F32 base_link_th );
	void set_angle_zero(F32 angle_deg);

	bool fix_range(F32 &angle, F32 &speed);
	void get_para(F32 &max_a ,F32 &min_a, F32 &angle_zero);
	//void set_trans_matrix(F32 trans_x, F32 trans_y, F32 trans_th);

protected:
private:

	SPos pos_;  //steering wheel in odom base

	F32 angle_zero_;
	F32 angle_max_;
	F32 angle_min_;
	
	VecPosition v_O_;
	bool b_straight_;
	bool b_inplace_;
};








#endif//_STEERING_SINGLE_KYOSHO_2022_
