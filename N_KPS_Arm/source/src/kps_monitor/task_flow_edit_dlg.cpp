
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"


#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "dispatching/traffic_control.h"
#include "mapserver/MapServer.h"

#include "protobuf_msg/state_machine_factory.h"
#include "role_table.h"

#include "flow_main_para_tab.h"
#include "flow_extern_para_tab.h"
#include "dispatching/task_flow_factory.h"
#include "task_flow_table.h"
#include "task_flow_model.h"

#include "task_flow_edit_dlg.h"

task_flow_edit_dlg::task_flow_edit_dlg( QWidget *parent)
{
	parent_ = parent;

	task_flow_table_ = new task_flow_table(this);
	
	init_task_flow();
	fill_task_flow_name();
	init_btn();

	QVBoxLayout *mainLayout = new QVBoxLayout;      
	mainLayout->setSizeConstraint(QLayout::SetNoConstraint); // 不强占位置：可以将窗口压到高度为0
	mainLayout->addLayout(grid_);
	mainLayout->addWidget(task_flow_table_);
	mainLayout->addLayout(btn_grid_);

	setLayout(mainLayout);


}

task_flow_edit_dlg::~task_flow_edit_dlg()
{
	
}

void task_flow_edit_dlg::init_task_flow()
{
	grid_ = new QGridLayout();

	QLabel* lb_task_flow_nm = new QLabel(tr("flow name:"));
	qcmb_task_flow_nm_ = new(std::nothrow) QComboBox(this);
	connect(qcmb_task_flow_nm_,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCombChanged(QString)));

	btn_add_flow_ = new QPushButton(tr("add"));
	btn_del_flow_ = new QPushButton(tr("del"));
	btn_save_flow_ = new QPushButton(tr("save"));

	btn_analyze_ = new QPushButton(tr("analyze")); 
	btn_instantiation_ = new QPushButton(tr("instantiation")); 


	connect(btn_add_flow_, SIGNAL(clicked(bool)), this, SLOT(ChooseAdd(bool)));
	connect(btn_del_flow_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));
	connect(btn_save_flow_, SIGNAL(clicked(bool)), this, SLOT(ChooseSave(bool)));

	connect(btn_analyze_, SIGNAL(clicked(bool)), parent_, SLOT(ChooseAnalyze(bool)));
	connect(btn_instantiation_, SIGNAL(clicked(bool)), parent_, SLOT(ChooseInstantiation(bool)));

	//connect(btn_analyze_,SIGNAL(toggled(bool)),this,SLOT(ChooseRunHis(bool)));

	grid_->addWidget(lb_task_flow_nm,0,0,1,1);
	grid_->addWidget(qcmb_task_flow_nm_,0,1,1,3);
	grid_->addWidget(btn_add_flow_,0,5,1,1);
	grid_->addWidget(btn_del_flow_,0,6,1,1);
	grid_->addWidget(btn_save_flow_,0,7,1,1);
	QLabel* lb_empty = new QLabel("");
	grid_->addWidget(lb_empty,0,8,1,1);
	grid_->addWidget(btn_analyze_,0,9,1,1);
	grid_->addWidget(btn_instantiation_,0,10,1,1);
}

void task_flow_edit_dlg::init_btn()
{
	btn_add_ = new QPushButton(tr("new"));
	btn_del_ = new QPushButton(tr("del"));

	btn_required_ = new QPushButton(tr("required"));
	btn_optional_ = new QPushButton(tr("optional"));
	btn_disable_ = new QPushButton(tr("disable")); 


	connect(btn_add_, SIGNAL(clicked(bool)), this, SLOT(ChooseAddAct(bool)));
	connect(btn_del_, SIGNAL(clicked(bool)), this, SLOT(ChooseDelAct(bool)));
	
	connect(btn_required_, SIGNAL(clicked(bool)), this, SLOT(ChooseReqAct(bool)));
	connect(btn_optional_, SIGNAL(clicked(bool)), this, SLOT(ChooseOptAct(bool)));
	connect(btn_disable_, SIGNAL(clicked(bool)), this, SLOT(ChooseDisAct(bool)));

	btn_grid_ = new QGridLayout();
	btn_grid_->addWidget(btn_add_,0,0,1,1);
	btn_grid_->addWidget(btn_del_,0,1,1,1);
	btn_grid_->addWidget(new QLabel(""),0,2,1,1);
	btn_grid_->addWidget(new QLabel(""),0,3,1,1);
	btn_grid_->addWidget(btn_required_,0,4,1,1);
	btn_grid_->addWidget(btn_optional_,0,5,1,1);
	btn_grid_->addWidget(btn_disable_,0,6,1,1);


}
void task_flow_edit_dlg::onCombChanged(const QString &qs)
{
	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());

	if ( task_flow_table_ && fd){
		task_flow_table_->show_task_flow(fd->l_task_flow_);
	}else{
		std::list<SSTaskFlow*> l_task_flow;
		task_flow_table_->show_task_flow(l_task_flow);
	}
}
void task_flow_edit_dlg::update_table(){

	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());

	if (!fd){
		return ;
	}

	QVector<QStringList> qv_data = task_flow_table_->get_data();

	foreach (QStringList row, qv_data) {

		int i_index = row.at(COL_TASK_FLOW_ID).toInt();
		SSTaskFlow* stf = fd->get_data(i_index);
		if (stf){
			stf->str_get_put_ = row.at(COL_TASK_FLOW_PUTGET).toStdString();
			stf->str_mv_seg_ = row.at(COL_TASK_FLOW_MV_SEG).toStdString();

			for ( int i = 0 ; i < 8 ; ++i ){
				stf->v_act_dec_[i].str_act_ = row.at(COL_TASK_FLOW_ACT_1 + i).toStdString();
				if (stf->v_act_dec_[i].str_act_ == ACT_PUT_RELEASE){
					stf->v_act_dec_[i].act_dec_ = ACT_DEC::ACT_OPTIONAL;
				}
			}
		
		}
	}
}
void task_flow_edit_dlg::ChooseAddAct(bool flag)
{

	update_table();

	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());
	
	if (fd){
		

		std::map<int, int> m_sel = task_flow_table_->sel_task_flow();
		if ( m_sel.size() > 0 ){
			fd->insert_data( m_sel.begin()->first );
		}else{
			fd->create_data();
		}
		task_flow_table_->show_task_flow(fd->l_task_flow_);

	}else{
		QMessageBox::warning(0, tr("task flow"), tr("select task flow first!"));
	}
	
}

