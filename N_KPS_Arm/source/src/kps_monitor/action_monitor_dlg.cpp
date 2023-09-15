
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "action_monitor_table.h"
#include "action_data_model.h"
#include "action/action_def.h"
#include "action/device_exaction_fork.h"
#include "action/device_exaction_lift.h"
#include "action/device_exaction_ref_forbidden.h"
#include "action/device_exaction_charge.h"
#include "action/action_factory.h"
#include "project/task_rpc_client.h"

#include "action_monitor_dlg.h"

action_monitor_dlg::action_monitor_dlg( QWidget *parent)
	: QDialog(parent)
{

	action_table_ = new action_monitor_table(this);

	QGridLayout* grid = new QGridLayout();

	QLabel *lab_action_type = new QLabel(tr("Action type:"));
	QLabel *lab_action_exp = new QLabel(tr("para exp:"));
	qedit_action_para_exp_ = new QLineEdit(this);

	ACTION_FACTORY.get_action(m_type_name_,m_type_para_);
	init_action_type_cmb();
	set_action_type();
	QLabel *lab_action_para = new QLabel(tr("para:"));
	qedit_action_para_ = new QLineEdit(this);

	btn_run_ = new QPushButton(tr("Run")); 
	connect(btn_run_, SIGNAL(clicked(bool)), this, SLOT(ChooseRun(bool)));

	btn_force_complete_ = new QPushButton(tr("ForceComplete")); 
	connect(btn_force_complete_, SIGNAL(clicked(bool)), this, SLOT(ChooseForceComplete(bool)));
	
	btn_redo_ = new QPushButton(tr("Redo")); 
	connect(btn_redo_, SIGNAL(clicked(bool)), this, SLOT(ChooseRedo(bool)));

	btn_del_ = new QPushButton(tr("Del")); 
	connect(btn_del_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));

	btn_load_ = new QPushButton(tr("Load")); 
	connect(btn_load_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));

	btn_save_ = new QPushButton(tr("Save")); 
	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));


	grid->addWidget(action_table_,0,0,3,10);

	grid->addWidget(lab_action_type,14,0,1,1);
	grid->addWidget(qcmb_action_type_,14,1,1,1);
	grid->addWidget(lab_action_exp,14,2,1,1);
	grid->addWidget(qedit_action_para_exp_,14,3,1,7);

	grid->addWidget(lab_action_para,15,2,1,1);
	grid->addWidget(qedit_action_para_,15,3,1,7);

	grid->addWidget(btn_run_,16,3,1,1);
	grid->addWidget(btn_force_complete_,16,4,1,1);
	grid->addWidget(btn_redo_,16,5,1,1);
	grid->addWidget(btn_del_,16,6,1,1);

	grid->addWidget(btn_load_,16,8,1,1);
	grid->addWidget(btn_save_,16,9,1,1);


	setLayout(grid);


	init_timer();

}

action_monitor_dlg::~action_monitor_dlg()
{

}

