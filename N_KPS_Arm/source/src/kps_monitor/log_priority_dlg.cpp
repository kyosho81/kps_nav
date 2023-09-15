
#include <QDebug>
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"

#include "scene/map_view.h"
#include "scene/map_scene.h"

#include "robot/Geometry.h"
#include "Comm/Comm.h"

#include "msg_pump/msg_pump.hpp"
#include "log/Log4cppMsgIndex.h"
#include "trans_dev/trans_dev.h"
#include "PortDef.h"

#include "property/qtpropertymanager.h"
#include "property/qtvariantproperty.h"
#include "property/qttreepropertybrowser.h"
#include "property/qteditorfactory.h"

#include "log_priority_dlg.h"




log_priority_dlg::log_priority_dlg( QWidget *parent)
{
	
	enumNames_ << SRT_PRO_EMERG << SRT_PRO_FATAL << SRT_PRO_ALERT << SRT_PRO_CRIT<< SRT_PRO_ERROR <<SRT_PRO_WARN<< SRT_PRO_NOTICE<<SRT_PRO_INFO<<SRT_PRO_DEBUG<<SRT_PRO_NOTSET;
	
	str_ip_ = "127.0.0.1";
	i_log_port_ = LOG_MONITOR_PORT_SET;

	i_get_all_priority_ = 0;
	i_set_priority_ = 0;

}

log_priority_dlg::~log_priority_dlg()
{
	
}

void log_priority_dlg::init(const std::string str_ip){

	str_ip_ = str_ip;
	i_log_port_ = LOG_MONITOR_PORT_SET;
	
	memset(ch_get_all_priority_,0,100);
	memset(ch_set_priority_,0,100);
	memset(ch_read_all_,0,500);

	i_get_all_priority_ = 0;
	i_set_priority_ = 0;
	i_read_all_ = 0;

	timer_ = 0;

	variantManager_ = 0;
	enumManager_ = 0;
	//boolManager_ = 0;
	variantEditor_ = 0;


	QGridLayout* grid = new QGridLayout();

	grid->addWidget(create_para_wiget(),0,0);

	btn_refresh_ = new QPushButton(tr("Upload"));
	btn_save_ = new QPushButton(tr("Download"));
	btn_close_ = new QPushButton(tr("Close"));

	connect(btn_refresh_, SIGNAL(clicked(bool)), this, SLOT(ChooseRefresh(bool)));
	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseSave(bool)));
	connect(btn_close_, SIGNAL(clicked(bool)), this, SLOT(ChooseClose(bool)));

	grid->addWidget(btn_refresh_,12,0);
	grid->addWidget(btn_save_,13,0);
	grid->addWidget(btn_close_,14,0);
	grid->setColumnMinimumWidth(0,300);

	QVBoxLayout* v1 = new QVBoxLayout();
	v1->addLayout(grid);
	QLabel *lab_nun = new QLabel(tr(""));
	v1->addWidget(lab_nun);
	

	QHBoxLayout* h1 = new QHBoxLayout();
	
	
	h1->addLayout(v1);

	setLayout(h1);

	init_cmd();
	init_tcp_client();
	

	for ( int i = 0 ; i < 10 ; ++i )
	{
		if( get_priority() ){
			break;
		}else{
			SLEEP(200);
		}
		
	}
	
// 	if (p_tcp_client_)
// 	{
// 		init_timer();
// 	}
	
}

QWidget* log_priority_dlg::create_para_wiget(){

	variantManager_ = new QtVariantPropertyManager();
	
	enumManager_ = new QtEnumPropertyManager();
//	boolManager_ = new QtBoolPropertyManager();

	
	//log_priority_group_ = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(),QLatin1String("Log priority"));
	//log_priority_group_->setPropertyId(QLatin1String("Log priority"));
	
	
	//log_priority_group->addSubProperty(item_log_priority_);
	//laser_para_group->removeSubProperty();

	
	



	QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
	QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory();
	//QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory();

	variantEditor_ = new QtTreePropertyBrowser();
	
	variantEditor_->setFactoryForManager(variantManager_, variantFactory);
	variantEditor_->setFactoryForManager(enumManager_, comboBoxFactory);
	//variantEditor->setFactoryForManager(boolManager_, checkBoxFactory);
	
	
	variantEditor_->setPropertiesWithoutValueMarked(true);
	variantEditor_->setRootIsDecorated(false);
	
	//variantEditor_->addProperty(log_priority_group_);
	
	connect(variantManager_, SIGNAL(valueChanged(QtProperty *, QVariant)),
		this, SLOT(valueChanged(QtProperty *, QVariant)));
	connect(enumManager_, SIGNAL(valueChanged(QtProperty *, int)),
		this, SLOT(valueChanged(QtProperty *, int)));
	
	return (QWidget*)variantEditor_;
}
void log_priority_dlg::valueChanged(QtProperty *property, const QVariant &value)
{
	std::string str_pro_name = property->propertyName().toStdString();
	std::string str_priority = value.toString().toStdString();
	std::cout<<"str_pro_name:"<<str_pro_name<<" priority:"<<str_priority<<std::endl;
// 	if (property->propertyName()== QLatin1String("calib line")) {
// 		item_line_->setLine(value.toDouble(),-2,value.toDouble(),2);
// 	} 
}
void log_priority_dlg::valueChanged(QtProperty *property, int val)
{
	if (!b_check_value_change_)
	{
		return;
	}

	std::string str_pro_name = property->propertyName().toStdString();
	int ipriority = log4cpp::log_msg_index::cmbintex_to_pri(val);
	//std::cout<<"str_pro_name:"<<str_pro_name<<" priority:"<<ipriority<<std::endl;
	std::stringstream ss;
	ss<<"set_priority "<<str_pro_name<<" "<<ipriority;
	i_set_priority_ = cComm::String2Charlist((S8*)ch_set_priority_,100,ss.str());
	std::cout<<ss.str()<<std::endl;

	if (p_tcp_client_ && p_tcp_client_->m_Status.IsOpen()){
		p_tcp_client_->WriteData(ch_set_priority_,i_set_priority_);
	}
	memset(ch_set_priority_,0,100);
	i_set_priority_ = 0;
}
void log_priority_dlg::init_timer()
{
	if (!timer_)
	{
		timer_ = new QTimer(this);
		timer_->setInterval(1000);
		connect(timer_, SIGNAL(timeout()), this, SLOT(get_priority()));

		timer_->start();
	}
	
}

