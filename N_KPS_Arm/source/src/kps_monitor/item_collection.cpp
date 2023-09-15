#include <iostream>

#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QObject>





#define SIM_PATH_ITEM "sim_path_item"

#include "Comm/Comm.h"
#include "scene/item_define.h"
#include "kps_main_win.h"
#include "mapserver/map_def.h"
#include "scene/map_scene.h"
#include "scene/map_item.h"
#include "scene/robot_item.h"
#include "scene/map_view.h"

#include "interface/xml_rpc_client.h"
#include "robot/robot_remote_para.h"
#include "project/project_manage.h"

//item
#include "scene/map_item.h"
#include "scene/particle_item.h"
#include "scene/bag_item.h"
#include "scene/range_item.h"
#include "scene/reflector_item.h"
#include "scene/lab_item.h"
#include "scene/view_data_item.h"
#include "scene/node_item.h"
#include "scene/edge_item.h"
#include "scene/producer_item.h"
#include "scene/consumer_item.h"
#include "scene/processer_item.h"
#include "scene/storage_item.h"
#include "scene/charge_item.h"
#include "scene/rect_item.h"
#include "scene/qrcode_item.h"
//#include "scene/control_item.h"
#include "opencv_cus/subdiv.h"

#include "item_collection.h"




item_collection::item_collection()
{
	main_win_ = 0;
	i_max_bag_item_ = 3000;
	i_current_index_ = 0;

	new_range_nm_ = "";
//	select_pro_nm_ = "";

	b_show_ex_reflector_ = false;
	b_show_laser_ = true;
	b_show_particles_ = true;

	i_laser_ori_cab_ = 0;

	tmp_line_item_ = 0;

	p_sel_rect_ = 0;
}

item_collection::~item_collection()
{

}

void item_collection::init( kps_main_win* main_win )
{
	main_win_ = main_win;
}

void item_collection::remove_all_item()
{
	main_win_->get_scene()->del_all();
}

void item_collection::show_map_rect()
{
	map_item*  p_map_item = get_map_item();

	p_map_item->update();
}

void item_collection::show_map_item( const std::vector<int> &v_data )
{

	map_item*  p_map_item = get_map_item();

	p_map_item->set_map_value(v_data);
	p_map_item->update();
}

void item_collection::show_map_item( const std::vector<Sxy> &v_data )
{
	map_item*  p_map_item = get_map_item();

	p_map_item->set_map_value(v_data);
}

void item_collection::save_map( std::string map_nm )
{
	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		p_map_item->save_map(map_nm);
	}
}

bool item_collection::open_map( std::string map_nm )
{
	main_win_->get_scene()->del_item(MAP_ITEM);

	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		return p_map_item->open_map(map_nm);
	}
}

void item_collection::download_map( std::vector<int> &v_data )
{

	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		p_map_item->download_map(v_data);
	}
}

map_item* item_collection::get_map_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,MAP_ITEM);

	map_item*  p_map_item = static_cast<map_item*>(qi);

	if (!p_map_item)
	{
		p_map_item = new map_item();
		main_win_->get_scene()->add_item( MAP_ITEM , (QGraphicsItem*)p_map_item);
	}

	return p_map_item;
}

void item_collection::set_robot_est( qt_eve::mouse_event::SLocal_ev event )
{
	robot_item* p_robot = get_robot_item();
	if (p_robot)
	{
		if (event.LO_SHOW == event.show_set_)
		{
			p_robot->set_est_pos(event.target_pos_,true);
		}else{
			p_robot->set_est_pos(event.target_pos_,false);
		}
		p_robot->update();
	}
	
}

robot_item* item_collection::get_robot_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,ROBOT_ITEM);

	robot_item*  p_robot_item = static_cast<robot_item*>(qi);

	if (!p_robot_item)
	{
		p_robot_item = new robot_item();
		SLaser_para laser_para = Singleton_remote_para::get_mutable_instance().get_laser_para();
		p_robot_item->set_laser_para(laser_para);

		std::vector<SVec> v_robot_shape = Singleton_remote_para::get_mutable_instance().get_robot_shape();
		p_robot_item->set_robot_shape(v_robot_shape);

	
		main_win_->get_scene()->add_item( ROBOT_ITEM , (QGraphicsItem*)p_robot_item);
	}

	return p_robot_item;
}
particle_item* item_collection::get_particle_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,PARTICLE_ITEM);

	particle_item*  p_particle_item = static_cast<particle_item*>(qi);

	if (!p_particle_item)
	{
		p_particle_item = new particle_item();
		main_win_->get_scene()->add_item( PARTICLE_ITEM , (QGraphicsItem*)p_particle_item);
	}

	return p_particle_item;
}

void item_collection::show_particle_item( const std::vector<STriangle>& v_particles )
{
	particle_item* p_particle_item = get_particle_item();
	p_particle_item->update_particles(v_particles);
}

void item_collection::show_sim_path(const SPos& pos, const std::vector<STriangle>& v_path)
{
	particle_item* sim_path_it = get_sim_path_item();

	sim_path_it->update_particles(v_path);
}

void item_collection::show_reflector_list(const std::vector<SVec> &reflector_list, const bool &b_new /*= false*/)
{
	if (b_new)
	{
		main_win_->get_scene()->del_item(REFLECTOR_ITEM);
		main_win_->get_scene()->del_item(LAB_ITEM);
	}
	std::vector<SVec>::const_iterator cit = reflector_list.begin();
	for ( ; cit !=  reflector_list.end() ; ++cit )
	{
		get_new_reflector_item(cit->x_,cit->y_);
	}
	
}

void item_collection::show_reflector_list( const std::vector<SReflectorPos> &v_ref_pos )
{

	main_win_->get_scene()->del_item(REFLECTOR_ITEM);
	main_win_->get_scene()->del_item(LAB_ITEM);

	std::vector<SReflectorPos>::const_iterator cit = v_ref_pos.begin();
	for ( ; cit !=  v_ref_pos.end() ; ++cit )
	{
		reflector_item* p_reflector_item = get_new_reflector_item(cit->pos_.x_,cit->pos_.y_);
		
		lab_item* p_lab_item = get_new_lab_item(cit->pos_.x_,cit->pos_.y_);
		p_reflector_item->set_id(cit->id_);
		p_lab_item->set_id(cit->id_);

	}
}

bool item_collection::show_ex_reflector()
{
	b_show_ex_reflector_ = !b_show_ex_reflector_;
	return b_show_ex_reflector_;
}

