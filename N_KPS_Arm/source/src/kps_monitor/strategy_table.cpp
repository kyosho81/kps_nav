
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"

#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"
#include "protobuf_msg/comb_factory.h"
#include "readonly_delegate.h"
#include "combox_delegate.h"
#include "checkbox_delegate.h"

#include "strategy_model.h"

#include "strategy_table.h"

strategy_table::strategy_table( QWidget *parent)
	: QTableView(parent)
{

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

	
	model_ = new strategy_model(this);
	readonly_delegate* read_only = new readonly_delegate(this);
	combo_del_from_ = new combo_delegate(this);
	combo_del_to_ = new combo_delegate(this);
	checkbox_enable_ = new checkbox_delegate(this);
	checkbox_enable_->setColumn(COL_STRATEGY_ENABLE);

	checkbox_match_= new checkbox_delegate(this);
	checkbox_match_->setColumn(COL_STRATEGY_MATCH_ST);

	QMap<int,QString> items;
	std::vector<std::string> v_comb;
	COMB_FACTORY.get_role_name(v_comb);
	 
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_from_->setItems(items);
	combo_del_to_->setItems(items);

	//delegate_ = new interface_delegate();

	this->setModel(model_);   //绑定数据模型
	//this->setItemDelegate(delegate_);
	this->setSortingEnabled(true);
	this->setAlternatingRowColors(true);
	this->setStyleSheet("QTableView::item:hover{background-color:red;}");

	//set table header
	QStringList headers;
	headers << tr("strategy_id")<<tr("enable")<<tr("from_role")<<tr("f_id_gp")<<tr("carry_type")<<tr("to_role")<<tr("t_id_gp")<<tr("receive_type")<<tr("match_start")<<tr("agv_id_gp")<<tr("priority")<<tr("task_flow");
	model_->setHorizontalHeader(headers);


	setItemDelegateForColumn(COL_STRATEGY_ID, read_only);
	setItemDelegateForColumn(COL_STRATEGY_ENABLE,checkbox_enable_);
	setItemDelegateForColumn(COL_STRATEGY_ROLE_FROM, combo_del_from_); //
	setItemDelegateForColumn(COL_STRATEGY_ROLE_TO, combo_del_to_); //
	setItemDelegateForColumn(COL_STRATEGY_MATCH_ST, checkbox_match_); //

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

strategy_table::~strategy_table()
{

}
// 
// std::string strategy_table::covSta(manual_order::MANUAL_STATE state){
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
std::map<int, int> strategy_table::sel_schedule()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();
	
	std::map<int, int> m_row;

	foreach (QModelIndex index, selected) {
		std::string str_id = model_->get_data(index.row(),COL_STRATEGY_ID);
		int id = -1;
		if(cComm::ConvertToNum(id,str_id)){
			m_row[ id ] = 0;
		}
	}
	return m_row;
	//return model_->remove_row(m_row);
}

QVector<QStringList> strategy_table::get_data()
{
	return model_->DataVector();
}

void strategy_table::show_strategy( std::map<int,schedule_interface_data*> &m_schedule_list )
{
	QVector<QStringList> data;

	auto it = m_schedule_list.begin();
	for ( ; it != m_schedule_list.end() ; ++it ){
		QStringList rowset;


		schedule_interface_data* p_si_data = it->second;
		//headers << "strategy_id"<<"enable"<<"from_role"<<"f_id_gp"<<"carry_type"<<"to_role"<<"t_id_gp"<<"receive_type"<<"agv_id_gp"<<"priority"<<"task_flow_type";

 		rowset.push_back(QString::number(p_si_data->get_index()));
 		rowset.push_back(QString::number(p_si_data->activated()));
 		rowset.push_back(QString::fromStdString(p_si_data->start_role()));
 		rowset.push_back(QString::fromStdString(p_si_data->start_gp_id()));
 		rowset.push_back(QString::fromStdString(p_si_data->output_type()));
 		rowset.push_back(QString::fromStdString(p_si_data->end_role()));
 		rowset.push_back(QString::fromStdString(p_si_data->end_gp_id()));
		rowset.push_back(QString::fromStdString(p_si_data->input_type()));
		rowset.push_back(QString::number(p_si_data->match_from_start()));
		rowset.push_back(QString::fromStdString(p_si_data->agv_gp_id_str()));
 		rowset.push_back(QString::fromStdString(p_si_data->priority_str()));
		rowset.push_back(QString::fromStdString(p_si_data->task_flow_str()));
		SDelete(p_si_data);

		data.append(rowset);
	}

	model_->setData(data);
}

