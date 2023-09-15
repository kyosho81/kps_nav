
#ifndef _TASK_FLOW_TABLE_TABLE_H_
#define _TASK_FLOW_TABLE_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#include "dispatching/manual_order.h"
#include "robot/task_flow_def.h"
#endif


class task_flow_model;
class combo_delegate;
class checkbox_delegate;

class task_flow_table : public QTableView 
{

	Q_OBJECT

public:

	task_flow_table( QWidget *parent = 0 );
	~task_flow_table();

	void show_task_flow( std::list<SSTaskFlow*> &l_task_flow );

	std::map<int, int> sel_task_flow();

	QVector<QStringList> get_data();
	std::list<std::pair<int,int> > get_sel();
	//std::string covSta(manual_order::MANUAL_STATE state);

private:


	task_flow_model* model_;

	combo_delegate* combo_del_get_put_;
	combo_delegate* combo_del_mv_seg_;
	std::map<int,combo_delegate*> m_combo_del_act_;
	
	//checkbox_delegate* checkbox_enable_;
};

#endif//_TASK_FLOW_TABLE_TABLE_H_