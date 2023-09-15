
#ifndef _COMBOX_DELEGATE_H_
#define _COMBOX_DELEGATE_H_

#include <QTimer>
#include <QItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif

class combo_delegate : public QItemDelegate
{
	Q_OBJECT
public:
	combo_delegate(QObject *parent = 0);

	void setItems(QMap<int,QString> items);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const  QModelIndex &index) const;

private:
	QMap<int,QString> mapItems;    //下拉框列表项
};


#endif//_COMBOX_DELEGATE_H_