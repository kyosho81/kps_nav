#ifndef _KPS_MOUSE_EVENT_H
#define _KPS_MOUSE_EVENT_H


#ifndef Q_MOC_RUN 
#include <boost/signals2.hpp>
#include "robot/RobotStruct.h"
#endif

// #include <QMainWindow>
class QGraphicsSceneMouseEvent;
// 

class map_scene;

namespace qt_eve{
 //: public QObject{
class mouse_event
{
	//Q_OBJECT

public:

	mouse_event();
	~mouse_event();
	//
	typedef enum{MU_NONE,MU_SEL,MU_LOCATE,MU_AUTO_LOC,MU_RECT,MU_RANGE,MU_START_POS,MU_ADD_REFECTOR,MU_ADD_NODE,MU_ADD_EDGE,MU_RAND_EDGE,MU_ADD_PRODUCER,MU_ADD_CONSUMER,MU_ADD_PROCESSER,MU_ADD_STORAGE,MU_ADD_CHARGE,MU_ADD_QRCOD} MU_TYPE;

public:
	//show status bar
	
	typedef boost::signals2::signal< void (std::string) > Signel_Lab;
	typedef Signel_Lab::slot_type Slot_Lab;
	void bind_lab_event(Slot_Lab event_slot)
	{
		m_sigLab_.connect(event_slot);
	};

public:
	//set robot pos
	typedef struct _SLocal_ev 
	{
		enum Local_st{
			LO_SHOW,
			LO_SET
		};
		Local_st show_set_;
		SPos target_pos_;
	}SLocal_ev;

	typedef boost::signals2::signal< void (SLocal_ev) > Signel_Local;
	typedef Signel_Local::slot_type Slot_Local;
	void bind_local_event(Slot_Local event_slot)
	{
		m_sig_Local_.connect(event_slot);
	};


public:
	//set range pos
	typedef struct _SRange_ev 
	{
		enum Range_st{
			RA_NONE,
			RA_NEW,
			RA_ROT,
			RA_ZOOM,
			RA_MOVE
		};
		Range_st show_set_;
		SPos target_; 
		//RA_NEW  pos x y th
		//RA_ROT  only th 
		//RA_ZOOM x zoom x axle percent y axle percent
	}SRange_ev;

