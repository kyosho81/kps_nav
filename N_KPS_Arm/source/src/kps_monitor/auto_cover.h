#ifndef _AUTO_COVER_20181113_H
#define _AUTO_COVER_20181113_H

#include <boost/serialization/singleton.hpp>

#include "robot/Geometry.h"
#include "sep_block.h"
#include "block_path.h"

class vec_value 
{
public:

	vec_value(){
		pos_.setX(0);
		pos_.setY(0);
		value_ = 0;
		angle_ = 0;
	};
	~vec_value(){};

	VecPosition pos_;
	F32 angle_;
	S8 value_;
};

class GridMap;


class auto_cover{


public:

	auto_cover();
	~auto_cover();

	void init( GridMap* p_global_map , std::vector<Sxy> v_range_list );
	void init( GridMap* p_global_map , std::vector<std::vector<Sxy>> v_all_range );
	void get_path( std::vector<std::vector<SOdomSpeed>> &v_block_path , const SPos &pos);
	std::vector<Sxy> get_show_list();
	std::vector<segment_inline> get_seg_ln();

private:
	
	F32 road_width_;
	int map_obs_size_;
	

	GridMap* p_tmp_map_;
	GridMap* p_global_map_;

	void draw_range_line( const Sxy &p1 , const Sxy &p2 );
	VecPosition get_vecfromline( VecPosition &vec ,const SPos &r, const Sxy &p1 , const Sxy &p2 );
	bool searchEmpty(SPos &find_pos, SPos begin_pos, const std::vector<Sxy> &v_range_list);
	bool searchEmpty(SPos &find_pos, VecPosition vec, const F32 &angle_rad ,const std::vector<Sxy> &v_range_list);
	bool searchObstacle( SPos &find_pos, SPos begin_pos , const std::vector<Sxy> &v_range_list);
	bool searchObstacle( SPos &find_pos, VecPosition vec,const F32 &angle_rad , const std::vector<Sxy> &v_range_list);
	//SPos searchValue(VecPosition vec,const F32 &angle,const S8 &p_value,const bool &b_greater);
	S8 getValue(const VecPosition &vec);
	S8 getValue(const SPos &pos);
	S8 getValue(const U32 &gx,const U32 &gy );
	S8 fast_getValue(const U32 &gx,const U32 &gy );
	S8 fast_getValue(const VecPosition &vec);
	//1.cal get begin pos to edge
	bool get_begin_pos(SPos &pos_begin, const SPos &robot_pos,const std::vector<Sxy> &v_range_list);
	
	//2.slice map to channel
	SPos get_line_start_pos( const SPos &pos_begin, std::vector<Sxy> v_range_list );
	int create_pos_on_clean_line( std::map<F32,SPos> &m_pos_on_line, const SPos &pos_begin, std::vector<Sxy> v_range_list );
	void slice_map( segment_inline &seg_line_list, const SPos &pos_begin, const std::vector<Sxy> &v_range_list );
	//3. make toplogy
	void make_toplogy();
	//4. search path 
	void search_path();


	//map border (top left top right bottom right bottom left)
private:
	void set_border(Sxy xy);
	F32 min_x_;
	F32 min_y_;
	F32 max_x_;
	F32 max_y_;
	std::vector<Sxy> get_border();

private:
	void put_show_seg(SSegment seg);
	void put_show_list(const VecPosition &vec);
	void put_show_list(const SPos &pos);

	std::vector<Sxy> show_pos_list_;
	std::vector<segment_inline> seg_line_all_;

private:

	bool search_close_to_wall( SPos &target_pos, SPos ori_pos , const F32 &dis );

	bool rot_search_empty(SPos &target_pos, SPos ori_pos , const F32 &dis, const bool &b_empty);
	//void VecP2SPos(SPos &spos, const VecPosition &vec,const F32 &angle);
	//F32 SPos2VecP( VecPosition &vec, const SPos &spos );

private:
	bool search_bound( std::list<SPos> &rl_block ,SPos &closest_pos, const SPos &pos , const std::vector<Sxy> &v_range_list);
	bool search_bound_pix( std::list<SPos> &rl_block, const SPos &pos , const std::vector<Sxy> &v_range_list);
	void show_bound(const std::list<SPos> &l_block);

	int sep_block( std::vector< int > &l_block_list , const std::list<SPos> &l_block );
	int dt_separate_block( std::vector< std::list<SPos> > &l_block_list , const std::list<SPos> &l_block );
	int get_key_point_path( segment_inline &seg_line_list, const std::list<SPos> &l_block );
	int get_run_path(std::vector<SOdomSpeed> &v_run_path ,segment_inline &seg_line_list);
	bool search_close_to_wall_pix(U32 &find_gx,U32 &find_gy,const U32 &ori_gx,const U32 &ori_gy);
	
	std::map<int,int> m_reached_;
	std::map<int,int> m_value_;
	void init_template();
	std::vector<std::pair<int,int>> template_;
private:
	separate_block sep_block_;
	block_path     path_block_;
	std::list<area> l_area_list_;
};

typedef boost::serialization::singleton<auto_cover> Singleton_Auto_Cover;
#define AUTO_COVER Singleton_Auto_Cover::get_mutable_instance() 

#endif // _AUTO_COVER_20181113_H
