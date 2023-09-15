#ifndef _AMCL_TF_WANGHONGTAO_2017_12_12_
#define _AMCL_TF_WANGHONGTAO_2017_12_12_

#include "Comm.h"
#include "RobotStruct.h"

class amcl_tf
{
public:
	amcl_tf();
	~amcl_tf();

	void adjusting_tf( const SPos &amcl_pos , const SPos &odom_pos );
	SPos get_pos_after_tf( const SPos &odom_pos );

	void clear();

protected:
private:

	double tf_x_;
	double tf_y_;
	double tf_a_;

	double wx_;
	double wy_;
	double wa_;
};





#endif//_AMCL_TF_WANGHONGTAO_2017_12_12_