void item_collection::time_event(bool b_online)
{
	bool b_reflash = false;

	SPos robot_pos;

	SPUB_BAG pub_bag;
	if(show_buf_list_.size()){
		show_buf_list_.get(pub_bag);
		show_bag_item(pub_bag);
		b_reflash = true;
	}

	SPUB_BAG_EX pub_bag_ex;
	if (show_ex_buf_list_.size()){
		show_ex_buf_list_.get(pub_bag_ex);
		show_bag_ex_item(pub_bag_ex);
		
		b_reflash = true;
	}
	
// 	{
// 		boost::mutex::scoped_lock lock(mu_mapping_list_);
// 		while ( show_mapping_list_.size() ){
// 			pub_bag_ex = show_mapping_list_.front();
// 			show_mapping_item(pub_bag_ex);
// 			show_mapping_list_.pop_front();
// 		}
// 	}


	//////////////////////////////////////////////////////////////////////////
	{//reflector for g2o mappint
		boost::mutex::scoped_lock lock(mu_reflector_);
		auto it = v_reflector_item_.begin();
		for ( ; it !=  v_reflector_item_.end() ; ++it ){
			reflector_item* p_reflector_item = *it;

			main_win_->get_scene()->add_item( REFLECTOR_ITEM , (QGraphicsItem*)(p_reflector_item));
//			std::cout<<"scene add mapping reflector!"<<p_reflector_item->get_id()<<" pos:"<<p_reflector_item->pos().x()<<" "<<p_reflector_item->pos().y()<<std::endl;
		}
		v_reflector_item_.clear();
	}

	main_win_->get_view()->update();

	if (!b_online){
		return;
	}

	robot_item* p_robot = get_robot_item();
	if (!p_robot)
	{
		return;
	}

	SPOS_CONFIDENCE pos_confi;
	pos_confi.confidence_.b_amcl_confidence_ = false;
	//if have reflector loc show robot in reflector pos
	if(Singleton_XML_Client::get_mutable_instance().get_reflector_pos(pos_confi) && (pos_confi.confidence_.b_amcl_confidence_)){
	//if(pos_confi.confidence_.b_amcl_confidence_){
		std::cout<<"ref pos conf:"<<pos_confi.confidence_.amcl_confidence_<<" x:"<<pos_confi.pos_.x_<<" "<<pos_confi.pos_.y_<<" "<<pos_confi.pos_.th_<<std::endl;
		
		if (v_ref_conf_.size()){
			v_ref_conf_.clear();
		}
		v_ref_conf_.push_back(pos_confi);

		p_robot->set_ref_pos(pos_confi.pos_);
		b_reflash = true;

		if(Singleton_XML_Client::get_mutable_instance().get_robot_pos(robot_pos)){
			
			p_robot->set_amcl_pos_ref(robot_pos);
			b_reflash = true;
		}	
	
	}else{
		//if only amcl pos
		if(Singleton_XML_Client::get_mutable_instance().get_robot_pos(robot_pos)){
// 			robot_pos.x_ = 0;
// 			robot_pos.y_ = 0;
// 			robot_pos.th_ = 0;
			std::cout<<"robot_pos x:"<<robot_pos.x_<<" "<<robot_pos.y_<<" "<<robot_pos.th_<<std::endl;
			p_robot->set_amcl_pos(robot_pos);
			b_reflash = true;
		}	
	}
		
	if(b_show_laser_){

		if(!b_show_ex_reflector_){
			//use amcl laser first
			SLaserXYEx laser_ex;
			if(Singleton_XML_Client::get_mutable_instance().get_sim_laser(laser_ex)){
				p_robot->set_laser(laser_ex);
				b_reflash = true;
				i_laser_ori_cab_ = 20;
			}else{//else use original laser
				if (i_laser_ori_cab_ > 0)
				{
					i_laser_ori_cab_--;
				}else{
					std::vector<SLaser_used> v_laser_data;
					if(Singleton_XML_Client::get_mutable_instance().get_laser(v_laser_data)){

						//if(Singleton_XML_Client::get_mutable_instance().get_ex_laser(v_laser_data)){
						p_robot->set_laser(v_laser_data);
						b_reflash = true;
					}
				}

			}



		}else{

			SLaser_Ex_Ref laser_ex_ref;
			if(Singleton_XML_Client::get_mutable_instance().get_pub_laser_ex_ref(laser_ex_ref)){
				p_robot->set_laser_ex_ref(laser_ex_ref);
				b_reflash = true;
			}
		}
	}else{
		std::vector<SLaser_used> v_laser_data;
		p_robot->set_laser(v_laser_data);
	}
	
	

	std::vector<Range_type> v_show_range_type;
	if (Singleton_XML_Client::get_mutable_instance().get_chk_laser_show(v_show_range_type)){
		p_robot->set_range_show(v_show_range_type);
		b_reflash = true;
	}
	
	//p_robot->set_range_show(v_show_range_type);

	SOdomSpeed odom;
	if(Singleton_XML_Client::get_mutable_instance().get_odom_speed(odom)){
		//std::cout<<"odom.vx_:"<<odom.vx_<<" odom.vw_:"<<odom.vw_<<std::endl;
	
		p_robot->set_speed(odom.vx_,odom.vy_,odom.vw_);
		b_reflash = true;

// 		robot_pos.x_ = odom.x_;
// 		robot_pos.y_ = odom.y_;
// 		robot_pos.th_ = odom.th_;
// 		p_robot->set_amcl_pos(robot_pos);
	}
	//

	if(!b_show_ex_reflector_){
		SReflector ref;
		if(Singleton_XML_Client::get_mutable_instance().get_scan_reflector(ref)){

			p_robot->set_scan_reflector(ref);
			b_reflash = true;
		}
	}
	
	
	if (b_show_particles_)
	{
		particle_item* p_particle_item = get_particle_item();
		std::vector<STriangle> v_particles;
		if(Singleton_XML_Client::get_mutable_instance().get_particles(v_particles)){

			p_particle_item->update_particles(v_particles);
			//std::cout<<"get v_particles size:"<<v_particles.size()<<std::endl;
			b_reflash = true;
		}
	}else{
		particle_item* p_particle_item = get_particle_item();
		std::vector<STriangle> v_particles;
		p_particle_item->update_particles(v_particles);
	}
	
 	

	
	if(Singleton_XML_Client::get_mutable_instance().get_pub_bag(pub_bag)){
		show_bag_item(pub_bag);
		b_reflash = true;
	}
	

	std::vector<STriangle> v_path;
	if(Singleton_XML_Client::get_mutable_instance().get_sim_path(v_path)){
		show_sim_path(robot_pos,v_path);
		b_reflash = true;
	}
	if (b_reflash)
	{
		p_robot->update();
	}
	std::vector<SView_Data> v_data;
	if(Singleton_XML_Client::get_mutable_instance().get_view_data(v_data)){

		show_view_data(v_data);
		std::vector<SView_Data>::iterator it = v_data.begin();
		for ( ; it != v_data.end() ; ++it ){
			delete[] it->uc_data_;
			it->uc_data_ = 0;
		}
	}

	
	
}
void item_collection::show_bag_item( const SPUB_BAG &pub_bag )
{
	boost::mutex::scoped_lock lock(mu_bag_);
	
	bag_item* p_bag_item = 0;
	if (v_bag_item_.size() < i_max_bag_item_)
	{
		p_bag_item = new bag_item();
		std::string str_nm = bag_item_id2str(v_bag_item_.size());
		main_win_->get_scene()->add_item( str_nm , (QGraphicsItem*)p_bag_item);
		v_bag_item_.push_back(p_bag_item);
		std::string str_robot_shape = pub_bag.robot_shape_;
		std::vector<SVec> v_robot_shape = robot_remote_para::get_robot_shape(str_robot_shape);
		p_bag_item->set_robot_shape(v_robot_shape);
		p_bag_item->set_laser_para(pub_bag.laser_para_);
	}else{

		p_bag_item = v_bag_item_[i_current_index_];
		
	}
	SPos odom;
	if (b_bag_odom_amcl_){
		odom.x_ = pub_bag.odom_.x_;
		odom.y_ = pub_bag.odom_.y_;
		odom.th_ = pub_bag.odom_.th_;
	}else{
		odom = pub_bag.amcl_pos_;
	}
	

// 	if( (fabs(odom.x_) + fabs(odom.y_) + fabs(odom.th_)) < 1e-3){
// 		odom.x_ = pub_bag.amcl_pos_.x_;
// 		odom.y_ = pub_bag.amcl_pos_.y_;
// 		odom.th_ = pub_bag.amcl_pos_.th_;
// 	}

	p_bag_item->set_odom_pos(odom);
	p_bag_item->set_laser(pub_bag.laser_,pub_bag.confidence_);
	p_bag_item->set_speed(pub_bag.odom_.vx_,pub_bag.odom_.vy_,pub_bag.odom_.vw_);

	i_current_index_++;
	i_current_index_ =  i_current_index_ % i_max_bag_item_;
}

