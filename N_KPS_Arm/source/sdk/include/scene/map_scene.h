#ifndef _MAP_SCENE_KYOSHO_20180701_
#define _MAP_SCENE_KYOSHO_20180701_

#include <map>

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "scene/item_define.h"
#endif
#include <QtGui/QGraphicsScene>
#include <QGraphicsItem>

class QGraphicsLineItem;

#include "scene/mouse_event.h"

class map_scene : public QGraphicsScene
{
	Q_OBJECT
public:

	map_scene(QObject *parent = 0);
	~map_scene();

	
	void add_item(std::string nm, QGraphicsItem* p_item);
	QGraphicsItem* get_item( std::vector<QGraphicsItem*> &v_item , std::string nm );
	void del_item(QGraphicsItem* p_item);
	void del_item(std::string nm);
	void del_all();
	bool sel_item(const std::string &str_type, const std::string &str_id);
	bool update_item(const std::string &str_type,const std::string &str_id);
	bool update_item();

	void bind_lab_event(qt_eve::mouse_event::Slot_Lab event_slot);
	void bind_local_event(qt_eve::mouse_event::Slot_Local event_slot);
	void bind_range_event(qt_eve::mouse_event::Slot_Range event_slot);
	void bind_reflector_event( qt_eve::mouse_event::Slot_Reflector event_slot );
	void bind_node_event( qt_eve::mouse_event::Slot_Node event_slot );
	void bind_edge_event( qt_eve::mouse_event::Slot_Edge event_slot );
	void bind_producer_event(qt_eve::mouse_event::Slot_Producer event_slot);
	void bind_consumer_event(qt_eve::mouse_event::Slot_Consumer event_slot);
    void bind_processer_event( qt_eve::mouse_event::Slot_Processer event_slot );
	void bind_storage_event(qt_eve::mouse_event::Slot_Storage event_slot);
	void bind_charge_event(qt_eve::mouse_event::Slot_Charge event_slot);
	void bind_sel_event(qt_eve::mouse_event::Slot_Sel event_slot);
	void bind_rect_event(qt_eve::mouse_event::Slot_Rect event_slot);
	void bind_qrcod_event(qt_eve::mouse_event::Slot_QrCode event_slot);

	void set_mouse_event( const qt_eve::mouse_event::MU_TYPE& type );

private:

	std::multimap<std::string , QGraphicsItem* >items_list_;

protected:

	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	
private:

	qt_eve::mouse_event m_event_;
	

	//select items
public slots:
	void slot_sel_item(QString str);
private:
	bool split_id_data(std::string &str_type , std::string &str_id, std::string str_sig);
};


#endif //_MAP_SCENE_KYOSHO_20180701_
