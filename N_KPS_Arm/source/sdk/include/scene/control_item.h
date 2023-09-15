#ifndef _CONTROL_ITEM_KYOSHO_20180715_
#define _CONTROL_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

#include <QGraphicsItem>

#include "robot/RobotStruct.h"


class control_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	control_item(QGraphicsItem *parent = 0);
	~control_item();

	QRectF boundingRect() const;

	
	int ctl_index_;

private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	
	QPainterPath shape() const;
	
private:

	QPainterPath painter_path_;

	QRectF bounding_rect_;
	F32 f_pan_width_;

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
//public:
signals:
	void s_update(int,SPos);
};

#endif//_CONTROL_ITEM_KYOSHO_20180715_