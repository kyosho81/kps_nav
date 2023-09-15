
#ifndef _ORDER_TABLE_H_
#define _ORDER_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif

class protobuf_base;
class order_schedule;
class order_model;

class order_table : public QTableView 
{

	Q_OBJECT

public:
	order_table( QWidget *parent = 0 );
	~order_table();

	void show_order_list(std::list<order_schedule*> l_order);
	


private:

	std::string get_role_name( protobuf_base* p_role );

	order_model* model_;


};

#endif//_ORDER_TABLE_H_