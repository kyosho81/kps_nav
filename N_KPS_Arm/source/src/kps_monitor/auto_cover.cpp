#include <iostream>

#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "Comm/TimerDiff.h"
#include "robot/vec2pos.hpp"

#include "mapserver/GridMap.h"
#include "mapserver/MapServer.h"
#include "pca.h"

#include "auto_cover.h"

auto_cover::auto_cover()
{
	road_width_ = 0.8;
	p_tmp_map_ = CREATE_MEM_GMAP("cover_map");
	p_global_map_ = 0 ;
	map_obs_size_ = 5000;

	max_x_ = -1e10;
	max_y_ = -1e10;
	min_x_ = 1e10;
	min_y_ = 1e10;

	init_template();
}

auto_cover::~auto_cover()
{

}

void auto_cover::init( GridMap* p_global_map , std::vector<Sxy> v_range_list )
{
	

	if (v_range_list.size() ==0){
		p_global_map->get_map_border(min_x_,min_y_,max_x_,max_y_);
	}

	p_global_map_ = p_global_map;
	p_tmp_map_->clear();
	m_value_.clear();
	m_reached_.clear();
	map_obs_size_ = p_global_map_->occupy_point_.size();

	if (v_range_list.size() > 0)
	{
		Sxy p_front;
		p_front = *v_range_list.begin();
		v_range_list.push_back(p_front);

		std::vector<Sxy>::iterator it = v_range_list.begin();

		for ( ; it != v_range_list.end() ; ++it )
		{
			Sxy &wxy(*it);
			set_border(wxy);
			p_tmp_map_->setgrid(wxy.x_,wxy.y_,MAP_OCCUPY_MAX);

			if (it != v_range_list.begin() )
			{
				draw_range_line(p_front,*it);
				p_front = *it;
			}
		}
		F32 global_map_inf = 0.2;
		Config::getConfig("loc_global_map_inf",global_map_inf);
		MAP_SERVER.fast_inflation(global_map_inf,p_tmp_map_->Get_name());
	}

	map_obs_size_ += p_tmp_map_->occupy_point_.size();

// 	MAP_SERVER.MergeMap(p_tmp_map_->Get_name(),p_global_map_->Get_name());
// 	MAP_SERVER.save_map(p_tmp_map_->Get_name(),".//auto.igm");
}
void auto_cover::init( GridMap* p_global_map , std::vector<std::vector<Sxy>> v_all_range )
{
	if (v_all_range.size() ==0){
		p_global_map->get_map_border(min_x_,min_y_,max_x_,max_y_);
	}

	p_global_map_ = p_global_map;
	p_tmp_map_->clear();
	m_value_.clear();
	m_reached_.clear();
	map_obs_size_ = p_global_map_->occupy_point_.size();


	std::vector<std::vector<Sxy>>::iterator it = v_all_range.begin();
	for ( ; it != v_all_range.end(); ++it ){

		std::vector<Sxy> &v_range_list(*it);

		if (v_range_list.size() > 0){
			Sxy p_front;
			p_front = *v_range_list.begin();
			v_range_list.push_back(p_front);

			std::vector<Sxy>::iterator it2 = v_range_list.begin();

			for ( ; it2 != v_range_list.end() ; ++it2 )
			{
				Sxy &wxy(*it2);
				set_border(wxy);
				p_tmp_map_->setgrid(wxy.x_,wxy.y_,MAP_OCCUPY_MAX);

				if (it2 != v_range_list.begin() )
				{
					draw_range_line(p_front,*it2);
					p_front = *it2;
				}
			}
			
		}

	}

	F32 global_map_inf = 0.1;
	Config::getConfig("loc_global_map_inf",global_map_inf);
	MAP_SERVER.fast_inflation(global_map_inf,p_tmp_map_->Get_name());
	
	map_obs_size_ += p_tmp_map_->occupy_point_.size();
	// 	MAP_SERVER.MergeMap(p_tmp_map_->Get_name(),p_global_map_->Get_name());
	// 	MAP_SERVER.save_map(p_tmp_map_->Get_name(),".//auto.igm");
}
void auto_cover::init_template(){
	template_.push_back(std::make_pair(1,1));
	template_.push_back(std::make_pair(1,0));
	template_.push_back(std::make_pair(1,-1));
	template_.push_back(std::make_pair(0,-1));
	template_.push_back(std::make_pair(-1,-1));
	template_.push_back(std::make_pair(-1,0));
	template_.push_back(std::make_pair(-1,1));
	template_.push_back(std::make_pair(0,1));
}
void auto_cover::get_path( std::vector<std::vector<SOdomSpeed>> &v_block_path, const SPos &pos  )
{
	v_block_path.clear();
	seg_line_all_.clear();

	//1 check robot pos
	VecPosition vec;
	Pos2Vec(vec,pos);
	if( getValue(vec) != MAP_EMPTY){
		std::cout<<"get path err: robot pos err! x:"<<pos.x_<<" y:"<<pos.y_<<" th:"<<pos.th_<<" value:"<<int(getValue(vec))<<std::endl;
		return;
	}

	//2 search_border
	std::list<SPos> l_block;

	if(!search_bound_pix( l_block, pos, get_border()/*map border*/)){
		// 	if ( !search_bound( l_block ,closest_pos, pos , v_range_list)) 	{
		std::cout<<"auto_cover::separate_block error! "<<std::endl;
		return ;
	}

	//3 separate_block
	sep_block_.init(p_tmp_map_,p_global_map_);
	sep_block_.do_separate_block(l_area_list_,l_block);
	
	//4 path block
	path_block_.init(p_tmp_map_,p_global_map_);
	path_block_.bind_fnc_searchEmpty(boost::bind( &auto_cover::searchEmpty,this,_1,_2,_3  ));
	path_block_.bind_fnc_fast_getValue(boost::bind( &auto_cover::fast_getValue,this,_1  ));
	path_block_.do_path_block(l_area_list_);
	//3 find path for each block
// 	std::vector< std::list<SPos> >::iterator it = l_block_list.begin();
// 	//it++;
// 	for ( ; it != l_block_list.end(); ++it )
// 	{
// 		
// 		std::list<SPos> &l_block = (*it);
// 		show_bound(l_block);
// 		break;
// 		segment_inline seg_line_list;
// 		get_key_point_path( seg_line_list, l_block );
// 		seg_line_all_.push_back(seg_line_list);
// 		std::vector<SOdomSpeed> v_path;
// 		get_run_path(v_path , seg_line_list);
// 		v_block_path.push_back(v_path);
// 	}
	

	
}


