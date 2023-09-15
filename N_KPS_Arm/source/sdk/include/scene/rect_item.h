#ifndef _RECT_ITEM_KYOSHO_20180715_
#define _RECT_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "scene/QTypeDefine.h"
#include "robot/RobotStruct.h"

class protobuf_rect;
class map_scene;


class rect_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:

	rect_item(QGraphicsItem *parent = 0);
	~rect_item();

	boost::function<void( std::string str_role_type , std::vector< std::vector<Sxy>> v_xy)> fnc_create_multi_roles_;

	enum { Type = QtType::ITEM_RECT };
	int type() const{ return Type;}

	void set_scene(map_scene* m_scene);
	void set_name(const std::string str_nm);
	std::string get_name();

	void set_pos(const SPos &pos);
	void update_show();

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mouseReleaseEvent( QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	
private:

	

	QPainterPath painter_rect_path_;

	QRectF bounding_rect_;

	map_scene* map_scene_;

	float f_pan_width_;
private://
	boost::mutex paint_mutex_;
	

private:
	std::string str_nm_;
	protobuf_rect* p_rect_;

public slots:
	
};

#endif//_RECT_ITEM_KYOSHO_20180715_