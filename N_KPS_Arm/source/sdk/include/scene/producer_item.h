#ifndef _PRODUCER_ITEM_WANGHONGTAO_20220101_
#define _PRODUCER_ITEM_WANGHONGTAO_20220101_


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
class protobuf_producer;

class producer_item : public QObject , public QGraphicsEllipseItem
{
	Q_OBJECT	

public:

	producer_item(float x, float y, QGraphicsItem *parent = 0);
	~producer_item();

	enum { Type = QtType::ITEM_PRODUCER };
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
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void draw_msg(QPainter *painter);
	void draw_pallet(QPainter *painter);
	void draw_enable( QPainter *painter );
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

	protobuf_producer* p_producer_;
	
	int assigned_agv_id_;
	bool b_occupyed_;
	std::string str_pt_;
	int i_pallet_state_;//0 empt 1 pallet on 2 full pallet
};
#endif//_PRODUCER_ITEM_WANGHONGTAO_20220101_
