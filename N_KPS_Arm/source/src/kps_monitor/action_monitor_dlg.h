
#ifndef _ACTION_MONITOR_DLG_H_
#define _ACTION_MONITOR_DLG_H_

#include <QTimer>
#include <QTableView>
#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif



class action_monitor_table;

class action_monitor_dlg : public QDialog 
{

	Q_OBJECT

public:
	action_monitor_dlg( QWidget *parent = 0 );
	~action_monitor_dlg();

	void init_timer();

	void set_tfb(const std::vector<task_feadback> &tfb);

	public slots:
		void updateProgressValue();

private:

	QTimer *timer_;

	action_monitor_table* action_table_;

private:
	
	void init_action_type_cmb();
	void set_action_type();
	void init_table();

	std::map<U8,std::string> m_type_name_;
	std::map<U8,std::pair<std::string,std::string>> m_type_para_;
	std::map<U8,int> m_devid_taskid_;

	QLineEdit* qedit_action_para_exp_;
	QLineEdit* qedit_action_para_;

	QStringList indicator_;
	QComboBox* qcmb_action_type_;
	QCompleter* qcomp_action_type_;
	QStringListModel* qstrlist_action_type_;
	QLineEdit* qedit_action_type_;

	QPushButton* btn_run_;
	QPushButton* btn_force_complete_;
	QPushButton* btn_redo_;
	QPushButton* btn_del_;

	QPushButton* btn_load_;	
	QPushButton* btn_save_;

private:
	boost::mutex mu_tfb_;
	std::vector<task_feadback> tfb_;
	bool check_task_init(task_feadback &fb,int i_task_id);
private slots:
	
	void ChooseRun( bool flag );
	void ChooseForceComplete( bool flag );
	void ChooseRedo( bool flag );
	void ChooseDel( bool flag );

	void ChooseLoad( bool flag );
	void ChooseSave( bool flag );

public slots:
	bool eventFilter(QObject * watched , QEvent * event);
};

#endif//_ACTION_MONITOR_DLG_H_