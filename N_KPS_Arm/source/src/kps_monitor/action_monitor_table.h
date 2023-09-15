
#ifndef _ACTION_MONITOR_TABLE_H_
#define _ACTION_MONITOR_TABLE_H_

#include <QTimer>
#include <QTableView>
#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif



class action_data_model;

class action_monitor_table : public QTableView 
{

	Q_OBJECT

public:
	action_monitor_table( QWidget *parent = 0 );
	~action_monitor_table();

	action_data_model* model_;
	int get_select_action_id();

private:

};

#endif//_ACTION_MONITOR_TABLE_H_