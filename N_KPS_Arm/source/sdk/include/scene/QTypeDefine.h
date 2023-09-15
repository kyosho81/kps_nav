#ifndef _KYOSHO_20191204_QT_TYPE_DEFINE_
#define _KYOSHO_20191204_QT_TYPE_DEFINE_

#include <QVariant>
#include <QPoint>
#include <QColor>


class QtType : public QVariant
{
public:

	typedef enum{ITEM_NONE = UserType ,ITEM_REFLECTOR = UserType + 1,ITEM_LAB = UserType + 2,ITEM_NODE = UserType + 3,ITEM_EDGE = UserType + 4,ITEM_CTRL = UserType + 5,ITEM_NODE_CTRL = UserType + 6,ITEM_RANGE = UserType + 7
				,ITEM_PRODUCER = UserType + 8,ITEM_CONSUMER = UserType + 9,ITEM_PROCESSER = UserType + 10,ITEM_STORAGE = UserType + 11,ITEM_CHARGE = UserType + 12,ITEM_MAP = UserType + 13,ITEM_RECT = UserType + 14,ITEM_QRCODE = UserType + 15} ITEM_TYPE;
	typedef enum{ITEM_BACK_ZV = 0,
				 ITEM_PARTICLE_ZV = 19,
				 ITEM_VIEW_DATA_ZV = 20,
				 ITEM_NODE_ZV = 9,
				 ITEM_EDGE_ZV = 8,
				 ITEM_CTRL_ZV = 7,
				 ITEM_ROLE = 6
	} ITEM_ZVALUE;	
};

#endif//_KYOSHO_20191204_QT_TYPE_DEFINE_