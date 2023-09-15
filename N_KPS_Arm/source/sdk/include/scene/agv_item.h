#ifndef _AGV_ITEM_KYOSHO_20180715_
#define _AGV_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

#include <QGraphicsItem>

#include "robot/RobotStruct.h"

class agv_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	agv_item(QGraphicsItem *parent = 0);
	~agv_item();

	int i_id_;

	void set_robot_shape(const std::vector<SVec> v_robot_shape);
	void set_amcl_pos(SPos amcl_pos);

	void set_amcl_pos_ref(SPos amcl_pos);
	void set_ref_pos(SPos ref_pos);

	void set_speed(const double &vx,const double &vy,const double &vw);

	void set_run_path(std::list<SOdomSpeed> &l_path);

protected:
private:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void draw_id(QPainter *painter);
	int id_showsize_;
	int string_width_;
	int string_height_;
private:
	

	void set_pos(const SPos &pos);

	boost::mutex paint_mutex_;

	QPainterPath painter_robot_shape_path_;
	QPainterPath painter_speed_;

	QRectF bounding_rect_;



		



private://show amcl ref pos
	void draw_triangle(QPainter *painter , SPos pos);
	bool get_amcl_in_ref( SPos &loc_diff );

	CSBuffer<SPos,1> buf_amcl_pos_;
	CSBuffer<SPos,1> buf_ref_pos_;

	std::list<SOdomSpeed> l_path_;
};

#endif//_AGV_ITEM_KYOSHO_20180715_