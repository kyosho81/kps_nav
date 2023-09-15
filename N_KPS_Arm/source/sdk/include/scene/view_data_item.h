#ifndef _VIEW_DATA_ITEM_KYOSHO_20201224_
#define _VIEW_DATA_ITEM_KYOSHO_20201224_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#endif

#include <QPointF>
#include <QtGui>
#include <QGraphicsItem>
#include <iostream>

#include <string>
#include "robot/RobotStruct.h"
#include "Geometry.h"

class view_data_item :public QObject , public QGraphicsItem
{
	Q_OBJECT
	//Q_INTERFACES(QObject QGraphicsItem)

public:

	view_data_item(QGraphicsItem *parent = 0);
	~view_data_item();
	
	void update_view_data(std::vector<SView_Data> &v_data);
	//void update_particles(const std::vector<STriangle>& v_particles);

private:
	//std::vector<STriangle> particles_;
	void draw_point( QPainter *painter  );
	void draw_pos( QPainter *painter );
	void draw_lab( QPainter *painter );

public:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	QRectF m_bound_rect;

	void get_triangle( QPointF* p , const SPos &pos);
	void get_square( QPointF* p , const SPos &pos);
	void get_square( QPointF* p , const SVec &point);


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


};

#endif//_VIEW_DATA_ITEM_KYOSHO_20201224_