	typedef boost::signals2::signal< void (SRange_ev) > Signel_Range;
	typedef Signel_Range::slot_type Slot_Range;
	void bind_range_event(Slot_Range event_slot)
	{
		m_sig_range_.connect(event_slot);
	};

public:
	//set reflector pos
	typedef struct _SReflector_ev 
	{
		enum Ref_st{
			RE_MENUAL_ADD
		};
		Ref_st ref_set_;
		SPos target_; 

	}SReflector_ev;
	typedef boost::signals2::signal< void (SReflector_ev) > Signel_Reflector;
	typedef Signel_Reflector::slot_type Slot_Reflector;
	void bind_reflector_event(Slot_Reflector event_slot)
	{
		m_sig_reflector_.connect(event_slot);
	};

public:
	//set node pos
	typedef struct _SNode_ev 
	{
		enum Node_st{
			RE_MENUAL_ADD
		};
		Node_st node_set_;
		SPos target_; 

	}SNode_ev;
	typedef boost::signals2::signal< void (SNode_ev) > Signel_Node;
	typedef Signel_Node::slot_type Slot_Node;
	void bind_node_event(Slot_Node event_slot)
	{
		m_sig_node_.connect(event_slot);
	};


public:
	typedef struct _SEdge_ev 
	{
		enum Edge_st{
			LO_INIT,
			LO_SET,
			LO_LINK
		};
		Edge_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SEdge_ev;


	typedef boost::signals2::signal< void (SEdge_ev) > Signel_Edge;
	typedef Signel_Edge::slot_type Slot_Edge;
	void bind_edge_event(Slot_Edge event_slot)
	{
		m_sig_edge_.connect(event_slot);
	};

public:
	typedef struct _SProcuder_ev 
	{
		enum Procuder_st{
			PRODUCER_ADD
		};
		Procuder_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SProcuder_ev;


	typedef boost::signals2::signal< void (SProcuder_ev) > Signel_Producer;
	typedef Signel_Producer::slot_type Slot_Producer;
	void bind_producer_event(Slot_Producer event_slot)
	{
		m_sig_producer_.connect(event_slot);
	};

public:
	typedef struct _SConsumer_ev 
	{
		enum Consumer_st{
			CONSUMER_ADD
		};
		Consumer_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SConsumer_ev;


	typedef boost::signals2::signal< void (SConsumer_ev) > Signel_Consumer;
	typedef Signel_Consumer::slot_type Slot_Consumer;
	void bind_consumer_event(Slot_Consumer event_slot)
	{
		m_sig_consumer_.connect(event_slot);
	};

	typedef struct _SProcesser_ev 
	{
		enum Processer_st{
			PROCESSER_ADD
		};
		Processer_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SProcesser_ev;


	typedef boost::signals2::signal< void (SProcesser_ev) > Signel_Processer;
	typedef Signel_Processer::slot_type Slot_Processer;
	void bind_processer_event(Slot_Processer event_slot)
	{
		m_sig_processer_.connect(event_slot);
	};

	typedef struct _SStorage_ev 
	{
		enum Storage_st{
			STORAGE_ADD
		};
		Storage_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SStorage_ev;


	typedef boost::signals2::signal< void (SStorage_ev) > Signel_Storage;
	typedef Signel_Storage::slot_type Slot_Storage;
	void bind_storage_event(Slot_Storage event_slot)
	{
		m_sig_storage_.connect(event_slot);
	};

	typedef struct _SCharge_ev 
	{
		enum Charge_st{
			CHARGE_ADD
		};
		Charge_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SCharge_ev;


	typedef boost::signals2::signal< void (SCharge_ev) > Signel_Charge;
	typedef Signel_Charge::slot_type Slot_Charge;
	void bind_charge_event(Slot_Charge event_slot)
	{
		m_sig_charge_.connect(event_slot);
	};
	//////////
	typedef struct _SQrCode_ev 
	{
		enum QrCode_st{
			QRCODE_BEGIN,
			QRCODE_END
		};
		QrCode_st link_set_;
		SPos start_pos_;
		SPos current_pos_;
	}SQrCode_ev;


	typedef boost::signals2::signal< void (SQrCode_ev) > Signel_QrCode;
	typedef Signel_QrCode::slot_type Slot_QrCode;
	void bind_qrcode_event(Slot_QrCode event_slot)
	{
		m_sig_qrcode_.connect(event_slot);
	};
	//////////////////////
	typedef struct _SSel_ev 
	{
		enum Sel_st{
			SEL_MOVE,
			SEL_END
		};
		Sel_st sel_;
		SPos start_pos_;
		SPos current_pos_;
	}SSel_ev;

	typedef boost::signals2::signal< void (SSel_ev) > Signel_Sel;
	typedef Signel_Sel::slot_type Slot_Sel;
	void bind_sel_event(Slot_Sel event_slot)
	{
		m_sig_sel_.connect(event_slot);
	};

	typedef struct _SRect_ev 
	{
		enum Rect_st{
			RECT_ADD
		};
		Rect_st rect_set_;
		SPos current_pos_;
	}SSRect_ev ;


	typedef boost::signals2::signal< void (SSRect_ev) > Signel_Rect;
	typedef Signel_Rect::slot_type Slot_Rect;
	void bind_rect_event(Slot_Rect event_slot)
	{
		m_sig_rect_.connect(event_slot);
	};

public:
	void set_mouse_event(const MU_TYPE& type);


	void mousePressEvent( QGraphicsSceneMouseEvent *mouseEvent );
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );

	SRange_ev range_sig_;

private:

	map_scene* map_scene_;

	MU_TYPE mu_type_;

private:

	
	Signel_Lab m_sigLab_;
	Signel_Local m_sig_Local_;
	Signel_Range m_sig_range_;
	Signel_Reflector m_sig_reflector_;
	Signel_Node m_sig_node_;
	Signel_Edge m_sig_edge_;
	Signel_Producer m_sig_producer_;
	Signel_Consumer m_sig_consumer_;
	Signel_Processer m_sig_processer_;
	Signel_Storage m_sig_storage_;
	Signel_Charge m_sig_charge_;
	Signel_QrCode m_sig_qrcode_;
	Signel_Sel m_sig_sel_;
	Signel_Rect m_sig_rect_;
	//Signel_Edge m_sig_edge_;
//locate event
private:
	F64 start_locate_x_;
	F64 start_locate_y_;
	bool b_start_locate_;

	bool b_edge_;
	F64 start_edge_x_;
	F64 start_edge_y_;

	F64 start_sel_x_;
	F64 start_sel_y_;
	bool b_start_sel_;

	SPos get_estimate_pos(const F64 &start_locate_x,const F64 &start_locate_y,const F64 &end_locate_x,const F64 &end_locate_y);
};

}

#endif // _KPS_MOUSE_EVENT_H
