
#include <QProgressBar>
#include <QApplication>
#include <QTimeEdit>

#include "QDebug"

#include "interface_model.h"

#include "time_delegate.h"
/****************************************************
 * TimeDelegate
 ****************************************************/
time_delegate::time_delegate(QObject *parent) :
    QItemDelegate(parent)
{
}
 
QWidget *time_delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QTimeEdit *editor = new QTimeEdit(parent);
    editor->setDisplayFormat("hh:mm:ss");
    editor->setCalendarPopup(true);
    return editor;
}
 
void time_delegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QString str =index.model()->data(index).toString();
 
    QTimeEdit *pTime = static_cast<QTimeEdit*>(editor);
    pTime->setTime(QTime::fromString(str,"hh:mm:ss"));
}
 
void time_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *pTime = static_cast<QTimeEdit*>(editor);
    QString str = pTime->time().toString("hh:mm:ss");
    model->setData(index,str);
}
 
void time_delegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}

