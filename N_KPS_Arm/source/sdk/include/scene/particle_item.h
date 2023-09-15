#ifndef _PARTICLES_ITEM_KYOSHO_20180715_
#define _PARTICLES_ITEM_KYOSHO_20180715_


#include <QtGui>
#include <QGraphicsItem>
#include <iostream>

#include <string>
#include "robot/RobotStruct.h"

class particle_item :public QObject , public QGraphicsItem
{
	Q_OBJECT
	//Q_INTERFACES(QObject QGraphicsItem)

public:

	particle_item(QGraphicsItem *parent = 0);
	~particle_item();
	
	void update_particles(const std::vector<STriangle>& v_particles);


private:
	std::vector<STriangle> particles_;

public:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	QRectF m_bound_rect;
	void UpdateBoundRect();
	void get_triangle(STriangle &triangle);
};

#endif//_PARTICLES_ITEM_KYOSHO_20180715_
