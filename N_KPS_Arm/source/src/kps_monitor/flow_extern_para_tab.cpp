
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"


#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "dispatching/traffic_control.h"
#include "mapserver/MapServer.h"

#include "flow_extern_para_tab.h"

task_flow_extern_para_tab::task_flow_extern_para_tab( QWidget *parent)
{
	btn_accepte_order_ = new QPushButton("extern");

	QVBoxLayout *mainLayout = new QVBoxLayout;      
	mainLayout->setSizeConstraint(QLayout::SetNoConstraint); // 不强占位置：可以将窗口压到高度为0
	mainLayout->addWidget(btn_accepte_order_);

	setLayout(mainLayout);
}

task_flow_extern_para_tab::~task_flow_extern_para_tab()
{
	
}

int task_flow_extern_para_tab::get_para( std::map<std::string,std::string> &m_para )
{
	return m_para.size();
}