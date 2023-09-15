#ifndef _KPS_ITEM_COLLECTION_H
#define _KPS_ITEM_COLLECTION_H

#include <vector>

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "Comm/buffer_con.hpp"
#endif

#include <QMainWindow>
#include <QGraphicsRectItem>

class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QGraphicsItem;
class QGraphicsLineItem;

class kps_main_win;
class map_item;
class robot_item;
class particle_item;
class bag_item;
class range_item;
class reflector_item;
class lab_item;
class node_item;
class edge_item;
class producer_item;
class consumer_item;
class processer_item;
class storage_item;
class charge_item;
class rect_item;
class qrcode_item;

class GridMap;
class protobuf_reflector;


#include "scene/mouse_event.h"

class item_collection : public QObject{

	Q_OBJECT

public:
	item_collection();
	~item_collection();

	void init(kps_main_win* main_win);
	void remove_all_item();
	void show_map_rect();
	void show_map_item(const std::vector<int> &v_data);
	void show_map_item(const std::vector<Sxy> &v_data);
	void show_particle_item(const std::vector<STriangle>& v_particles);
	void show_sim_path( const SPos& pos, const std::vector<STriangle>& v_path);
	void show_reflector_list( const std::vector<SVec> &reflector_list, const bool &b_new = false);
	void show_reflector_list( const std::vector<SReflectorPos> &v_ref_pos );
	bool show_ex_reflector();
	bool show_laser();
	bool show_particles();
	bool show_view_data(std::vector<SView_Data> &v_data);

	void save_map(std::string map_nm);
	bool open_map(std::string map_nm);
	void set_map(GridMap* p_map);
	//void get_map(GridMap* p_map);
	GridMap* get_map();
	
	void download_map( std::vector<int> &v_data);
	
	map_item* get_map_item();
	robot_item* get_robot_item();
	particle_item* get_particle_item();
	particle_item* get_sim_path_item();
	reflector_item* get_new_reflector_item( const F32 &fx, const F32 &fy );
	lab_item* get_new_lab_item( const F32 &fx, const F32 &fy );
	node_item* get_new_node_item(const int &id,  const F32 &fx, const F32 &fy );
	edge_item* get_new_edge(const int &id,const int &i_nsrc,const int &i_ndst);
	edge_item* get_new_edge(const int &id,node_item* nsrc,node_item* ndst);
	edge_item* get_edge(const int &id);
	bool set_ori_dir( const int &id , DIRECTION forward,DIRECTION backward,DIRECTION leftshift,DIRECTION rightshift);
	node_item* get_node(const int &id);
	range_item* get_new_range_item(const std::string &str_range_nm);
	producer_item* get_new_producer_item( const int &id ,  const F32 &fx, const F32 &fy );
	consumer_item* get_new_consumer_item( const int &id ,  const F32 &fx, const F32 &fy );
	processer_item* get_new_processer_item( const int &id ,  const F32 &fx, const F32 &fy );
	storage_item* get_new_storage_item( const int &id ,  const F32 &fx, const F32 &fy );
	charge_item* get_new_charge_item( const int &id ,  const F32 &fx, const F32 &fy );
	rect_item* get_new_rect_item( const std::string &str_rect_nm,  const F32 &fx, const F32 &fy );
	qrcode_item* get_new_qrcode_item( SQrCode qr_code);

	QGraphicsRectItem* get_select_item();

	int rand_edge();

	void add_bag_item(const SPUB_BAG &pub_bag );
	void add_key_item(const SPUB_BAG &pub_bag , bool b_bag_odom_amcl = true);
	void show_bag_item(const SPUB_BAG &pub_bag);
	void clear_bag_item();
	bool b_bag_odom_amcl_;

	void add_bag_ex_item(const SPUB_BAG_EX &pub_bag_ex);
	void show_bag_ex_item(const SPUB_BAG_EX &pub_bag_ex);

	void add_mapping_item(const SPUB_BAG_EX &pub_bag_ex);
	void show_mapping_item(const SPUB_BAG_EX &pub_bag_ex);
	void clear_bag_item_thread();

	void add_mapping_reflector(protobuf_reflector* p_ref, SPUB_BAG_EX* p_bag_ex ,double nx, double ny);
	void clear_mapping_reflector();
	
	void show_qr_list( const std::vector<SQrCode> &v_qr_code );

	void set_robot_est(qt_eve::mouse_event::SLocal_ev event);
	void set_range_pos(qt_eve::mouse_event::SRange_ev event);
	void set_reflector_pos(qt_eve::mouse_event::SReflector_ev event);
	void set_node_pos(qt_eve::mouse_event::SNode_ev event);
	void link_edge_pos(qt_eve::mouse_event::SEdge_ev event);
	void set_producer_pos(qt_eve::mouse_event::SProcuder_ev event);
	void set_consumer_pos(qt_eve::mouse_event::SConsumer_ev event);
	void set_processer_pos(qt_eve::mouse_event::SProcesser_ev event);
	void set_storage_pos(qt_eve::mouse_event::SStorage_ev event);
	void set_charge_pos(qt_eve::mouse_event::SCharge_ev event);
	void set_rect_pos(qt_eve::mouse_event::SSRect_ev event);
	void set_qrcode_pos(qt_eve::mouse_event::SQrCode_ev event);
	void add_qrcode_pos( SQrCode qr_code );
	
	void multi_sel(qt_eve::mouse_event::SSel_ev event);

	void range_clear();

	void align_node();
	void create_multi_roles(std::string str_role_type, std::vector< std::vector<Sxy>> v_xy );
	void create_multi_producer(std::vector< std::vector<Sxy>> v_xy);
	void create_multi_consumer(std::vector< std::vector<Sxy>> v_xy);
	void create_multi_storage(std::vector< std::vector<Sxy>> v_xy);

	void time_event(bool b_online);
	
	//void set_sel_pro(const std::string pro_nm);
	std::vector<SPOS_CONFIDENCE> v_ref_conf_;

private:
	

	kps_main_win* main_win_;

	boost::mutex mu_bag_;
	std::vector<bag_item*> v_bag_item_;
	int i_max_bag_item_;
	int i_current_index_;

	int bag_item_str2id(const std::string &str_nm);
	std::string bag_item_id2str(const int &id);

//range ref
	std::string add_new_range(range_item* &r_item, const SPos &pos);
	std::string new_range_nm_;
	std::string select_pro_nm_;

	CSBuffer<SPUB_BAG,1> show_buf_list_;
	CSBuffer<SPUB_BAG_EX,1> show_ex_buf_list_;
	
	boost::mutex mu_mapping_list_;
	std::list<SPUB_BAG_EX> show_mapping_list_;

	bool b_show_ex_reflector_;
	bool b_show_laser_;
	bool b_show_particles_;

	int i_laser_ori_cab_;

private:
	void create_temp_edge_line();

	QGraphicsLineItem* tmp_line_item_;
	QList<QGraphicsItem*> link_edge_pari_;


	QGraphicsRectItem* p_sel_rect_;


	std::list<QGraphicsItem*> l_align_node_;

	THSafe<bool> th_clear_bag_item_;

private:
	boost::mutex mu_reflector_;
	std::vector<reflector_item*> v_reflector_item_;
};

#endif // _KPS_ITEM_COLLECTION_H
