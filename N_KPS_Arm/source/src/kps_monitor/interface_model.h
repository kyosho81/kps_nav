#ifndef _INTEFACE_MODEL_H
#define _INTEFACE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>


#define COL_ORDER_ID     0
#define COL_FROM_ROLE    1
#define COL_FROM_ROLE_ID 2
#define COL_TO_ROLE      3
#define COL_TO_ROLE_ID   4
#define COL_TO_AGV_ID    5
#define COL_ORDER_TIME   6

class interface_model : public QAbstractTableModel
{

	Q_OBJECT

public:

	explicit interface_model(QObject *parent = 0);
	~interface_model(void);

	int rowCount(const QModelIndex &parent) const;

	int columnCount(const QModelIndex &parent) const;

	QVariant data(const QModelIndex &index, int role) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

	void setHorizontalHeader(const QStringList& headers);

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void setData(const QVector<QStringList>& data);
	bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

	std::string remove_row(int i_row);
	std::vector<std::string> remove_row(std::map<int, int> m_row);
	std::vector<std::string> selected(std::map<int, int> m_row);

	QVector<QStringList> DataVector();
	
	std::string get_data(int row,int col);


	public slots:

private:
	QStringList m_HorizontalHeader;
	QVector<QStringList> m_data;

};
#endif//_ORDER_MODEL_H