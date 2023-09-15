#ifndef _STEERING_MULTI_KYOSHO_2022_
#define _STEERING_MULTI_KYOSHO_2022_

#include "MyDefine.h"
#include "TimerDiff.h"
#include "steering_single.h"

class steering_multi
{
public:

	steering_multi();
	~steering_multi();

	steeing_single* add(int i_id);
	steeing_single* get(int id);
	bool del(int id);

	bool cal_resolv(int i_id, F32 &angle, F32 &speed, F32 v , F32 w);
	bool cal_fusion(int i_id, F32 &dx, F32 &dy, F32 &da, F32 cur_angle , F32 cur_ds , F32 runtime_x, F32 runtime_y ,F32 runtime_a);

	bool set_max_min_angle(int id, F32 max_a ,F32 min_a);
	bool set_pos(int id, F32 base_link_x, F32 base_link_y, F32 base_link_th );
	bool set_angle_zero(int id, F32 angle_rad);

	//bool set_trans_matrix(int id, F32 trans_x, F32 trans_y, F32 trans_th);

protected:
private:
	
	std::map<int,steeing_single*> m_steering_;
	

};








#endif//_STEERING_MULTI_KYOSHO_2022_
