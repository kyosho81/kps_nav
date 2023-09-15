
#ifndef _MANUAL_TABLE_H_
#define _MANUAL_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#include "dispatching/manual_order.h"

#endif


class manual_model;


class manual_table : public QTableView 
{

	Q_OBJECT

public:

	manual_table( QWidget *parent = 0 );
	~manual_table();

	void show_manual_order(std::map<std::string ,manual_order*> m_manual_order);

	std::vector<std::string>  del_sel_order();
	std::vector<std::string> sel_order();

	QVector<QStringList> get_data();

	std::string covSta(manual_order::MANUAL_STATE state);

private:


	manual_model* model_;


};

#endif//_MANUAL_TABLE_H_