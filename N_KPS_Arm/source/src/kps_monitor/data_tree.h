#ifndef _DATA_TREE_20201116_H_
#define _DATA_TREE_20201116_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include <QTreeView>
#include "scene/mouse_event.h"
#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

class map_scene;

class data_tree : public QTreeView
{
	Q_OBJECT

public:
	data_tree( QWidget *parent = 0 );
	~data_tree();

	void init( QObject* obj,map_scene* map_sc);

protected:
private:
	void mouseDoubleClickEvent(QMouseEvent *event); 
signals:
	void sig_show_data(QString str);
	void sig_sel_item(QString str);
private:
	map_scene* map_scene_;
};

#endif//_DATA_TREE_20201116_H_