void auto_cover::show_bound(const std::list<SPos> &l_block){
	std::list<SPos>::const_iterator cit = l_block.cbegin();
	for ( ; cit != l_block.cend(); ++cit ){
		VecPosition vec;
		Pos2Vec(vec,*cit);
		put_show_list(vec);
	}
}

int auto_cover::dt_separate_block(std::vector< std::list<SPos> > &l_block_list , const std::list<SPos> &l_block)
{
	sep_block_.init(p_tmp_map_,p_global_map_);
	sep_block_.do_separate_block(l_block_list,l_block);
	std::list<std::pair<Sxy,Sxy>> vl = sep_block_.get_sep_line();
	std::list<std::pair<Sxy,Sxy>>::iterator it = vl.begin();
	for ( ; it != vl.end() ; ++it ){
		Sxy p1 = (*it).first;
		Sxy p2 = (*it).second;
		
		
		VecPosition v1(p1.x_,p1.y_);
		VecPosition v2(p2.x_,p2.y_);

		VecPosition v12 = v2 - v1;
		int icount = v12.getMagnitude() / 0.05;
		v12 = VecPosition( 0.05 ,v12.getDirection(),POLAR);


		for ( int i = 1; i < icount ; ++i )
		{
			v2 = v1 + v12 * i;
			put_show_list(v2);
		}
	}
	
// 	l_block_list.push_back(l_block);
 	return l_block_list.size();
}


int auto_cover::get_key_point_path(segment_inline &seg_line_list, const std::list<SPos> &l_block)
{
	//1 pca find clean axis
	std::vector<SVec> vec;
	SVec mean = Singleton_PCA::get_mutable_instance().pca2d(vec,l_block);
	std::vector<Sxy> rangle_list = Singleton_PCA::get_mutable_instance().get_range();
	
	SPos mid_pos;
	if ( vec.size() > 0 )
	{
		mid_pos.th_ = VecPosition(vec[0].x_,vec[0].y_).getDirection();
		std::cout<<"clear_axis_angle:"<<mid_pos.th_<<std::endl;
		mid_pos.th_ = Deg2Rad(mid_pos.th_);
	}
	mid_pos.x_ = mean.x_;
	mid_pos.y_ = mean.y_;

	//2 slice map
	slice_map( seg_line_list, mid_pos , rangle_list);

	return 0;
}

