
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "action_data_model.h"

#include "action_monitor_table.h"

action_monitor_table::action_monitor_table( QWidget *parent)
	: QTableView(parent)
{

	setSelectionBehavior(QAbstractItemView::SelectRows); //只能选中行
	
	setAlternatingRowColors(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	//this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选中一行
	/*this->setMinimumWidth((int)1200);*/
	setObjectName(tr("action_monitor"));
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	horizontalHeader()->setStretchLastSection(true);


	model_ = new action_data_model(this);
	setModel(model_);   //绑定数据模型

	//set table header
	QStringList headers;
	headers << tr("action id")<<tr("action status")<<tr("init para");
	model_->setHorizontalHeader(headers);

	setColumnWidth(1, 120);

	setSortingEnabled(true);

}

action_monitor_table::~action_monitor_table()
{

}

int action_monitor_table::get_select_action_id()
{
	//QList<QModelIndex> list qmindex = selectionModel()->selectedRows()
	QModelIndexList qmindex = selectedIndexes();
	int i_action_id = -1;
	if (qmindex.size() > 0){
		//i_row = qmindex[0].row();
		QVector<QStringList> qv_data = model_->DataVector();
		i_action_id = qv_data[qmindex[0].row()].at(0).toInt();

	}
	return i_action_id;
}

