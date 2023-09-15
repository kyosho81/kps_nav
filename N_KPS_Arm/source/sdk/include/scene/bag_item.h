#ifndef _BAG_ITEM_KYOSHO_20180715_
#define _BAG_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

#include <QGraphicsItem>

#include "robot/RobotStruct.h"

class bag_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	bag_item(QGraphicsItem *parent = 0);
	~bag_item();


	void set_robot_shape(const std::vector<SVec> v_robot_shape);
	void set_amcl_pos(const SPos &amcl_pos);
	void set_odom_pos(const SPos &odom_pos);
	void set_speed(const double &vx,const double &vy,const double &vw);
	void set_laser( const SLaser &laser, F32 confidence  = 1);
	void set_laser_ex ( const SLaser_Ex &laser_ex);
	void set_laser_ref ( const SReflector &laser_ref);
	void set_laser_para( const SLaser_para &laser_para);

protected:
private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	
private:

	void set_pos(const SPos &pos);
	
	QPainterPath painter_robot_shape_path_;
	QPainterPath painter_speed_;
	

	QRectF bounding_rect_;

private://laser data
	boost::mutex paint_mutex_;
	QPainterPath painter_laser_;
	QPainterPath painter_laser_ref_;
	//laser para
	SLaser_para laser_para_;
	
private://laser angle sin cos
	void init_laser_angle();
	std::vector<F32> v_cos_;
	std::vector<F32> v_sin_;

private://laser reflector
	QPointF center_;
	F32 rx_;
	F32 ry_;
	
	bool b_fixed_amcl_frame_;
};

#endif//_BAG_ITEM_KYOSHO_20180715_