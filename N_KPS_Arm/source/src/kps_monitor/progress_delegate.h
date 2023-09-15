
#ifndef _PROGRESS_DELEGATE_H_
#define _PROGRESS_DELEGATE_H_

#include <QTimer>
#include <QStyledItemDelegate>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "project/task_base.h"
#endif

/*
* QProgressBar
*/
class progbar_delegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	progbar_delegate(QObject *parent = 0);

	void setColumn(int col, int min, int max);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const
	{
		return NULL;
	}

protected:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
	int column;
	int maxValue;			// 设置最大值
	int minValue;			// 设置最小值
};


#endif//_PROGRESS_DELEGATE_H_