
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "interface_model.h"
#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"
#include "interface_delegate.h"
#include "dispatching/manual_order.h"
#include "dispatching\manual_para_def.h"

#include "interface_table.h"

interface_table::interface_table( QWidget *parent)
	: QTableView(parent)
{
	//	model_ = new dev_data_models(this);

	// 	model_ = new QStandardItemModel(this);
	// 	model_->setItem(0, 0, new QStandardItem("1")); 
	// 	model_->setItem(0, 1, new QStandardItem("2"));
	// 	model_->setItem(0, 2, new QStandardItem("3"));
	//	this->setModel(model_);

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::DoubleClicked);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	/*this->setMinimumWidth((int)1200);*/
	this->setObjectName("interface");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);

	
	model_ = new interface_model(this);
	
	delegate_ = new interface_delegate();

	this->setModel(model_);   //绑定数据模型
	this->setItemDelegate(delegate_);
	this->setSortingEnabled(true);
	this->setAlternatingRowColors(true);
	this->setStyleSheet("QTableView::item:hover{background-color:red;}");

	//set table header
	QStringList headers;
	headers << tr("order_id")<<tr("from_role")<<tr("f_id")<<tr("to_role")<<tr("t_id")<<tr("agv")<<tr("order_time");
	model_->setHorizontalHeader(headers);

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

interface_table::~interface_table()
{

}
void interface_table::show_manual_order(std::map<std::string ,manual_order*> m_manual_order)
{

	QVector<QStringList> data;

	auto it = m_manual_order.begin();
	for ( ; it != m_manual_order.end() ; ++it ){
		QStringList rowset;


		manual_order* p_order = it->second;

		rowset.push_back(QString::fromStdString(p_order->str_order_id_));
		rowset.push_back(QString::fromStdString(p_order->str_from_role_));
		rowset.push_back(QString::fromStdString(p_order->str_from_role_gp_id_));
		rowset.push_back(QString::fromStdString(p_order->str_to_role_));
		rowset.push_back(QString::fromStdString(p_order->str_to_role_gp_id_));
		rowset.push_back(QString::fromStdString(p_order->str_agv_gp_id_));
		rowset.push_back(QString::fromStdString(p_order->str_order_time_));
	
		data.append(rowset);
	}

	model_->setData(data);
}

std::vector<std::string> interface_table::del_sel_order()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();
	
	std::map<int, int> m_row;


	foreach (QModelIndex index, selected) {
		m_row[index.row()] = 0; //QModelIndex 有更多数据可用
	}

	return model_->remove_row(m_row);

}

std::vector<std::string> interface_table::sel_order()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();

	std::map<int, int> m_row;


	foreach (QModelIndex index, selected) {
		m_row[index.row()] = 0; //QModelIndex 有更多数据可用
	}

	return model_->selected(m_row);
}

QVector<QStringList> interface_table::get_data()
{
	return model_->DataVector();
}

