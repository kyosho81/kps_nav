#ifndef _DEV_DATA_MODEL_H
#define _DEV_DATA_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class dev_data_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit dev_data_model(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setHorizontalHeader(const QStringList& headers);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setData(const QVector<QStringList>& data);
	QVector<QStringList> DataVector();
	
	~dev_data_model(void);

signals:

	public slots:

private:
	QStringList m_HorizontalHeader;
	QVector<QStringList> m_data;

};
#endif//_DEV_DATA_MODEL_H