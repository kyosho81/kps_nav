
#include <QProgressBar>
#include <QApplication>
#include <QComboBox>
#include <QLineEdit>

#include "QDebug"

#include "interface_model.h"

#include "progress_delegate.h"


/****************************************************
* ProgressBarDelegate
****************************************************/

progbar_delegate::progbar_delegate(QObject *parent) :
QStyledItemDelegate(parent)
{
}

void progbar_delegate::setColumn(int col, int min, int max)
{
	column = col;
	maxValue = max;
	minValue = min;
}

// 绘制进度条
void progbar_delegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
	if (index.column() == column) {
		QStyleOptionProgressBar bar;
		bar.rect = option.rect;
		bar.progress = index.data().toInt();
		bar.maximum = maxValue;
		bar.minimum = minValue;
		bar.text = QString("%1%").arg(bar.progress);
		bar.textAlignment = Qt::AlignCenter;
		bar.textVisible = true;

		QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter);
	}
	else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}


