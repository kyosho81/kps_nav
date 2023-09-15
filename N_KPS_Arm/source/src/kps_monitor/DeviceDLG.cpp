#include "plot/Plot_Lib.h"
#include "Struct.h"
#include "Dirver_CMD.h"
#include "ControlDLG.h"

ControlDlg::ControlDlg( Plot* plot,QWidget *parent ):plot_(plot)
{
	QGridLayout *grid = new QGridLayout();

	QLabel *hall_label = new QLabel(tr("Hall:"));	//霍尔状态
	QLabel *step_label = new QLabel(tr("Step:"));   //当前运行步骤

	QLabel *c_direction_label = new QLabel(tr("c_dircetion:"));//当前方向
	QLabel *cv_label = new QLabel(tr("CV:"));                  //当前速度

	QLabel *v_label = new QLabel(tr("v:"));		  //当前设定值
	QLabel *sv_label = new QLabel(tr("SV:"));     //各种变换后设定值
	QLabel *msv_label = new QLabel(tr("Mcu SV:"));//嵌入式计算加速度后的设定值

	QLabel *out_label = new QLabel(tr("Out:"));   //PID计算后的输出速度
	QLabel *direction_label = new QLabel(tr("dircetion:")); //输出方向
	QLabel *pwm_label = new QLabel(tr("pwm:"));             //输出PWM

	QLabel *P_label = new QLabel(tr("P:"));		 //P参数
	QLabel *I_label = new QLabel(tr("I:"));      //I参数

	QLabel *I2_label = new QLabel(tr("I_max:")); //超过电流算I2t
	QLabel *t_label = new QLabel(tr("I_t:"));    //I2t最大累计时间
	

	
	QLabel *v_reverse_label = new QLabel(tr("reverse:")); //是否反向
	QLabel *v_acc_label = new QLabel(tr("v_acc:"));       //加速限幅



	QLabel *current_label = new QLabel(tr("Current:"));    //当前电流
	QLabel *total_i2t_label = new QLabel(tr("Total_i2t:"));//当前累计电流
	QLabel *overload_label = new QLabel(tr("Overload:"));  //是否过流保护

	


	txt_hall_ = new QLineEdit;
	txt_step_ = new QLineEdit;

	txt_c_dirction_ = new QLineEdit();
	txt_Current_cv_ = new QLineEdit();
	txt_Current_cv2_ = new QLineEdit();

	txt_v_ = new QLineEdit;
	txt_Current_sv_ = new QLineEdit();
	
	txt_reverse_ = new QLineEdit;
	txt_acc_ = new QLineEdit;

	txt_dirction_ = new QLineEdit();
	
	txt_pwm_ = new QLineEdit();

	
	
	txt_out_ = new QLineEdit();
	txt_m_sv_ = new QLineEdit();

	txt_P_ = new QLineEdit();
	txt_I_ = new QLineEdit();

	txt_I2_ = new QLineEdit();
	txt_t_ = new QLineEdit();


	txt_current_ = new QLineEdit();
	txt_current2_ = new QLineEdit();
	txt_total_i2t_ = new QLineEdit();
	txt_overload_ = new QLineEdit(); 

	txt_test_direction_ = new QLineEdit();
	txt_test_pwm_ = new QLineEdit();

	txt_disable_ = new QLineEdit();
	txt_emergency_ = new QLineEdit();
	txt_overload2_ = new QLineEdit();

	btn_Run_ = new QPushButton("Run");
	btn_Stop_ = new QPushButton("Stop");
	btn_Set_ = new QPushButton("Set");
	btn_disable_ = new QPushButton("Disable");
	btn_enable_ = new QPushButton("Enable");

	btn_set_test_ = new QPushButton("Test");
	btn_set_stop_ = new QPushButton("Stop");

	grid->addWidget(hall_label,0,0);
	grid->addWidget(step_label,1,0);
	grid->addWidget(txt_hall_,0,1);
	grid->addWidget(txt_step_,1,1);

	grid->addWidget(c_direction_label,2,0);
	grid->addWidget(cv_label,3,0);
	grid->addWidget(txt_c_dirction_,2,1);
	grid->addWidget(txt_Current_cv_,3,1);
	grid->addWidget(txt_Current_cv2_,3,2);

	
	grid->addWidget(v_label,4,0);
	grid->addWidget(sv_label,5,0);
	grid->addWidget(msv_label,6,0);
	
	grid->addWidget(txt_v_,4,1);
	grid->addWidget(txt_Current_sv_,5,1);
	grid->addWidget(txt_m_sv_,6,1);

	
	grid->addWidget(out_label,7,0);
	grid->addWidget(direction_label,8,0);
	grid->addWidget(pwm_label,9,0);
	grid->addWidget(txt_out_,7,1);
	grid->addWidget(txt_dirction_,8,1);
	grid->addWidget(txt_pwm_,9,1);

	
	grid->addWidget(P_label,10,0);
	grid->addWidget(I_label,11,0);
	grid->addWidget(txt_P_,10,1);
	grid->addWidget(txt_I_,11,1);
	
	
	grid->addWidget(I2_label,12,0);
	grid->addWidget(t_label,13,0);
	grid->addWidget(txt_I2_,12,1);
	grid->addWidget(txt_t_,13,1);


	grid->addWidget(v_acc_label,14,0);
	grid->addWidget(v_reverse_label,15,0);
	grid->addWidget(txt_acc_,14,1);
	grid->addWidget(txt_reverse_,15,1);

	
	grid->addWidget(current_label,16,0);
	grid->addWidget(total_i2t_label,17,0);
	grid->addWidget(overload_label,18,0);
	grid->addWidget(txt_current_,16,1);
	grid->addWidget(txt_current2_,16,2);
	grid->addWidget(txt_total_i2t_,17,1);
	grid->addWidget(txt_overload_,18,1);

	grid->addWidget(btn_Run_,19,0);
	grid->addWidget(btn_Stop_,19,1);
	grid->addWidget(btn_Set_,19,2);

	grid->addWidget(btn_disable_,22,0);
	grid->addWidget(btn_enable_,22,1);


	
		
	QLabel *test_pwm_label = new QLabel(tr("PWM:"));    //当前电流
	QLabel *test_direction_label = new QLabel(tr("Direction:"));//当前累计电流
	grid->addWidget(test_direction_label,23,0);
	grid->addWidget(txt_test_direction_,23,1);
	grid->addWidget(test_pwm_label,23,2);
	grid->addWidget(txt_test_pwm_,23,3);
	grid->addWidget(btn_set_test_,23,4);
	grid->addWidget(btn_set_stop_,23,5);


	QLabel *lab_disable_ = new QLabel(tr("disable:"));    //I2t最大累计时间
	QLabel *lab_emergency_ = new QLabel(tr("emergency:"));    //I2t最大累计时间
	QLabel *lab_overload2_ = new QLabel(tr("overload:"));    //I2t最大累计时间
	grid->addWidget(lab_disable_,24,0);
	grid->addWidget(lab_emergency_,24,1);
	grid->addWidget(lab_overload2_,24,2);

	grid->addWidget(txt_disable_,25,0);
	grid->addWidget(txt_emergency_,25,1);
	grid->addWidget(txt_overload2_,25,2);

	


	setLayout(grid);

	d_cmd_ = new Driver_CMD();

	connect(btn_Run_, SIGNAL(clicked(bool)), this, SLOT(ChooseRun(bool)));
	connect(btn_Stop_, SIGNAL(clicked(bool)), this, SLOT(ChooseStop(bool)));
	connect(btn_Set_, SIGNAL(clicked(bool)), this, SLOT(ChooseSet(bool)));

	connect(btn_disable_, SIGNAL(clicked(bool)), this, SLOT(ChooseDisable(bool)));
	connect(btn_enable_, SIGNAL(clicked(bool)), this, SLOT(ChooseEnable(bool)));

	connect(btn_set_test_, SIGNAL(clicked(bool)), this, SLOT(ChooseTestModel(bool)));
	connect(btn_set_stop_, SIGNAL(clicked(bool)), this, SLOT(ChooseStopModel(bool)));

	mv_ = plot_->AddPlot("mv",500);

	i_pwm_ = plot_->AddPlot("pwm",500);
	sv_ = plot_->AddPlot("sv",500);
	cv_ = plot_->AddPlot("cv",500);
	cv2_ = plot_->AddPlot("cv2",500);
	out_ = plot_->AddPlot("out",500);

	current_ = plot_->AddPlot("current",500);
	total_i2t_ = plot_->AddPlot("total_i2t",500);
	overload_ = plot_->AddPlot("overload",500);

	last_time_ = 0;
	flag_ = 1;

	txt_P_->setText(QString::number(0.01));
	txt_I_->setText(QString::number(0.05));
	
	txt_I2_->setText(QString::number(20));
	txt_t_->setText(QString::number(10));
	txt_current_->setText(QString::number(0));

	txt_v_->setText(QString::number(0));
	txt_reverse_->setText(QString::number(1));
	txt_acc_->setText(QString::number(200000));

	txt_test_direction_->setText(QString::number(CW));
	txt_test_pwm_->setText(QString::number(0));

	b_set = true;
	b_disable = false;
	b_enable = false;

	b_set_test = false;
	b_set_stop = false;

}

