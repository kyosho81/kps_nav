#ifndef _NODE_ITEM_KYOSHO_20201224_
#define _NODE_ITEM_KYOSHO_20201224_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#endif

#include <QPointF>
#include <QtGui>
#include <QGraphicsItem>
#include <iostream>

#include <string>
#include "robot/RobotStruct.h"
#include "scene/QTypeDefine.h"
#include "Geometry.h"

class node_item :public QObject , public QGraphicsItem
{
	Q_OBJECT
	//Q_INTERFACES(QObject QGraphicsItem)

public:

	node_item(QGraphicsItem *parent = 0);
	~node_item();
	
	enum { Type = QtType::ITEM_NODE };
	int type() const{ return Type;}

	void set_id(const int &id);
	int get_id();
	SPos get_pos();

	void addEdge(QGraphicsItem* edge);
	void removeEdge(QGraphicsItem *edge);
	QList<QGraphicsItem*> get_edge_list();

	//void update_view_data(std::vector<SView_Data> &v_data);
	//void update_particles(const std::vector<STriangle>& v_particles);
	void update_show();

private:
	//std::vector<STriangle> particles_;
	void draw_point( QPainter *painter , QPainterPath &path);
	void draw_pos( QPainter *painter , QPainterPath &path);
	void draw_lab( QPainter *painter , QPainterPath &path);

	QPainterPath path_;

public:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	QRectF m_bound_rect;

	void get_triangle( QVector<QPointF> &vqp , const SPos &pos);
	void get_square( QVector<QPointF> &vqp , const SPos &pos);
	void get_square( QVector<QPointF> &vqp , const SVec &point);


	boost::mutex mu_view_data_;

	void new_point( std::string str_name, const F32 &px, const F32 &py, const int &st ,std::string str_lab ="" );
	void new_pos( std::string str_name, const F32 &px, const F32 &py, const F32 &pth, const int &st ,std::string str_lab ="" );

	typedef struct _SView_Point
	{

		std::string str_name_;
		SVec point_;

		int shape_type_;

		SVec lab_pos_;
		std::string str_lab_;

	}SView_Point;

	typedef struct _SView_Pos
	{

		std::string str_name_;
		SPos pos_;

		int shape_type_;

		SVec lab_pos_;
		std::string str_lab_;

	}SView_Pos;

	std::multimap<std::string,SView_Point> m_point_;
	std::multimap<std::string,SView_Pos> m_pos_;

	float xmin_;
	float ymin_;
	float xmax_;
	float ymax_;

	VecPosition triangle_[3];
	VecPosition square_[4];

	float lab_Showsize_;
	int stringWidth_;
	int stringHeight_;


private:
	int id_;
	QList<QGraphicsItem *> edgeList_;
protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif//_NODE_ITEM_KYOSHO_20201224_
