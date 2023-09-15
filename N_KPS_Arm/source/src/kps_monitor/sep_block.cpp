#include <iostream>

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "robot/vec2pos.hpp"

#include "mapserver/GridMap.h"
#include "mapserver/MapServer.h"
#include "pca.h"

#include "sep_block.h"



separate_block::separate_block()
{
	i_min_id_diff_ = 50;
	f_choke_dis_ = 0.5;

	octree_ = 0;

	p_forbidden_map_ = 0;
	p_global_map_ = 0;
}

separate_block::~separate_block()
{

}
//step 1: init map <id,pos>
//step 2: init qt tree
//step 3: get from map head and search qt tree
//        when close to id(id diff < 200) remove
//        when diff > 200 maybe choke point
//step 4: search min choke point
//stet 5: separate block
int separate_block::do_separate_block(std::vector< std::list<SPos> > &l_block_list , const std::list<SPos> &l_block)
{
	//step 1: init map <id,pos>
	init_map(l_block);

	//step 2: init qt tree
	//m_id_pos_ input
	init_qt_tree();

	//step 3:
	search_choke_point();

	//step 4:
	create_separate_block(l_block_list);

	return l_block_list.size();
}

int separate_block::do_separate_block( std::list<area> &l_area_list, const std::list<SPos> &l_block )
{
	//step 1: init map <id,pos>
	init_map(l_block);

	//step 2: init qt tree
	//m_id_pos_ input
	init_qt_tree();

	//step 3:
	search_choke_point();

	//step 4:
	create_separate_block(l_area_list);

	return l_area_list.size();
}

void separate_block::init_map(const std::list<SPos> &l_block)
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

void separate_block::init_qt_tree()
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
//step 3: get from map head and search qt tree
//        when close to id(id diff < 200) remove
//        when diff > 200 maybe choke point
void separate_block::search_choke_point()
{	
	//clear output:vp_choke_point_
	vp_choke_point_.clear();
	std::vector<int> v_choke_pf;
	std::vector<int> v_choke_pt;

	//bbx
	octomap::OcTreeKey bbxMinKey, bbxMaxKey;

	std::map<int,SPos>::iterator it = m_id_pos_.begin();
	for ( ; it != m_id_pos_.end() ; ++it){

		octomap::point3d bbxMin(it->second.x_ - f_choke_dis_, it->second.y_ - f_choke_dis_, - 1.0);
		octomap::point3d bbxMax(it->second.x_ + f_choke_dis_, it->second.y_ + f_choke_dis_, float(m_id_pos_.size()));

		octree_->coordToKeyChecked(bbxMin, bbxMinKey);
		octree_->coordToKeyChecked(bbxMax, bbxMaxKey);

		//sort by id
		std::map<int,int> m_tmp;
		for(octomap::OcTree::leaf_bbx_iterator it = octree_->begin_leafs_bbx(bbxMinKey,bbxMaxKey), end = octree_->end_leafs_bbx();
			it!= end; ++it)
		{
			octomap::OcTreeKey currentKey = it.getKey();
			assert(!octree_->nodeHasChildren(&(*it)));
			octomap::point3d b = octree_->keyToCoord(currentKey);

			m_tmp[int(b(2))] = 0;

// 			SPos spf = m_id_pos_.find((*it2).second)->second;
// 			std::cout<<"p x:"<<spf.x_<<" "<<spf.y_<<std::endl;
		}

		
		//check id diff > 50
		int last_id  = -1;
		std::map<int,int>::iterator it3 = m_tmp.begin();
		for ( ; it3 != m_tmp.end(); ++it3){

			if (last_id == -1){
				last_id = it3->first;
			}else{

				int cur_id = it3->first;

				if (  (cur_id > (m_id_pos_.size() - i_min_id_diff_ )) && (last_id < i_min_id_diff_) ){
					last_id += m_id_pos_.size();
				}

				if ( abs(  cur_id - last_id) > i_min_id_diff_){
					if (last_id >= m_id_pos_.size()){
						last_id -= m_id_pos_.size();
					}
					
					v_choke_pf.push_back(last_id);
					v_choke_pt.push_back(cur_id);
					
				}
				last_id = it3->first;
			}
		}
	}

	
	std::vector<int>::iterator it1 = v_choke_pf.begin();
	std::vector<int>::iterator it2 = v_choke_pt.begin();
	for ( ; it1 != v_choke_pf.end(); ++it1){
		for ( ; it2 != v_choke_pt.end(); ++it2){
			SPos pf = m_id_pos_[*it1];
			SPos pt = m_id_pos_[*it2];

			VecPosition v1(pf.x_,pf.y_);
			VecPosition v2(pt.x_,pt.y_);

			VecPosition v12 = v2 - v1;
			if ( v12.getMagnitude() > f_choke_dis_){
				break;
			}

			int icount = v12.getMagnitude() / 0.05;
			v12 /= icount;
			VecPosition tmp = v1;

			bool b_unreachable = false;
			for ( int i = 0 ; i < icount ; ++i){
				tmp += v12;

				S8 value = MAP_UNKNOWN;
				p_forbidden_map_->getgrid(F32(tmp.getX()),F32(tmp.getY()),value);
				if (value != MAP_EMPTY){
					b_unreachable = true;
					break;
				}
				p_global_map_->getgrid(F32(tmp.getX()),F32(tmp.getY()),value);
				if (value != MAP_EMPTY){
					b_unreachable = true;
					break;
				}
			}
			if (!b_unreachable){
				vp_choke_point_.push_back(std::make_pair(*it1,*it2));
			}

		}
	}

	//merge close choke point
	std::list<std::pair<int,int>>::iterator it4 = vp_choke_point_.begin();
	std::list<std::pair<int,int>>::iterator it5 = vp_choke_point_.begin();
	for ( ; it4 != vp_choke_point_.end(); ++it4 ){
		it5 = it4;
		it5++;
		for ( ; it5 != vp_choke_point_.end();  ){

			if ( ((abs( it4->first - it5->first) ) < 5 ) && ((abs( it4->second - it5->second) ) < 5)){
				it4->first = (it4->first + it5->first)/2;
				it4->second = (it4->second + it5->second)/2;
				it5 = vp_choke_point_.erase(it5);
			}else{
				//vp_choke_point_.push_back(*it4);
				it5++;
			}
		}
		
	}
}