ControlDlg::~ControlDlg()
{

}

void ControlDlg::ShowData()
{

}
void ControlDlg::timerEvent(QTimerEvent *){
	S8 direction = 0;
	S8 c_direction = 0;
	U8 pwn = 0;

	F32 cv = 0;
	F32 cv2 = 0;
	F32 out = 0;
	F32 current = 0;

	F32 RPM = 0 ;
	F32 C_RPM = 0;
	F32 current2 = 0 ;

	U8 disable = 0;
	U8 emergency = 0;
	U8 over_load2 = 0;
	U8 pwm2 = 0;

	F32 current_i2t = 0.0;
	F32 totoal_i2t = 0.0;
	U8 over_load =	0;
	U8 hall;
	U8 step;

	S8 test_direction  = CW;
	U8 test_pwm = 0;;

	boost::posix_time::ptime systime( boost::posix_time::microsec_clock::local_time());
	boost::posix_time::time_duration localtd = systime.time_of_day();
	double local_time = localtd.total_microseconds() / 1e6;
	
	if (last_time_ == 0)
	{
		last_time_ = local_time;
	}
	else{
		double diff = local_time - last_time_;
		if (diff > 5)
		{
			//flag_ = -flag_;
			last_time_ = local_time;
		}
	}


	
	F32 p = txt_P_->text().toFloat();
	F32 i = txt_I_->text().toFloat();

	U8 I2 = txt_I2_->text().toInt();
	U8 t = txt_t_->text().toInt();


	F32 sv = txt_v_->text().toFloat();
	sv = flag_* sv;
	F32 acc = txt_acc_->text().toFloat();
	S8 reverse = txt_reverse_->text().toFloat();
	
	d_cmd_->SetSpeed(sv);
	//d_cmd_->Set_Driver2_V(sv,sv);
	//d_cmd_->SetSpeed(0.2,0);
//#if 1
	if (b_set)
	{
		d_cmd_->Setpara(p,i,0);
		d_cmd_->SetI2t_Para(I2,t);
		d_cmd_->SetSpeedPara(reverse,acc);
		b_set = false;
	}
	if (b_disable)
	{
		d_cmd_->Set_PC_Status_disable(1);
		b_disable = false;
	}
	if (b_enable )
	{
		d_cmd_->Set_PC_Status_disable(0);
		b_enable = false;
	}

	test_direction = txt_test_direction_->text().toInt();
	test_pwm = txt_test_pwm_->text().toInt();

	if (b_set_test)
	{
		d_cmd_->Set_PC_Status_Test(test_direction,test_pwm);
		b_set_test = false;
	}
	if (b_set_stop)
	{
		d_cmd_->Set_PC_Status_Stop();
		b_set_stop = false;
	}
	

	//d_cmd_->GetRPM_Current(RPM,C_RPM,current2,disable,emergency,over_load2,pwm2);
	
	txt_m_sv_->setText(QString::number(RPM));
	txt_Current_cv2_->setText(QString::number(C_RPM));     //当前速度
	txt_current2_->setText(QString::number(current2));

	txt_disable_->setText(QString::number(disable));
	txt_emergency_->setText(QString::number(emergency));
	txt_overload2_->setText(QString::number(over_load2));

#if 1
	d_cmd_->GetI2t(current_i2t,totoal_i2t,over_load);
	txt_current_->setText(QString::number(current_i2t));
	txt_total_i2t_->setText(QString::number(totoal_i2t));
	txt_overload_->setText(QString::number(over_load));

	plot_->AddPlotData(current_,local_time,current_i2t);

	d_cmd_->GetStatus(c_direction,direction,pwn,cv,out,current);
	txt_out_->setText(QString::number(out));			//PID计算后速度

	txt_pwm_->setText(QString::number(pwn));

#else
	d_cmd_->GetStatus(c_direction,direction,pwn,cv,out,current);
	
	d_cmd_->GetHall(hall,step);
	//
	txt_hall_->setText(QString::number(hall,2));		//hall DIO
	txt_step_->setText(QString::number(step,16));       //换向步骤

	txt_c_dirction_->setText(QString::number(c_direction));//当前方向
	txt_dirction_->setText(QString::number(direction));    //当前方向

	d_cmd_->GetSpeed(cv,cv2);
	txt_Current_cv_->setText(QString::number(cv));         //当前速度
	txt_Current_cv2_->setText(QString::number(cv2));         //当前速度
	
	
	if (fabs(cv) < 1e-6)
	{
		cv = 0;
	}

	//txt_Current_sv_->setText(QString::number(sv));		//设定速度
	txt_out_->setText(QString::number(out));			//PID计算后速度

	txt_pwm_->setText(QString::number(pwn));

	//
	//
	//
	//
	

	//txt_current_->setText(QString::number(current));
	
	//txt_total_i2t_->setText(QString::number(totoal_i2t));
	//txt_overload_->setText(QString::number(over_load));
	
	if((fabs(sv)>10) && (fabs(cv) < 0.0001))
	{
		sv = sv;
	}

	//plot_->AddPlotData(mv_,local_time,sv);
	plot_->AddPlotData(mv_,local_time,1.0);

	//plot_->AddPlotData(i_pwm_,local_time,pwn);
	//plot_->AddPlotData(sv_,local_time,sv);
	plot_->AddPlotData(sv_,local_time,1.0);
	//plot_->AddPlotData(cv_,local_time,cv);
	plot_->AddPlotData(cv_,local_time,1.0);
	plot_->AddPlotData(cv2_,local_time,1.0);
	//plot_->AddPlotData(out_,local_time,out);
	plot_->AddPlotData(out_,local_time,1.0);

	plot_->AddPlotData(current_,local_time,current);
	plot_->AddPlotData(total_i2t_,local_time,totoal_i2t);
	plot_->AddPlotData(overload_,local_time,over_load);

#endif

}
void ControlDlg::ChooseRun( bool flag )
{
	itimer_ = startTimer(40);
}

void ControlDlg::ChooseStop( bool flag )
{
	killTimer(itimer_);
}



void ControlDlg::ChooseSet(bool flag ){

	b_set = true;
}

void ControlDlg::ChooseDisable( bool flag )
{
	b_disable = true;
}

void ControlDlg::ChooseEnable( bool flag )
{
	b_enable = true;
}

void ControlDlg::ChooseTestModel( bool flag )
{
	b_set_test = true;
}
void ControlDlg::ChooseStopModel( bool flag )
{
	b_set_stop = true;
}