int auto_cover::get_run_path(std::vector<SOdomSpeed> &v_run_path ,segment_inline &seg_line_list)
{
	return 0;
}
bool auto_cover::search_close_to_wall_pix(U32 &find_gx,U32 &find_gy,const U32 &ori_gx,const U32 &ori_gy){

	U32 c_gx = 0;
	U32 c_gy = 0;
	S8 value = MAP_OCCUPY_MAX;
	int reached_index = 0 ; 
	int i_before = 0;
	int i_after = 0;
	//find empty and close to occupy
	//and unreached
	for (int i = 0 ; i < 8; ++i ){

		find_gx = ori_gx + template_[i].first;
		find_gy = ori_gy + template_[i].second;
		
		//when reached ignore
		reached_index = p_global_map_->g2i(find_gx,find_gy);
		if (m_reached_.count(reached_index) > 0){
			continue;
		}

		//when occupy ignore
		value = fast_getValue(find_gx,find_gy);
		if (value != MAP_EMPTY){
			continue;
		}

		//check before after
		if ( i == 0 ){
			i_before = 7;
		}else{
			i_before = i -1;
		}
		c_gx = ori_gx + template_[i_before].first;
		c_gy = ori_gy + template_[i_before].second;
		value = fast_getValue(c_gx,c_gy);
		if (value != MAP_EMPTY){

			return true;
		}


		if ( i == 7 ){
			i_after = 0;
		}else{
			i_after = i + 1;
		}
		c_gx = ori_gx + template_[i_after].first;
		c_gy = ori_gy + template_[i_after].second;
		value = fast_getValue(c_gx,c_gy);
		if (value != MAP_EMPTY){

			return true;
		}
	}

	return false;
}
bool auto_cover::search_bound_pix( std::list<SPos> &rl_block , const SPos &pos , const std::vector<Sxy> &v_range_list )
{
	//clear output 
	rl_block.clear();
	//clear history data
	m_reached_.clear();

	SPos closest_pos;
	if( !get_begin_pos(closest_pos , pos , v_range_list)){
		return false;
	}
	U32 find_gx;
	U32 find_gy;
	U32 ori_gx;
	U32 ori_gy;
	p_global_map_->world2grid(closest_pos.x_,closest_pos.y_,ori_gx,ori_gy);
	
	if(!search_close_to_wall_pix(find_gx,find_gy,ori_gx,ori_gy)){
		std::cout<<"begin pos error!"<<std::endl;
		return false;
	}
	
	ori_gx = find_gx;
	ori_gy = find_gy;
	int begin_index = p_global_map_->g2i(ori_gx,ori_gy);

	//create begin vector
	F32 begin_wx = 0;
	F32 begin_wy = 0;
	p_global_map_->grid2world(find_gx,find_gy,begin_wx,begin_wy);
	VecPosition vbegin(begin_wx,begin_wy);

	//create begin angle
	VecPosition vori; 
	Pos2Vec( vori, pos);
	F32 begin_angle = (vbegin - vori).getDirection();

	//push begin pix
	std::list<std::pair<int,int>> l_pix_bound;
	l_pix_bound.push_back(std::make_pair(ori_gx,ori_gy));


	//search all pix find bound
	int i_search = 0;
	for (int i = 0; i < map_obs_size_ ; ++i ){

		////////////////////////////////
		//find next pix
		if(!search_close_to_wall_pix(find_gx,find_gy,ori_gx,ori_gy)){
			//when find err, backtracking
			l_pix_bound.pop_back();
			if (l_pix_bound.size() > 0){
				std::list<std::pair<int,int>>::reverse_iterator it = l_pix_bound.rbegin();
				ori_gx = it->first;
				ori_gy = it->second;
			}else{
				std::cout<<"search_bound_pix backtracking error!"<<std::endl;
				return false;
			}
		}else{
			//when find new pix
			//push into l_pix_bound
			l_pix_bound.push_back(std::make_pair(find_gx,find_gy));
			//mark reached
			int i_find_index = p_global_map_->g2i(find_gx,find_gy);
			m_reached_[i_find_index] = i;

			ori_gx = find_gx;
			ori_gy = find_gy;
		}

		////////////////////////////////
		//check go around
		//begin search 

		F32 cur_wx = 0;
		F32 cur_wy = 0;
		p_global_map_->grid2world(find_gx,find_gy,cur_wx,cur_wy);

		VecPosition vcur(cur_wx,cur_wy);
		vcur -= vori;
		F32 cur_angle = vcur.getDirection();
		cur_angle = VecPosition::angle_diff(Deg2Rad(begin_angle) , Deg2Rad(cur_angle));


		if ( i_search == 0)
		{
			if( fabs(cur_angle) > Deg2Rad(90)){
				i_search = 1;
			}
		}else if( i_search == 1 ){
			//if( fabs(cur_angle) <10){
			int cur_index = p_global_map_->g2i(find_gx,find_gy);
			if (cur_index == begin_index){
				i_search = 2;
				break;
			}
		}
	}

	if ( i_search == 2)
	{
		F32 wx = 0;
		F32 wy = 0;
		

		auto it = l_pix_bound.begin();
		for ( ; it != l_pix_bound.end(); ++it){

			p_global_map_->grid2world(it->first,it->second,wx,wy);

			SPos pos;
			pos.x_ = wx;
			pos.y_ = wy;
			pos.th_ = 0;
			rl_block.push_back(pos);
		}
		return true;
	}
	return false;

}
bool auto_cover::search_bound( std::list<SPos> &rl_block ,SPos &closest_pos , const SPos &pos , const std::vector<Sxy> &v_range_list){

	SPos tmp_pos;
	std::vector<SPos> l_block;
	if( !get_begin_pos(tmp_pos , pos , v_range_list)){
		return false;
	}

	closest_pos = tmp_pos;
	l_block.push_back(tmp_pos);
	int i_cloest_pos_index = 0;

	F32 min_dis = 1000;

	VecPosition vfirst;
	VecPosition vori; 
	Pos2Vec( vfirst, tmp_pos);
	Pos2Vec( vori, pos);
	F32 ori_angle = (vfirst - vori).getDirection();

	SPos search_pos = tmp_pos;
	int i_search = 0;
	//std::cout<<"search_pos x:"<<search_pos.x_<<" y:"<<search_pos.y_<<" th:"<<search_pos.th_<<std::endl;
	for (int i = 0; i < map_obs_size_*2 ; ++i )
	{
		if( !search_close_to_wall(search_pos,tmp_pos,0.23) ){
			break;
		}
		//std::cout<<"search_pos index:"<<i<<" x:"<<search_pos.x_<<" y:"<<search_pos.y_<<" th:"<<search_pos.th_<<std::endl;
		tmp_pos = search_pos ;
		l_block.push_back(tmp_pos);
		
		VecPosition vcur; 
		Pos2Vec( vcur, tmp_pos);
		vcur -= vori;
		F32 cur_angle = vcur.getDirection();
		cur_angle = VecPosition::angle_diff(Deg2Rad(ori_angle) , Deg2Rad(cur_angle));

		//std::cout<<"cur_angle:"<<Rad2Deg(cur_angle)<<std::endl;

		if(vcur.getMagnitude() < min_dis){
			min_dis = vcur.getMagnitude();
			closest_pos = tmp_pos;
			i_cloest_pos_index = l_block.size() -1;
		}
		//std::cout<<"ser inde:"<<i<<" angle_diff:"<<cur_angle<<" c x:"<<closest_pos.x_<<" "<<closest_pos.y_<<" "<<closest_pos.th_<<std::endl;
		
		//begin search 
		if ( i_search == 0)
		{
			if( fabs(cur_angle) > Deg2Rad(90)){
				i_search = 1;
			}
		}else if( i_search == 1 ){
			//if( fabs(cur_angle) <10){
			Pos2Vec( vcur, tmp_pos);
			vcur -= vfirst;
			std::cout<<"fx:"<<vfirst.getX()<<" fy:"<<vfirst.getY()<<" cx:"<<tmp_pos.x_<<" cy:"<<tmp_pos.y_<<std::endl;
			//if( (vcur.getMagnitude() < 0.1) && (fabs(cur_angle) < Deg2Rad(5))){
			std::cout<<"dis:"<<vcur.getMagnitude()<<std::endl;
			if( vcur.getMagnitude() < 0.1){
				i_search = 2;
				break;
			}
		}
	}

	if ( i_search == 2)
	{
 		std::vector<SPos>::iterator it = l_block.begin() + i_cloest_pos_index;
 		if ( it != l_block.end())
 		{
 			rl_block.insert(rl_block.end(),it,l_block.end());
 			rl_block.insert(rl_block.end(),l_block.begin(),it);
 		}
		//rl_block.insert(rl_block.end(),l_block.begin(),l_block.end());
		return true;
	}
	return false;
}

