
#ifndef _IO_TABLE_KYOSHO_20230220_H_
#define _IO_TABLE_KYOSHO_20230220_H_

#include <QTimer>
#include <QTableView>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#include "dispatching/manual_order.h"

#endif


class dio_model;
class combo_delegate;
class checkbox_delegate;

bool less_sort(SDIO_NM_INDEX a ,SDIO_NM_INDEX b );

class dio_table : public QTableView 
{

	Q_OBJECT

public:

	dio_table( QWidget *parent = 0 );
	~dio_table();

	void show_dio_para( std::map<std::string, SDIO_NM_INDEX> &m_dio_bind );
	void show_dio_data( std::vector<SDIO_NM_INDEX> &v_data );
	std::map<int, int> sel_dio();

	QVector<QStringList> get_data();

	//std::string covSta(manual_order::MANUAL_STATE state);

private:


	dio_model* model_;

	combo_delegate* combo_del_io_type_;
	combo_delegate* combo_del_function_;
	combo_delegate* combo_del_dev_type_;
	combo_delegate* combo_del_pin_;

	checkbox_delegate* checkbox_enable_;
};

#endif//_IO_TABLE_KYOSHO_20230220_H_