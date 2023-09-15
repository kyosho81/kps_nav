
#include <QDebug>

#include "interface/xml_rpc_client.h"

#include "manual_ctl_dlg.h"

manual_ctl_dlg::manual_ctl_dlg(QWidget *parent /*= 0 */)
{
	b_show_ = true;
}

manual_ctl_dlg::~manual_ctl_dlg()
{

}

void manual_ctl_dlg::init()
{
	btn_ccw_ = new QPushButton(tr("ccw"));
	btn_cw_ = new QPushButton(tr("cw"));
	btn_forward_ = new QPushButton(tr("forward"));
	btn_backward_ = new QPushButton(tr("backward"));
	btn_leftshift_ = new QPushButton(tr("leftshift"));
	btn_rightshift_ = new QPushButton(tr("rightshift"));
	btn_stop_ = new QPushButton(tr("stop"));

	connect(btn_ccw_, SIGNAL(clicked(bool)), this, SLOT(ChooseCCW(bool)));
	connect(btn_cw_, SIGNAL(clicked(bool)), this, SLOT(ChooseCW(bool)));
	connect(btn_forward_, SIGNAL(clicked(bool)), this, SLOT(ChooseForward(bool)));
	connect(btn_backward_, SIGNAL(clicked(bool)), this, SLOT(ChooseBackward(bool)));
	connect(btn_leftshift_, SIGNAL(clicked(bool)), this, SLOT(ChooseLeftShift(bool)));
	connect(btn_rightshift_, SIGNAL(clicked(bool)), this, SLOT(ChooseRightShift(bool)));
	connect(btn_stop_, SIGNAL(clicked(bool)), this, SLOT(ChooseStop(bool)));

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(btn_leftshift_,0,0);
	grid->addWidget(btn_ccw_,1,0);
	grid->addWidget(btn_forward_,2,0);

	grid->addWidget(btn_stop_,0,1,3,1);

	grid->addWidget(btn_rightshift_,0,2);
	grid->addWidget(btn_cw_,1,2);
	grid->addWidget(btn_backward_,2,2);

	setLayout(grid);

}

bool manual_ctl_dlg::show_btn()
{
	b_show_ = !b_show_;

	if (b_show_){
		btn_leftshift_->show();
		btn_rightshift_->show();
		btn_ccw_->show();
		btn_cw_->show();
		btn_forward_->show();
		btn_backward_->show();
		btn_stop_->show();
	}else{
		btn_leftshift_->hide();
		btn_rightshift_->hide();
		btn_ccw_->hide();
		btn_cw_->hide();
		btn_forward_->hide();
		btn_backward_->hide();
		btn_stop_->hide();
	}

	return b_show_;
}

void manual_ctl_dlg::ChooseCCW(bool flag)
{

	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("rot_left 0.1");
	std::cout<<"action:do_rot_left over:"<<std::endl;
}
void manual_ctl_dlg::ChooseCW(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("rot_right 0.1");
	std::cout<<"action:do_rot_right over:"<<std::endl;
}

void manual_ctl_dlg::ChooseForward(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("front 0.2");
	std::cout<<"action:do_move_front over:"<<std::endl;
}

void manual_ctl_dlg::ChooseBackward(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("back 0.15");
	std::cout<<"action:do_move_back over:"<<std::endl;
}

void manual_ctl_dlg::ChooseLeftShift(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("dir 90 0.1");
	std::cout<<"action:do_move_left over:"<<std::endl;

	
}

void manual_ctl_dlg::ChooseRightShift(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("dir -90 0.1");
	std::cout<<"action:do_move_right over:"<<std::endl;

}

void manual_ctl_dlg::ChooseStop(bool flag)
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("stop");
	std::cout<<"action:do_move_stop over:"<<std::endl;
}