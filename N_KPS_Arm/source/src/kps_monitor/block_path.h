#ifndef _BLOCK_PATH_20210309_H
#define _BLOCK_PATH_20210309_H

#include "octomap/octomap.h"
#include "robot/Geometry.h"
#include "robot/RobotStruct.h"

#include "area.h"
#include "segment.h"

class block_path
{
public:
	block_path();
	~block_path();

	
	void init(GridMap* p_forbidden_map,GridMap* p_global_map);
	int do_path_block( std::list<area> &l_area_list);
	void bind_fnc_searchEmpty(boost::function<bool (SPos &find_pos, SPos begin_pos, const std::vector<Sxy> &v_range_list)> fnc);
	void bind_fnc_fast_getValue(boost::function<S8 ( const VecPosition &vec )> fnc);
	void bind_fnc_searchObstacle(boost::function<SPos ( SPos &find_pos, SPos begin_pos , const std::vector<Sxy> &v_range_list)> fnc);
	static bool posInRange(VecPosition vec ,const std::vector<Sxy> &v_range_list);

protected:
private:

	GridMap* p_forbidden_map_;
	GridMap* p_global_map_;

	void init_map(const std::list<SPos> &l_block);
	std::map<int,SPos> m_id_pos_;

	void init_qt_tree();
	octomap::OcTree* octree_;


	int cal_path( area &ar);

	void cal_pca(const std::list<SPos> &block_point);

	SPos get_line_start_pos( const SPos &pos_begin, std::vector<Sxy> v_range_list );
	int create_pos_on_clean_line( std::map<F32,SPos> &m_pos_on_line, const SPos &pos_begin, std::vector<Sxy> v_range_list , int map_obs_size );
	
	SPos mid_pos_;

	std::vector<Sxy> rangle_list_;

	int create_segment_on_slice_line(std::map<F32,segment_inline> &seg,std::map<F32,SPos> pos_on_line, std::vector<Sxy> v_range_list , int map_obs_size );
	bool find_slice_search_start(SPos &start_pos, const SPos &ori_pos,const std::vector<Sxy> &v_range_list);
	SPos ins_range_slice(SPos ori_pos, Sxy pf, Sxy pt);
private:
	boost::function<bool (SPos &find_pos, SPos begin_pos, const std::vector<Sxy> &v_range_list)> fnc_searchEmpty_;
	boost::function<S8 ( const VecPosition &vec )> fnc_fast_getValue_;
	boost::function<bool ( SPos &find_pos, SPos begin_pos , const std::vector<Sxy> &v_range_list)> fnc_searchObstacle_;
	float road_width_;

};

#endif // _BLOCK_PATH_20210309_H
