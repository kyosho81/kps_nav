#ifndef _TASK_FLOW_DLG_20230414_H_
#define _TASK_FLOW_DLG_20230414_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"
#include "protobuf_msg/base.pb.h"
#endif

class map_scene;
class task_flow_para_dlg;
class task_flow_edit_dlg;
class protobuf_base;
class task_flow_data;

class task_flow_dlg : public QDialog
{
	Q_OBJECT

public:

	task_flow_dlg( QWidget *parent = 0 );
	~task_flow_dlg();

	void init( map_scene* map_scene );

private:


	map_scene* map_scene_;
	//map_view* map_view_;
	task_flow_para_dlg* task_flow_para_dlg_;
	task_flow_edit_dlg* task_flow_edit_dlg_;

	
private:
	protobuf_base* get_role( std::string str_name, std::map<std::string,std::string> m_para);
	std::string get_para(std::string str_name,std::map<std::string,std::string> m_para);
	int filter_action(std::list<KPS::mp_bind_action> &l_bind_action, std::string type);
	int get_turn_action(std::vector<int> &v_turn_node, std::list<KPS::mp_bind_action> l_bind_action);
	int do_analyze(task_flow_data* tf, std::map<std::string,std::string> m_main_para , std::map<std::string,std::string> m_ext_para);

private slots:

	void ChooseAnalyze(bool flag);
	void ChooseInstantiation(bool flag);
	

};

#endif//_TASK_FLOW_DLG_20230414_H_