void auto_cover::draw_range_line( const Sxy &p1 , const Sxy &p2 )
{
	VecPosition v1(p1.x_,p1.y_);
	VecPosition v2(p2.x_,p2.y_);

	VecPosition v12 = v2 - v1;
	int icount = v12.getMagnitude() / 0.05;
	v12 = VecPosition( 0.05 ,v12.getDirection(),POLAR);


	for ( int i = 1; i < icount ; ++i )
	{
		v2 = v1 + v12 * i;
		p_tmp_map_->setgrid( F32(v2.getX()), F32(v2.getY()), MAP_OCCUPY_MAX);
	}
}

VecPosition auto_cover::get_vecfromline(  VecPosition &vec, const SPos &r, const Sxy &p1 , const Sxy &p2 )
{
	VecPosition v1(p1.x_,p1.y_);
	VecPosition v2(p2.x_,p2.y_);
	VecPosition v3(r.x_,r.y_);

	Line ln = Line::makeLineFromTwoPoints(v1,v2);
	VecPosition vtmp = ln.getPointOnLineClosestTo(v3);
	v3 = vtmp - v3;

	if ( v3.getMagnitude() < vec.getMagnitude())
	{
		vec = v3;
	}

	return v3;
}

//start pos must be in empty
//find empty pos close to Obstacle

