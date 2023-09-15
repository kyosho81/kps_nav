
#ifndef _TIME_DELEGATE_H_
#define _TIME_DELEGATE_H_

#include <QTimer>
#include <QItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif

/*
 * TimeEdit
 */
class time_delegate : public QItemDelegate
{
    Q_OBJECT
public:
    time_delegate(QObject *parent = 0);
 
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const  QModelIndex &index) const;
};

#endif//_TIME_DELEGATE_H_