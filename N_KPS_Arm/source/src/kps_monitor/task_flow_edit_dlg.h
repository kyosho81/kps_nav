#ifndef _TASK_FLOW_EDIT_DLG_20230414_H_
#define _TASK_FLOW_EDIT_DLG_20230414_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"

#endif

class task_flow_table;
class task_flow_data;

class task_flow_edit_dlg : public QDialog
{
	Q_OBJECT

public:

	task_flow_edit_dlg( QWidget *parent = 0 );
	~task_flow_edit_dlg();

	task_flow_data* get_task_flow();
	bool save_data();

private:

	QWidget* parent_;

private:
	void init_task_flow();
	
	QComboBox* qcmb_task_flow_nm_;
	QPushButton* btn_add_flow_;
	QPushButton* btn_del_flow_;
	QPushButton* btn_save_flow_;

	QPushButton* btn_analyze_;
	QPushButton* btn_instantiation_;

	QGridLayout* grid_;
	
	bool fill_task_flow_name();

private slots:
	void ChooseAdd( bool flag );
	void ChooseDel( bool flag );
	void ChooseSave( bool flag );

// 	void ChooseAanlyze( bool flag );
// 	void ChooseInstantiation( bool flag );

private:
	void update_table();

	task_flow_table* task_flow_table_;

	void init_btn();
	QGridLayout* btn_grid_;

	QPushButton* btn_add_;	
	QPushButton* btn_del_;

	QPushButton* btn_required_;	
	QPushButton* btn_optional_;
	QPushButton* btn_disable_;

private slots:
	void ChooseAddAct( bool flag );
	void ChooseDelAct( bool flag );

	void ChooseReqAct( bool flag );
	void ChooseOptAct( bool flag );
	void ChooseDisAct( bool flag );
	void onCombChanged(const QString &qs);


};

#endif//_TASK_FLOW_EDIT_DLG_20230414_H_