bool auto_cover::searchEmpty(SPos &find_pos, SPos begin_pos, const std::vector<Sxy> &v_range_list)
{
	VecPosition vbegin;
	F32 angle_rad ;
	angle_rad = Pos2Vec(vbegin, begin_pos);
	return searchEmpty(find_pos , vbegin , angle_rad, v_range_list);
}

//start pos must be in empty
//find empty pos close to Obstacle
bool auto_cover::searchEmpty(SPos &find_pos, VecPosition vec, const F32 &angle_rad ,const std::vector<Sxy> &v_range_list)
{
	bool b_find = false;

	Vec2Pos(find_pos,vec,angle_rad);

	VecPosition v_step( road_width_ / 2 ,Rad2Deg(angle_rad) ,POLAR);
	S8 value = MAP_EMPTY;
	bool b_get_end = false;
	VecPosition vec_begin = vec;
	while ( ( v_range_list.size() > 0 ) ? block_path::posInRange(vec , v_range_list) : p_tmp_map_->check_valid(F32(vec.getX()), F32(vec.getY())))
	{

		value = getValue(vec);
		//search obstacle value
		if ( value > 0 && value <= MAP_OCCUPY_MAX)
		{
			b_get_end = true;
			
		}else if( value == MAP_EMPTY ){
			//find empty break;
			if (b_get_end)
			{
				b_find = true;
				break;
			}
		}
		//find obs and go back
		if( b_get_end )
		{
			v_step = VecPosition(0.05,VecPosition::normalizeAngle( Rad2Deg(angle_rad) + 180 ),POLAR);
		}
		//put_show_list(vec);
		vec += v_step;
		
	}

	if(b_find){
		find_pos.x_ = vec.getX();
		find_pos.y_ = vec.getY();
		vec -= vec_begin;
		find_pos.th_ = Deg2Rad(vec.getDirection());
	}
	
	
	return b_find;

	
}
//start pos must be in obstacle
//find obstacle pos close to empty
bool auto_cover::searchObstacle( SPos &find_pos, SPos begin_pos , const std::vector<Sxy> &v_range_list )
{
	VecPosition vbegin;
	F32 angle_rad ;
	angle_rad = Pos2Vec(vbegin, begin_pos);
	return searchObstacle(find_pos , vbegin , angle_rad, v_range_list);
}

//start pos must be in obstacle
//find obstacle pos close to empty
bool auto_cover::searchObstacle( SPos &find_pos, VecPosition vec,const F32 &angle_rad , const std::vector<Sxy> &v_range_list)
{
	bool b_find = false;

	VecPosition v_step(road_width_,angle_rad,POLAR);
	S8 value = MAP_EMPTY;

	bool b_get_end = false;
	VecPosition vec_begin = vec;
	while ( ( v_range_list.size() > 0 ) ? block_path::posInRange(vec , v_range_list) : p_tmp_map_->check_valid(F32(vec.getX()), F32(vec.getY())))
	{

		value = getValue(vec);

		//search empty value
		if (value == MAP_EMPTY)
		{
			b_get_end = true;

		}else if( value > 0 && value <= MAP_OCCUPY_MAX ){
			//find obstacle break;
			if (b_get_end)
			{
				break;
			}
		}
		//find empty and go back
		if( b_get_end )
		{
			v_step = VecPosition(0.05,VecPosition::normalizeAngle( Rad2Deg(angle_rad) + 180 ),POLAR);
		}
		//put_show_list(vec);
		vec += v_step;

	}


	if(b_find){
		find_pos.x_ = vec.getX();
		find_pos.y_ = vec.getY();
		vec -= vec_begin;
		find_pos.th_ = Deg2Rad(vec.getDirection());
	}

	return b_find;

}



void auto_cover::put_show_list( const VecPosition &vec )
{
	Sxy xy;
	xy.x_ = vec.getX();
	xy.y_ = vec.getY();
	show_pos_list_.push_back(xy);
}

void auto_cover::put_show_list( const SPos &pos )
{
	VecPosition vec;
	Pos2Vec( vec , pos );
	put_show_list(vec);
}

std::vector<Sxy> auto_cover::get_show_list()
{
	return show_pos_list_;
}

std::vector<segment_inline> auto_cover::get_seg_ln()
{
	return seg_line_all_;
}

