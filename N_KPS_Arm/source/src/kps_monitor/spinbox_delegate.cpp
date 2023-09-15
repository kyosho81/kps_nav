
#include <QProgressBar>
#include <QApplication>
#include <QDoubleSpinBox>

#include "QDebug"

#include "interface_model.h"

#include "spinbox_delegate.h"

 
/****************************************************
 * SpinBoxDelegate
 ****************************************************/
spinbox_delegate::spinbox_delegate(QObject *parent) :
    QItemDelegate(parent)
{
    //初始化最大最小值
    minValue = 1.00;
    maxValue = 100.00;
}
 
void spinbox_delegate::setRange(double min, double max)
{
    minValue = min;
    maxValue = max;
}
 
QWidget *spinbox_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor =  new QDoubleSpinBox(parent);
    editor->setMinimum(minValue);
    editor->setMaximum(maxValue);
    editor->setSingleStep(0.000001);
    editor->setDecimals(6);
    return editor;
}
 
void spinbox_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *spinBox =  static_cast <QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}
 
void spinbox_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox =  static_cast <QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}
 
void spinbox_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
