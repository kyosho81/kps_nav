#ifndef _REFLECTOR_ITEM_KYOSHO_20210715_
#define _REFLECTOR_ITEM_KYOSHO_20210715_


#include <QtGui>
#include <QVector>
#include <QMap>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QRectF>
#include <QList>

#include <iostream>
#include <vector>
#include <map>

#ifndef Q_MOC_RUN
#include <boost/thread.hpp>
#endif
#include "robot/RobotStruct.h"
#include "scene/QTypeDefine.h"

// class EdgeLineItem;
// class EdgeBezierItem;
class protobuf_reflector;
class p_bag_ex_;

class reflector_item : public QObject , public QGraphicsEllipseItem
{
	Q_OBJECT	

public:

	reflector_item(float x, float y, QGraphicsItem *parent = 0);
	~reflector_item();

	enum { Type = QtType::ITEM_REFLECTOR };
	int type() const{ return Type;}

	void set_id(const int &id);
	int get_id();

	void set_ref_bag( protobuf_reflector* p_ref, SPUB_BAG_EX* p_bag_ex );

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	void update_show( bool b_update_pos = true );
private:

public:

	QRectF boundingRect() const;
	QPainterPath shape() const;


protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	
private:
	QPainterPath path_;

	void UpdateBoundRect();
	QRectF m_bound_rect;

	QPointF center_;
	F32 rx_;
	F32 ry_;
	QColor color_;

	int id_;

	protobuf_reflector* p_ref_;
	SPUB_BAG_EX* p_bag_ex_;
};
#endif//_REFLECTOR_ITEM_KYOSHO_20210715_
