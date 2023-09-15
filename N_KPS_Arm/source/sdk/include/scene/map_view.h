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

	// ƽ���ٶ�
	void setTranslateSpeed(qreal speed);
	qreal translateSpeed() const;

	// ���ŵ�����
	void setZoomDelta(qreal delta);
	qreal zoomDelta() const;

protected:
	// ��/��/��/�Ҽ�����������ƶ�����/�����������š��ո�/�س�����ת
	void keyPressEvent(QKeyEvent *event) ;
	// ƽ��
	void mouseMoveEvent(QMouseEvent *event) ;
	void mousePressEvent(QMouseEvent *event) ;
	void mouseReleaseEvent(QMouseEvent *event); 
	// �Ŵ�/��С
	void wheelEvent(QWheelEvent *event) ;

	public Q_SLOTS:
		void zoomIn();  // �Ŵ�
		void zoomOut();  // ��С
		void zoom(float scaleFactor); // ���� - scaleFactor�����ŵı�������
		void translate(QPointF delta);  // ƽ��

private:
	Qt::MouseButton m_translateButton;  // ƽ�ư�ť
	qreal m_translateSpeed;  // ƽ���ٶ�
	qreal m_zoomDelta;  // ���ŵ�����
	bool m_bMouseTranslate;  // ƽ�Ʊ�ʶ
	QPoint m_lastMousePos;  // �������µ�λ��
	qreal m_scale;  // ����ֵ
};


#endif //_MAP_VIEW_KYOSHO_20180701_
