#include "iostream"


#include <QAbstractTableModel>
#include <QBrush>

#include "protobuf_msg/comb_factory.h"

#include "task_flow_model.h"


task_flow_model::task_flow_model(QObject *parent) :
QAbstractTableModel(parent)
{
}

task_flow_model::~task_flow_model()
{

}


int task_flow_model::rowCount(const QModelIndex &parent) const
{
	return m_data.size();
}

int task_flow_model::columnCount(const QModelIndex &parent) const
{
	return m_HorizontalHeader.count();
}

QVariant task_flow_model::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == Qt::TextAlignmentRole)
	{
		return int(Qt::AlignHCenter | Qt::AlignVCenter);
	}
	if (role == Qt::DisplayRole) {
		int ncol = index.column();
		int nrow =  index.row();
		QStringList values = m_data.at(nrow);
		

		if (values.size() > ncol)
			return values.at(ncol);
		else
			return QVariant();
	}
	if(role == Qt::BackgroundRole)
	{
		
	}
	if(role == Qt::ForegroundRole)
	{
		int ncol = index.column();
		int nrow =  index.row();
		QStringList values = m_data.at(nrow);
// 		if(values.at(2).toStdString()=="DS Err")
// 		{
// 			return QBrush(QColor(Qt::red));
// 		}
// 		if((values.at(3).toStdString() != ".") && (values.at(2).toStdString() != "Mapping Idle"))
// 		{
// 			return QBrush(QColor(Qt::darkRed));
// 		}
// 		if((values.at(2).toStdString() == "DS Run")  || (values.at(2).toStdString() == "Bag Idle") || (values.at(2).toStdString() == "Mapping Idle"))
// 		{
// 			return QBrush(QColor(Qt::darkGreen));
// 		}else{
// 			return QBrush(QColor(Qt::darkRed));
// 		}
	}
	if (role == Qt::EditRole) {
		QStringList values = m_data.at(index.row());
		QString qs = values.at(index.column());
		return qs;
	}
	if(role == Qt::UserRole)
	{
// 		if(index.column() == COL_FROM_ROLE)
// 		{
// 			QStringList comb_role_list;
// 
// 			std::vector<std::string> v_comb;
// 			COMB_FACTORY.get_role_name(v_comb);
// 			auto it = v_comb.begin();
// 			for ( ; it != v_comb.end() ; ++it ){
// 				comb_role_list<<QString::fromStdString(*it);
// 			}
// 			return comb_role_list;
// 
// 		}else if(index.column() == COL_TO_ROLE)
// 		{
// 			QStringList comb_role_list;
// 
// 			std::vector<std::string> v_comb;
// 			COMB_FACTORY.get_role_name(v_comb);
// 			auto it = v_comb.begin();
// 			for ( ; it != v_comb.end() ; ++it ){
// 				comb_role_list<<QString::fromStdString(*it);
// 			}
// 			return comb_role_list;
// 		}
		
	
	}
	return QVariant();
}

Qt::ItemFlags task_flow_model::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	//flag &= ~Qt::ItemIsEditable;


	flag |= Qt::ItemIsEditable; // 设置单元格可编辑,此处注释,单元格无法被编辑
	return flag;
}

void task_flow_model::setHorizontalHeader(const QStringList &headers)
{
	m_HorizontalHeader =  headers;
}


QVariant task_flow_model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		return m_HorizontalHeader.at(section);
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

void task_flow_model::setData(const QVector<QStringList> &data)
{
	m_data = data;
	QModelIndex topLeft = createIndex(0,0);
	 QModelIndex bottomRight = createIndex(m_data.size(),m_HorizontalHeader.count());

	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}

bool task_flow_model::setData( const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole */ )
{
	if(role != Qt::EditRole || 
		!index.isValid() || 
		index.row()>=m_data.size() || 
		index.column()>=m_HorizontalHeader.count()
		) {
			return false;
	}
	if ( (index.column() == COL_TASK_FLOW_ID) ||
		 (index.column() == COL_TASK_FLOW_PUTGET) ||
		 (index.column() == COL_TASK_FLOW_MV_SEG) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 0) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 1) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 2) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 3) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 4) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 5) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 6) ||
		 (index.column() == COL_TASK_FLOW_ACT_1 + 7) 
		){
		std::string str = value.toString().toStdString();
		m_data.operator [](index.row()).replace(index.column(), value.toString());
		return true;
	}


	return false;
}

QVector<QStringList> task_flow_model::DataVector()
{
	return m_data;
	
}
std::vector<std::string> task_flow_model::remove_row(std::map<int, int> m_row){
	std::vector<std::string> v_res;
	auto it = m_row.begin();
	for ( ; it != m_row.end() ; ++it ){
		v_res.push_back(remove_row(it->first));
	}
	return v_res;
}
std::string task_flow_model::remove_row( int i_row )
{
	auto it = m_data.begin() + i_row;
	std::string str_name;

	if ( it != m_data.end() ){

		str_name = (*it).at(0).toStdString();
		m_data.erase(it);

		QModelIndex topLeft = createIndex(0,0);
		QModelIndex bottomRight = createIndex(m_data.size(),m_HorizontalHeader.count());

		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
		
		return str_name;
	}
	return str_name;
	
}

std::string task_flow_model::get_data( int row,int col )
{
	if (row >= m_data.size()  ){
		return "";
	}
	QStringList values = m_data.at(row);

	if ( col < values.size() ){
		return values.at(col).toStdString();
	}
	
	return "";
}

std::vector<std::string> task_flow_model::selected(std::map<int, int> m_row)
{
	std::vector<std::string> v_res;

	auto it = m_row.begin();
	for ( ; it != m_row.end() ; ++it ){

		auto it2 = m_data.begin() + it->first;
		std::string str_name;

		if ( it2 != m_data.end() ){

			str_name = (*it2).at(0).toStdString();
			v_res.push_back(str_name);
		}
	}
	return v_res;
}