void action_monitor_dlg::init_timer()
{
	timer_ = new QTimer(this);
	timer_->setInterval(1000);
	connect(timer_, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer_->start();
}

void action_monitor_dlg::updateProgressValue()
{
	std::vector<task_feadback> tfb;
	{
		boost::mutex::scoped_lock lock(mu_tfb_);
		tfb = tfb_;
	}

 	QVector<QStringList> data;
 
	std::vector<task_feadback>::iterator it = tfb.begin();
	for ( ; it != tfb.end() ; ++it ){

 		task_feadback &fb(*it);
 		QStringList rowset;
 		rowset.push_back(QString::number(fb.get_task_id()));
 		rowset.push_back(QString::fromStdString(fb.get_str_status()));	
 		rowset.push_back(QString::fromStdString(fb.get_init_para()));

 		data.append(rowset);
 	}
 	//timer_->stop();
	action_data_model* tb = action_table_->model_;
	tb->setData(data);
 
}


void action_monitor_dlg::init_action_type_cmb()
{
	qedit_action_type_ = new(std::nothrow) QLineEdit(this);

	qcmb_action_type_ = new(std::nothrow) QComboBox(this);

	qcomp_action_type_ = new(std::nothrow) QCompleter();

	qstrlist_action_type_ = new QStringListModel();

	qstrlist_action_type_->setStringList(indicator_);//仅显示indicator里面的

	qcomp_action_type_->setModel(qstrlist_action_type_);

	qcomp_action_type_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_action_type_->clear();

	qcmb_action_type_->addItems(indicator_);

	qcmb_action_type_->setEditable(false);  //设置可编辑

	qcmb_action_type_->setCompleter(qcomp_action_type_); //模糊匹

	qedit_action_type_->setToolTip("select action:");

	qcmb_action_type_->setLineEdit(qedit_action_type_);   //与编辑m_edit绑定
	qcmb_action_type_->setGeometry(11,12,200,22);
	qedit_action_type_->selectAll();
	qcmb_action_type_->installEventFilter(this);
}

void action_monitor_dlg::set_action_type()
{

	qstrlist_action_type_->setStringList(indicator_);
	qcomp_action_type_->setModel(qstrlist_action_type_);

	qcmb_action_type_->clear();
	auto it = m_type_name_.begin();
	for ( ; it != m_type_name_.end() ; ++it ){
		qcmb_action_type_->addItem(QString::fromStdString(it->second),it->first);
	}

	//qcmb_action_type_->addItems(indicator_);

}



void action_monitor_dlg::ChooseRun(bool flag)
{
	int i_action_type = qcmb_action_type_->currentIndex();
	QVariant qvindex = qcmb_action_type_->itemData(i_action_type);
	int dev_id = qvindex.toInt();

	QString qs = qedit_action_para_->text();

	auto it = m_type_para_.find(qvindex.toInt());
	if ( it != m_type_para_.end()){
		std::pair<std::string, std::string> &p_para = it->second;
		p_para.second = qs.toStdString();
	}else{
		QMessageBox::warning(0, tr("Error"), tr("Can't run on AGV!"));
	}


	int i_action_id = TASK_XML_CLIENT.create_task_act(qs.toStdString());
	
	task_feadback fb;
	for ( int i = 0 ; i < 100 ; ++i ){
		if (check_task_init(fb,i_action_id)){
			m_devid_taskid_[i_action_id] = i_action_id;
			break;

		}
		SLEEP(100);
	}
	
}
bool action_monitor_dlg::check_task_init(task_feadback &fb,int i_task_id)
{
	std::vector<task_feadback> ftb;
	TASK_XML_CLIENT.get_feadback(i_task_id,ftb);

	if (ftb.size() > 0){
		fb = ftb[0];
		return true;
	}
	return false;
}
void action_monitor_dlg::ChooseForceComplete(bool flag)
{
	//int i_action_type = qcmb_action_type_->currentIndex();
	//QVariant qvindex = qcmb_action_type_->itemData(i_action_type);
	//int dev_id = qvindex.toInt();

	int action_id = action_table_->get_select_action_id();
	if (m_devid_taskid_.count(action_id)){
		TASK_XML_CLIENT.force_complete(m_devid_taskid_[action_id]);
	}
	
}

void action_monitor_dlg::ChooseRedo(bool flag)
{
	int action_id = action_table_->get_select_action_id();
	if (m_devid_taskid_.count(action_id)){
		TASK_XML_CLIENT.redo(m_devid_taskid_[action_id]);
	}
}

void action_monitor_dlg::ChooseDel(bool flag)
{
	int action_id = action_table_->get_select_action_id();
	if (m_devid_taskid_.count(action_id)){
		TASK_XML_CLIENT.remove_task(m_devid_taskid_[action_id]);
	}
}

void action_monitor_dlg::ChooseLoad(bool flag)
{

}

void action_monitor_dlg::ChooseSave(bool flag)
{

}

bool action_monitor_dlg::eventFilter(QObject * watched , QEvent * event)
{
	if (watched == qcmb_action_type_){
		QString qs;

		int i_action_type = qcmb_action_type_->currentIndex();
		QVariant qvindex = qcmb_action_type_->itemData(i_action_type);
		auto it = m_type_para_.find(qvindex.toInt());
		if ( it != m_type_para_.end()){
			std::pair<std::string, std::string> p_para = it->second;
			qedit_action_para_exp_->setText(QString::fromStdString(p_para.first));
			qedit_action_para_->setText(QString::fromStdString(p_para.second));
		}else{
			qedit_action_para_exp_->setText("");
			qedit_action_para_->setText("");
		}

	}
	return QDialog::eventFilter(watched,event);
}

void action_monitor_dlg::set_tfb(const std::vector<task_feadback> &tfb)
{
	boost::mutex::scoped_lock lock(mu_tfb_);
	tfb_ = tfb;
}