void task_flow_edit_dlg::ChooseDelAct(bool flag)
{
	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());

	if (fd){
		std::map<int, int> m_del = task_flow_table_->sel_task_flow();
		auto it = m_del.begin();
		for ( ; it != m_del.end() ; ++it ){
			fd->del_data(it->first);
		}

		task_flow_table_->show_task_flow(fd->l_task_flow_);
	}else{
		QMessageBox::warning(0, tr("task flow"), tr("select task flow first!"));
	}

	
}

void task_flow_edit_dlg::ChooseReqAct(bool flag)
{
	update_table();

	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());
	if (fd){
		std::list<std::pair<int,int> > m_sel = task_flow_table_->get_sel();
		auto it = m_sel.begin();
		for ( ; it !=m_sel.end() ; ++it){
			int irow = it->first;
			SSTaskFlow* stf = fd->get_data(irow);
			if (stf){
				int icol = it->second;
				icol -= COL_TASK_FLOW_ACT_1;
				if (icol < stf->v_act_dec_.size()){
					stf->v_act_dec_[icol].act_dec_ = ACT_DEC::ACT_REQUIRE;
				}
				
				
			}
		}
	}
	
}

void task_flow_edit_dlg::ChooseOptAct(bool flag)
{
	update_table();

	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());
	if (fd){
		std::list<std::pair<int,int> > m_sel = task_flow_table_->get_sel();
		auto it = m_sel.begin();
		for ( ; it !=m_sel.end() ; ++it){
			int irow = it->first;
			SSTaskFlow* stf = fd->get_data(irow);
			if (stf){
				int icol = it->second;
				icol -= COL_TASK_FLOW_ACT_1;
				if (icol < stf->v_act_dec_.size()){
					stf->v_act_dec_[icol].act_dec_ = ACT_DEC::ACT_OPTIONAL;
				}


			}
		}
	}
}

void task_flow_edit_dlg::ChooseDisAct(bool flag)
{
	update_table();

	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	task_flow_data* fd = TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());
	if (fd){
		std::list<std::pair<int,int> > m_sel = task_flow_table_->get_sel();
		auto it = m_sel.begin();
		for ( ; it !=m_sel.end() ; ++it){
			int irow = it->first;
			SSTaskFlow* stf = fd->get_data(irow);
			if (stf){
				int icol = it->second;
				icol -= COL_TASK_FLOW_ACT_1;
				if (icol < stf->v_act_dec_.size()){
					stf->v_act_dec_[icol].act_dec_ = ACT_DEC::ACT_DISABLE;
				}


			}
		}
	}
}

bool task_flow_edit_dlg::fill_task_flow_name()
{
	std::vector<std::string> v_task_flow_nms;
	TASK_FLOW_FACTORY.get_task_flow_nms(v_task_flow_nms);
	
	qcmb_task_flow_nm_->clear();

	auto it = v_task_flow_nms.begin();
	for ( ; it != v_task_flow_nms.end() ; ++it ){
		qcmb_task_flow_nm_->addItem(it->c_str());
	}
	return true;
}

void task_flow_edit_dlg::ChooseAdd(bool flag)
{
	bool ok = true;
	QString qstr_task_flow_nm ;
	qstr_task_flow_nm = QInputDialog::getText(this, tr("task flow"),
		tr("New task flow name:"), QLineEdit::Normal,
		qstr_task_flow_nm, &ok);

	if (TASK_FLOW_FACTORY.check_task_flow(qstr_task_flow_nm.toStdString())){
		QMessageBox::warning(0, tr("task flow"), tr("task flow Duplicate!"));
	}else{
		TASK_FLOW_FACTORY.new_task_flow_data(qstr_task_flow_nm.toStdString());
		fill_task_flow_name();
		QMessageBox::information(0, tr("task flow"), tr("task flow created!"));
	}
	
}

void task_flow_edit_dlg::ChooseDel(bool flag)
{
	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	TASK_FLOW_FACTORY.del_task_flow_data(qstr_task_flow_nm.toStdString());
	fill_task_flow_name();
	QMessageBox::information(0, tr("task flow"), tr("task flow deleted!"));
}

void task_flow_edit_dlg::ChooseSave(bool flag)
{
	save_data();

	QMessageBox::information(0, tr("task flow"), tr("task flow saved!"));
}

task_flow_data* task_flow_edit_dlg::get_task_flow()
{
	QString qstr_task_flow_nm = qcmb_task_flow_nm_->currentText();
	return TASK_FLOW_FACTORY.get_task_flow_data(qstr_task_flow_nm.toStdString());
}

bool task_flow_edit_dlg::save_data()
{
	update_table();

	return TASK_FLOW_FACTORY.save_file();
}


