#ifndef _KPS_ACTION_H
#define _KPS_ACTION_H

#include <QMainWindow>

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

class kps_main_win;
class item_collection;
class GridMap;

class LaserReading;
class laser2d_loop_closure;
class path_search_dlg;
class dynamic_loc;
class PSMNode;

#ifndef Q_MOC_RUN 
#include <boost/signals2.hpp>
#include "bag/bag.h"
#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"
#include "action_permission.h"
#endif


#include "scene/mouse_event.h"

class action_collection : public QObject{

	Q_OBJECT

public:
	action_collection();
	~action_collection();

	void init(kps_main_win* main_win , item_collection* item);
	
	void sel_file_acton();
	void sel_map_acton();
	void sel_location();
	void sel_log_bag();
	void sel_reflector();
	void sel_move();
	void sel_project();
	void sel_calib();
	void sel_loop_closure();
	void sel_show_log();
	void sel_init();
	void sel_tools();

	void clear_all_menu();

	void set_range_pos(qt_eve::mouse_event::SRange_ev event);

	void bind_show_mv(boost::function<bool(void)> fnc);

private:
	
	void load_menu(std::string str_group, QMenu* p_menu);
	kps_main_win* main_win_;
	item_collection* item_;
	action_permission act_permission_;
	std::string str_user_;
//menu
private:
	QMenuBar* main_menuBar_;
	void create_menu();

//tool bar
private:
	QToolBar* main_Toolbar_;
	void create_toolbar();

//mapping menubar
private:
	U32 m_event_;
	bool set_CursorShape(qt_eve::mouse_event::MU_TYPE mt);
	
	void create_map_action();
	
	QMenu* map_menu_;
	QAction* begin_mapping_;
	QAction* end_mapping_;
	QAction* save_mapping_;
	QAction* show_mapping_;
	QAction* begin_bag_mapping_;
	QAction* end_bag_mapping_;

	
	QAction* arm_mapping_;
	bool b_arm_mapping_;
	QString qs_arm_mapping_;
	void th_arm_mapping(std::string str_map_name);

private slots:

	void do_begin_mapping();
	void do_end_mapping();
	void do_begin_bag_mapping();
	void do_end_bag_mapping();
	void do_save_mapping();
	void do_show_mapping();

	void do_arm_mapping();
	

//file action
private:
	
	void create_file_action();

	QMenu* file_menu_;
	//QAction* open_map_;
	QAction* open_map_;
	QAction* upload_map_;
	QAction* download_map_;
	QAction* download_map_file_;
	QAction* save_map_;
	QAction* save_onboard_map_;
	QAction* set_onboard_map_;

	

//map action
private slots:

	void do_open_map();
	
	void th_bag_mapping(std::string bag_path,std::string path);
	void do_bag_mapping_onpc();
	void do_upload_map();
	void do_upload_map_separate();
	void do_download_map();
	void do_download_map_file();
	void do_save_onboard_map();
	void do_save_map();
	void do_set_onboard_map();

	
//locate action
private:

	void create_locate_action();
	QMenu* location_menu_;

	QAction* show_laser_;
	QAction* show_particles_;

	QAction* locate_;
	QAction* auto_locate_;
	
	void th_loop_closure();
	bool b_auto_locate_;

private slots:
	void do_show_laser();
	void do_show_particles();
	void do_locate();
	void do_auto_locate();

	
	
	//log bag action
private:

	void create_log_bag_action();
	QMenu* log_bag_menu_;
	QAction* log_bag_begin_;
	QAction* log_bag_end_;

	QAction* log_bag_play_;
	QAction* log_bag_play_stop_;
	QAction* log_bag_continue_;

	QAction* log_bag_gmapping_;
	QAction* log_bag_upload_;

	QAction* log_bag_suro_debug_;
	QAction* log_bag_play_back;
	QAction* log_bag_ex_play_;
	QAction* log_bag_dynamic_key_;

	QAction* log_bag_clear_;

	protobuf_bag play_back_bag_;
	protobuf_bag_ex play_back_bag_ex_;

private slots:

	void do_log_bag_begin();
	void do_log_bag_end();
	void do_log_bag_play();
	void do_log_bag_play_stop();
	void do_log_bag_play_continue();
	void do_log_upload();

	void do_log_bag_play_onpc();
	void do_log_ex_play_onpc();
	void do_log_keyframe_onpc();

	void do_clear_bag_show();

	void do_log_bag_suro_debug();
	void do_log_bag_flirt_debug();

//reflector action
private:

	void create_reflector_action();
	QMenu* reflector_menu_;

	QAction* open_reflector_;
	QAction* save_reflector_;
	QAction* upload_reflector_;
	QAction* download_reflector_;

	QAction* show_ex_reflector_;
	QAction* add_reflector_;
	QAction* del_item_;

	QAction* log_bag_ex_begin_;
	QAction* log_bag_ex_end_;
	QAction* reflector_mapping_;

	QAction* reflector_gmapping_;
	QAction* reflector_modify_;
	QAction* reflector_g2o_;

private slots:

	void do_open_reflector();
	void do_save_reflector();
	void do_upload_reflector();
	void do_download_reflector();

	void do_show_ex_reflector();
	void do_add_reflector();
	void do_del_ref();

