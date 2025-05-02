#ifndef BCWIDGET_H
#define BCWIDGET_H

#include <QWidget>
//无边框窗口移动使用
#include <QPoint>
#include <QMouseEvent>
//绘制窗口使用
#include <QPainter>
//右键菜单使用
#include <QContextMenuEvent>
//系统托盘使用
#include <QSystemTrayIcon>
#include <QDesktopServices>
//标题栏使用
#include <QToolButton>//关闭按钮
#include <QPixmap>//用于图片
#include <QImage>
#include <QRect>
#include <QCursor>

#define TITLE_BAR_HEIGHT 30//用于拖拽窗口
#define PADDING 10//用于缩放窗口
#define CLOSE_BUTTON_STYLE "QToolButton{background-color:transparent;"\
    "color:white; border : none;}"\
    "QToolButton:hover{background-color:red;"\
    "color:white; border : none;}"\
    "QToolButton:pressed{color:black;background-color:rgba(255,69,0,100);}"
#define BUTTON_STYLE "QToolButton{background-color:transparent;"\
    "color:white; border : none;}"\
    "QToolButton:hover{background-color:rgba(100,100,100,80);"\
    "color:white; border : none;}"\
    "QToolButton:pressed{color:white;background-color:rgba(100,100,100,150);}"

enum Direction {
    UP=0, DOWN=1, LEFT,
    RIGHT, LEFTTOP, LEFTBOTTOM,
    RIGHTBOTTOM, RIGHTTOP, NONE
};

class BcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BcWidget(QWidget *parent = nullptr);
    void initWidget();
    void initButton();
    void setTitlePhoto(QString photofile,int scaledw = 20,int scaledh = 20);
    void setTitleText(QString text);
    void setIsCanMax(bool b_isCan);
    void setIsCanMin(bool b_isCan);
    void setWindowFixedSize(int width,int height);
    bool isSizeFixed();
    void downWindowFixedSize();
    QString getTitleText();
    QString getTitlePhotoFile();
    QImage getTitlePhoto();
    void setsize(int width,int height);
    void unMaxOrMax();
    int titleTextXBeginPos = 45;
    int titleImageXBeginPos = 18;
    int titleButtonXEndPos = 15;
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void paintWidget();
    void paintButton();
private:
    //改变鼠标样式
    void region(const QPoint &currentGlobalPoint);

    bool m_isMove; //窗口是否正在移动
    QPoint m_pressPoint;//鼠标按下去的坐标
    bool m_isLeftPressDown;  // 判断左键是否按下
    Direction dir;// 窗口大小改变时，记录改变方向

    QImage title_img;
    QString title_text;
    QString title_photo_file;

    QToolButton* min_button;
    QToolButton* max_button;
    QToolButton* close_button;

    bool b_cansf = 1;
    bool b_canMin = 1;
    bool b_canMax = 1;
    bool b_isMax = 0;
    QRect _location;
signals:

public slots:
};

#endif // BCWIDGET_H