int item_collection::bag_item_str2id( const std::string &str_nm )
{
	std::vector<std::string> vstr;
	cComm::SplitString(str_nm,"_",vstr);
	if (vstr.size() > 1)
	{

	}
	return -1;
}

std::string item_collection::bag_item_id2str( const int &id )
{
	std::stringstream ss;
	ss<<BAG_ITEM<<"_"<<id;
	return ss.str();
}

void item_collection::clear_bag_item()
{

	boost::mutex::scoped_lock lock(mu_bag_);

	std::vector<bag_item*>::iterator it = v_bag_item_.begin();
	for ( ;it != v_bag_item_.end(); ++it)
	{
		main_win_->get_scene()->del_item( (QGraphicsItem*)*it) ;
	}
	v_bag_item_.clear();
	show_buf_list_.clear();
	show_ex_buf_list_.clear();
}

void item_collection::add_bag_ex_item(const SPUB_BAG_EX &pub_bag_ex)
{
	show_ex_buf_list_.put(pub_bag_ex);
}

void item_collection::show_bag_ex_item(const SPUB_BAG_EX &pub_bag_ex)
{
	boost::mutex::scoped_lock lock(mu_bag_);

	bag_item* p_bag_item = 0;
	if (v_bag_item_.size() < i_max_bag_item_)
	{
		p_bag_item = new bag_item();
		std::string str_nm = bag_item_id2str(v_bag_item_.size());
		main_win_->get_scene()->add_item( str_nm , (QGraphicsItem*)p_bag_item);
		v_bag_item_.push_back(p_bag_item);
		std::string str_robot_shape = pub_bag_ex.robot_shape_;
		std::vector<SVec> v_robot_shape = robot_remote_para::get_robot_shape(str_robot_shape);
		p_bag_item->set_robot_shape(v_robot_shape);
		p_bag_item->set_laser_para(pub_bag_ex.laser_para_);
	}else{
		if (i_current_index_ < v_bag_item_.size()){
			p_bag_item = v_bag_item_[i_current_index_];
		}else{
			std::cout<<"error call!!!"<<std::endl;
			return;
		}
		
	}


	SPos odom;
	odom.x_ = pub_bag_ex.odom_.x_;
	odom.y_ = pub_bag_ex.odom_.y_;
	odom.th_ = pub_bag_ex.odom_.th_;

	p_bag_item->set_odom_pos(odom);
	p_bag_item->set_laser_ex(pub_bag_ex.laser_ex_ref_.laser_ex_);
	p_bag_item->set_laser_ref(pub_bag_ex.laser_ex_ref_.laser_reflector_);
	p_bag_item->set_speed(pub_bag_ex.odom_.vx_,pub_bag_ex.odom_.vy_,pub_bag_ex.odom_.vw_);
	p_bag_item->update();

	i_current_index_++;
	i_current_index_ =  i_current_index_ % i_max_bag_item_;
}

void item_collection::add_mapping_item( const SPUB_BAG_EX &pub_bag_ex )
{
	boost::mutex::scoped_lock lock(mu_mapping_list_);
	show_mapping_list_.push_back(pub_bag_ex);
}


void item_collection::show_mapping_item(const SPUB_BAG_EX &pub_bag_ex)
{
	if (th_clear_bag_item_()){

		std::vector<bag_item*>::iterator it = v_bag_item_.begin();
		for ( ;it != v_bag_item_.end(); ++it)
		{
			main_win_->get_scene()->del_item( (QGraphicsItem*)*it) ;
		}
		v_bag_item_.clear();
		show_buf_list_.clear();
		show_ex_buf_list_.clear();

		th_clear_bag_item_ = false;
	}

	bag_item* p_bag_item = new bag_item();
	std::string str_nm = bag_item_id2str(v_bag_item_.size());
	main_win_->get_scene()->add_item( str_nm , (QGraphicsItem*)p_bag_item);
	v_bag_item_.push_back(p_bag_item);
	std::string str_robot_shape = pub_bag_ex.robot_shape_;
	std::vector<SVec> v_robot_shape = robot_remote_para::get_robot_shape(str_robot_shape);
	p_bag_item->set_robot_shape(v_robot_shape);
	p_bag_item->set_laser_para(pub_bag_ex.laser_para_);


	SPos odom;
	odom.x_ = pub_bag_ex.odom_.x_;
	odom.y_ = pub_bag_ex.odom_.y_;
	odom.th_ = pub_bag_ex.odom_.th_;

	p_bag_item->set_odom_pos(odom);
	p_bag_item->set_laser_ex(pub_bag_ex.laser_ex_ref_.laser_ex_);
	p_bag_item->set_laser_ref(pub_bag_ex.laser_ex_ref_.laser_reflector_);
	p_bag_item->set_speed(pub_bag_ex.odom_.vx_,pub_bag_ex.odom_.vy_,pub_bag_ex.odom_.vw_);

}

void item_collection::clear_bag_item_thread()
{
	th_clear_bag_item_ = true;
}

void item_collection::add_mapping_reflector(protobuf_reflector* p_ref, SPUB_BAG_EX* p_bag_ex,double nx, double ny )
{
	
	boost::mutex::scoped_lock lock(mu_reflector_);
	reflector_item* p_reflector_item = new reflector_item(nx, ny);
	p_reflector_item->set_ref_bag(p_ref,p_bag_ex);
	p_reflector_item->set_id(p_ref->get_id());

	v_reflector_item_.push_back(p_reflector_item);

	//std::cout<<"item collection add mapping reflector!"<<p_ref->get_id()<<" pos:"<<nx<<" "<<ny<<std::endl;
}

void item_collection::clear_mapping_reflector()
{
	std::vector<QGraphicsItem *> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,REFLECTOR_ITEM);
	auto it = v_item.begin();
	for ( ; it != v_item.end() ; ++it ){
		reflector_item* p_reflector_item = static_cast<reflector_item*>(*it);
		p_reflector_item->set_ref_bag(0,0);
		main_win_->get_scene()->del_item( (QGraphicsItem*)*it) ;
	}
	//main_win_->get_scene()->del_item(REFLECTOR_ITEM);
}


