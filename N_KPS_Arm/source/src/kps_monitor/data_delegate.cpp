
#include <QProgressBar>
#include <QApplication>
#include <QComboBox>
#include <QDateEdit>

#include "QDebug"

#include "interface_model.h"

#include "data_delegate.h"

 
/****************************************************
 * DateDelegate
 ****************************************************/

date_delegate::date_delegate(QObject *parent) :
    QItemDelegate(parent)
{
}
 
QWidget *date_delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QDateEdit *editor = new QDateEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    return editor;
}
 
void date_delegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QString str =index.model()->data(index).toString();
 
    QDateEdit *pDate = static_cast<QDateEdit*>(editor);
    pDate->setDate(QDate::fromString(str,"yyyy-MM-dd"));
}
 
void date_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateEdit *pDate = static_cast<QDateEdit*>(editor);
    QString str = pDate->date().toString("yyyy-MM-dd");
    model->setData(index,str);
}
 
void date_delegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}
