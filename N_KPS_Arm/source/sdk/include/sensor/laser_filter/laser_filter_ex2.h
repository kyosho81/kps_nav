#ifndef _LASER_FILTER_EX2_KYOSHO_20191010_
#define _LASER_FILTER_EX2_KYOSHO_20191010_

#include <Eigen/Dense>

#include "RobotStruct.h"

#include "polygon_ex2.h"

class laser_filter_ex2
{
public:

	laser_filter_ex2();
	~laser_filter_ex2();
	
	void init_laser_para(const SLaser_Ex2 &laser_ex2);
	void init_laser_para(const SLaser_Ex2 &laser_ex2,const F32 &laser_dx,const F32 &laser_dy);
	void init_laser_para(const std::string &str_robot_shape, const SLaser_Ex2 &laser_ex2,const F32 &laser_dx,const F32 &laser_dy);

	
	void filter_used( SLaser_Ex2& used_laser);
	void fill_seg( SLaser_Ex2 &laser_range ,const F32 &min_angle,const F32 &max_angle);
	void median_filter( SLaser_Ex2 &laser_ex);
	void get_win_index(int &i_from,int &i_to,const int &index,const int &half_win,const int &min_index,const int &max_index);
	void average_filter( SLaser_Ex2 &laser_ex);
	bool make_from_data(VecPosition &pos,SLaser_Ex2 &laser_ex,const int &index);
	void make_ray(VecPosition &v_ray,const SLaser_Ex2 &laser_ex,const int &index,const int &min_index,const int &max_index);
	int make_seg( U8* seg, std::multimap<int,std::vector<SVec> > &seg_list, SLaser_Ex2 used_laser , const int &mid_filter = 1);
	bool curve_fit( SVec &v , const std::vector<SPos> &v_pos);
	int filter_intesity( std::multimap<int,std::vector<SPos> > &seg_list, SLaser_Ex2 &used_laser);
	int filter_intesity_wj2(std::multimap<int,std::vector<SPos> > &seg_list, SLaser_Ex2 &used_laser);

	void get_filter(SLaser_Ex2& filter_laser);

	void save(const std::string &file_nm,const SLaser_Ex2& filter_laser);
	void load(const std::string &file_nm, SLaser_Ex2& filter_laser);
	
protected:
private:


	polygon_ex2 polygon_ex2_;
	
	SLaser_Ex2 min_range_;

	F32 step_const_;

	U32 min_intensity_;
	U32 max_intensity_;
	F32 min_range_diff_;
	F32 reflect_pillar_radii_;
};

#endif//_LASER_FILTER_EX2_KYOSHO_20191010_
