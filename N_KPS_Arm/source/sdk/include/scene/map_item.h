#ifndef _MAP_ITEM_KYOSHO_20180715_
#define _MAP_ITEM_KYOSHO_20180715_

#include <QGraphicsItem>
#include "scene/QTypeDefine.h"

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#endif

class GridMap;

class map_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	map_item(QGraphicsItem *parent = 0);
	~map_item();

	enum { Type = QtType::ITEM_MAP };
	int type() const{ return Type;}

	void set_map(GridMap* map);
	void get_map(GridMap* map);
	GridMap* get_map();

	void set_map_value(const std::vector<int> &v_data);
	void set_map_value(const std::vector<Sxy> &v_data);
	void save_map(std::string str_map_path);
	bool open_map(std::string str_map_path);
	void download_map(std::vector<int> &v_data);

protected:
private:
	int value2pgm(int val);

	//double anchor_x_;
	//double anchor_y_;
	//double width_;
	//double height_;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	GridMap* mem_show_map_;

	void show_map_image();

	QImage* get_qimage(int i_width, int i_height);
	QImage* p_qimage_;
	uchar* img_data_;

};

#endif//_MAP_ITEM_KYOSHO_20180715_