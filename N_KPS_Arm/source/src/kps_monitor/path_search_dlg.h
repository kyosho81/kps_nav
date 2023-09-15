#ifndef _PATH_SEARCH_DLG_H_
#define _PATH_SEARCH_DLG_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include <QTextEdit>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
class task_rpc_client;
#endif



class path_search_dlg : public QDialog
{
	Q_OBJECT

public:

	path_search_dlg( QWidget *parent = 0 );
	~path_search_dlg();

	void init();

	void init_timer();


	public slots:
		void updateTimerEvent();
		bool eventFilter(QObject * watched , QEvent * event);

	void ChooseExchange( bool flag );
	void ChooseSearch( bool flag );
	void ChooseShow( bool flag );
	void ChooseClose( bool flag );

	
	void ChooseMvlist( bool flag );
	void ChooseMvdetail( bool flag );

	void ChooseErase( bool flag );
	void ChooseLoad( bool flag );
	void ChooseSave( bool flag );

	void ChooseRunPath( bool flag );
	void ChooseRunLoop( bool flag );

private:
	bool event(QEvent *e);
	void init_node_list();
	void init_start_node();
	void init_end_node();
	void init_start_angle();
	void init_end_angle();

	bool b_run_;
	QTimer *timer_;
	QStringList indicator_;

	QComboBox* qcmb_start_node_;
	QCompleter* qcomp_start_node_;
	QStringListModel* qstrlist_start_node_;
	QLineEdit* qedit_start_node_;

	QComboBox* qcmb_end_node_;
	QCompleter* qcomp_end_node_;
	QStringListModel* qstrlist_end_node_;
	QLineEdit* qedit_end_node_;

	QComboBox* qcmb_start_angle_;
	QCompleter* qcomp_start_angle_;
	QStringListModel* qstrlist_start_angle_;
	QLineEdit* qedit_start_angle_;

	QComboBox* qcmb_end_angle_;
	QCompleter* qcomp_end_angle_;
	QStringListModel* qstrlist_end_angle_;
	QLineEdit* qedit_end_angle_;

	QLineEdit* qedit_speed_;
	QLineEdit* qedit_ori_;

	QTextEdit* txt_Result_;

	QPushButton* btn_exchange_;
	QPushButton* btn_search_;
	QPushButton* btn_show_;
	QPushButton* btn_close_;

	//QTextEdit* txt_mult_path_;
	QListWidget* txt_path_;

	QPushButton* btn_mvlist_;
	QPushButton* btn_mvdetail_;

	QPushButton* btn_erase_path_;
	QPushButton* btn_load_path_;
	QPushButton* btn_save_path_;

	QPushButton* btn_run_path_;
	QPushButton* btn_run_loop_;
	int index_;

	int get_run_path(std::vector<SPathData> &seg_path);
	task_rpc_client* p_task_rpc_client_;
	std::list<std::vector<SPathData>> l_run_path_;
	std::list<std::vector<SPathData>>::iterator it_run_;
	int i_run_path_id_;
	void show_path_loop();

private:
	std::string get_dev_ip();
	ORIENTAION ori_;
	std::list<int> l_path_;
};

#endif//_PATH_SEARCH_DLG_H_