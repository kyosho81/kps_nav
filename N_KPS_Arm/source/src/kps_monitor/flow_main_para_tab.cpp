
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"


#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "protobuf_msg/comb_factory.h"
#include "protobuf_msg/task_flow_def.h"

#include "flow_main_para_tab.h"

task_flow_main_para_tab::task_flow_main_para_tab( QWidget *parent)
{
	qcmb_start_angle_ = 0;
	qcomp_start_angle_ = 0;
	qstrlist_start_angle_ = 0;
	qedit_start_angle_ = 0;
	

	QGridLayout* grid = new QGridLayout();
	
	init_roles(grid);

	setLayout(grid);

}

task_flow_main_para_tab::~task_flow_main_para_tab()
{
	
}


void task_flow_main_para_tab::init_roles(QGridLayout* grid){

	QLabel* lb_role_from = new QLabel(tr("role_from:"));

	qcmb_role_from_ = new(std::nothrow) QComboBox(this);
	qcmb_role_from_id_ = new(std::nothrow) QComboBox(this);

	grid->addWidget(lb_role_from,0,0,1,1);
	grid->addWidget(qcmb_role_from_,0,1,1,1);
	grid->addWidget(qcmb_role_from_id_,0,2,1,1);


	QLabel* lb_role_to = new QLabel(tr("role_to:"));

	qcmb_role_to_ = new(std::nothrow) QComboBox(this);
	qcmb_role_to_id_ = new(std::nothrow) QComboBox(this);

	grid->addWidget(lb_role_to,0,4,1,1);
	grid->addWidget(qcmb_role_to_,0,5,1,1);
	grid->addWidget(qcmb_role_to_id_,0,6,1,1);

	QLabel* lb_node_id = new QLabel(tr("node_id:"));
	QLabel *lb_start_angle = new QLabel(tr("start angle:"));
	QLabel* lb_pallet_type = new QLabel(tr("pallet_type:"));
	QLabel* lb_cargo_type = new QLabel(tr("cargo_type:"));
	qcmb_node_id_ = new(std::nothrow) QComboBox(this);
	init_start_angle();
	qcmb_pallet_type_ = new(std::nothrow) QComboBox(this);
	qcmb_cargo_type_ = new(std::nothrow) QComboBox(this);
	qcmb_pallet_type_->installEventFilter(this);
	qcmb_cargo_type_->installEventFilter(this);

	grid->addWidget(lb_node_id,1,0,1,1);
	grid->addWidget(qcmb_node_id_,1,1,1,1);
	grid->addWidget(lb_start_angle,1,2,1,1);
	grid->addWidget(qcmb_start_angle_,1,3,1,1);

	grid->addWidget(lb_pallet_type,1,4,1,1);
	grid->addWidget(qcmb_pallet_type_,1,5,1,1);
	grid->addWidget(lb_cargo_type,1,6,1,1);
	grid->addWidget(qcmb_cargo_type_,1,7,1,1);

	fill_cmb_role();
	fill_cmb_type();
}

void task_flow_main_para_tab::init_start_angle()
{
	qedit_start_angle_ = new(std::nothrow) QLineEdit(this);

	qcmb_start_angle_ = new(std::nothrow) QComboBox(this);

	qcomp_start_angle_ = new(std::nothrow) QCompleter();

	QStringList indicator;

	indicator << QString("") << QString("0") << QString("90") << QString("-90")<< QString("180");

	qstrlist_start_angle_ = new QStringListModel();

	qstrlist_start_angle_->setStringList(indicator);//仅显示indicator里面的

	qcomp_start_angle_->setModel(qstrlist_start_angle_);

	qcomp_start_angle_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_start_angle_->clear();

	qcmb_start_angle_->addItems(indicator);

	qcmb_start_angle_->setEditable(true);  //设置可编辑

	qcmb_start_angle_->setCompleter(qcomp_start_angle_); //模糊匹

	qedit_start_angle_->setToolTip(tr("select node:"));

	qcmb_start_angle_->setLineEdit(qedit_start_angle_);   //与编辑m_edit绑定
	qcmb_start_angle_->setGeometry(11,12,200,22);
	qedit_start_angle_->selectAll();
	qedit_start_angle_->installEventFilter(this);
	qcmb_start_angle_->setMouseTracking(true);
}