	void do_log_ex_begin();
	void do_log_ex_end();
	void do_ref_mapping();
	void th_ref_mapping(std::string path);

	void do_ref_gmapping();
	void th_ref_gmapping(std::string path);

	void do_ref_modify();
	void th_ref_modify(std::string path);

	void do_ref_g2o();
	void th_ref_g2o(std::string path);

private:
	void* ref_mapping_;
	std::string str_path_gmap_;

	//void del_all_reflect_items();
	//move action
private:

	void create_move_action();
	QMenu* move_menu_;
	QAction* move_cw_;//clockwise
	QAction* move_ccw_;//counterclockwise
	QAction* move_front_;
	QAction* move_back_;
	QAction* move_stop_;
	QAction* move_left_;
	QAction* move_right_;
	QAction* move_ori_;
	QAction* move_show_;

private slots:

	void do_rot_left();
	void do_rot_right();
	void do_move_front();
	void do_move_back();
	void do_move_stop();
	void do_move_left();
	void do_move_right();
	void do_move_universal();
	void do_move_show();
	//calibration action
private:

	void create_calib_action();
	QMenu* calib_menu_;
	QAction* laser_cross_;

private slots:

	void do_show_laser_cross();

	//range action
private:
	bool b_wander_run_;
	void load_pro_item();
	void th_wander();
	void create_project_action();
	QMenu* project_menu_;
	
	QAction* open_project_;
	QAction* save_project_;

	QAction* download_project_;
	QAction* upload_project_;
	QAction* set_onboard_project_;

	

	QAction* select_;
	QAction* align_;
	QAction* rect_;
	QAction* range_;

	QAction* node_;
	QAction* edge_;
	QAction* rand_edge_;
	QAction* del_node_edge_;

	QAction* wander_;
	QAction* auto_cover_;
	
	

	QAction* producer_;
	QAction* consumer_;
	QAction* processer_;
	QAction* storage_;
	QAction* charge_;

	
	bool b_select_;
	bool b_align_;
	bool b_rect_;
	bool b_range_;

	bool b_add_node_;
	bool b_add_edge_;
	bool b_add_producer_;
	bool b_add_consumer_;
	bool b_add_processer_;
	bool b_add_storage_;
	bool b_add_charge_;

	private slots:

		void do_open_project();
		void do_save_project();

		void do_download_project();
		void do_upload_project();
		void do_set_onboard_project();

		void do_select();
		void do_align();
		void do_node();
		void do_edge();
		void do_rand_edge();
		void do_del_node_edge();

		void do_range();
		void do_rect();
		
		void do_wander();
		void do_auto_cover();

		void do_producer();
		void do_consumer();
		void do_processer();
		void do_storage();
		void do_charge();
	//loop closure
private:

	void create_loop_closure_action();
	QMenu* loop_closure_menu_;
	QAction* load_refscan_;
	QAction* mathc_one_;

private slots:
	void do_load_ref();
	void do_match_one_scan();
	void conver_laserRead2pubBag(SPUB_BAG &pub_bag,LaserReading* lreadReference);

private:
	void create_show_log();
	QMenu* show_log_menu_;
	QAction* show_log_;
	QAction* clear_log_;
	QAction* set_priority_;
	QAction* set_para_;

private slots:
	void do_show_log();
	void do_clear_log();
	void do_set_priority();
	void do_set_para();

	//init action
private:

	void create_init_action();
	QMenu* init_menu_;

	QAction* para_init_;
	QAction* auto_init_;

private slots:
	void do_para_init();
	void do_auto_init();

	//tools action
private:

	void create_tools_action();
	QMenu* tools_menu_;

	QAction* zoom_in_;
	QAction* zoom_out_;
	QAction* search_path_;
	QAction* dy_location_;
	QAction* scan_match_;
	QAction* add_qr_code_;
	QAction* exp_qr_code_;
	QAction* imp_qr_code_;

	path_search_dlg* path_search_dlg_;
	dynamic_loc* p_dy_;
	SAMCL_CONFIDENCE amcl_conf_;
	PSMNode* p_psm_node_;

	bool b_add_qrcode_;

	private slots:
		void do_zoom_in();
		void do_zoom_out();
		void do_search_path();
		void do_dynamic_loc();
		void do_scan_match();
		void do_add_qrcode();
		void do_exp_qrcode();
		void do_imp_qrcode();
private://map item

	void show_map_date(const std::vector<int> &v_data);
	void set_mouse_event(const qt_eve::mouse_event::MU_TYPE &type);
	
	bool b_locate_;
	bool b_add_reflector_;

private://process bar
	bool get_process_bar(SProcess_Bar &pro_bar);

private:
	std::string bag_path_;
	bool b_laser_diff_;
	cbag bag_;
	
// loop_closure
	laser2d_loop_closure* p_lc_;
	int i_current_index_;
	
	////////////////
	//GridMap* p_tmp_map_;

private:
	std::string pro_path_;
signals:
	void sig_show_mapping_str(QString str);
public slots:
	void slot_show_mapping_str(QString str);

signals:
	void sig_show_wander_str(QString str);
public slots:
	void slot_show_wander_str(QString str);
	
private:
	boost::function<bool (void)> fnc_show_mv_;
};

#endif // _KPS_ACTION_H
