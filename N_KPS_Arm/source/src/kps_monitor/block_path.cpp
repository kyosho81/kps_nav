#include <iostream>

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "robot/vec2pos.hpp"

#include "mapserver/GridMap.h"
#include "mapserver/MapServer.h"
#include "pca.h"

#include "block_path.h"


block_path::block_path()
{

	octree_ = 0;

	p_forbidden_map_ = 0;
	p_global_map_ = 0;

	road_width_ = 0.8;

}

block_path::~block_path()
{

}
int block_path::do_path_block( std::list<area> &l_area_list )
{

	auto it = l_area_list.begin();
	for ( ; it != l_area_list.end() ; ++it  ){
		cal_path(*it);
	}

	return l_area_list.size();
}

void block_path::init_map(const std::list<SPos> &l_block)
{
	
	m_id_pos_.clear();
	int i_id = 0 ; 
	std::list<SPos>::const_iterator cit = l_block.cbegin();
	for ( ; cit != l_block.cend() ; ++cit ){
		m_id_pos_[i_id++] = *cit;
// 		if (i_id > 1000){
// 			break;
// 		}
//		std::cout<<"pos x:"<<i_id<<" "<<(*cit).x_<<" "<<(*cit).y_<<std::endl;
//		SLEEP(100);
	}

}

void block_path::init_qt_tree()
{
	SDelete(octree_);

	
	octree_ = new octomap::OcTree(0.05);

	std::map<int,SPos>::iterator it = m_id_pos_.begin();
	for ( ; it != m_id_pos_.end() ; ++it ){
// 		vertex np( (long double)it->second.x_,(long double)it->second.y_);
// 		qtree_->insert(np,it->first);
		octree_->updateNode( octomap::point3d((float)it->second.x_,(float)it->second.y_,(float)it->first), true );
	}
	octree_->updateInnerOccupancy();
}
void block_path::init( GridMap* p_forbidden_map,GridMap* p_global_map )
{
	p_forbidden_map_ = p_forbidden_map;
	p_global_map_ = p_global_map;
}

int block_path::cal_path( area &ar )
{
	//1 pca find clean axis
	std::vector<SVec> axle_vec;
	SVec mean = Singleton_PCA::get_mutable_instance().pca2d(axle_vec,ar.get_block_point());
	std::vector<Sxy> rangle_list = Singleton_PCA::get_mutable_instance().get_range();


	if ( axle_vec.size() > 0 )
	{
		mid_pos_.th_ = VecPosition(axle_vec[0].x_,axle_vec[0].y_).getDirection();
		//std::cout<<"clear_axis_angle:"<<mid_pos.th_<<std::endl;
		mid_pos_.th_ = Deg2Rad(mid_pos_.th_);
	}
	mid_pos_.x_ = mean.x_;
	mid_pos_.y_ = mean.y_;


	//1 create slice line para
	std::map<F32,SPos> pos_on_line;
	create_pos_on_clean_line( pos_on_line , mid_pos_ , ar.get_border() , ar.get_block_point().size() );

	//2 create segment for each pos on slice line
	std::map<F32,segment_inline> seg;
	return create_segment_on_slice_line(seg,pos_on_line,ar.get_border(), ar.get_block_point().size());

	return 0;
}


void block_path::cal_pca(const std::list<SPos> &block_point)
{
	std::vector<SVec> vec_axle;
	SVec mean = Singleton_PCA::get_mutable_instance().pca2d(vec_axle,block_point);
	rangle_list_ = Singleton_PCA::get_mutable_instance().get_range();


	if ( vec_axle.size() > 0 )
	{
		mid_pos_.th_ = VecPosition(vec_axle[0].x_,vec_axle[0].y_).getDirection();
		//std::cout<<"clear_axis_angle:"<<mid_pos.th_<<std::endl;
		mid_pos_.th_ = Deg2Rad(mid_pos_.th_);
	}
	mid_pos_.x_ = mean.x_;
	mid_pos_.y_ = mean.y_;
}

SPos block_path::get_line_start_pos( const SPos &pos_begin, std::vector<Sxy> v_range_list )
{
	SPos start_pos = pos_begin;
	if (v_range_list.size() < 1)
	{
		return start_pos;
	}
	std::vector<Sxy>::iterator it = v_range_list.begin();
	Sxy xy_from = *it;
	//v_range_list.push_back(xy_from);
	//it = v_range_list.begin();
	++it;

	Line ln_clean_line = Line::makeLineFromPositionAndAngle(VecPosition(pos_begin.x_,pos_begin.y_),Rad2Deg(pos_begin.th_));
	F32 angle_diff = M_PI;
	Line ln;
	VecPosition v_drop;

	for ( ; it != v_range_list.end() ; ++it )
	{
		Sxy &xy_to = *it;
		Line ln_range = Line::makeLineFromTwoPoints(VecPosition(xy_from.x_,xy_from.y_),VecPosition(xy_to.x_,xy_to.y_));

		v_drop = ln_range.getPointOnLineClosestTo(VecPosition(pos_begin.x_,pos_begin.y_));
		v_drop = v_drop - VecPosition(pos_begin.x_,pos_begin.y_);

		F32 angle = VecPosition::angle_diff(Deg2Rad( v_drop.getDirection() ), pos_begin.th_ ) ;
		if( fabs( angle ) < angle_diff){
			angle_diff = fabs( angle );
			ln = ln_range;
		}
		xy_from = xy_to;
	}

	ln.getIntersection(ln_clean_line,v_drop);

	Vec2Pos(start_pos,v_drop,VecPosition::normalizeAngleRad( pos_begin.th_+ M_PI));

	fnc_searchEmpty_(start_pos,start_pos,v_range_list);

	return start_pos;
}

