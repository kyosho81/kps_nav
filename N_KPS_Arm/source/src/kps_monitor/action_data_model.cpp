#include "iostream"


#include <QAbstractTableModel>
#include <QBrush>

#include "action_data_model.h"

action_data_model::action_data_model(QObject *parent) :
QAbstractTableModel(parent)
{
}

action_data_model::~action_data_model()
{

}


int action_data_model::rowCount(const QModelIndex &parent) const
{
	return m_data.size();
}

int action_data_model::columnCount(const QModelIndex &parent) const
{
	return m_HorizontalHeader.count();
}

QVariant action_data_model::data(const QModelIndex &index, int role) const
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
	return QVariant();
}

Qt::ItemFlags action_data_model::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	// flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑
	return flag;
}

void action_data_model::setHorizontalHeader(const QStringList &headers)
{
	m_HorizontalHeader =  headers;
}


QVariant action_data_model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		return m_HorizontalHeader.at(section);
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

void action_data_model::setData(const QVector<QStringList> &data)
{
	m_data = data;
	QModelIndex topLeft = createIndex(0,0);
	 QModelIndex bottomRight = createIndex(m_data.size(),m_HorizontalHeader.count());
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}

QVector<QStringList> action_data_model::DataVector()
{
	return m_data;
	
}