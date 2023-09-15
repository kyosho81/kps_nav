#ifndef _MERGE_TF_WANGHONGTAO_2019_1_30_
#define _MERGE_TF_WANGHONGTAO_2019_1_30_

#include "Comm.h"
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"

class merge_tf
{
public:
	merge_tf();
	~merge_tf();

	void adjusting_tf( const SPos &amcl_pos , const SPos &odom_pos , const bool b_force_merge = false);
	bool get_pos_after_tf( SPOS_CONFIDENCE &conf_pos , const SPos &odom_pos );
	//SPos get_pos();
	bool update_confidence(const SAMCL_CONFIDENCE &amcl_confidence);

protected:
private:

	double tf_x_;
	double tf_y_;
	double tf_a_;

	double last_tf_x_;
	double last_tf_y_;
	double last_tf_a_;

	bool cal_tf_diff(double nx, double ny, double na, double lx, double ly, double la);
	float f_max_jump_magnitude_;
	float f_max_jump_angle_;

	double wx_;
	double wy_;
	double wa_;
	boost::mutex mu_p_;

	SPos w_pos_;

	//SBuffer<SPos> merge_amcl_;

	THSafe<SAMCL_CONFIDENCE> amcl_confidence_;
	SPos set_amcl_pos_;
	int i_drop_counts_;
	int reflash_cnt_;
};





#endif//_MERGE_TF_WANGHONGTAO_2019_1_30_