int block_path::create_pos_on_clean_line( std::map<F32,SPos> &m_pos_on_line, const SPos &pos_begin, std::vector<Sxy> v_range_list, int map_obs_size)
{
	m_pos_on_line.clear();
	SPos start_pos = get_line_start_pos( pos_begin, v_range_list);

	VecPosition vec(start_pos.x_,start_pos.y_);
	VecPosition v_step(road_width_,Rad2Deg(start_pos.th_),POLAR);
	VecPosition vec_drop;

	for (int i = 0  ; i < map_obs_size*2 ; ++i )
	{

		vec_drop = vec + v_step * i;
		F32 dis = (vec_drop - vec).getMagnitude();

		if (posInRange( vec_drop, v_range_list))
		{
			SPos pos;
			pos.x_ = vec_drop.getX();
			pos.y_ = vec_drop.getY();
			pos.th_ = start_pos.th_;
			m_pos_on_line[dis] = pos;
		}else{
			break;
		}
	}
	return m_pos_on_line.size();
}
void block_path::bind_fnc_searchEmpty( boost::function<bool (SPos &find_pos, SPos begin_pos, const std::vector<Sxy> &v_range_list)> fnc )
{
	fnc_searchEmpty_ = fnc;
}
void block_path::bind_fnc_fast_getValue( boost::function<S8 ( const VecPosition &vec )> fnc )
{
	fnc_fast_getValue_ = fnc;
}

bool block_path::posInRange(VecPosition vec ,const std::vector<Sxy> &v_range_list){

	F32 angle = 0;

	std::vector<Sxy>::const_iterator cit = v_range_list.cbegin();
	if(cit == v_range_list.cend()){
		return false;
	}
	Sxy p_front = *cit;
	for ( ; cit != v_range_list.cend() ; ++cit )
	{
		if (cit != v_range_list.cbegin() )
		{
			VecPosition v1(p_front.x_,p_front.y_);
			VecPosition v2(cit->x_,cit->y_);

			v1 = v1- vec;
			v2 = v2- vec;
			angle += fabs( VecPosition::IntersectionAngle(v1,v2) );
			p_front = *cit;
		}
	}
	if ( fabs(angle - 360) < 1e-3 )
	{
		return true;
	}
	return false;
}

///////////////////////
//      *
//------x-------------
//      *
//      *
//     ^* ori
//      *
//      *
//------*-start-------
//      *
bool block_path::find_slice_search_start(SPos &start_pos, const SPos &ori_pos,const std::vector<Sxy> &v_range_list){
	auto cit_from = v_range_list.cend();
	auto cit_to = v_range_list.cbegin();
	for ( ; cit_to != v_range_list.cend(); ++cit_to ){

		if (cit_from != v_range_list.cend() ){
			start_pos = ins_range_slice(ori_pos,*cit_from,*cit_to);
			if( posInRange(VecPosition(start_pos.x_,start_pos.y_),v_range_list) ) {
				if ( fabs(VecPosition::angle_diff(start_pos.th_,ori_pos.th_)) < 0.02/*Deg2Rad(0.1)*/){
					return true;
				}
			}
		}
		cit_from = cit_to;
	}
	return false;
}
SPos block_path::ins_range_slice(SPos ori_pos, Sxy pf, Sxy pt){
	VecPosition ori(ori_pos.x_,ori_pos.y_);
	Line ln_slice = Line::makeLineFromPositionAndAngle(ori,Rad2Deg(ori_pos.th_));
	Line ln_range = Line::makeLineFromTwoPoints(VecPosition(pt.x_,pt.y_),VecPosition(pt.x_,pt.y_));

	VecPosition v_ins;
	ln_range.getIntersection(ln_slice,v_ins);

	SPos res_pos;
	res_pos.x_ = v_ins.getX();
	res_pos.y_ = v_ins.getY();
	//res_pos.th_ = pos.th_;
	
	ori -= v_ins;
	res_pos.th_ = Deg2Rad(v_ins.getDirection());

	return res_pos;
}
int block_path::create_segment_on_slice_line( std::map<F32,segment_inline> &seg,std::map<F32,SPos> pos_on_line , std::vector<Sxy> v_range_list , int map_obs_size )
{
	auto it = pos_on_line.begin();
	for ( ; it != pos_on_line.end() ; ++it ){
		SPos start_pos;
		if (find_slice_search_start(start_pos,it->second,v_range_list)){
			
			SSegment seg_slice_ln;
			VecPosition v_start;
			Pos2Vec(v_start,start_pos);
			S8 value = fnc_fast_getValue_(v_start);
			if (value == MAP_EMPTY){
				seg_slice_ln.p1_= v_start;
				//fnc_searchEmpty_
			}

		}
	}

	return seg.size();
}

void block_path::bind_fnc_searchObstacle( boost::function<SPos (SPos &find_pos, SPos begin_pos , const std::vector<Sxy> &v_range_list)> fnc )
{

}


