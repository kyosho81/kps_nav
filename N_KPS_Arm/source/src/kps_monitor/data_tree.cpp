
#include <QDebug>
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"
#include "Comm/Comm.h"

#include "data_tree.h"

data_tree::data_tree( QWidget *parent)
{
	map_scene_ = 0;
}

data_tree::~data_tree()
{



}

void data_tree::init(QObject* obj,map_scene* map_sc)
{
	connect(this,SIGNAL(sig_sel_item(QString)),(QObject*)map_sc,SLOT(slot_sel_item(QString))); 
	connect(this,SIGNAL(sig_show_data(QString)),obj,SLOT(slot_show_data(QString))); 
}

void data_tree::mouseDoubleClickEvent(QMouseEvent *event)
{

	if (event->button() == Qt::LeftButton) {
		QModelIndex index0 = currentIndex(); 
		QVariant data = index0.data(Qt::UserRole+1);
		qDebug() <<" tree signal:" << index0.data().toString(); 
		sig_show_data(index0.data().toString());
		sig_sel_item(index0.data().toString());

	}
}

#if 0
QTreeView* treeView;
......
	QItemSelectionModel* selectionModel = treeView->selectionModel();
// 假设要选取有效范围内的第3行
QModelIndex headModelIndex = treeView->model()->index(2, 0);
QModelIndex tailModelIndex = treeView->model()->index(2, treeView->model()->columnCount()-1);

QItemSelection itemSelection(headModelIndex, tailModelIndex);
selectionModel->select(itemSelection, QItemSelectionModel::SelectCurrent);

#endif