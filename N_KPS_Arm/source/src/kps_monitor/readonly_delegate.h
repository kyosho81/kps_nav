
#ifndef _READ_ONLY_DELEGATE_H_
#define _READ_ONLY_DELEGATE_H_

#include <QTimer>
#include <QItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif


/*
 * ReadOnly
 */
class readonly_delegate : public QItemDelegate
{
    Q_OBJECT
public:

    readonly_delegate(QObject *parent = 0): QItemDelegate(parent) {}
 
    void setItems(QStringList items);
 
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const
    {
        return NULL;
    }
};


#endif//_READ_ONLY_DELEGATE_H_