#ifndef _TASK_FLOW_EXTERN_PARA_TAB_20230414_H_
#define _TASK_FLOW_EXTERN_PARA_TAB_20230414_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"

#endif


class task_flow_extern_para_tab : public QDialog
{
	Q_OBJECT

public:

	task_flow_extern_para_tab( QWidget *parent = 0 );
	~task_flow_extern_para_tab();

	int get_para( std::map<std::string,std::string> &m_para );
	

private:


	QPushButton* btn_accepte_order_;	
	


private slots:
// 	void ChooseRunHis( bool flag );
// 	void ChooseAccepteOrder( bool flag );

};

#endif//_TASK_FLOW_EXTERN_PARA_TAB_20230414_H_