void task_flow_main_para_tab::fill_cmb_role()
{
	QStringList comb_role_list;
	qcmb_role_to_->addItem("");

	std::vector<std::string> v_comb;
	COMB_FACTORY.get_role_all(v_comb);
	auto it = v_comb.begin();
	for ( ; it != v_comb.end() ; ++it ){
		qcmb_role_from_->addItem(it->c_str());
		qcmb_role_to_->addItem(it->c_str());
	}

	std::string str_id;
	for ( int i = 0 ; i < 100 ; ++i ){
		str_id = cComm::ConvertToString(i);
		qcmb_role_from_id_->addItem(str_id.c_str());
		qcmb_role_to_id_->addItem(str_id.c_str());
		qcmb_node_id_->addItem(str_id.c_str());
	}
	
}

void task_flow_main_para_tab::fill_cmb_type()
{
	std::vector<std::string> v_ct;
	v_ct.push_back("");
	COMB_FACTORY.get_cargo_type(v_ct);

	auto it = v_ct.begin();
	for ( ; it != v_ct.end() ; ++it ){
		qcmb_cargo_type_->addItem(it->c_str());
	}

	std::vector<std::string> v_pt;
	COMB_FACTORY.get_pallet_type(v_pt);
	v_pt.push_back("");
	it = v_pt.begin();
	for ( ; it != v_pt.end() ; ++it ){
		qcmb_pallet_type_->addItem(it->c_str());
	}
}



bool task_flow_main_para_tab::eventFilter(QObject * watched , QEvent * event)
{

	//	if (QEvent::MouseButtonPress == event->type()){
	if (QEvent::MouseButtonPress == event->type()){
		if (watched == qcmb_cargo_type_){

			qcmb_cargo_type_->clear();
			std::vector<std::string> v_ct;
			COMB_FACTORY.get_cargo_type(v_ct);
			v_ct.push_back("");
			auto it = v_ct.begin();
			for ( ; it != v_ct.end() ; ++it ){
				qcmb_cargo_type_->addItem(it->c_str());
			}
		}else if (watched == qcmb_pallet_type_){
			qcmb_pallet_type_->clear();
			std::vector<std::string> v_pt;
			COMB_FACTORY.get_pallet_type(v_pt);
			v_pt.push_back("");
			auto it = v_pt.begin();
			for ( ; it != v_pt.end() ; ++it ){
				qcmb_pallet_type_->addItem(it->c_str());
			}
		}
	}
	return QWidget::eventFilter(watched,event);
}

int task_flow_main_para_tab::get_para( std::map<std::string,std::string> &m_para )
{
	m_para[TF_NODE_ID] = qcmb_node_id_->currentText().toStdString();
	m_para[TF_START_ANGLE] = qcmb_start_angle_->currentText().toStdString();

	m_para[TF_FROM_ROLE] = qcmb_role_from_->currentText().toStdString();
	m_para[TF_TO_ROLE] = qcmb_role_to_->currentText().toStdString();

	m_para[TF_FROM_ROLE] = m_para[TF_FROM_ROLE] + "_" + qcmb_role_from_id_->currentText().toStdString();
	m_para[TF_TO_ROLE] = m_para[TF_TO_ROLE] + "_" + qcmb_role_to_id_->currentText().toStdString();

	m_para[TF_PALLET_TYPE] = qcmb_pallet_type_->currentText().toStdString();
	m_para[TF_CARGO_TYPE] = qcmb_cargo_type_->currentText().toStdString();

	return m_para.size();
}
