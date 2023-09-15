
#ifndef _STRATEGY_TABLE_H_
#define _STRATEGY_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#include "dispatching/manual_order.h"

#endif


class strategy_model;
class combo_delegate;
class checkbox_delegate;

class strategy_table : public QTableView 
{

	Q_OBJECT

public:

	strategy_table( QWidget *parent = 0 );
	~strategy_table();

	void show_strategy( std::map<int,schedule_interface_data*> &m_schedule_list );

	std::map<int, int> sel_schedule();

	QVector<QStringList> get_data();

	//std::string covSta(manual_order::MANUAL_STATE state);

private:


	strategy_model* model_;

	combo_delegate* combo_del_from_;
	combo_delegate* combo_del_to_;
	checkbox_delegate* checkbox_enable_;
	checkbox_delegate* checkbox_match_;
};

#endif//_STRATEGY_TABLE_H_