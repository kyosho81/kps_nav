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

	QLineEdit* txt_current_;	//��ǰ����
	QLineEdit* txt_current2_;	//��ǰ����
	QLineEdit* txt_total_i2t_;	//�ۼ��ܵ���
	QLineEdit* txt_overload_;	//�Ƿ����

	QLineEdit* txt_v_;			//V
	QLineEdit* txt_acc_;		//v_acc
	QLineEdit* txt_reverse_;	//v_reverse

	QLineEdit* txt_dirction_;	//���㷽��
	QLineEdit* txt_c_dirction_; //��ǰ����
	QLineEdit* txt_pwm_;

	QLineEdit* txt_Current_sv_;	//��ǰ�ٶ�
	QLineEdit* txt_Current_cv_;	//��ǰ�ٶ�
	QLineEdit* txt_Current_cv2_;	//��ǰ�ٶ�
	QLineEdit* txt_out_;	//��ǰ�ٶ�
	QLineEdit* txt_m_sv_;	//�������ƺ���ٶ�

	QLineEdit* txt_hall_;	//����״̬
	QLineEdit* txt_step_;	//������

	QLineEdit* txt_test_direction_;		//����pwm
	QLineEdit* txt_test_pwm_;			//���Է���

	QLineEdit* txt_disable_;		//disable
	QLineEdit* txt_emergency_;		//emergency
	QLineEdit* txt_overload2_;		//overload

	

	QPushButton* btn_Run_;		//��ʼ
	QPushButton* btn_Stop_;		//ֹͣ

	QPushButton* btn_Set_;		//����

	QPushButton* btn_disable_;	//disable
	QPushButton* btn_enable_;	//enable

	QPushButton* btn_set_test_;	//test_model
	QPushButton* btn_set_stop_;	//enable

	bool b_set;					//д��PID����
	bool b_disable;				//disable������
	bool b_enable;				//enable������

	bool b_set_test;			//���ò���ģʽ
	bool b_set_stop;			//����ֹͣģʽ

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