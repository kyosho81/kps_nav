
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

#include "task_flow_para_dlg.h"

task_flow_para_dlg::task_flow_para_dlg( QWidget *parent)
{


	tabWidget = new QTabWidget;    // 创建QTabWidget
	tb_task_flow_main_para_tab_ = new task_flow_main_para_tab();
	tb_task_flow_extern_para_tab_ = new task_flow_extern_para_tab();
 	tabWidget->addTab(tb_task_flow_main_para_tab_, tr("main_para"));    // 将三个页Widget添加到标签Widget
 	tabWidget->addTab(tb_task_flow_extern_para_tab_, tr("extern_para"));
// 	tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
	
	QVBoxLayout *mainLayout = new QVBoxLayout;      
	mainLayout->setSizeConstraint(QLayout::SetNoConstraint); // 不强占位置：可以将窗口压到高度为0
	mainLayout->addWidget(tabWidget);

	setLayout(mainLayout);


}

task_flow_para_dlg::~task_flow_para_dlg()
{
	
}

int task_flow_para_dlg::get_main_para( std::map<std::string,std::string> &m_para )
{
	return tb_task_flow_main_para_tab_->get_para(m_para);
}

int task_flow_para_dlg::get_ext_para( std::map<std::string,std::string> &m_para )
{
	return tb_task_flow_extern_para_tab_->get_para(m_para);
}
