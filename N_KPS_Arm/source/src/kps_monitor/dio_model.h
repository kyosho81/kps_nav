#ifndef _DIO_MODEL_KYOSHO_20320220_H
#define _DIO_MODEL_KYOSHO_20320220_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#endif

#define COL_DIO_SEQ        0
#define COL_DIO_ENABLE     1
#define COL_DIO_IO_TYPE    2
#define COL_DIO_FUNCTION   3
#define COL_DIO_DEV_TYPE   4
#define COL_DIO_INDEX      5
#define COL_DIO_DATA       6


class dio_model : public QAbstractTableModel
{

	Q_OBJECT

public:

	explicit dio_model(QObject *parent = 0);
	~dio_model(void);

	int rowCount(const QModelIndex &parent) const;

	int columnCount(const QModelIndex &parent) const;

	QVariant data(const QModelIndex &index, int role) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

	void setHorizontalHeader(const QStringList& headers);

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void setData(const QVector<QStringList>& data);
	bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	bool setIOData( std::vector<SDIO_NM_INDEX> &v_data);

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
#endif//_DIO_MODEL_KYOSHO_20320220_H