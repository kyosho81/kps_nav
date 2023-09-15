#ifndef _DEV_MONITOR_DLG_H_
#define _DEV_MONITOR_DLG_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#endif

class dev_data_model;

class Dev_monitor_dlg : public QTableView 
{

	Q_OBJECT

public:
	Dev_monitor_dlg( QWidget *parent = 0 );
	~Dev_monitor_dlg();

	void init_timer();

	
	public slots:
		void updateProgressValue();

private:

	QTimer *timer_;
	dev_data_model* model_;

private:
	std::string toStrDevStatus(const int &sta);
	std::string toStrDevErrCode(const SDevStatus  &sta);
	std::string err_codeToStr(const U16 &err_code);
};

#endif//_DEV_MONITOR_DLG_H_