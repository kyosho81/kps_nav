
#ifndef _INTERFACE_TABLE_H_
#define _INTERFACE_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif


class interface_delegate;
class interface_model;
class manual_order;

class interface_table : public QTableView 
{

	Q_OBJECT

public:

	interface_table( QWidget *parent = 0 );
	~interface_table();

	void show_manual_order(std::map<std::string ,manual_order*> m_manual_order);

	std::vector<std::string>  del_sel_order();
	std::vector<std::string> sel_order();

	QVector<QStringList> get_data();

private:


	interface_model* model_;
	interface_delegate* delegate_;

};

#endif//_INTERFACE_TABLE_H_