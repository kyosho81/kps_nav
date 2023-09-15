#ifndef _KPS_ITEM_LAB_H_20191202_
#define _KPS_ITEM_LAB_H_20191202_


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

class lab_item : public QObject , public QGraphicsEllipseItem
{
	Q_OBJECT	

public:

	lab_item(float x, float y, QGraphicsItem *parent = 0);
	~lab_item();

	void set_id(const int &id);
	int get_id();
	void set_lab(const std::string str_lab);
	std::string get_lab();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	enum { Type = QtType::ITEM_LAB };
	int type() const{ return Type;}
	
private:

	//void UpdateBoundRect();

public:

	QRectF boundingRect() const;
	QPainterPath shape() const;

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
protected:

	

private:
	QPainterPath path_;

	QRectF m_bound_rect;


	QColor color_;
	QString qs_lab_;
	int id_;

	float lab_Showsize_;
	int stringWidth_;
	int stringHeight_;
};
#endif//_KPS_ITEM_LAB_H_20191202_