void item_collection::show_qr_list(const std::vector<SQrCode> &v_qr_code)
{
	main_win_->get_scene()->del_item(REFLECTOR_ITEM);

	std::vector<SQrCode>::const_iterator cit = v_qr_code.begin();
	for ( ; cit !=  v_qr_code.end() ; ++cit )
	{
		get_new_qrcode_item( *cit );
	}
}

void item_collection::set_range_pos( qt_eve::mouse_event::SRange_ev event )
{

	range_item* r_item = 0;

	switch(event.show_set_){
	case event.RA_NONE:
		{
			std::vector<QGraphicsItem*> v_item;
			QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,new_range_nm_);
			r_item = static_cast<range_item*>(qi);

// 			if (r_item)
// 			{
// 				r_item->add_point(event.target_);
// 			}
			

			if ( (r_item) && (r_item->point_size() < 3)){
				main_win_->get_scene()->removeItem(r_item);
			}else{
				std::vector<Sxy> v_pos;
				r_item->get_range_pos(v_pos);
				PRO_MANAGE.set_range(CURRENT_PRO,r_item->get_name(),v_pos);
			}

			new_range_nm_ = "";

		}
		break;
	case event.RA_NEW:
		
		if ( new_range_nm_.length() < 1 )
		{
			new_range_nm_ = add_new_range(r_item,event.target_);
			if( new_range_nm_.length() > 0){
				main_win_->get_scene()->add_item( new_range_nm_ , (QGraphicsItem*)r_item);
			}else{
				std::cout<<"select map first!"<<std::endl;
				assert(false);
			}
			
		}else{
			std::vector<QGraphicsItem*> v_item;
			QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,new_range_nm_);
			r_item = static_cast<range_item*>(qi);
		}
		if (r_item)
		{
			std::cout<<"range add_point:"<<event.target_.x_<<" "<<event.target_.y_<<std::endl;
			r_item->add_point(event.target_);
			std::vector<Sxy> v_pos;
			r_item->get_range_pos(v_pos);
			PRO_MANAGE.set_range(CURRENT_PRO,r_item->get_name(),v_pos);
		}
		

		break;
	case event.RA_ROT:
		break;
// 	case event.RA_MOVE:
// 
// 		if ( new_range_nm_.length() > 0 )
// 		{
// 			
// 			foreach (QGraphicsItem *item, main_win_->get_scene()->selectedItems()) {
// 				if (  QtType::ITEM_RANGE == item->type() )
// 				{
// 					r_item = static_cast<range_item*>(item);
// 					std::vector<Sxy> v_pos;
// 					r_item->get_range_pos(v_pos);
// 					PRO_MANAGE.set_range(CURRENT_PRO,r_item->get_name(),v_pos);
// 				}
// 			
// 			}
// 
// 		}
// 
// 		break;

	default:
		break;
	}
	if (r_item)
	{
		r_item->update();
	}
	
}

void item_collection::set_reflector_pos(qt_eve::mouse_event::SReflector_ev event)
{
	if (event.RE_MENUAL_ADD == event.ref_set_)
	{
		reflector_item* p_reflector_item = get_new_reflector_item(event.target_.x_,event.target_.y_);
		
		SVec vp;
		vp.x_ = event.target_.x_;
		vp.y_ = event.target_.y_;
		protobuf_reflector* p_reflector = Singleton_Project_Manage::get_mutable_instance().create_reflector("",vp);
		protobuf_lab* p_lab = Singleton_Project_Manage::get_mutable_instance().create_lab("",vp);
		
		p_reflector->set_lab_id(p_lab->get_id());
		std::stringstream ss;
		ss<<p_reflector->get_id();

		lab_item* p_lab_item = get_new_lab_item(vp.x_,vp.y_);
		p_lab_item->set_id(p_lab->get_id());
		p_lab_item->set_lab(ss.str());

		p_lab->set_lab(p_lab_item->get_lab());
		

		p_reflector_item->set_id(p_reflector->get_id());
	}
}
void item_collection::set_node_pos(qt_eve::mouse_event::SNode_ev event)
{
	if (event.RE_MENUAL_ADD == event.node_set_)
	{
		SVec pos;
		pos.x_ = event.target_.x_;
		pos.y_ = event.target_.y_;
		protobuf_node* p_node = PRO_MANAGE.create_node(CURRENT_PRO,pos);
		node_item* p_node_item = get_new_node_item(p_node->get_id(),event.target_.x_,event.target_.y_);
	}
}
void item_collection::link_edge_pos(qt_eve::mouse_event::SEdge_ev event)
{
	if (event.LO_INIT == event.link_set_){
		create_temp_edge_line();
		link_edge_pari_.clear();
	}else if (event.LO_SET == event.link_set_){

		//search current node item under mouse pos 
		QList<QGraphicsItem *> l_items = main_win_->get_scene()->items(	QRectF(event.current_pos_.x_ - 0.1,event.current_pos_.y_ - 0.1,0.2,0.2 )); 
		//if link_edge_pari_ size < 2 then insert node of edge
		for (int i = 0; i < l_items.size(); ++i) {
			QGraphicsItem * p_item = l_items.at(i);
			if ( p_item->type()== QtType::ITEM_NODE){
				if (link_edge_pari_.size() < 2){
					if (link_edge_pari_.indexOf(p_item) == -1){
						link_edge_pari_.push_back(p_item);
					}
				}
			}
		}
		//if link_edge_pari_size == 1 means have start node
		F32 fstart_x = 0;
		F32 fstart_y = 0;
		if (link_edge_pari_.size()> 0){
			fstart_x = link_edge_pari_.at(0)->pos().x();
			fstart_y = link_edge_pari_.at(0)->pos().y();
		}else{
			fstart_x = event.start_pos_.x_;
			fstart_y = event.start_pos_.y_;
		}
		F32 fend_x = 0;
		F32 fend_y = 0;
		if (link_edge_pari_.size()> 1){
			fend_x = link_edge_pari_.at(1)->pos().x();
			fend_y = link_edge_pari_.at(1)->pos().y();
		}else{
			fend_x = event.current_pos_.x_;
			fend_y = event.current_pos_.y_;
		}
		
		tmp_line_item_->setLine(fstart_x,fstart_y,fend_x,fend_y);
		tmp_line_item_->setVisible(true);

	}else if(event.LO_LINK == event.link_set_){
		tmp_line_item_->setVisible(false);

		if (link_edge_pari_.size() == 2){

			if( ( QtType::ITEM_NODE == link_edge_pari_.at(0)->type() ) && (QtType::ITEM_NODE == link_edge_pari_.at(1)->type()) ){
				node_item* p_src =  qgraphicsitem_cast<node_item*>(link_edge_pari_.at(0));
				node_item* p_dst =  qgraphicsitem_cast<node_item*>(link_edge_pari_.at(1));
				protobuf_edge* p_edge = PRO_MANAGE.create_edge(CURRENT_PRO,p_src->get_id(),p_dst->get_id() );
				if (p_edge){
					edge_item* p_edge_item = get_new_edge(p_edge->get_id(),p_src,p_dst);
					p_edge_item->set_forward(p_edge->forward());
					p_edge_item->set_backward(p_edge->backward());
					p_edge_item->set_leftshift(p_edge->leftshift());
					p_edge_item->set_rightshift(p_edge->rightshift());


				}
				
			}

		}
		
	}
}

