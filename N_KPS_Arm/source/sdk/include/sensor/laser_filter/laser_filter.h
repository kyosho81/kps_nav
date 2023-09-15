#ifndef _LASER_FILTER_KYOSHO_20160316_
#define _LASER_FILTER_KYOSHO_20160316_

#include "RobotStruct.h"

#include "polygon.h"

class laser_filter
{
public:
	laser_filter();
	~laser_filter();
	
	void init_laser_para(const SLaser &laser,const F32 &laser_dx,const F32 &laser_dy);
	void init_laser_para(const std::string &str_robot_shape, const SLaser &laser,const F32 &laser_dx,const F32 &laser_dy);
	//	void set_laser_para( const F32& min_angle,const F32& max_angle,const SLaser& laser);
	void filter_used( SLaser& used_laser , bool b_max = false);
	void fill_seg( SLaser &laser_range ,const F32 &min_angle,const F32 &max_angle);
// 	void set_laser_para(const F32& min_angle,const F32& max_angle,const SLaser_Urg& laser_urg);
// 	void filter_used( SLaser_Urg& used_laser );
	void get_filter(SLaser& filter_laser);

	void save(const std::string &file_nm,const SLaser& filter_laser);
	void load(const std::string &file_nm, SLaser& filter_laser);
	void segment_used( SLaser& used_laser );
	void segment_used( F32* const range , U8 *seg, const int &i_size, F32 seg_min_dis = 0.1 );
	void segment_line( F32* const range , U8 *seg, const int &i_size , F32 seg_min_dis );
	int  get_line(std::vector<SLine2P> &ln, F32 ln_min_len = 0.25, F32 ln_max_len = 0.5, F32 max_line_in_range = 1.5);
	SLaserXY laserxy_;
protected:
private:
// 	void set_max_min(const F32& min_angle,const F32& max_angle);
// 	void set_max_min();

	polygon polygon_;
	
	SLaser min_range_;
//	SLaser_Urg min_range_urg_;
	
// 	F32 start_angle_;
// 	F32 resolution_;

// 	F32 min_fangle_;
// 	F32 max_fangle_;
// 
// 	U32 min_iangle_;
// 	U32 max_iangle_;
	bool check_line(F32* range, int index, F32 seg_min_c);
	std::map<int , std::pair<int,int> > m_seg_index_;
	F32* cos_range_;
	F32* sin_range_;
	F32 get_cos_range(int i , F32* range );
	F32 get_sin_range(int i , F32* range );

	SLaserXY cos_sin_;
	F32 laser_dx_;
	F32 laser_dy_;
};

#endif//_LASER_FILTER_KYOSHO_20160316_
