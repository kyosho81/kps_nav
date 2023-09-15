#ifndef _NODE_CONTROL_ITEM_KYOSHO_20180715_
#define _NODE_CONTROL_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

#include <QGraphicsItem>

#include "robot/RobotStruct.h"
#include "scene/QTypeDefine.h"

class edge_item;

class node_control_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	node_control_item(QGraphicsItem *parent = 0);
	~node_control_item();

	QRectF boundingRect() const;

	enum { Type = QtType::ITEM_NODE_CTRL };
	int type() const{ return Type;}

	void set_id(const int &id);
	int get_id();

	QPainterPath shape() const;
private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	
	
	
private:

	QPainterPath painter_path_;

	QRectF bounding_rect_;

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
//public:
signals:
	void s_update(int,SPos);

private:
	int id_;
};

#endif//_CONTROL_ITEM_KYOSHO_20180715_