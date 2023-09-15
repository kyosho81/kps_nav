#ifndef _STRATEGE_MODEL_H
#define _STRATEGE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>


#define COL_STRATEGY_ID        0
#define COL_STRATEGY_ENABLE    1
#define COL_STRATEGY_ROLE_FROM 2
#define COL_STRATEGY_FROM_GP   3
#define COL_STRATEGY_OUTPUT    4
#define COL_STRATEGY_ROLE_TO   5
#define COL_STRATEGY_TO_GP     6
#define COL_STRATEGY_INPUT     7
#define COL_STRATEGY_MATCH_ST  8
#define COL_STRATEGY_AGV_ID_GP 9
#define COL_STRATEGY_PRIORYTY  10
#define COL_STRATEGY_TASK_FLOW 11

class strategy_model : public QAbstractTableModel
{

	Q_OBJECT

public:

	explicit strategy_model(QObject *parent = 0);
	~strategy_model(void);

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
#endif//_STRATEGE_MODEL_H