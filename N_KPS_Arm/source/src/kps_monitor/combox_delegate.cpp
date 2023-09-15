
#include <QProgressBar>
#include <QApplication>
#include <QComboBox>
#include <QLineEdit>

#include "QDebug"

#include "interface_model.h"

#include "combox_delegate.h"

 
/****************************************************
 * ComboDelegate
 ****************************************************/
combo_delegate::combo_delegate(QObject *parent) :
    QItemDelegate(parent)
{
}
 
void combo_delegate::setItems(QMap<int,QString> items)
{
    mapItems = items;
}
 
QWidget *combo_delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QComboBox *editor = new QComboBox(parent);
	QMap<int,QString>::const_iterator it = mapItems.begin();
	while (it != mapItems.end())
	{
		editor->addItem(it.value(),it.key());
		//editor->addItem(it.value());
		++it;
	}
    editor->installEventFilter(const_cast<combo_delegate*>(this));
    return editor;
}
 
void combo_delegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
	QString data =index.model()->data(index).toString();
 
    QComboBox *box = static_cast<QComboBox*>(editor);
    int i=box->findText(data);
    box->setCurrentIndex(i);
}
 
void combo_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    //QVariant data = box->itemData(box->findText(box->currentText()));
    model->setData(index,box->currentText(), Qt::EditRole);
}
 
void combo_delegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	comboBox->showPopup();//drop down immediately
}
