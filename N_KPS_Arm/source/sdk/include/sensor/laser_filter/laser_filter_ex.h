#ifndef _LASER_FILTER_EX_KYOSHO_20191010_
#define _LASER_FILTER_EX_KYOSHO_20191010_

#include <Eigen/Dense>

#include "RobotStruct.h"

#include "polygon_ex.h"
#include "quadtree/QuadTree.h"

class laser_filter_ex
{
public:

	laser_filter_ex();
	~laser_filter_ex();
	
	void init_laser_para(const SLaser_Ex &laser);
	void init_laser_para(const SLaser_Ex &laser,const F32 &laser_dx,const F32 &laser_dy);
	void init_laser_para(const std::string &str_robot_shape, const SLaser_Ex &laser,const F32 &laser_dx,const F32 &laser_dy);

	
	void filter_used( SLaser_Ex& used_laser);
	void fill_seg( SLaser_Ex &laser_range ,const F32 &min_angle,const F32 &max_angle);
	void median_filter( SLaser_Ex &laser_ex);
	void get_win_index(int &i_from,int &i_to,const int &index,const int &half_win,const int &min_index,const int &max_index);
	void average_filter( SLaser_Ex &laser_ex);
	bool make_from_data(VecPosition &pos,SLaser_Ex &laser_ex,const int &index);
	void make_ray(VecPosition &v_ray,const SLaser_Ex &laser_ex,const int &index,const int &min_index,const int &max_index);
	int make_seg( U8* seg, std::multimap<int,std::vector<SVec> > &seg_list, SLaser_Ex used_laser , const int &mid_filter = 1);
	bool curve_fit( SVec &v , const std::vector<SPos> &v_pos);
	int filter_intesity( std::multimap<int,std::vector<SPos> > &seg_list, SLaser_Ex &used_laser);
	int filter_intesity_wj( std::multimap<int,std::vector<SPos> > &seg_list, SLaser_Ex &used_laser);
	int filter_intesity_wj3( std::multimap<int,std::vector<SPos> > &seg_list, SLaser_Ex &used_laser,F32 seg_min_dis = 0.3);
	bool check_line(F32* range, int index, F32 seg_min_c);
	F32 get_dis( int i_start, int i_end, F32* range );
	void get_filter(SLaser_Ex& filter_laser);

	void save(const std::string &file_nm,const SLaser_Ex& filter_laser);
	void load(const std::string &file_nm, SLaser_Ex& filter_laser);
	
protected:
private:


	polygon_ex polygon_ex_;
	
	SLaser_Ex min_range_;

	F32 step_const_;

	U32 min_intensity_;
	U32 max_intensity_;
	F32 min_range_diff_;
	F32 reflect_pillar_radii_;
private://filter wj3
	F32* cos_range_;
	F32* sin_range_;
	SLaserXYEx cos_sin_;
	F32 get_cos_range(int i , F32* range );
	F32 get_sin_range(int i , F32* range );
	
	std::map<int , std::pair<int,int> > m_seg_index_;

	QuadTree<int>* qtree_;

};

#endif//_LASER_FILTER_EX_KYOSHO_20191010_