void item_collection::set_producer_pos(qt_eve::mouse_event::SProcuder_ev event)
{
	if (event.PRODUCER_ADD == event.link_set_){
		SVec pos;
		pos.x_ = event.start_pos_.x_;
		pos.y_ = event.start_pos_.y_;
		protobuf_producer* p_producer = PRO_MANAGE.create_producer(CURRENT_PRO,pos);
		producer_item* p_producer_item = get_new_producer_item(p_producer->get_id(),event.start_pos_.x_,event.start_pos_.y_);
	}
}


void item_collection::set_consumer_pos(qt_eve::mouse_event::SConsumer_ev event)
{
	if (event.CONSUMER_ADD == event.link_set_){
		SVec pos;
		pos.x_ = event.start_pos_.x_;
		pos.y_ = event.start_pos_.y_;
		protobuf_consumer* p_consumer = PRO_MANAGE.create_consumer(CURRENT_PRO,pos);
		consumer_item* p_consumer_item = get_new_consumer_item(p_consumer->get_id(),event.start_pos_.x_,event.start_pos_.y_);
	}
}

std::string item_collection::add_new_range( range_item* &r_item, const SPos &pos )
{


 	r_item = new range_item();
 	r_item->set_scene(main_win_->get_scene());
 	std::string str_range_nm = PRO_MANAGE.create_range(CURRENT_PRO);
 	r_item->set_name(str_range_nm);
 	r_item->setPos(pos.x_,pos.y_);
 	r_item->setRotation(0);

	return str_range_nm;


}

// void item_collection::set_sel_pro( const std::string pro_nm )
// {
// 	select_pro_nm_ = pro_nm;
// }

void item_collection::set_map( GridMap* p_map )
{

	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		p_map_item->set_map(p_map);
	}
}


GridMap* item_collection::get_map()
{
	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		return p_map_item->get_map();
	}
}

particle_item* item_collection::get_sim_path_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,SIM_PATH_ITEM);

	particle_item*  p_sim_path_item = static_cast<particle_item*>(qi);

	if (!p_sim_path_item)
	{
		p_sim_path_item = new particle_item();
		main_win_->get_scene()->add_item( SIM_PATH_ITEM , (QGraphicsItem*)p_sim_path_item);
	}

	return p_sim_path_item;
}

reflector_item* item_collection::get_new_reflector_item( const F32 &fx, const F32 &fy )
{
	reflector_item* p_reflector_item = new reflector_item(fx, fy);
	main_win_->get_scene()->add_item( REFLECTOR_ITEM , (QGraphicsItem*)p_reflector_item);
	return p_reflector_item;
}

lab_item* item_collection::get_new_lab_item(const F32 &fx, const F32 &fy)
{
	lab_item* p_lab_item = new lab_item(fx, fy);
	main_win_->get_scene()->add_item( LAB_ITEM , (QGraphicsItem*)p_lab_item);
	return p_lab_item;
}
node_item* item_collection::get_new_node_item(const int &id, const F32 &fx, const F32 &fy)
{
	node_item* p_node_item = new node_item();
	p_node_item->set_id(id);
	p_node_item->setPos(fx,fy);
	std::stringstream ss;
	ss<<id;
	p_node_item->new_point("node_pos",0,0,0,ss.str());
	main_win_->get_scene()->add_item( NODE_ITEM , (QGraphicsItem*)p_node_item);

	return p_node_item;
}

void item_collection::add_bag_item( const SPUB_BAG &pub_bag )
{

	show_buf_list_.put(pub_bag);

}

void item_collection::add_key_item( const SPUB_BAG &pub_bag, bool b_bag_odom_amcl )
{
	
	show_buf_list_.put(pub_bag);
	b_bag_odom_amcl_ = b_bag_odom_amcl;
}

bool item_collection::show_laser()
{
	b_show_laser_ = !b_show_laser_;
	return b_show_laser_;
}

bool item_collection::show_particles()
{
	b_show_particles_ = !b_show_particles_;
	return b_show_particles_;
}

bool item_collection::show_view_data(std::vector<SView_Data> &v_data)
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = main_win_->get_scene()->get_item(v_item,VIEW_DATA_ITEM);

	view_data_item*  p_view_data_item = static_cast<view_data_item*>(qi);

	if (!p_view_data_item)
	{
		p_view_data_item = new view_data_item();
		main_win_->get_scene()->add_item( VIEW_DATA_ITEM , (QGraphicsItem*)p_view_data_item);
	}

	p_view_data_item->update_view_data(v_data);
	p_view_data_item->update();
	return true;
}

int item_collection::rand_edge()
{
	std::map<int,SPos> m_id_pos;
	std::map<int,node_item*> m_id_item;

	foreach (QGraphicsItem *item, main_win_->get_scene()->items()) 
	{
		if (item->isSelected())
		{
			if (item->type() == QtType::ITEM_NODE)
			{
				node_item*  p_node_item = static_cast<node_item*>(item);
				m_id_pos[p_node_item->get_id()] = p_node_item->get_pos();
				m_id_item[p_node_item->get_id()] = p_node_item;
			}
		}
	}
	if (m_id_pos.size() < 2){
		return 0;
	}
	subdiv sdiv;
	std::vector<std::pair<int,int>> edge;
	sdiv.subdiv_2d(edge,m_id_pos);
	
	std::map<int,node_item*>::iterator itn = m_id_item.end();
	std::vector<std::pair<int,int>>::iterator it = edge.begin();
	for ( ; it != edge.end() ; ++it ){
		
		node_item* nsrc = 0;
		node_item* ndst = 0;

		itn = m_id_item.find(it->first);
		if (itn != m_id_item.end()){
			nsrc = itn->second;
		}
		itn = m_id_item.find(it->second);
		if (itn != m_id_item.end()){
			ndst = itn->second;
		}
// 		if ( nsrc && ndst ){
// 			edge_item* p_edge_item = new edge_item( nsrc, ndst );
// 			main_win_->get_scene()->add_item( EDGE_ITEM , (QGraphicsItem*)p_edge_item);
// 		}

		protobuf_edge* p_edge = PRO_MANAGE.create_edge(CURRENT_PRO,nsrc->get_id(),ndst->get_id() );
		if (p_edge){
			edge_item* p_edge_item = get_new_edge(p_edge->get_id(),nsrc,ndst);
			p_edge_item->set_forward(p_edge->forward());
			p_edge_item->set_backward(p_edge->backward());
			p_edge_item->set_leftshift(p_edge->leftshift());
			p_edge_item->set_rightshift(p_edge->rightshift());

		}else{
			std::cout<<"create edge fail: multi define!"<<nsrc->get_id()<<" "<<ndst->get_id()<<std::endl;
		}
	}
	return 1;
// 
// 
// 
// 	return 1;
}

void item_collection::create_temp_edge_line()
{
	if (!tmp_line_item_){
		tmp_line_item_ = new QGraphicsLineItem();
		tmp_line_item_->setZValue(QtType::ITEM_EDGE_ZV);
		main_win_->get_scene()->addItem(tmp_line_item_);
	}
	
	//tmp_line_item_->setActive(false);
}

