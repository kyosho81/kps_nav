#ifndef _RANGE_ITEM_KYOSHO_20180715_
#define _RANGE_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif
#include <QGraphicsItem>

#include "scene/QTypeDefine.h"
#include "robot/RobotStruct.h"


class map_scene;
class control_item;

class range_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:

	range_item(QGraphicsItem *parent = 0);
	~range_item();

	enum { Type = QtType::ITEM_RANGE };
	int type() const{ return Type;}

	void set_scene(map_scene* m_scene);
	void set_name(const std::string str_nm);
	std::string get_name();

	void add_point(const SPos &pos);
	void add_point(const std::vector<Sxy> &v_list);
	int point_size();
	void update_ctl_pos(int ctl_index, SPos pos){};

	int get_range_pos(std::vector<Sxy> &v_pos);
	int get_bound_rect(std::vector<Sxy> &v_pos);

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	
private:

	void set_pos(const SPos &pos);

	QPainterPath painter_range_path_;

	QRectF bounding_rect_;

	map_scene* map_scene_;
	std::string str_nm_;

	float f_pan_width_;
private://
	boost::mutex paint_mutex_;
	

private:
	QPolygonF polygon_point_;

	void create_ctl_item(const SPos &pos);
	void show_ctl_item(const bool &b_show);

	std::vector<control_item*> v_ctl_node_;

public slots:
	void ctl_slot(int clt_index,SPos pos);

};

#endif//_RANGE_ITEM_KYOSHO_20180715_