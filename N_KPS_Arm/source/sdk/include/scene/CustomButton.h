#include <QWidget>

#include <QPoint>
#include "qmath.h"

enum QUADRANT_NUM {
    QUADRANT_UP,
    QUADRANT_LEFT,
    QUADRANT_DOWN,
    QUADRANT_RIGHT,
    QUADRANT_NO_DEFINE,
};

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget* parent = NULL);
    // ���û������뾶;
    void setRadiusValue(int radius);
    void setArcLength(int arcLength);
    void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text);

    QPixmap getPixmap(const int ping);
    QColor getColor(const int ping);
    int getLineNum(const int ping);
    QPixmap getSignalPixmap(const QColor &color,const int lineNum);//��ȡ�ź�λͼ

	void setBeginDegree(int degree);



    void setStrUp(QString str){mStrUp = str;}
    void setStrLeft(QString str){mStrLeft = str;}
    void setStrDown(QString str){mStrDown = str;}
    void setStrRight(QString str){mStrRight = str;}

    void setTextModeEn(bool mode){m_bTextModeEn = mode;}


    void setSPLcolor(QColor color){colorSPL = color;update();}
    void setSectorColor(QColor color){mSectorColor = color;update();}
    void setBKGcolor(QColor color){colorBKG = color;update();}
    void setWidgetStyle(QString style);

    void setAxesVertical(bool axesVertical);

private:
     // ��ʼ����ť;
    void initButton();
    // ���ư�ť; 
    void paintEvent(QPaintEvent *);
    // ���Բ��;
    void addArc(int x, int y, int startAngle, int angleLength, QColor color);

    // ����¼�;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    int analysisAngle(int x,int y);

signals:
    // �����;
    void signalButtonClicked(int buttonId);
    // ����ɿ�;
    void signalButtonReleased(int buttonId);
private:
    // �������뾶;
    int m_radius, m_arcLength;

    // Բ��·��;
    QList<QPainterPath> m_arcPathList;
    QList<QPainterPath> m_textPathList;
    // Բ����ɫ;
    QList<QBrush> m_colorList;
    // ��ǰ��갴ť/���� ��ť������;
    int m_pressIndex, m_enterIndex;
    // ����¼���־λ;
    bool m_isMousePressed;
    bool m_isMouseEntered;

    QUADRANT_NUM mCurWorkRegion;

    QPoint mCenterRound;
    QPixmap mDegreePixmap;

    QString mStrUp;
    QString mStrLeft;
    QString mStrDown;
    QString mStrRight;

	bool m_bTextModeEn;

    QColor mSectorColor;


    //beijing�ָ�����ɫ
    QColor colorBKG;
    QColor colorSPL;
    QColor colorSectorUp2;
    QColor colorSectorUp;
    QColor colorSectorDown;

    QColor colorbgGradient0;
    QColor colorbgGradient1;

    QColor colorExcircle0;
    QColor colorExcircle5;
    QColor colorExcircle9;

    QColor colorInnerCircle0;
    QColor colorInnerCircle9;

    bool mAxesVertical;

};










