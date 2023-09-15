
#ifndef _INTERFACE_DELEGATE_H_
#define _INTERFACE_DELEGATE_H_

#include <QTimer>
#include <QStyledItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif


class interface_delegate : public QStyledItemDelegate 
{

public:
	interface_delegate();
	~interface_delegate();

		
protected:

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//create ComboBox
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	//set data do model to update 
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	//get data from model to fill ComboBox
	void setEditorData(QWidget *editor, const QModelIndex &index) const;

};

#endif//_INTERFACE_DELEGATE_H_