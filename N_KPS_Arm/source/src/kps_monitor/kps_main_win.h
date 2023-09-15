#ifndef _KPS_MAIN_WIN_H
#define _KPS_MAIN_WIN_H

#include <QtGui/QMainWindow>
//#include "ui_driver_arm.h"
#include <QtGui>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "threadpool/threadpool.hpp"
#endif

class Plot;
class map_scene;
class map_view;
class action_collection;
class item_collection;
class mouse_event;
class Calib_dlg;
class action_monitor_dlg;
class cTransferDevice;
class rpc_config_server;
class agv_manage_dlg;
class data_manage_dlg;
class order_dlg;
class interface_dlg;
class strategy_dlg;
class dio_dlg;
class task_flow_dlg;

class kps_main_win : public QMainWindow
{
	Q_OBJECT

public:
	kps_main_win( bool b_init_core, bool b_agvs, QWidget *parent = 0, Qt::WFlags flags = 0);
	~kps_main_win();
	
// 	void sel_map_dock();
// 	void sel_task_dock();
// 	void sel_calib_dock();

	map_scene* get_scene();
	map_view* get_view();
	action_monitor_dlg* get_action();
	void show_status_bar(std::string str_msg);
	void show_entropy_bar(const SAMCL_ENTROPY &ae);
	void show_confidence_bar(const SAMCL_CONFIDENCE &ac);
	void show_rconfidence_bar( const SPOS_CONFIDENCE &ac );

	void show_process(const std::string &str_nm,const int &icount ,const int &itotal);
	void show_process(SProcess_Bar pro_bar);
	void set_show_log();
	void clear_show_log();
	void clear_show_bag();
	//void set_check_priority(bool b_check);
	//void bind_show_priority( boost::function<void(const std::string &str_pro_nm, const std::string &str_priority)> fnc);
	std::string get_ip();
	
	void remove_agv();

private:

	bool b_agvs_;

	typedef enum{DEV_STA,MAPPING,LOCATION,LOG_BAG,REFLECTOR,CALIB,PROJECT,LOOP_CLOSURE,INIT,TOOLS} MTYPE;
	void CreateMenuDock();
	void CreateDevMonitorDock();
	void CreateMapMonitorDock();
	void CreateCalibrationDock();
	void CreateActionTrayDock();
	void CreateDataDock();
	void CreateOrderDock();
	void CreateInterfaceDock();
	void CreateStrategyDock();
	void CreateTaskFlowDock();

	//void sel_dev_dock();
	
	bool Reg_sh_map(std::string sh_name,U32 dsize);
	void create_rpc( bool b_init_core );
	bool b_online_;

	std::string para_ip_;
	QButtonGroup* buttonGroup_; 
	QWidget *menu_widget_;
	QWidget* dev_widget_;
	QWidget* project_widget_;
	QWidget* calib_widget_;
	QWidget* tcontrol_widget_;

	map_scene* map_scene_;
	map_view* map_view_;

	QDockWidget* menu_dock_;
	QDockWidget* dev_dock_;
	QDockWidget* map_dock_;
	QDockWidget* calib_dock_;
	QDockWidget* action_dock_;
	QDockWidget* agv_manage_dock_;
	QDockWidget* dio_dock_;
	QDockWidget* order_dock_;
	QDockWidget* interface_dock_;
	QDockWidget* strategy_dock_;
	QDockWidget* log_dock_;
	QDockWidget* data_manage_dock_;
	QDockWidget* task_flow_dock_;
	//Ui::Driver_ArmClass ui;
	Plot* plot;

	action_collection* action_;
	item_collection* item_;

	Calib_dlg* calib_dlg_;
	action_monitor_dlg* action_dlg_;
	agv_manage_dlg* agv_manage_dlg_;
	dio_dlg* dio_dlg_;
	data_manage_dlg* data_manage_dlg_;
	order_dlg* order_dlg_;
	interface_dlg* interface_dlg_;
	strategy_dlg* strategy_dlg_;
	task_flow_dlg* task_flow_dlg_;

private slots:
	void buttonGroupClicked(int type);

private:

	void create_status_bar();
	
	QLabel* lab_status_;

private:

	void create_confidence_bar();
	QLabel* lab_entropy_;
	QLabel* lab_confidence_;

private:
	void create_process_bar();
	QProgressBar* process_bar_;
	bool b_show_pro_;

private:
	void CreateLogDock();
	void slot_print_log(std::string str);
	void connect_log_server();
	bool merge_data(std::string &str,char* p_data,const int &ilen);
	void th_log_client();
	void show_log();
	void show_action();

	
	//void pro_priority_filter(std::string &str);
	//THSafe<bool> th_check_priority_;
	bool b_show_log_;
	LBuffer<std::string> mubuf_log_;
	boost::threadpool::pool pt_log_;
	THSafe<int> th_log_run_;
	cTransferDevice* tcp_log_client_;
	std::string str_merge_str_;
	QTextBrowser* log_browser_;
	
	boost::function<void(const std::string &str_pro_nm, const std::string &str_priority)> fnc_show_priority_;

private:
	int timer_id_;
	void timerEvent(QTimerEvent *event);

	void run_timer();
	void stop_timer();
	

	THSafe<SProcess_Bar> ths_process_bar_;
	
private:
	rpc_config_server* rpc_config_server_;

private:
	bool update_pipe_log_playback(std::string name,U8* data,U32 len);
	

};

#endif // _KPS_MAIN_WIN_H
