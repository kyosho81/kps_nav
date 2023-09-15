#ifndef _DEVICE_DLG_WANGHONGTAO_2013_03_06_
#define _DEVICE_DLG_WANGHONGTAO_2013_03_06_

#include <QtGui>
#include <QDialog>

class Driver_CMD;
class Plot;

class ControlDlg : public QDialog
{
	Q_OBJECT

public:
	ControlDlg(Plot* plot,QWidget *parent = 0);
	~ControlDlg();
	
	void ShowData();


protected:

private:
	Plot* plot_;
	long last_time_;
	int flag_;

	int mv_;
	int i_pwm_;

	int sv_;
	int cv_;
	int cv2_;
	int out_;

	int current_;
	int total_i2t_;
	int overload_;

	
	QLineEdit* txt_P_;			//P
	QLineEdit* txt_I_;			//I

	QLineEdit* txt_I2_;			//I2
	QLineEdit* txt_t_;			//t

	QLineEdit* txt_current_;	//当前电流
	QLineEdit* txt_current2_;	//当前电流
	QLineEdit* txt_total_i2t_;	//累计总电流
	QLineEdit* txt_overload_;	//是否过流

	QLineEdit* txt_v_;			//V
	QLineEdit* txt_acc_;		//v_acc
	QLineEdit* txt_reverse_;	//v_reverse

	QLineEdit* txt_dirction_;	//计算方向
	QLineEdit* txt_c_dirction_; //当前方向
	QLineEdit* txt_pwm_;

	QLineEdit* txt_Current_sv_;	//当前速度
	QLineEdit* txt_Current_cv_;	//当前速度
	QLineEdit* txt_Current_cv2_;	//当前速度
	QLineEdit* txt_out_;	//当前速度
	QLineEdit* txt_m_sv_;	//加速限制后的速度

	QLineEdit* txt_hall_;	//霍尔状态
	QLineEdit* txt_step_;	//换向步骤

	QLineEdit* txt_test_direction_;		//测试pwm
	QLineEdit* txt_test_pwm_;			//测试方向

	QLineEdit* txt_disable_;		//disable
	QLineEdit* txt_emergency_;		//emergency
	QLineEdit* txt_overload2_;		//overload

	

	QPushButton* btn_Run_;		//开始
	QPushButton* btn_Stop_;		//停止

	QPushButton* btn_Set_;		//设置

	QPushButton* btn_disable_;	//disable
	QPushButton* btn_enable_;	//enable

	QPushButton* btn_set_test_;	//test_model
	QPushButton* btn_set_stop_;	//enable

	bool b_set;					//写下PID参数
	bool b_disable;				//disable驱动器
	bool b_enable;				//enable驱动器

	bool b_set_test;			//设置测试模式
	bool b_set_stop;			//设置停止模式

	void timerEvent(QTimerEvent *);
	int itimer_;
	Driver_CMD* d_cmd_;
	private slots:
		void ChooseRun( bool flag );
		void ChooseStop(bool flag );
		void ChooseSet(bool flag );
		void ChooseEnable(bool flag );
		void ChooseDisable(bool flag );

		void ChooseTestModel(bool flat);
		void ChooseStopModel(bool flat);
		
};
#endif//_DEVICE_DLG_WANGHONGTAO_2013_03_06_s