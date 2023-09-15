#ifndef _MAP_VIEW_KYOSHO_20180701_
#define _MAP_VIEW_KYOSHO_20180701_

#include <QGraphicsView>

class QWheelEvent;
class QKeyEvent;

class map_view : public QGraphicsView{

	Q_OBJECT
public:
	explicit map_view(QWidget *parent = 0);
	~map_view();

	// 平移速度
	void setTranslateSpeed(qreal speed);
	qreal translateSpeed() const;

	// 缩放的增量
	void setZoomDelta(qreal delta);
	qreal zoomDelta() const;

protected:
	// 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
	void keyPressEvent(QKeyEvent *event) ;
	// 平移
	void mouseMoveEvent(QMouseEvent *event) ;
	void mousePressEvent(QMouseEvent *event) ;
	void mouseReleaseEvent(QMouseEvent *event); 
	// 放大/缩小
	void wheelEvent(QWheelEvent *event) ;

	public Q_SLOTS:
		void zoomIn();  // 放大
		void zoomOut();  // 缩小
		void zoom(float scaleFactor); // 缩放 - scaleFactor：缩放的比例因子
		void translate(QPointF delta);  // 平移

private:
	Qt::MouseButton m_translateButton;  // 平移按钮
	qreal m_translateSpeed;  // 平移速度
	qreal m_zoomDelta;  // 缩放的增量
	bool m_bMouseTranslate;  // 平移标识
	QPoint m_lastMousePos;  // 鼠标最后按下的位置
	qreal m_scale;  // 缩放值
};


#endif //_MAP_VIEW_KYOSHO_20180701_