bool auto_cover::get_begin_pos( SPos &pos_begin ,const SPos &robot_pos, const std::vector<Sxy> &v_range_list)
{
	std::vector<Sxy>::const_iterator cit = v_range_list.cbegin();
	F32 angle = Rad2Deg( robot_pos.th_ );
	if ( cit != v_range_list.cend() )
	{
		Sxy p_front = *cit;

		VecPosition vtarget( 1000, 0 );

		//search angle to the closest line
		for ( ; cit != v_range_list.cend() ; ++cit )
		{

			if (cit != v_range_list.cbegin() )
			{
				get_vecfromline ( vtarget , robot_pos , p_front , *cit);
				p_front = *cit;
			}
		}
		angle = vtarget.getDirection();
	}
	angle = Deg2Rad(angle);
	return searchEmpty( pos_begin, VecPosition(robot_pos.x_,robot_pos.y_) , angle , v_range_list);

}
SPos auto_cover::get_line_start_pos( const SPos &pos_begin,  std::vector<Sxy> v_range_list ){
	
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
	
	searchEmpty(start_pos,start_pos,v_range_list);

	return start_pos;
}
int auto_cover::create_pos_on_clean_line( std::map<F32,SPos> &m_pos_on_line, const SPos &pos_begin,  std::vector<Sxy> v_range_list ){
	
	m_pos_on_line.clear();
	SPos start_pos = get_line_start_pos( pos_begin, v_range_list);

	VecPosition vec(start_pos.x_,start_pos.y_);
	VecPosition v_step(road_width_,Rad2Deg(start_pos.th_),POLAR);
	VecPosition vec_drop;
	
	for (int i = 0  ; i < map_obs_size_ ; ++i )
	{

		vec_drop = vec + v_step * i;
		F32 dis = (vec_drop - vec).getMagnitude();
		
		if (block_path::posInRange( vec_drop, v_range_list))
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

void auto_cover::slice_map( segment_inline &seg_line_list, const SPos &pos_begin, const std::vector<Sxy> &v_range_list )
{

	//1 create slice line para
	std::map<F32,SPos> pos_on_line;
	create_pos_on_clean_line( pos_on_line , pos_begin , v_range_list);


// 	for (int i = 0 ; i < 10000; i++)
// 	{
// 
// 		vec_drop = vec + v_step * i;
// 		F32 dis = (vec_drop - vec).getMagnitude();
// 		SPos pos;
// 		pos.x_ = vec_drop.getX();
// 		pos.y_ = vec_drop.getY();
// 		pos.th_ = pos_begin.th_;
// 		if (posInRange(vec_drop))
// 		{
// 			m_pos_on_line[dis] = pos;
// 		}else{
// 			break;
// 		}
// 		
// 	}
// 
// 
// 	v_step = VecPosition(road_width_, (pos_begin.th_ + 180 ),POLAR);
// 	for (int i = 1 ; i < 10000; i++)
// 	{
// 
// 		vec_drop = vec + v_step * i;
// 		F32 dis = (vec_drop - vec).getMagnitude();
// 		SPos pos;
// 		pos.x_ = vec_drop.getX();
// 		pos.y_ = vec_drop.getY();
// 		pos.th_ = pos_begin.th_;
// 		if (posInRange(vec_drop))
// 		{
// 			m_pos_on_line[-dis] = pos;
// 		}else{
// 			break;
// 		}
// 	}

	//2 create slice segment
	

}

void auto_cover::set_border(Sxy xy)
{
	max_x_ = cComm::Max(xy.x_,max_x_);
	max_y_ = cComm::Max(xy.y_,max_y_);

	min_x_ = cComm::Min(xy.x_,min_x_);
	min_y_ = cComm::Min(xy.y_,min_y_);
}

// {
// 	std::map<F32,SPos>::iterator it = m_pos_on_line.begin();
// 	for ( ; it != m_pos_on_line.end() ; ++it )
// 	{
// 		std::list<vec_value> v_vec_value;
// 
// 		VecPosition vec_drop ;
// 		SPos &mid_pos(it->second);
// 		vec_drop = VecPosition(mid_pos.x_,mid_pos.y_);
// 
// 		//from positive angle
// 		while (posInRange(vec_drop)){
// 
// 			S8 value = getValue(vec_drop);
// 			if ( value != MAP_UNKNOWN )
// 			{
// 				vec_value v;
// 				v.pos_ = vec_drop;
// 				v.value_ = value;
// 				v.angle_ = mid_pos.th_;
// 				v_vec_value.push_back(v);
// 			}
// 
// 			vec_drop += VecPosition( road_width_ / 2 , VecPosition::normalizeAngle(mid_pos.th_ + 90) , POLAR);  
// 		}
// 
// 		//from negative angle
// 		vec_drop = VecPosition(mid_pos.x_,mid_pos.y_) + VecPosition( road_width_ / 2 , VecPosition::normalizeAngle(mid_pos.th_ - 90) , POLAR); 
// 		while (posInRange(vec_drop)){
// 			S8 value = getValue(vec_drop);
// 			if ( value != MAP_UNKNOWN )
// 			{
// 				vec_value v;
// 				v.pos_ = vec_drop;
// 				v.value_ = value;
// 				v.angle_ = mid_pos.th_;
// 				v_vec_value.push_front(v);
// 			}
// 			vec_drop += VecPosition( road_width_ / 2 ,VecPosition::normalizeAngle(mid_pos.th_ - 90) , POLAR); 
// 		}
// 		//del same value
// 		S8 last_value = MAP_ERR;
// 		std::list<vec_value>::iterator it = v_vec_value.begin();
// 		std::vector<vec_value> v_for_search;
// 		for ( ; it !=  v_vec_value.end() ; ++it )
// 		{
// 			vec_value &tmp(*it);
// 			if ( (last_value != 0) && ( tmp.value_ == 0)  )
// 			{
// 				v_for_search.push_back(*it);
// 			}
// 			last_value = tmp.value_;
// 			std::cout<<"pox x:"<<tmp.pos_.getX()<<" y:"<<tmp.pos_.getY()<<" value:"<<int(tmp.value_)<<std::endl;
// 		}
// 		//create segment from empty pos
// 		std::vector<vec_value>::iterator it2 = v_for_search.begin();
// 		segment_inline v_seg_inline;
// 		for ( ; it2 != v_for_search.end() ; ++it2 )
// 		{
// 			vec_value &tmp(*it2);
// 			SPos s_from = searchEmpty(tmp.pos_,VecPosition::normalizeAngle( tmp.angle_ + 90));
// 			SPos s_to = searchEmpty(tmp.pos_,VecPosition::normalizeAngle( tmp.angle_ - 90));
// 			SSegment seg;
// 			seg.p1_ = VecPosition(s_from.x_,s_from.y_);
// 			seg.p2_ = VecPosition(s_to.x_,s_to.y_);
// 
// 			v_seg_inline.put(seg);
// 		}
// 		if (v_seg_inline.from_to_list_.size())
// 		{
// 			all_seg_line_list_.push_back(v_seg_inline);
// 		}
// 
// 	}
// 
// 	std::vector<segment_inline>::iterator it3 = all_seg_line_list_.begin();
// 	for ( ; it3 != all_seg_line_list_.end(); ++it3 )
// 	{
// 		segment_inline &seg_line(*it3);
// 		std::vector<SSegment>::iterator it = seg_line.from_to_list_.begin();
// 		for ( ; it != seg_line.from_to_list_.end() ; ++it )
// 		{
// 			put_show_seg(*it);
// 		}
// 
// 	}
// }

// SPos auto_cover::searchValue( VecPosition vec,const F32 &angle,const S8 &p_value,const bool &b_greater )
// {
// 	S8 value = MAP_EMPTY;
// 	S8 g_value = MAP_EMPTY;
// 
// 	while (posInRange(vec)){
// 		p_tmp_map_->getgtid( F32(vec.getX()), F32(vec.getY()), value);
// 		p_global_map_->getgtid( F32(vec.getX()), F32(vec.getY()), g_value);
// 		g_value += value;
// 		if (b_greater)
// 		{
// 			if(g_value >= p_value){
// 				break;
// 			}
// 		}else{
// 			if(g_value <= p_value){
// 				break;
// 			}
// 		}
// 		vec += VecPosition(0.05,angle,POLAR);
// 	}
// 	SPos pos;
// 	pos.x_ = vec.getX();
// 	pos.y_ = vec.getY();
// 	pos.th_ = angle;
// 	return pos;
// 
// }
S8 auto_cover::fast_getValue(const U32 &gx,const U32 &gy ){
	int index = p_global_map_->g2i(gx,gy);
	std::map<int,int>::iterator it =  m_value_.find(index);
	if (it != m_value_.end()){
		return it->second;
	}else{
		S8 value = getValue(gx,gy);
		m_value_[index] = value;
		return value;
	}
}

S8 auto_cover::fast_getValue( const VecPosition &vec )
{
	U32 gx = 0;
	U32 gy = 0;
	p_tmp_map_->world2grid(vec.getX(),vec.getY(),gx,gy);

	return fast_getValue(gx,gy);
}

S8 auto_cover::getValue(const U32 &gx,const U32 &gy )
{
	S8 value = MAP_EMPTY;
	S8 g_value = MAP_EMPTY;

	p_tmp_map_->getgrid( gx, gy, value);

	p_global_map_->getgrid( gx, gy, g_value);

	//std::cout<<"g_value:"<<int(g_value)<<" value:"<<int(value)<<std::endl;
	//if err
	if ( g_value < 0 )
	{
		return g_value;
	}
	if ( value < 0)
	{
		return value;
	}

	if( g_value <  value) {
		g_value = value;
	}
	//std::cout<<"final value:"<<int(g_value)<<std::endl;

	return g_value;
}
S8 auto_cover::getValue( const VecPosition &vec )
{
	S8 value = MAP_EMPTY;
	S8 g_value = MAP_EMPTY;

	p_tmp_map_->getgrid( F32(vec.getX()), F32(vec.getY()), value);

	p_global_map_->getgrid( F32(vec.getX()), F32(vec.getY()), g_value);

	//std::cout<<"g_value:"<<int(g_value)<<" value:"<<int(value)<<std::endl;
	//if err
	if ( g_value < 0 )
	{
		return g_value;
	}
	if ( value < 0)
	{
		return value;
	}

	if( g_value <  value) {
		g_value = value;
	}
	//std::cout<<"final value:"<<int(g_value)<<std::endl;

	return g_value;
}

S8 auto_cover::getValue( const SPos &pos )
{
	VecPosition vec(0,0);
	Pos2Vec(vec,pos);
	return getValue(vec);
}

std::vector<Sxy> auto_cover::get_border()
{
	std::vector<Sxy> map_border;
	Sxy xy;
	xy.x_ = min_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top left

	xy.x_ = max_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top right

	xy.x_ = max_x_;
	xy.y_ = min_y_;
	map_border.push_back(xy);// bottom right

	xy.x_ = min_x_;
	xy.y_ = min_y_;
	map_border.push_back(xy);// bottom left

	xy.x_ = min_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top left
	return map_border;
}

void auto_cover::put_show_seg( SSegment seg )
{
	VecPosition step = seg.p1_ - seg.p2_;
	int icount = step.getMagnitude() / 0.05;
	step /= icount;
	VecPosition tmp = seg.p2_;
	for ( int i = 0 ; i < icount ; ++i)
	{
		tmp += step;
		put_show_list(tmp);
	}
}

// void auto_cover::VecP2SPos( SPos &spos, const VecPosition &vec,const F32 &angle )
// {
// 	spos.x_ = vec.getX();
// 	spos.y_ = vec.getY();
// 	spos.th_ = angle;
// }

// F32 auto_cover::SPos2VecP( VecPosition &vec, const SPos &spos )
// {
// 	vec = VecPosition(spos.x_,spos.y_);
// 	return spos.th_;
// }

bool auto_cover::rot_search_empty(SPos &target_pos, SPos ori_pos , const F32 &dis,const bool &b_empty){


	S8 value = getValue(ori_pos);
	target_pos = ori_pos;
	if ( value < 0 )
	{
		return false;
	}
	
	
	VecPosition vori;
	F32 rad_angle = Pos2Vec(vori , ori_pos);

	S8 v = 0 ;
	F32 min_angle = 3;
	int idir = -1;
	int index = 0;

	F32 angle = rad_angle;

	int isearch_count = 360 / min_angle + 3;
	for (int i = 0 ; i < isearch_count ; ++i)
	{
		//add diff angle
		angle = Rad2Deg(rad_angle) + idir*index*min_angle;
		angle = VecPosition::normalizeAngle(angle);
		
		//change direction,and index++ when direction < 0
		if ( idir*index < 0)
		{
			index ++;
		}
		idir*=-1;
		if( index == 0){
			index ++;
		}
		//get value 
		VecPosition vdis(dis, angle, POLAR);
		vdis = vori + vdis;
		//set default value

		S8 v = getValue(vdis);
		//put_show_list(vdis);


		if (b_empty)
		{
			if ( v == 0 )
			{
				Vec2Pos(target_pos, vdis, Deg2Rad(angle));
				return true;
			}
		}else{
			if ( v != 0 )
			{
				Vec2Pos(target_pos, vdis, Deg2Rad(angle));
				return true;
			}
		}
		
	}

	return false;
}

bool auto_cover::search_close_to_wall( SPos &target_pos , SPos ori_pos , const F32 &dis )
{
	target_pos = ori_pos;
	//search no empty pos
	F32 search_dis = dis / 2;
	int b_find = false;
	for (int i = 0 ; i < 10000 ; ++i )
	{
		if(!rot_search_empty(target_pos,ori_pos,search_dis,false) )
		{
			std::cout<<"search_close_to_wall is all clear!index:"<<i<<" dis:"<<search_dis<<std::endl;
			search_dis += dis / 2;
			if(search_dis > p_tmp_map_->Get_width()){
				std::cout<<"search_close_to_wall 'search_dis' out of map size"<<std::endl;
				break;
			}
		}else
		{
			b_find = true;
			break;
		}
	}
	if ( !b_find )
	{
		return false;
	}

	b_find = false;
	ori_pos.th_ = target_pos.th_;
	search_dis = dis / 2;
	for ( int i = 0 ; i < 10000 ; ++i )
	{
		if (!rot_search_empty(target_pos,ori_pos,search_dis,true))
		{
			std::cout<<"search_close_to_wall is all obs!"<<i<<" dis:"<<search_dis<<std::endl;
			search_dis += dis / 2;
			if(search_dis > p_tmp_map_->Get_width()){
				std::cout<<"search_close_to_wall 'search_dis' out of map size"<<std::endl;
				break;
			}
		}else{
			b_find = true;
			break;
		}
	}
	if (!b_find)
	{
		return false;
	}
	return true;
}









