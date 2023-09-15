
#include <QProgressBar>
#include <QApplication>
#include <QComboBox>
#include <QLineEdit>

#include "QDebug"

#include "interface_model.h"

#include "interface_delegate.h"

interface_delegate::interface_delegate()
{
	
}

interface_delegate::~interface_delegate()
{

}

void interface_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem viewOption(option);
	initStyleOption(&viewOption, index);
	if (option.state.testFlag(QStyle::State_HasFocus))
		viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

	QStyledItemDelegate::paint(painter, viewOption, index);

	//if (index.column() == 2)
	//{
	//	int nProgress = index.model()->data(index, Qt::UserRole).toInt();
	//	int nLeft = 8;
	//	int nTop = 8;
	//	int nWidth = option.rect.width() - 2 * nLeft;
	//	int nHeight = option.rect.height() - 2 * nTop;

	//	// 设置进度条的风格
	//	QStyleOptionProgressBar progressBarOption;
	//	progressBarOption.initFrom(option.widget);
	//	// 设置进度条显示的区域
	//	progressBarOption.rect = QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight);
	//	// 设置最小值
	//	progressBarOption.minimum = 0;
	//	// 设置最大值
	//	progressBarOption.maximum = 100;
	//	// 设置对齐方式
	//	progressBarOption.textAlignment = Qt::AlignCenter;
	//	// 设置进度
	//	progressBarOption.progress = nProgress;
	//	// 设置文本（百分比）
	//	progressBarOption.text = QString("%1%").arg(nProgress);
	//	// 设置文本可见
	//	progressBarOption.textVisible = true;

	//	QProgressBar progressBar;

	//	//绘制进度条
	//	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, &progressBar);
	//}
	//else if(index.column()==3)
	//{
	//}
}

//create ComboBox
QWidget* interface_delegate::createEditor(
	QWidget *parent, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if((index.column() == COL_FROM_ROLE) || (index.column() == COL_TO_ROLE) )
	{
		QComboBox *comboBox = new QComboBox(parent);
		comboBox->setFixedHeight(option.rect.height());
		QStringList qsl = index.model()->data(index,Qt::UserRole).toStringList();
		comboBox->addItems(qsl); //fill item data from data model
		return comboBox;
	}
	else
	{   
		index.model()->data(index,Qt::DisplayRole).toString();
		return QStyledItemDelegate::createEditor(parent, option, index);
	}

}
//get data from model to fill ComboBox
void interface_delegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	if((index.column() == COL_FROM_ROLE) || (index.column() == COL_TO_ROLE) )
	{
		QString text = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *comboBox =  static_cast <QComboBox*>(editor);
		int cur_index = comboBox->findText(text);
		comboBox->setCurrentIndex(cur_index);
	}
	else
	{
		QString text = index.model()->data(index, Qt::EditRole).toString();
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);  
		lineEdit->setText(text);  

		//QStyledItemDelegate::setEditorData(editor, index);
	}
}

//set data do model to update 
void interface_delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{

	if((index.column() == COL_FROM_ROLE) || (index.column() == COL_TO_ROLE) )
	{
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		if(comboBox!=0){
			model->setData(index, comboBox->currentText(), Qt::EditRole);
			//can emit signame
		}
	}
	else
	{
		//model->setData(index, comboBox->currentText(), Qt::EditRole);
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}


void interface_delegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if((index.column() == COL_FROM_ROLE) || (index.column() == COL_TO_ROLE) )
	{
		editor->setGeometry(option.rect);
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		comboBox->showPopup();//drop down immediately
	}else
	{
		QStyledItemDelegate::updateEditorGeometry(editor, option, index);
	}
}

