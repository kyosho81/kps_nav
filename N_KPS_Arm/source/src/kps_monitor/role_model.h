#ifndef _ROLE_MODEL_H
#define _ROLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class role_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit role_model(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setHorizontalHeader(const QStringList& headers);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setData(const QVector<QStringList>& data);
	QVector<QStringList> DataVector();
	
	~role_model(void);


	public slots:

private:
	QStringList m_HorizontalHeader;
	QVector<QStringList> m_data;

};
#endif//_ROLE_MODEL_H