std::list<std::pair<Sxy,Sxy>> separate_block::get_sep_line()
{
	std::list<std::pair<Sxy,Sxy>> vsxy;

	std::list<std::pair<int,int>>::iterator it = vp_choke_point_.begin();
	for ( ; it != vp_choke_point_.end() ; ++it ){
		SPos spf = m_id_pos_.find((*it).second)->second;
		SPos spt = m_id_pos_.find((*it).first)->second;
		Sxy sf;
		Sxy st;
		sf.x_ = spf.x_;
		sf.y_ = spf.y_;
		st.x_ = spt.x_;
		st.y_ = spt.y_;
		//std::cout<<"id f:"<<(*it).first<<" id t:"<<(*it).second<<std::endl;
		std::cout<<"id fa:"<<sf.x_<<" "<<sf.y_<<std::endl;
		std::cout<<  " ft:"<<st.x_<<" "<<st.y_<<std::endl;

		vsxy.push_back(std::make_pair(sf,st));

	}
	return vsxy;
}

void separate_block::init( GridMap* p_forbidden_map,GridMap* p_global_map )
{
	p_forbidden_map_ = p_forbidden_map;
	p_global_map_ = p_global_map;
}

void separate_block::create_separate_block(std::vector< std::list<SPos> > &l_block_list)
{
	int i_frist_sep_id = -1;
	int i_last_sep_id = -1;
	std::list<std::pair<int,int>>::iterator it = vp_choke_point_.begin();
	for ( ; it != vp_choke_point_.end(); ++it ){
		int i_from = cComm::Min(it->first,it->second);
		int i_to = cComm::Max(it->first,it->second);
		
		std::list<SPos> l_block;

		if (i_last_sep_id != -1){
			for ( int i = i_last_sep_id; i < i_from ; ++i ){
				SPos pos = m_id_pos_[i];
				l_block.push_back(pos);
			}
			
		}
		if (l_block.size()){
			l_block_list.push_back(l_block);
			l_block.clear();
		}
		

		for ( int i = i_from; i < i_to ; ++i ){
	
			SPos pos = m_id_pos_[i];
			l_block.push_back(pos);

			if (i_frist_sep_id == -1){
				i_frist_sep_id = i;
			}
			
		}

		i_last_sep_id = i_to;

		if (l_block.size()){
			l_block_list.push_back(l_block);
			l_block.clear();
		}
		

	}
	std::list<SPos> l_block;
	for ( int i = i_last_sep_id; i < m_id_pos_.size() ; ++i ){
		SPos pos = m_id_pos_[i];
		l_block.push_back(pos);
	}
	for ( int i = 0; i < i_frist_sep_id ; ++i ){
		SPos pos = m_id_pos_[i];
		l_block.push_back(pos);
	}
	if (l_block.size()){
		l_block_list.push_back(l_block);
	}
}

void separate_block::create_separate_block( std::list<area> &l_area_list )
{
	int i_frist_sep_id = -1;
	int i_last_sep_id = -1;
	std::list<std::pair<int,int>>::iterator it = vp_choke_point_.begin();
	for ( ; it != vp_choke_point_.end(); ++it ){
		int i_from = cComm::Min(it->first,it->second);
		int i_to = cComm::Max(it->first,it->second);


		area ar;
		SPos from_pos = m_id_pos_[i_from];
		SPos to_pos = m_id_pos_[i_to];

		for ( int i = i_from; i < i_to ; ++i ){

			SPos pos = m_id_pos_[i];
			ar.put_point(pos);
			m_id_pos_.erase(i);
		}
		

		ar.outlet_.push_back(std::make_pair(from_pos,to_pos));
		l_area_list.push_back(ar);
	}

	area ar;

	VecPosition vfrom;
	VecPosition vto;
	auto it2 = m_id_pos_.begin();
	auto it_last = m_id_pos_.end();

	for ( ; it2 != m_id_pos_.end() ; ++it2 ){

		
		ar.put_point(it2->second);
		//first ignore
		if (it_last == m_id_pos_.end()){
			it_last = it2;
			continue;
		}
		//continue id ignore
		if ( abs( it_last->first - it2->first) == 1){
			it_last = it2;
			continue;
		}
		//dis < 2m is outlet
		Pos2Vec(vfrom,it_last->second);
		Pos2Vec(vto,it2->second);
		VecPosition v = vfrom - vto;
		if ( v.getMagnitude() < 2.0/* 2m */ ){
			ar.outlet_.push_back(std::make_pair(it_last->second,it2->second));
		}
		it_last = it2;
	}
	l_area_list.push_back(ar);
}

