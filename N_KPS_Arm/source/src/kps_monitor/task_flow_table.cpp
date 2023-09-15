
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"

#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"
#include "protobuf_msg/comb_factory.h"
#include "readonly_delegate.h"
#include "combox_delegate.h"
#include "checkbox_delegate.h"

#include "task_flow_model.h"

#include "task_flow_table.h"

task_flow_table::task_flow_table( QWidget *parent)
	: QTableView(parent)
{

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::DoubleClicked);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	/*this->setMinimumWidth((int)1200);*/
	this->setObjectName("task_flow");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);

	
	model_ = new task_flow_model(this);

	readonly_delegate* read_only = new readonly_delegate(this);
	combo_del_get_put_ = new combo_delegate(this);
	combo_del_mv_seg_ = new combo_delegate(this);

// 	checkbox_enable_ = new checkbox_delegate(this);
// 	checkbox_enable_->setColumn(COL_STRATEGY_ENABLE);

 	QMap<int,QString> items;
 	std::vector<std::string> v_comb;
 	COMB_FACTORY.get_getput(v_comb);

	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_get_put_->setItems(items);

	items.clear();
	v_comb.clear();
	COMB_FACTORY.get_mv_seg(v_comb);
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_mv_seg_->setItems(items);
	//delegate_ = new interface_delegate();

	this->setModel(model_);   //绑定数据模型
	//this->setItemDelegate(delegate_);
	this->setSortingEnabled(true);
	this->setAlternatingRowColors(true);
	this->setStyleSheet("QTableView::item:hover{background-color:red;}");

	//set table header
	QStringList headers;
	headers << tr("id")<<tr("put_get")<<tr("mv_seg")<<tr("act1")<<tr("act2")<<tr("act3")<<tr("act4")<<tr("act5")<<tr("act6")<<tr("act7")<<tr("act8");
	model_->setHorizontalHeader(headers);


 	setItemDelegateForColumn(COL_TASK_FLOW_ID, read_only);
 	setItemDelegateForColumn(COL_TASK_FLOW_PUTGET,combo_del_get_put_);
 	setItemDelegateForColumn(COL_TASK_FLOW_MV_SEG, combo_del_mv_seg_);

	items.clear();
	v_comb.clear();
	COMB_FACTORY.get_actions(v_comb,true);
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}

	for ( int i = 0 ; i < 8; ++i ){
		m_combo_del_act_[i] = new combo_delegate();
		m_combo_del_act_[i]->setItems(items);
		setItemDelegateForColumn(COL_TASK_FLOW_ACT_1 + i, m_combo_del_act_[i]);
	}
// 	setItemDelegateForColumn(COL_STRATEGY_ROLE_TO, combo_del_to_); //

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

task_flow_table::~task_flow_table()
{

}
// 
// std::string task_flow_table::covSta(manual_order::MANUAL_STATE state){
// 	switch(state){
// 	case manual_order::MANUAL_NONE:
// 		return "NONE";
// 		break;
// 	case manual_order::MANUAL_COMMIT:
// 		return "COMMIT";
// 		break;
// 	case manual_order::MANUAL_DOING:
// 		return "DOING";
// 		break;
// 	case manual_order::MANUAL_DONE:
// 		return "DONE";
// 		break;
// 	case manual_order::MANUAL_ERROR:
// 		return "ERROR";
// 		break;
// 	}
// }
std::map<int, int> task_flow_table::sel_task_flow()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();
	
	std::map<int, int> m_row;

	foreach (QModelIndex index, selected) {
		std::string str_id = model_->get_data(index.row(),COL_TASK_FLOW_ID);
		int id = -1;
		if(cComm::ConvertToNum(id,str_id)){
			m_row[ id ] = 0;
		}
	}
	return m_row;
	//return model_->remove_row(m_row);
}

QVector<QStringList> task_flow_table::get_data()
{
	return model_->DataVector();
}

void task_flow_table::show_task_flow( std::list<SSTaskFlow*> &l_task_flow )
{
	QVector<QStringList> data;

	auto it = l_task_flow.begin();
	for ( ; it != l_task_flow.end() ; ++it ){
		QStringList rowset;

		SSTaskFlow* p_task_flow  = *it;

		rowset.push_back(QString::number(p_task_flow->i_id_));
		rowset.push_back(QString::fromStdString(p_task_flow->str_get_put_));
		rowset.push_back(QString::fromStdString(p_task_flow->str_mv_seg_));
		for (int i = 0 ; i < 8 ; ++i ){
			if ( i < p_task_flow->v_act_dec_.size() ){
				rowset.push_back(QString::fromStdString(p_task_flow->v_act_dec_[i].str_act_));
			}
		}
		

		data.append(rowset);
	}
	if (model_){
		model_->setData(data);
	}
	
}

std::list<std::pair<int,int> > task_flow_table::get_sel()
{
	std::list<std::pair<int,int> > lp_sel;
	QModelIndexList mindex = selectionModel()->selectedIndexes();
	int row = 0;
	int column = 0;
	for ( int i = 0; i < mindex.size() ; ++i ){
		row = mindex.at(i).row();
		column = mindex.at(i).column();
		if (((COL_TASK_FLOW_ACT_1 + 0) == column) ||
			((COL_TASK_FLOW_ACT_1 + 1) == column) ||
			((COL_TASK_FLOW_ACT_1 + 2) == column) ||
			((COL_TASK_FLOW_ACT_1 + 3) == column) ||
			((COL_TASK_FLOW_ACT_1 + 4) == column) ||
			((COL_TASK_FLOW_ACT_1 + 5) == column) ||
			((COL_TASK_FLOW_ACT_1 + 6) == column) ||
			((COL_TASK_FLOW_ACT_1 + 7) == column)
		){
			lp_sel.push_back(std::make_pair(row,column));
		}
		
	}
	return lp_sel;
}

