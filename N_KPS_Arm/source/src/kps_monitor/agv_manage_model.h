#ifndef _AGV_MANAGE_MODEL_H
#define _AGV_MANAGE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class agv_manage_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit agv_manage_model(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setHorizontalHeader(const QStringList& headers);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setData(const QVector<QStringList>& data);
	QVector<QStringList> DataVector();
	
	std::string get_data( int row,int col );

	~agv_manage_model(void);

signals:

	public slots:

private:
	QStringList m_HorizontalHeader;
	QVector<QStringList> m_data;

};
#endif//_AGV_MANAGE_MODEL_H