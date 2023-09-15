#ifndef _TASK_FLOW_MODEL_MODEL_H
#define _TASK_FLOW_MODEL_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>


#define COL_TASK_FLOW_ID            0
#define COL_TASK_FLOW_PUTGET		1
#define COL_TASK_FLOW_MV_SEG		2
#define COL_TASK_FLOW_ACT_1         3



class task_flow_model : public QAbstractTableModel
{

	Q_OBJECT

public:

	explicit task_flow_model(QObject *parent = 0);
	~task_flow_model(void);

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
#endif//_TASK_FLOW_MODEL_MODEL_H