edge_item* item_collection::get_new_edge(const int &id,node_item* nsrc,node_item* ndst)
{
	if ( (id >=0 ) && nsrc && ndst ){

		edge_item* p_edge_item = new edge_item( nsrc, ndst );
		p_edge_item->set_id(id);
		main_win_->get_scene()->add_item( EDGE_ITEM , (QGraphicsItem*)p_edge_item);

		return p_edge_item;
	}
	return 0;
}

edge_item* item_collection::get_new_edge(const int &id,const int &i_nsrc,const int &i_ndst)
{
	node_item* nsrc = get_node(i_nsrc);
	node_item* ndst = get_node(i_ndst);
	return get_new_edge(id,nsrc,ndst);
}


edge_item* item_collection::get_edge(const int &id)
{

	std::vector<QGraphicsItem*> v_item;
	main_win_->get_scene()->get_item(v_item,EDGE_ITEM);

	edge_item*  p_edge_item = 0;
	std::vector<QGraphicsItem*>::iterator it = v_item.begin();
	for (; it != v_item.end() ; ++it){
		p_edge_item = static_cast<edge_item*>(*it);
		if (p_edge_item->get_id() == id )
		{
			return p_edge_item;
		}
	}

	return 0;
}

bool item_collection::set_ori_dir(const int &id , DIRECTION forward,DIRECTION backward,DIRECTION leftshift,DIRECTION rightshift)
{
	edge_item* p_edge_item = get_edge(id);
	if (p_edge_item){
		p_edge_item->set_forward(forward);
		p_edge_item->set_backward(backward);
		p_edge_item->set_leftshift(leftshift);
		p_edge_item->set_rightshift(rightshift);
		return true;
	}
	return false;
}

node_item* item_collection::get_node( const int &id )
{
	std::vector<QGraphicsItem*> v_item;
	main_win_->get_scene()->get_item(v_item,NODE_ITEM);

	node_item*  p_node = 0;
	std::vector<QGraphicsItem*>::iterator it = v_item.begin();
	for (; it != v_item.end() ; ++it){
		p_node = static_cast<node_item*>(*it);
		if (p_node->get_id() == id )
		{
			return p_node;
		}
	}
	
	return 0;
}

range_item* item_collection::get_new_range_item(const std::string &str_range_nm)
{
	range_item* r_item = new range_item();
	r_item->set_scene(main_win_->get_scene());
	
	r_item->set_name(str_range_nm);
	r_item->setRotation(0);

	main_win_->get_scene()->add_item( str_range_nm , (QGraphicsItem*)r_item);

	return r_item;
}

producer_item* item_collection::get_new_producer_item(const int &id ,  const F32 &fx, const F32 &fy )
{
	producer_item* p_producer_item = new producer_item(fx,fy);
	p_producer_item->set_id(id);
	p_producer_item->setPos(fx,fy);

	main_win_->get_scene()->add_item( PRODUCER_ITEM , (QGraphicsItem*)p_producer_item);

	return p_producer_item;
}

consumer_item* item_collection::get_new_consumer_item(const int &id , const F32 &fx, const F32 &fy)
{
	consumer_item* p_consumer_item = new consumer_item(fx,fy);
	p_consumer_item->set_id(id);
	p_consumer_item->setPos(fx,fy);

	main_win_->get_scene()->add_item( CONSUMER_ITEM , (QGraphicsItem*)p_consumer_item);

	return p_consumer_item;
}

void item_collection::range_clear()
{
	new_range_nm_ ="";
}

void item_collection::set_charge_pos( qt_eve::mouse_event::SCharge_ev event )
{
	if (event.CHARGE_ADD == event.link_set_){
		SVec pos;
		pos.x_ = event.start_pos_.x_;
		pos.y_ = event.start_pos_.y_;
		protobuf_station* p_charge = PRO_MANAGE.create_charge(CURRENT_PRO,pos);
		charge_item* p_charge_item = get_new_charge_item(p_charge->get_id(),event.start_pos_.x_,event.start_pos_.y_);
	}
}

void item_collection::set_rect_pos(qt_eve::mouse_event::SSRect_ev event)
{
	if (event.RECT_ADD == event.rect_set_){
		SPos pos;
		pos.x_ = event.current_pos_.x_;
		pos.y_ = event.current_pos_.y_;
		pos.th_ = 0;
		protobuf_rect* p_rect = PRO_MANAGE.create_rect(CURRENT_PRO,pos);
		rect_item* p_rect_item = get_new_rect_item(p_rect->get_name(), pos.x_, pos.y_);
	}
}

void item_collection::multi_sel(qt_eve::mouse_event::SSel_ev event)
{
	QRectF rectf;
	rectf.setTopLeft(QPointF(event.start_pos_.x_,event.start_pos_.y_));
	rectf.setBottomRight(QPointF(event.current_pos_.x_,event.current_pos_.y_));
	Sxy topleft;
	Sxy bottomright;
	topleft.x_ = event.start_pos_.x_;
	topleft.y_ = event.start_pos_.y_;
	bottomright.x_ = event.current_pos_.x_;
	bottomright.y_ = event.current_pos_.y_;

	if (event.SEL_MOVE == event.sel_){
		
		get_select_item()->setRect(rectf);
		get_select_item()->setVisible(true);

	}else if(event.SEL_END == event.sel_){

		get_select_item()->setRect(rectf);

		std::map<int,protobuf_node*> m_node = PRO_MANAGE.get_node_range(CURRENT_PRO,topleft,bottomright);

		auto it = m_node.begin();
		for ( ; it != m_node.end() ; ++it ){
			node_item* p_item = get_node(it->first);

			p_item->setSelected(true);
		}

		QList<QGraphicsItem *> l_items = main_win_->get_scene()->items(	rectf ,Qt::IntersectsItemBoundingRect, Qt::DescendingOrder); 

		for (int i = 0; i < l_items.size(); ++i) {
			QGraphicsItem * p_item = l_items.at(i);

			if ( (p_item->type() != QtType::ITEM_EDGE) && p_item->type() != QtType::ITEM_NODE ){

				p_item->setSelected(true);
			}
		}

		get_select_item()->setVisible(false);
	}
	main_win_->get_scene()->update(-300,-300,600,600);
}
QGraphicsRectItem* item_collection::get_select_item()
{
	if(!p_sel_rect_){
		p_sel_rect_ = new QGraphicsRectItem();
		p_sel_rect_->setZValue(QtType::ITEM_EDGE_ZV);
		p_sel_rect_->setPen(QPen(Qt::red, 0.05, Qt::DotLine));
		main_win_->get_scene()->addItem(p_sel_rect_);
	}
	return p_sel_rect_;
}
charge_item* item_collection::get_new_charge_item( const int &id , const F32 &fx, const F32 &fy )
{
	charge_item* p_charge_item = new charge_item(fx,fy);
	p_charge_item->set_id(id);
	p_charge_item->setPos(fx,fy);

	main_win_->get_scene()->add_item( CHARGE_ITEM , (QGraphicsItem*)p_charge_item);

	return p_charge_item;
}

void item_collection::set_processer_pos( qt_eve::mouse_event::SProcesser_ev event )
{
	if (event.PROCESSER_ADD == event.link_set_){
		SVec pos;
		pos.x_ = event.start_pos_.x_;
		pos.y_ = event.start_pos_.y_;
		protobuf_processer* p_processer = PRO_MANAGE.create_processer(CURRENT_PRO,pos);
		processer_item* p_processer_item = get_new_processer_item(p_processer->get_id(),event.start_pos_.x_,event.start_pos_.y_);
	}
}

