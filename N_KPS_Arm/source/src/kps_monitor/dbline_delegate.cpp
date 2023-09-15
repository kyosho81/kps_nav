
#include <QProgressBar>
#include <QApplication>
#include <QComboBox>
#include <QLineEdit>

#include "QDebug"

#include "interface_model.h"

#include "dbline_delegate.h"

/****************************************************
 * DoubleLineEditDelegate
 ****************************************************/
dbline_delegate::dbline_delegate(QObject *parent) :
    QItemDelegate(parent)
{
    min = 0;
    max = 99;
}
 
void dbline_delegate::setRange(double bottom, double top, int decimals)
{
    min = bottom;
    max = top;
    dec = decimals;
}
 
QWidget *dbline_delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator(new QDoubleValidator(min, max, dec,editor));
    return editor;
}
 
void dbline_delegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QString str =index.model()->data(index).toString();
 
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(str);
}
 
void dbline_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString str = lineEdit->text();
    model->setData(index,str);
}
 
void dbline_delegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);

}
