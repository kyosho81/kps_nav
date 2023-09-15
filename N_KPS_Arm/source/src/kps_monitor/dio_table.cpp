
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"

#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"
#include "protobuf_msg/comb_factory.h"
#include "readonly_delegate.h"
#include "combox_delegate.h"
#include "checkbox_delegate.h"
#include "robot/dio_def.h"
#include "dio_model.h"

#include "dio_table.h"

dio_table::dio_table( QWidget *parent)
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

	
	model_ = new dio_model(this);
	readonly_delegate* read_only_seq = new readonly_delegate(this);
	readonly_delegate* read_only_data = new readonly_delegate(this);

	combo_del_io_type_ = new combo_delegate(this);
	combo_del_function_ = new combo_delegate(this);
	combo_del_dev_type_ = new combo_delegate(this);
	combo_del_pin_ = new combo_delegate(this);

	checkbox_enable_ = new checkbox_delegate(this);
	checkbox_enable_->setColumn(COL_DIO_ENABLE);

	QMap<int,QString> items;
	std::vector<std::string> v_comb;
	COMB_FACTORY.get_io_type(v_comb);
	 
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_io_type_->setItems(items);
	
	items.clear();
	v_comb.clear();
	COMB_FACTORY.get_di_function(v_comb);
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_function_->setItems(items);

	items.clear();
	v_comb.clear();
	COMB_FACTORY.get_dev_type(v_comb);
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_dev_type_->setItems(items);

	items.clear();
	v_comb.clear();
	COMB_FACTORY.get_di_pin(v_comb);
	for ( int i = 0 ; i < v_comb.size() ; ++i ){
		items[i] = QString::fromStdString(v_comb[i]);
	}
	combo_del_pin_->setItems(items);


	//delegate_ = new interface_delegate();

	this->setModel(model_);   //绑定数据模型
	//this->setItemDelegate(delegate_);
	this->setSortingEnabled(true);
	this->setAlternatingRowColors(true);
	this->setStyleSheet("QTableView::item:hover{background-color:red;}");

	//set table header
	QStringList headers;
	headers << tr("seq")<<tr("enable")<<tr("io_type")<<tr("function")<<tr("dev_type")<<tr("pin")<<tr("data");
	model_->setHorizontalHeader(headers);


	setItemDelegateForColumn(COL_DIO_SEQ, read_only_seq);
	setItemDelegateForColumn(COL_DIO_ENABLE,checkbox_enable_);
	setItemDelegateForColumn(COL_DIO_IO_TYPE, combo_del_io_type_); //
	setItemDelegateForColumn(COL_DIO_FUNCTION, combo_del_function_); //
	setItemDelegateForColumn(COL_DIO_DEV_TYPE, combo_del_dev_type_); 
	setItemDelegateForColumn(COL_DIO_INDEX, combo_del_pin_); 
	setItemDelegateForColumn(COL_DIO_DATA, read_only_data); 
	
	

	setSortingEnabled(true);
}

dio_table::~dio_table()
{

}
// 
// std::string io_table::covSta(manual_order::MANUAL_STATE state){
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
std::map<int, int> dio_table::sel_dio()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();
	
	std::map<int, int> m_row;

	foreach (QModelIndex index, selected) {
		std::string str_id = model_->get_data(index.row(),COL_DIO_SEQ);
		int id = -1;
		if(cComm::ConvertToNum(id,str_id)){
			m_row[ id ] = 0;
		}
	}
	return m_row;
	//return model_->remove_row(m_row);
}

QVector<QStringList> dio_table::get_data()
{
	return model_->DataVector();
}
bool less_sort(SDIO_NM_INDEX a ,SDIO_NM_INDEX b ){
	if ( a.i_dio_index_ < b.i_dio_index_){
		return true;
	}
	return false;
}
void dio_table::show_dio_para( std::map<std::string, SDIO_NM_INDEX> &m_dio_bind )
{
	QVector<QStringList> data;

	std::multimap<std::string,SDIO_NM_INDEX> mt_dio_bind;
	std::map<std::string,int> m_dio_type;
	auto it = m_dio_bind.begin();
	for ( ; it != m_dio_bind.end() ; ++it ){

		SDIO_NM_INDEX &dio_nm_index = it->second;
		mt_dio_bind.insert(std::make_pair( dio_nm_index.str_type_ , dio_nm_index ));
		m_dio_type[dio_nm_index.str_type_] = 0;
	}
	typedef std::pair<std::multimap<std::string,SDIO_NM_INDEX>::iterator, std::multimap<std::string,SDIO_NM_INDEX>::iterator> PRT_IT;
	
	std::list<SDIO_NM_INDEX> l_data;
	auto it_type = m_dio_type.begin();
	for (  ; it_type != m_dio_type.end() ; ++it_type ){
		PRT_IT p_it = mt_dio_bind.equal_range(it_type->first);
		
		std::vector<SDIO_NM_INDEX> v_dio;
		std::multimap<std::string,SDIO_NM_INDEX>::iterator it2 = p_it.first;
		for ( ; it2 != p_it.second ; ++it2 ){
			v_dio.push_back (it2->second);
		}

		std::sort(v_dio.begin(),v_dio.end(),less_sort);
		l_data.insert(l_data.end(),v_dio.begin(),v_dio.end());
	}

	int i_seq = 0;
	auto it_l = l_data.begin();
	for ( ; it_l != l_data.end() ; ++it_l ){
		
		SDIO_NM_INDEX &dio_nm_index = *it_l;

		//headers << tr("seq")<<tr("enable")<<tr("io_type")<<tr("function")<<tr("dev_type")<<tr("pin")<<tr("data");

		QStringList rowset;
		rowset.push_back(QString::number(i_seq++));
		rowset.push_back(QString::number(1));
		rowset.push_back(QString::fromStdString(std::string(dio_nm_index.str_type_)));
		rowset.push_back(QString::fromStdString(std::string(dio_nm_index.str_fnc_nm_)));
		rowset.push_back(QString::fromStdString(std::string(dio_nm_index.str_dev_nm_)));
		rowset.push_back(QString::fromStdString(cComm::ConvertToString(dio_nm_index.i_dio_index_)));
		rowset.push_back(QString::fromStdString(std::string("0")));

		data.append(rowset);
	}
	

	model_->setData(data);

	//setColumnWidth(COL_DIO_SEQ, 30);
	setColumnWidth(COL_DIO_ENABLE, 50);
	setColumnWidth(COL_DIO_IO_TYPE, 120);
	setColumnWidth(COL_DIO_FUNCTION, 200);
	setColumnWidth(COL_DIO_DEV_TYPE, 120);
	setColumnWidth(COL_DIO_INDEX, 120);
	setColumnWidth(COL_DIO_DATA, 120);
}

void dio_table::show_dio_data(std::vector<SDIO_NM_INDEX> &v_data)
{
	model_->setIOData(v_data);
}