void item_collection::set_storage_pos( qt_eve::mouse_event::SStorage_ev event )
{
	if (event.STORAGE_ADD == event.link_set_){
		SVec pos;
		pos.x_ = event.start_pos_.x_;
		pos.y_ = event.start_pos_.y_;
		protobuf_storage* p_storage = PRO_MANAGE.create_storage(CURRENT_PRO,pos);
		storage_item* p_storage_item = get_new_storage_item(p_storage->get_id(),event.start_pos_.x_,event.start_pos_.y_);
	}
}

processer_item* item_collection::get_new_processer_item( const int &id , const F32 &fx, const F32 &fy )
{
	processer_item* p_processer_item = new processer_item(fx,fy);
	p_processer_item->set_id(id);
	p_processer_item->setPos(fx,fy);

	main_win_->get_scene()->add_item( PROCESSER_ITEM , (QGraphicsItem*)p_processer_item);

	return p_processer_item;
}

storage_item* item_collection::get_new_storage_item( const int &id , const F32 &fx, const F32 &fy )
{
	storage_item* p_storage_item = new storage_item(fx,fy);
	p_storage_item->set_id(id);
	p_storage_item->setPos(fx,fy);

	main_win_->get_scene()->add_item( STORAGE_ITEM , (QGraphicsItem*)p_storage_item);

	return p_storage_item;
}

void item_collection::align_node()
{
	l_align_node_.clear();

	std::vector<QGraphicsItem*> v_item;
	main_win_->get_scene()->get_item(v_item,NODE_ITEM);

	auto it_0 = v_item.begin();
	for (; it_0 != v_item.end() ; ++it_0){
		
		if ( (*it_0)->type() == QtType::ITEM_NODE ){
			if ((*it_0)->isSelected()){
				l_align_node_.push_back((*it_0));
			}
		}
	}
	

	std::map<F32,std::pair<protobuf_node*,protobuf_node*>> m_dis;

	
	auto it = l_align_node_.begin();
	for ( ; it != l_align_node_.end() ; ++it ){

		node_item* p_item = static_cast<node_item*>(*it);
	
		protobuf_node* p_node1 =  PRO_MANAGE.get_node(CURRENT_PRO, p_item->get_id() );
		SPos pos1;
		p_node1->get_pos(pos1);
		VecPosition vp1( pos1.x_, pos1.y_);

		auto it2 = it;
		it2++;
		for ( ; it2 != l_align_node_.end() ; ++it2 ){

			p_item = static_cast<node_item*>(*it2);

			protobuf_node* p_node2 =  PRO_MANAGE.get_node(CURRENT_PRO, p_item->get_id() );
			SPos pos2;
			p_node2->get_pos(pos2);
			VecPosition vp2( pos2.x_, pos2.y_);
			m_dis[ (vp1 - vp2).getMagnitude()] = std::make_pair(p_node1,p_node2);

		}
	}
	
	if ( m_dis.size() == 0){
		return;
	}
	
	auto it3 = m_dis.rbegin();
	std::pair<protobuf_node*,protobuf_node*> pnn = it3->second;
	
	SPos pos;
	pnn.first->get_pos(pos);
	VecPosition vp1( pos.x_, pos.y_);
	pnn.second->get_pos(pos);
	VecPosition vp2( pos.x_, pos.y_);
	
	Line ln_align = Line::makeLineFromTwoPoints( vp1, vp2 );
	
	int node_id_1 = pnn.first->get_id();
	int node_id_2 = pnn.second->get_id();


	auto it4 = l_align_node_.begin();
	for ( ; it4 != l_align_node_.end() ; ++it4 ){


		node_item* p_item = static_cast<node_item*>(*it4);

		if ( (p_item->get_id() == node_id_1) || ( p_item->get_id() == node_id_2)){
			continue;
		}

		protobuf_node* p_node =  PRO_MANAGE.get_node(CURRENT_PRO, p_item->get_id() );
		SPos pos;
		p_node->get_pos(pos);

		VecPosition drop = ln_align.getPointOnLineClosestTo(VecPosition(pos.x_,pos.y_));

		p_node->set_pos(drop.getX(),drop.getY());
		p_item->update_show();
	}
}


void item_collection::create_multi_roles(std::string str_role_type, std::vector< std::vector<Sxy>> v_xy)
{
	if ( str_role_type == PRODUCER ){
		create_multi_producer(v_xy);
	}else if ( str_role_type == CONSUMER ){
		create_multi_consumer(v_xy);
	}else if ( str_role_type == STORAGE ){
		create_multi_storage(v_xy);
	}
}

void item_collection::create_multi_producer(std::vector< std::vector<Sxy>> v_xy)
{
	std::cout<<"item_collection::create_multi_producer"<<std::endl;
	
	std::vector<protobuf_producer*> v_prod;
	F32 edge_orientation = 0;

	int i_row = 0;
	int i_col = 0;
	auto it_row = v_xy.begin();
	for ( ; it_row != v_xy.end() ; ++it_row ){

		auto it_col = it_row->begin();
		
		node_item* p_src = 0;
		node_item* p_dst = 0;
		
		VecPosition v_from;
		i_row = 0;
		for ( ; it_col != it_row->end() ; ++it_col){

			Sxy &xy(*it_col);

			SVec pos;
			pos.x_ = xy.x_;
			pos.y_ = xy.y_;
			protobuf_node* p_node = PRO_MANAGE.create_node(CURRENT_PRO,pos);
			p_dst = get_new_node_item(p_node->get_id(),xy.x_,xy.y_);
			VecPosition v_to(xy.x_,xy.y_);


			protobuf_producer* p_producer = PRO_MANAGE.create_producer(CURRENT_PRO,pos);
			p_producer->bind_node(p_node->get_id(),0);
			p_producer->set_row_col(i_row,i_col);
			v_prod.push_back(p_producer);

			producer_item* p_producer_item = get_new_producer_item(p_producer->get_id(),xy.x_,xy.y_);

			if( it_col != it_row->begin() ){

				protobuf_edge* p_edge = PRO_MANAGE.create_edge(CURRENT_PRO,p_src->get_id(),p_dst->get_id() );
				p_edge->set_forward(DIRECTION::DIR_DST2SRC);
				p_edge->set_backward(DIRECTION::DIR_SRC2DST);
				if (p_edge){
					edge_item* p_edge_item = get_new_edge(p_edge->get_id(),p_src,p_dst);
					p_edge_item->set_forward(p_edge->forward());
					p_edge_item->set_backward(p_edge->backward());
					p_edge_item->set_leftshift(p_edge->leftshift());
					p_edge_item->set_rightshift(p_edge->rightshift());

				}
				v_from =  v_from - v_to;
				edge_orientation = v_from.getDirection();
				
			}
			v_from = v_to;
			p_src = p_dst;
			i_row++;
		}

		i_col++;
	}

	auto it = v_prod.begin();
	for ( ; it != v_prod.end() ; ++it){
		protobuf_producer* p_producer = *it;
		p_producer->set_rows_cols(i_row,i_col);
		p_producer->bind_ori(edge_orientation);
	}
}

