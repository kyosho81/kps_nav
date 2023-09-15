#ifndef _TASK_FLOW_MAIN_PARA_TAB_20230414_H_
#define _TASK_FLOW_MAIN_PARA_TAB_20230414_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"

#endif


class task_flow_main_para_tab : public QWidget
{
	Q_OBJECT

public:

	task_flow_main_para_tab( QWidget *parent = 0 );
	~task_flow_main_para_tab();
	
	int get_para( std::map<std::string,std::string> &m_para );

private:

	void init_roles(QGridLayout* grid);

	QComboBox* qcmb_role_from_;
	QComboBox* qcmb_role_from_id_;

	QComboBox* qcmb_role_to_;
	QComboBox* qcmb_role_to_id_;

	QComboBox* qcmb_node_id_;
	QComboBox* qcmb_start_angle_;
	QCompleter* qcomp_start_angle_;
	QStringListModel* qstrlist_start_angle_;
	QLineEdit* qedit_start_angle_;


	QComboBox* qcmb_pallet_type_;
	QComboBox* qcmb_cargo_type_;

	void init_start_angle();
	void fill_cmb_role();
	void fill_cmb_type();

	public slots:
		bool eventFilter(QObject * watched , QEvent * event);
		
};

#endif//_TASK_FLOW_MAIN_PARA_TAB_20230414_H_