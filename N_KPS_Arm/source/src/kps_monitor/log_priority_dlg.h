#ifndef _LOG_PRIORITY_DLG_KYOSHO_20200702_H_
#define _LOG_PRIORITY_DLG_KYOSHO_20200702_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include "scene/mouse_event.h"
#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

class cTransferDevice;

class QtProperty;
class QtVariantProperty;
class QtVariantPropertyManager;
class QtEnumPropertyManager;
class QtBoolPropertyManager;
class QtTreePropertyBrowser;


class log_priority_dlg : public QDialog
{
	Q_OBJECT

public:

	log_priority_dlg( QWidget *parent = 0 );
	~log_priority_dlg();

	void init(const std::string str_ip);
	

private:

	void init_timer();
	void stop_timer();
	
	void init_tcp_client();
	
	std::string str_ip_;
	int i_log_port_;
	cTransferDevice* p_tcp_client_;

	QTimer *timer_;

	//get priority
	bool b_check_value_change_;//when refresh data don't send,only when manual change
	void set_pro_nm_priority(const std::string &str_pro_nm, const std::string &str_priority);
	void init_cmd();
	U8 ch_get_all_priority_[100];
	int i_get_all_priority_;
	U8 ch_set_priority_[100];
	int i_set_priority_;

	U8 ch_read_all_[500];
	int i_read_all_;

public slots:

	void valueChanged(QtProperty *property, const QVariant &value);
	void valueChanged(QtProperty *property, int val);

	//para grid
private:
	
	QWidget* create_para_wiget();

	QtVariantPropertyManager *variantManager_;
	QtEnumPropertyManager *enumManager_;
//	QtBoolPropertyManager *boolManager_;
	QtTreePropertyBrowser *variantEditor_;
	//QtProperty *log_priority_group_;

//	QtProperty *item_log_priority_;
// 	QtVariantProperty* item_laser_ip_;
// 	QtProperty* item_laser_reverse_;
// 	QtVariantProperty* item_laser_start_angle_;
	std::map<std::string,QtProperty*> m_log_name_pri_;
	QStringList enumNames_;

	QPushButton* btn_refresh_;	//refresh 
	QPushButton* btn_save_;	    //save priority
	QPushButton* btn_close_;	//close window

private slots:
	bool get_priority();
	void ChooseRefresh( bool flag );
	void ChooseSave( bool flag );
	void ChooseClose( bool flag );
	//int str_pri_to_index(const std::string &str_priority);
	//void ChoosePreView(bool flag );
	



};

#endif//_LOG_PRIORITY_DLG_KYOSHO_20200702_H_