void item_collection::create_multi_consumer(std::vector< std::vector<Sxy>> v_xy)
{
	std::cout<<"item_collection::create_multi_consumer"<<std::endl;

	std::vector<protobuf_consumer*> v_con;
	F32 edge_orientation = 0;

	int i_row = 0;
	int i_col = 0;
	auto it_row = v_xy.begin();
	for ( ; it_row != v_xy.end() ; ++it_row ){

		auto it_col = it_row->begin();

		node_item* p_src = 0;
		node_item* p_dst = 0;

		VecPosition v_from;
		i_row = 0;
		for ( ; it_col != it_row->end() ; ++it_col){

			Sxy &xy(*it_col);

			SVec pos;
			pos.x_ = xy.x_;
			pos.y_ = xy.y_;
			protobuf_node* p_node = PRO_MANAGE.create_node(CURRENT_PRO,pos);
			p_dst = get_new_node_item(p_node->get_id(),xy.x_,xy.y_);
			VecPosition v_to(xy.x_,xy.y_);


			protobuf_consumer* p_consumer = PRO_MANAGE.create_consumer(CURRENT_PRO,pos);
			p_consumer->bind_node(p_node->get_id(),0);
			p_consumer->set_row_col(i_row,i_col);
			v_con.push_back(p_consumer);

			consumer_item* p_consumer_item = get_new_consumer_item(p_consumer->get_id(),xy.x_,xy.y_);

			if( it_col != it_row->begin() ){

				protobuf_edge* p_edge = PRO_MANAGE.create_edge(CURRENT_PRO,p_src->get_id(),p_dst->get_id() );
				p_edge->set_forward(DIRECTION::DIR_DST2SRC);
				p_edge->set_backward(DIRECTION::DIR_SRC2DST);
				if (p_edge){
					edge_item* p_edge_item = get_new_edge(p_edge->get_id(),p_src,p_dst);
					p_edge_item->set_forward(p_edge->forward());
					p_edge_item->set_backward(p_edge->backward());
					p_edge_item->set_leftshift(p_edge->leftshift());
					p_edge_item->set_rightshift(p_edge->rightshift());

				}
				v_from =  v_from - v_to;
				edge_orientation = v_from.getDirection();

			}
			v_from = v_to;
			p_src = p_dst;
			i_row++;
		}

		i_col++;
	}

	auto it = v_con.begin();
	for ( ; it != v_con.end() ; ++it){
		protobuf_consumer* p_consumer = *it;
		p_consumer->set_rows_cols(i_row,i_col);
		p_consumer->bind_ori(edge_orientation);
	}
}
void item_collection::create_multi_storage(std::vector< std::vector<Sxy>> v_xy)
{
	std::cout<<"item_collection::create_multi_storage"<<std::endl;

	std::vector<protobuf_storage*> v_sto;
	F32 edge_orientation = 0;

	int i_row = 0;
	int i_col = 0;
	auto it_row = v_xy.begin();
	for ( ; it_row != v_xy.end() ; ++it_row ){

		auto it_col = it_row->begin();

		node_item* p_src = 0;
		node_item* p_dst = 0;

		VecPosition v_from;
		i_row = 0;
		for ( ; it_col != it_row->end() ; ++it_col){

			Sxy &xy(*it_col);

			SVec pos;
			pos.x_ = xy.x_;
			pos.y_ = xy.y_;
			protobuf_node* p_node = PRO_MANAGE.create_node(CURRENT_PRO,pos);
			p_dst = get_new_node_item(p_node->get_id(),xy.x_,xy.y_);
			VecPosition v_to(xy.x_,xy.y_);


			protobuf_storage* p_storage = PRO_MANAGE.create_storage(CURRENT_PRO,pos);
			p_storage->bind_node(p_node->get_id(),0);
			p_storage->set_row_col(i_row,i_col);
			v_sto.push_back(p_storage);

			storage_item* p_storage_item = get_new_storage_item(p_storage->get_id(),xy.x_,xy.y_);

			if( it_col != it_row->begin() ){

				protobuf_edge* p_edge = PRO_MANAGE.create_edge(CURRENT_PRO,p_src->get_id(),p_dst->get_id() );
				p_edge->set_forward(DIRECTION::DIR_DST2SRC);
				p_edge->set_backward(DIRECTION::DIR_SRC2DST);
				if (p_edge){
					edge_item* p_edge_item = get_new_edge(p_edge->get_id(),p_src,p_dst);
					p_edge_item->set_forward(p_edge->forward());
					p_edge_item->set_backward(p_edge->backward());
					p_edge_item->set_leftshift(p_edge->leftshift());
					p_edge_item->set_rightshift(p_edge->rightshift());

				}
				v_from =  v_from - v_to;
				edge_orientation = v_from.getDirection();

			}
			v_from = v_to;
			p_src = p_dst;
			i_row++;
		}

		i_col++;
	}

	auto it = v_sto.begin();
	for ( ; it != v_sto.end() ; ++it){
		protobuf_storage* p_storage = *it;
		p_storage->set_rows_cols(i_row,i_col);
		p_storage->bind_ori(edge_orientation);
	}
}
rect_item* item_collection::get_new_rect_item( const std::string &str_rect_nm, const F32 &fx, const F32 &fy )
{
	rect_item* p_rect_item = new rect_item();
	p_rect_item->set_name(str_rect_nm);
	p_rect_item->setPos(fx,fy);
	p_rect_item->fnc_create_multi_roles_ = boost::bind(&item_collection::create_multi_roles,this,_1,_2);
	main_win_->get_scene()->add_item( RECT_ITEM , (QGraphicsItem*)p_rect_item);

	return p_rect_item;
}

void item_collection::set_qrcode_pos( qt_eve::mouse_event::SQrCode_ev event )
{
	if (event.QRCODE_END == event.link_set_)
	{
		SPos pos;
		
		SQrCode qr_code;
		memset(&qr_code,0,sizeof(SQrCode));
		qr_code.time_stemp_ = cTimerDiff::total_ms();
		qr_code.pos_.x_ = event.current_pos_.x_;
		qr_code.pos_.y_ = event.current_pos_.y_;
		qr_code.pos_.th_ = event.current_pos_.th_;

		add_qrcode_pos(qr_code);
	}
}
void item_collection::add_qrcode_pos( SQrCode qr_code ){
	protobuf_qrcode* p_qr_code  = PRO_MANAGE.create_qrcode(CURRENT_PRO,qr_code.pos_);
	p_qr_code->set_des(qr_code.ch_des_);
	p_qr_code->set_time_stemp(qr_code.time_stemp_);
	qrcode_item* p_qrcode_item = get_new_qrcode_item(qr_code);
}
qrcode_item* item_collection::get_new_qrcode_item( SQrCode qr_code )
{
	qrcode_item* p_qrcode_item = new qrcode_item(qr_code.pos_.x_,qr_code.pos_.y_,qr_code.pos_.th_);
	p_qrcode_item->set_id(qr_code.qr_id_);

	main_win_->get_scene()->add_item( QRCODE_ITEM , (QGraphicsItem*)p_qrcode_item);

	return p_qrcode_item;
}










