#include "iostream"


#include <QAbstractTableModel>
#include <QBrush>

#include "protobuf_msg/comb_factory.h"

#include "manual_model.h"


manual_model::manual_model(QObject *parent) :
QAbstractTableModel(parent)
{
}

manual_model::~manual_model()
{

}


int manual_model::rowCount(const QModelIndex &parent) const
{
	return m_data.size();
}

int manual_model::columnCount(const QModelIndex &parent) const
{
	return m_HorizontalHeader.count();
}

QVariant manual_model::data(const QModelIndex &index, int role) const
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
		if(index.column() == COL_FROM_ROLE)
		{
			QStringList comb_role_list;

			std::vector<std::string> v_comb;
			COMB_FACTORY.get_role_name(v_comb);
			auto it = v_comb.begin();
			for ( ; it != v_comb.end() ; ++it ){
				comb_role_list<<QString::fromStdString(*it);
			}
			return comb_role_list;

		}else if(index.column() == COL_TO_ROLE)
		{
			QStringList comb_role_list;

			std::vector<std::string> v_comb;
			COMB_FACTORY.get_role_name(v_comb);
			auto it = v_comb.begin();
			for ( ; it != v_comb.end() ; ++it ){
				comb_role_list<<QString::fromStdString(*it);
			}
			return comb_role_list;
		}
		
	
	}
	return QVariant();
}

Qt::ItemFlags manual_model::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	flag &= ~Qt::ItemIsEditable;


	// flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑
	return flag;
}

void manual_model::setHorizontalHeader(const QStringList &headers)
{
	m_HorizontalHeader =  headers;
}


QVariant manual_model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		return m_HorizontalHeader.at(section);
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

void manual_model::setData(const QVector<QStringList> &data)
{
	m_data = data;
	QModelIndex topLeft = createIndex(0,0);
	 QModelIndex bottomRight = createIndex(m_data.size(),m_HorizontalHeader.count());

	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}

bool manual_model::setData( const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole */ )
{
	if(role != Qt::EditRole || 
		!index.isValid() || 
		index.row()>=m_data.size() || 
		index.column()>=m_HorizontalHeader.count()
		) {
			return false;
	}
	if (index.column() == COL_ORDER_ID){
		return false;
	}
	//m_data.operator [](index.row()).replace(index.column(), value.toString());



	return true;
}

QVector<QStringList> manual_model::DataVector()
{
	return m_data;
	
}
std::vector<std::string> manual_model::remove_row(std::map<int, int> m_row){
	std::vector<std::string> v_res;
	auto it = m_row.begin();
	for ( ; it != m_row.end() ; ++it ){
		v_res.push_back(remove_row(it->first));
	}
	return v_res;
}
std::string manual_model::remove_row( int i_row )
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

std::string manual_model::get_data( int row,int col )
{
	if (m_data.size() >= row ){
		return "";
	}
	QStringList values = m_data.at(row);

	if (values.size() >= col){
		return values.at(col).toStdString();
	}
	
	return "";
}

std::vector<std::string> manual_model::selected(std::map<int, int> m_row)
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


