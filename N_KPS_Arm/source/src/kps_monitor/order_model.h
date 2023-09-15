#ifndef _ORDER_MODEL_H
#define _ORDER_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class order_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit order_model(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setHorizontalHeader(const QStringList& headers);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setData(const QVector<QStringList>& data);
	QVector<QStringList> DataVector();
	
	~order_model(void);


	public slots:

private:
	QStringList m_HorizontalHeader;
	QVector<QStringList> m_data;

};
#endif//_ORDER_MODEL_H