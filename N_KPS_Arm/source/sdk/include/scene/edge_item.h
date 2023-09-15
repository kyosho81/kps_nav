#ifndef _PACKAGE_SIMMONITOR_MONI_EDGEBEZIERITEM_11_23_WPM__
#define _PACKAGE_SIMMONITOR_MONI_EDGEBEZIERITEM_11_23_WPM__


#include <QtGui>
#include <QVector>
#include <QMap>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTimer>

#include <iostream>
#include <vector>
#include <map>

#ifndef Q_MOC_RUN
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#endif
#include "scene/QTypeDefine.h"

class map_scene;
class node_item;
class node_control_item;

class edge_item : public QObject , public QGraphicsItem
{

	Q_OBJECT	
public:
	edge_item( node_item* src,node_item* des, QGraphicsItem *parent = 0,QMenu *contextMenu = 0);
	~edge_item();

	enum { Type = QtType::ITEM_EDGE };
	int type() const{ return Type;}

	void set_id(const int &id);
	int get_id();

	void set_scene( map_scene* m_scene );

	node_item *sourceNode() const;
	node_item *destNode() const;

	void remove_Node(node_item* node);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	void adjust();

	void setCtlPos1(const double &x,const double &y);
	void setCtlPos2(const double &x,const double &y);

	void set_forward(DIRECTION dir);
	void set_backward(DIRECTION dir);
	void set_leftshift(DIRECTION dir);
	void set_rightshift(DIRECTION dir);



	void update_show();

public:

	QRectF boundingRect() const;
	QPainterPath shape() const;

	QPainterPath path_;

protected:

	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent (QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);


private:


	void UpdateBoundRect();

	
	
	QRectF m_bound_rect;

	int id_;

	node_item* node_src_;
	node_item* node_des_;
	

	QPointF qp_src_;
	QPointF qp_des_;

	//control point pos
	void update_pro_ctl();
	QPointF ctl_pos_1_;
	QPointF ctl_pos_2_;

	static node_control_item* ctl_node1_;
	static node_control_item* ctl_node2_;

	float f_pan_width_;

	map_scene* map_scene_;

	void create_control_node();
private:

	SSEdge_Ori_Dir ori_dir_;

	F32 speed_forward_;	F32 speed_backward_;
	F32 speed_leftshift_;	F32 speed_rightshift_;

	float ori_width_;
	float ori_height_;

	

	void get_triangle(STriangle &triangle);
	void cal_triangle( STriangle &ori_triangle , F32 px , F32 py , F32 angle_deg , F32 ori );
	void draw_orientation(QPainter *painter);
	void draw_orientation(QPainter *painter,QPointF center, F32 dir_angle,  bool b_forward , bool b_backward, bool b_leftshift, bool b_rightshift);


	bool src_forward();
	bool des_forward();
	bool src_backward();
	bool des_backward();
	bool src_leftshift();
	bool des_leftshift();
	bool src_rightshift();
	bool des_rightshift();

	//void draw_dri(QPainterPath &path,DIRECTION dir);

	QPointF center_;
//	F32 dir_src_dst_;

private slots:

		void ctl_slot(int clt_index,SPos pos);

// 		void removid_signal(int id);
// 		void rightclicked_signal(const QPoint& poss);
		
private:
	boost::mutex paint_mutex_;
};
#endif//_PACKAGE_SIMMONITOR_MONI_EDGEBEZIERITEM_11_23_WPM__
