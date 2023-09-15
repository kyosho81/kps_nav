#ifndef _TASK_FLOW_PARA_DLG_20230414_H_
#define _TASK_FLOW_PARA_DLG_20230414_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"

#endif

class task_flow_main_para_tab;
class task_flow_extern_para_tab;

class task_flow_para_dlg : public QDialog
{
	Q_OBJECT

public:

	task_flow_para_dlg( QWidget *parent = 0 );
	~task_flow_para_dlg();

	int get_main_para(std::map<std::string,std::string> &m_para);
	int get_ext_para(std::map<std::string,std::string> &m_para);

private:

	QTabWidget *tabWidget;

	task_flow_main_para_tab* tb_task_flow_main_para_tab_;
	task_flow_extern_para_tab* tb_task_flow_extern_para_tab_;
};

#endif//_TASK_FLOW_PARA_DLG_20230414_H_