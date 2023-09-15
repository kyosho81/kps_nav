#ifndef _MANUAL_CTL_DLG_20230214_H_
#define _MANUAL_CTL_DLG_20230214_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "Comm/buffer_con.hpp"
#endif



class manual_ctl_dlg : public QDialog
{
	Q_OBJECT

public:

	manual_ctl_dlg( QWidget *parent = 0 );
	~manual_ctl_dlg();

	void init();

	bool show_btn();

private:
	
	QPushButton* btn_ccw_;	            //counterclockwise
	QPushButton* btn_cw_;	            //clockwise
	QPushButton* btn_forward_;	        //forward
	QPushButton* btn_backward_;	        //backward
	QPushButton* btn_leftshift_;	    //leftshift
	QPushButton* btn_rightshift_;	    //rightshift
	QPushButton* btn_stop_;	            //stop
	
	bool b_show_;
private slots:
	
	void ChooseCCW( bool flag );
	void ChooseCW( bool flag );
	void ChooseForward( bool flag );
	void ChooseBackward( bool flag );
	void ChooseLeftShift( bool flag );
	void ChooseRightShift( bool flag );
	void ChooseStop( bool flag );
	
	
};

#endif//_MANUAL_CTL_DLG_20230214_H_