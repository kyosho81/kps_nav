
#ifndef _CHECKBOX_DELEGATE_H_
#define _CHECKBOX_DELEGATE_H_

#include <QTimer>
#include <QStyledItemDelegate>

/*
 * CheckBox
 */

class checkbox_delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    checkbox_delegate(QObject *parent = 0);
 
    void setColumn(int col);
 
protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);
 
private:
    int column;         //设置复选框的列
};

#endif//_CHECKBOX_DELEGATE_H_