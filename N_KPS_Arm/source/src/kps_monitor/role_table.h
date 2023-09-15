
#ifndef _ROLE_TABLE_H_
#define _ROLE_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif


class protobuf_base;
class role_model;

class role_table : public QTableView 
{

	Q_OBJECT

public:
	role_table( QWidget *parent = 0 );
	~role_table();

	void show_role_list(std::multimap< std::string, protobuf_base*> &mm_roles);



private:


	role_model* model_;


};

#endif//_ROLE_TABLE_H_