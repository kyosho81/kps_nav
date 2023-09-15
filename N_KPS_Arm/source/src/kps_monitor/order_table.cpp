
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "order_model.h"
#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"

#include "order_table.h"

order_table::order_table( QWidget *parent)
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
	this->setObjectName("order");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);


	model_ = new order_model(this);
	this->setModel(model_);   //绑定数据模型

	//set table header
	QStringList headers;
	headers << tr("index")<<tr("state")<<tr("schedule_type")<<tr("m_order_id")<<tr("agv_id")<<tr("role_from")<<tr("node_from")<<tr("role_to")<<tr("node_to")<<tr("pallet")<<tr("cargo")<<tr("time_b")<<tr("time_e")<<tr("diff_min");
	model_->setHorizontalHeader(headers);

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

order_table::~order_table()
{

}
std::string order_table::get_role_name( protobuf_base* p_role ){
	if (!p_role){
		return "";
	}
	std::stringstream ss;
	ss<<p_role->get_type()<<"_"<<p_role->get_id();
	return ss.str();
}
void order_table::show_order_list( std::list<order_schedule*> l_order )
{

	QVector<QStringList> data;

	auto it = l_order.begin();
	for ( ; it != l_order.end() ; ++it ){
		QStringList rowset;
		

		order_schedule* p_order = *it;

		rowset.push_back(QString::number(p_order->i_order_index_));
		rowset.push_back(QString::fromStdString(ORDER_FACTORY.get_order_state(p_order->th_assigned_())));
		rowset.push_back(QString::number(p_order->i_sch_index_));
		rowset.push_back(QString::fromStdString(p_order->str_manual_id_));
		rowset.push_back(QString::number(p_order->i_agv_id_));
		rowset.push_back(QString::fromStdString(get_role_name(p_order->p_from_)));
		rowset.push_back(QString::number(p_order->one_task_.i_from_node_id_));
		rowset.push_back(QString::fromStdString(get_role_name(p_order->p_to_)));
		rowset.push_back(QString::number(p_order->one_task_.i_to_node_id_));
		rowset.push_back(QString::fromStdString( p_order->one_task_.str_pallet_uuid_));
		rowset.push_back(QString::fromStdString( p_order->one_task_.str_cargo_uuid_));

		rowset.push_back(QString::fromStdString( p_order->str_begin_));
		rowset.push_back(QString::fromStdString( p_order->str_end_));
		rowset.push_back(QString::number(p_order->f_time_min_));

		data.append(rowset);
	}

 	model_->setData(data);
}

