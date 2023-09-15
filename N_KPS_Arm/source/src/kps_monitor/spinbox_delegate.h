
#ifndef _SPINBOX_DELEGATE_H_
#define _SPINBOX_DELEGATE_H_

#include <QTimer>
#include <QItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif
/*
 * DoubleSpinBox
 */
class spinbox_delegate : public QItemDelegate
{
    Q_OBJECT
public:
    spinbox_delegate(QObject *parent = 0);
 
    void setRange(double min, double max);
 
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const  QModelIndex &index) const;
 
private:
    double minValue;        //最小值
    double maxValue;        //最大值
};

#endif//_SPINBOX_DELEGATE_H_