void log_priority_dlg::stop_timer()
{
	if(timer_){
		timer_->stop();
		delete timer_;
	}

}

void log_priority_dlg::ChooseRefresh(bool flag)
{
	get_priority();
}
void log_priority_dlg::ChooseSave( bool flag )
{
	std::stringstream ss;
	ss<<"save_log";
	i_set_priority_ = cComm::String2Charlist((S8*)ch_set_priority_,100,ss.str());
	std::cout<<ss.str()<<std::endl;

	if (p_tcp_client_ && p_tcp_client_->m_Status.IsOpen()){
		p_tcp_client_->WriteData(ch_set_priority_,i_set_priority_);
	}
	memset(ch_set_priority_,0,100);
	i_set_priority_ = 0;
//	set_pro_nm_priority("pro1",SRT_PRO_INFO);
//	set_pro_nm_priority("pro2",SRT_PRO_DEBUG);

// 	if (b_connection_)
// 	{
// 		btn_connection_->setText("Connection");
// 	}else{
// 		btn_connection_->setText("DisConnection");
// 	}
// 	b_connection_ = !b_connection_;
	
}
void log_priority_dlg::ChooseClose( bool flag )
{
	this->close();
}

void log_priority_dlg::set_pro_nm_priority(const std::string &str_pro_nm, const std::string &str_priority)
{

	std::map<std::string,QtProperty*>::iterator it = m_log_name_pri_.find(str_pro_nm);
	if ( it != m_log_name_pri_.end() )
	{
		enumManager_->setValue( it->second,log4cpp::log_msg_index::str_pri_to_index(str_priority));
	}else{
		QtProperty* item_log_priority_ = enumManager_->addProperty(QString::fromStdString(str_pro_nm));
		
		enumManager_->setEnumNames(item_log_priority_, enumNames_);
		//log_priority_group_->addSubProperty(item_log_priority_);
		variantEditor_->addProperty(item_log_priority_);
		enumManager_->setValue(item_log_priority_,log4cpp::log_msg_index::str_pri_to_index(str_priority));
		m_log_name_pri_[str_pro_nm] =item_log_priority_; 
	}

	
}

void log_priority_dlg::init_tcp_client()
{
	if (str_ip_.size() < 1)
	{
		return;
	}
	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = str_ip_;
	conn_para.m_nRemotePort = i_log_port_;

	p_tcp_client_ = cTransferDevice::GetInstance(conn_para);
}

bool log_priority_dlg::get_priority()
{
	if (p_tcp_client_ && p_tcp_client_->m_Status.IsOpen()){

		p_tcp_client_->WriteData(ch_get_all_priority_,i_get_all_priority_);
		p_tcp_client_->ReadData(ch_read_all_,i_read_all_,500,200);

		std::string  str_all;
		cComm::Char2String(str_all,ch_read_all_) ;
		std::vector<std::string> v_str;
		cComm::SplitString(str_all,"#",v_str);

		b_check_value_change_ = false;

		std::vector<std::string>::iterator it = v_str.begin();
		for ( ; it != v_str.end() ; ++it ){
			std::vector<std::string> v_pair;
			cComm::SplitString(*it," ",v_pair);
			if (v_pair.size() > 1)
			{
				set_pro_nm_priority(v_pair[0],v_pair[1]);
			}

		}
		b_check_value_change_ = true;

		return true;
	}
	return false;
}

void log_priority_dlg::init_cmd()
{
	std::string str = "get_all_priority";
	i_get_all_priority_ = cComm::String2Charlist((S8*)ch_get_all_priority_,100,str);

}



