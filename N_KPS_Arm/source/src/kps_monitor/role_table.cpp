
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "role_model.h"
#include "protobuf_msg/protobuf_base.h"

#include "role_table.h"

role_table::role_table( QWidget *parent)
	: QTableView(parent)
{
	//	model_ = new dev_data_models(this);

	// 	model_ = new QStandardItemModel(this);
	// 	model_->setItem(0, 0, new QStandardItem("1")); 
	// 	model_->setItem(0, 1, new QStandardItem("2"));
	// 	model_->setItem(0, 2, new QStandardItem("3"));
	//	this->setModel(model_);

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	/*this->setMinimumWidth((int)1200);*/
	this->setObjectName("role");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);


	model_ = new role_model(this);
	this->setModel(model_);   //绑定数据模型

	//set table header
	QStringList headers;
	headers << tr("role_tpye_id")<<tr("state")<<tr("bind_node")<<tr("occupyed")<<tr("assigned agv");
	model_->setHorizontalHeader(headers);

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

role_table::~role_table()
{

}

void role_table::show_role_list(std::multimap< std::string, protobuf_base*> &mm_roles )
{

	QVector<QStringList> data;

	auto it = mm_roles.begin();
	for ( ; it != mm_roles.end() ; ++it ){
		QStringList rowset;
		std::stringstream ss;
		protobuf_base* p_base = it->second;
		ss<<it->first<<"_"<<p_base->get_id();
		rowset.push_back(QString::fromStdString(ss.str()));
		rowset.push_back(QString::fromStdString(p_base->get_status()));
		rowset.push_back(QString::number(p_base->get_bind_node_id()));
		rowset.push_back(QString::number(p_base->occupyed()));
		rowset.push_back(QString::number(p_base->get_assigned_agv()));
		data.append(rowset);
	}

 	model_->setData(data);
}

