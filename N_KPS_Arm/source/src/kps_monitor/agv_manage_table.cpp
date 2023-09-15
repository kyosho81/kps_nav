
#include <QDebug>
#include <QHeaderView>

#include "Comm/Comm.h"
#include "interface/xml_rpc_client.h"
#include "agv_manage_model.h"

#include "agv_manage_table.h"

agv_manage_table::agv_manage_table( QWidget *parent)
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
	this->setObjectName("agv_manage_monitor");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);


	model_ = new agv_manage_model(this);
	this->setModel(model_);   //绑定数据模型

	//set table header
	QStringList headers;
	headers << tr("id")<<tr("ip")<<tr("port")<<tr("type")<<tr("status")<<tr("lock")<<tr("pause")<<tr("node_from")<<tr("node_to")<<tr("fork_lev")<<tr("fork_speed")<<tr("battery")<<tr("message");
	model_->setHorizontalHeader(headers);

	this->setColumnWidth(1, 120);

	this->setSortingEnabled(true);
}

agv_manage_table::~agv_manage_table()
{

}

void agv_manage_table::show_agv_list(const std::map<int,SAGV_Info> &m_agv_infoo, std::map<int,SRobot_Inf> &m_robo_info , const std::map<int,std::pair<int,int>> &m_lock_pause , const std::map<int,SAct_Fork> &m_ex_data )
{

	QVector<QStringList> data;

	auto cit = m_agv_infoo.cbegin();
	for ( ; cit != m_agv_infoo.end() ; ++cit ){
	
		const SAGV_Info &agv_info(cit->second);
		QStringList rowset;
		rowset.push_back(QString::number(agv_info.id_));
		std::string str_ip = agv_info.ch_ip_;
		rowset.push_back(QString::fromStdString(str_ip));
		rowset.push_back(QString::number(agv_info.action_rpc_port_));	
		rowset.push_back(QString::fromStdString(covAgvType(agv_info.agv_type_)));
		rowset.push_back(QString::fromStdString(covAgvStatus(agv_info.status_)));
		
		auto it = m_lock_pause.find(cit->first);
		if (it != m_lock_pause.end()){
			rowset.push_back(QString::fromStdString(covLock(it->second.first)));
			rowset.push_back(QString::fromStdString(covPause(it->second.second)));
		}else{
			rowset.push_back(QString::fromStdString(""));
			rowset.push_back(QString::fromStdString(""));
		}
		auto it2 = m_ex_data.find(cit->first);
		if ( it2 != m_ex_data.end()){
			rowset.push_back(QString::number(it2->second.act_base_.node_from_));
			rowset.push_back(QString::number(it2->second.act_base_.node_to_));
			rowset.push_back(QString::number(it2->second.act_data_.level_));
			rowset.push_back(QString::number(it2->second.act_data_.speed_));
		}
		auto it3 = m_robo_info.find(cit->first);
		if ( it3 != m_robo_info.end() ){
			rowset.push_back(QString::number(it3->second.bat_.percent_*100));
		}
		std::string str_msg = agv_info.ch_msg_;
		rowset.push_back(QString::fromStdString(str_msg));
		data.append(rowset);
	}
 
 	model_->setData(data);
}

std::string agv_manage_table::covAgvType(const AGV_TYPE agv_type)
{
	switch (agv_type)
	{
	case AGV_TYPE::AGV_TYPE_2WD :
		return "2WD";
		break;
	case AGV_TYPE::AGV_TYPE_FORK_LIFT :
		return "FORK_LIFT";
		break;
	case AGV_TYPE::AGV_TYPE_SIM :
		return "SIM";
		break;
	default:
		return "UNKNOWN";
	}
}

std::string agv_manage_table::covAgvStatus(int status)
{
	switch ((AGV_SM)status)
	{
	case AGV_SM::AGV_SM_NONE :
		return "NONE";
		break;
	case AGV_SM::AGV_SM_IDLE :
		return "IDLE";
		break;
	case AGV_SM::AGV_SM_INIT :
		return "INIT";
		break;
	case AGV_SM::AGV_SM_PACK :
		return "PACK";
		break;
	case AGV_SM::AGV_SM_CHARGE :
		return "CHARGE";
		break;
	case AGV_SM::AGV_SM_PACKING :
		return "PACKING";
		break;
	case AGV_SM::AGV_SM_CHARGING :
		return "CHARGING";
		break;
	case AGV_SM::AGV_SM_WANDER :
		return "WANDER";
		break;
	case AGV_SM::AGV_SM_ERROR :
		return "ERROR";
		break;
	case AGV_SM::AGV_SM_CLOSE ://agv close
		return "CLOSETO";
		break;
	case AGV_SM::AGV_SM_TASK_INIT :
		return "TASK_INIT";
		break;
	case AGV_SM::AGV_SM_TASK_DO :
		return "TASK_DO";
		break;
	default:
		return "UNKNOWN";
	}
}

std::string agv_manage_table::covLock( int i_lock )
{
	switch (i_lock)
	{
	case 0:
		return "offline";
		break;
	case 1:
		return "lock";
		break;
	case 2:
		return "unlock";
		break;
	default:
		break;
	}
	return "";
}

std::string agv_manage_table::covPause( int i_pause )
{
	switch (i_pause)
	{
	case 0:
		return "run";
		break;
	case 1:
		return "pause";
		break;
	default:
		break;
	}
	return "";
}
std::map<int, int> agv_manage_table::sel_agv_lock()
{
	QItemSelectionModel *selections = selectionModel();
	QModelIndexList selected = selections->selectedIndexes();

	std::map<int, int> m_row;

	foreach (QModelIndex index, selected) {
		std::string str_id = model_->get_data(index.row(),0);
		std::string str_lock = model_->get_data(index.row(),5);
		int id = -1;
		if(cComm::ConvertToNum(id,str_id)){
			if (str_lock == "unlock"){
				m_row[ id ] = 2;
			}else if (str_lock == "lock"){
				m_row[ id ] = 1;
			}else{
				m_row[ id ] = 0;
			}
			
		}
	}
	return m_row;
	//return model_->remove_row(m_row);
}

