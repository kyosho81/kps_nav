
#ifndef _AGV_MANAGE_TABLE_H_
#define _AGV_MANAGE_TABLE_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif



class agv_manage_model;

class agv_manage_table : public QTableView 
{

	Q_OBJECT

public:
	agv_manage_table( QWidget *parent = 0 );
	~agv_manage_table();

	void show_agv_list(const std::map<int,SAGV_Info> &m_agv_info ,std::map<int,SRobot_Inf> &m_robo_info, const std::map<int,std::pair<int,int>> &m_lock_pause, const std::map<int,SAct_Fork> &m_ex_data);

	std::map<int, int> sel_agv_lock();

private:


	agv_manage_model* model_;

	std::string covAgvType(const AGV_TYPE agv_type);
	std::string covAgvStatus(int status);
	std::string covLock(int i_lock);
	std::string covPause(int i_pause);
	
};

#endif//_AGV_MANAGE_TABLE_H_