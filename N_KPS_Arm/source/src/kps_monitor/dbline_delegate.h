
#ifndef _DOUBLE_LINE_DELEGATE_H_
#define _DOUBLE_LINE_DELEGATE_H_

#include <QTimer>
#include <QItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif

/*
 * DoubleLineEdit
 */
class dbline_delegate : public QItemDelegate
{
    Q_OBJECT
public:
    dbline_delegate(QObject *parent = 0);
 
    void setRange(double bottom, double top, int decimals = 0);
 
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const  QModelIndex &index) const;
 
private:
    int min;        //最小值
    int max;        //最大值
    int dec;        //小数位数
};


#endif//_DOUBLE_LINE_DELEGATE_H_