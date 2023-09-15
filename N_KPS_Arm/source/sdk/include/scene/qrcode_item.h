#ifndef _QRCODE_ITEM_WANGHONGTAO_20230301_
#define _QRCODE_ITEM_WANGHONGTAO_20230301_


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
class protobuf_qrcode;

class qrcode_item : public QObject , public QGraphicsEllipseItem
{
	Q_OBJECT	

public:

	qrcode_item(float x, float y, float a, QGraphicsItem *parent = 0);
	~qrcode_item();

	enum { Type = QtType::ITEM_QRCODE };
	int type() const{ return Type;}

	void set_id(const int &id);
	int get_id();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	void update_show( bool b_update_pos = true );

private:

public:

	QRectF boundingRect() const;
	QPainterPath shape() const;


protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void draw_msg(QPainter *painter);
	void draw_pallet( QPainter *painter );

private:
	QPainterPath path_;

// 	void UpdateBoundRect();
// 	QRectF m_bound_rect;

	QPointF topleft_;
	F32 width_;
	F32 height_;
	QColor color_;

	int id_;

	int id_showsize_;
	int string_width_;
	int string_height_;

	protobuf_qrcode* p_qrcode_;

};
#endif//_QRCODE_ITEM_WANGHONGTAO_20230301_
