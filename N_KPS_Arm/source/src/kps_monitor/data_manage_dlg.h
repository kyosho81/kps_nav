#ifndef _DATA_MANAGE_DLG_H_
#define _DATA_MANAGE_DLG_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include <QSplitter>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"

#endif

class QStandardItemModel;
class data_edit_dlg;
class data_tree;
class map_scene;

class data_manage_dlg : public QSplitter
{
	Q_OBJECT

public:

	data_manage_dlg( QWidget *parent = 0 ) ;
	~data_manage_dlg();

	void init(map_scene* map_sc);

	


public slots:
	void updateTimerEvent();


	void ChooseRefresh(bool flag);
	void ChooseSave(bool flag);

	
	
private:
	QTimer *timer_;


// 	QPushButton* btn_refresh_;
// 	QPushButton* btn_save_;
// 	QPushButton* btn_add_;
// 	QPushButton* btn_del_;

private:
	void init_timer();
	QString merge_type_id( std::string str_type, int id);
	QString merge_type_name( std::string str_type, std::string str_nm);
	void init_tree_header();
	void load_tree_data();

	QStandardItemModel* model_;
	data_tree *tree_;
	data_edit_dlg* data_edit_dlg_;

private:

	void load_node();
	void load_edge();
	void load_reflector();
	void load_lab();
	void load_range();
	void load_cargo_type();
	void load_pallet_type();
	void load_producer();
	void load_consumer();
	void load_processer();
	void load_storage();
	void load_charge();
	void load_rect();
	void load_qrcode();

	QStandardItem* item_node_;
	QStandardItem* item_edge_;
	QStandardItem* item_reflector_;
	QStandardItem* item_lab_;
	QStandardItem* item_range_;
	QStandardItem* item_cargo_type_;
	QStandardItem* item_pallet_type_;
	QStandardItem* item_producer_;
	QStandardItem* item_consumer_;
	QStandardItem* item_processer_;
	QStandardItem* item_storage_;
	QStandardItem* item_charge_;
	QStandardItem* item_rect_;
	QStandardItem* item_qrcode_;
};

#endif//_DATA_MANAGE_DLG_H_