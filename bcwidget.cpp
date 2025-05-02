#include "bcwidget.h"
#include <QDebug>
#include <QAction>

BcWidget::BcWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

void BcWidget::initWidget()
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体背景全透明
    this->setMinimumSize(300,30);
    setTitleText("bcwidget title");
    setTitlePhoto(":/icon/BcEditor.png");
    this->setsize(400,300);
    initButton();
}
void BcWidget::initButton(){
    min_button = new QToolButton(this);
    max_button = new QToolButton(this);
    close_button = new QToolButton(this);
    min_button->setText("—");
    max_button->setText("□");
    close_button->setText("×");
    min_button->resize(40,30);
    max_button->resize(40,30);
    close_button->resize(40,30);
    close_button->setStyleSheet(CLOSE_BUTTON_STYLE);
    min_button->setStyleSheet(BUTTON_STYLE);
    max_button->setStyleSheet(BUTTON_STYLE);

    connect(close_button,&QToolButton::clicked,this,[=](){
        this->close();
    });
    connect(min_button,&QToolButton::clicked,this,[=](){
        this->showMinimized();
    });
    connect(max_button,&QToolButton::clicked,this,[=](){
        unMaxOrMax();
    });
}

void BcWidget::setWindowFixedSize(int width,int height){
    this->b_cansf = 0;
    this->setFixedSize(width,height);
}
bool BcWidget::isSizeFixed(){
    return !this->b_cansf;
}
void BcWidget::downWindowFixedSize(){
    this->b_cansf = 1;
}

void BcWidget::unMaxOrMax(){
    static QRect location = this->geometry();
    if (b_isMax) {
        this->setGeometry(_location);//恢复窗口原大小和位置
    }else {
        location = this->geometry();	//最大化前记录窗口大小和位置
        _location = location;
        //this->setGeometry(qApp->desktop()->availableGeometry());
        this->showFullScreen();	//设置窗口铺满全屏
    }
    b_isMax = !b_isMax;
}
void BcWidget::setTitlePhoto(QString photofile,int scaledw,int scaledh)
{
    this->setWindowIcon(QIcon(photofile));
    this->title_photo_file = photofile;
    title_img.load(title_photo_file);
    title_img = title_img.scaled(scaledw,scaledh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}
void BcWidget::setTitleText(QString text)
{
    this->title_text = text;
}
QString BcWidget::getTitleText(){
    return this->title_text;
}
QString BcWidget::getTitlePhotoFile(){
    return this->title_photo_file;
}
QImage BcWidget::getTitlePhoto(){
    return this->title_img;
}
void BcWidget::setsize(int width,int height){
    if(b_cansf) this->resize(width,height+TITLE_BAR_HEIGHT);
}

//无边框窗口拖动(可拖动范围为标题栏高度 TITLE_BAR_HEIGHT)
//无边框窗口缩放(可拖动范围为PADDING)
void BcWidget::region(const QPoint &currentGlobalPoint)
{
    if(!b_cansf)return;
    // 获取窗体在屏幕上的位置区域，topLeft为坐上角点，rightButton为右下角点
    QRect rect = this->rect();

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //将左上角的(0,0)转化为全局坐标
    QPoint rightButton = this->mapToGlobal(rect.bottomRight());

    int x = currentGlobalPoint.x(); //当前鼠标的坐标
    int y = currentGlobalPoint.y();

    if(((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
            && ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
    {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置光标形状
    }else if(((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
             && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
             && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if(((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
             && ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
    {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
    {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
    {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
    {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else if((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
    {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else
    {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}
void BcWidget::mousePressEvent(QMouseEvent*e)
{
    m_pressPoint = e->pos();
    switch(e->button())
    {
    case Qt::LeftButton:
        //拖动
        if (PADDING < m_pressPoint.y()&&m_pressPoint.y() < TITLE_BAR_HEIGHT)
        {
            m_isMove = true;
            if(b_isMax){
                this->setGeometry(_location);
                this->move(e->globalX()-(this->width()/2),e->globalY());
                b_isMax = 0;
            }
        }
        else
        {
            this->region(e->globalPos()); //窗口大小的改变——判断鼠标位置，改变光标形状
            m_isMove = false;
        }
        //缩放
        m_isLeftPressDown = true;
        if(dir != NONE)
        {
            this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
        }
        else
        {
            m_pressPoint = e->globalPos() - this->frameGeometry().topLeft();
            //globalPos()鼠标位置，topLeft()窗口左上角的位置
        }
        break;
    case Qt::RightButton:
        //this->setWindowState(Qt::WindowMinimized);
        break;
    default:
        QWidget::mousePressEvent(e);
    }
}
void BcWidget::mouseMoveEvent(QMouseEvent*e)
{
    if ((e->buttons() == Qt::LeftButton) && m_isMove)
    {
        QPoint parent_point = this->pos();
        parent_point.setX(parent_point.x() + e->x() - m_pressPoint.x());
        parent_point.setY(parent_point.y() + e->y() - m_pressPoint.y());
        this->move(parent_point);
    }else{

        QPoint globalPoint = e->globalPos();   //鼠标全局坐标

        QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
        QPoint topLeft = mapToGlobal(rect.topLeft());
        QPoint bottomRight = mapToGlobal(rect.bottomRight());

        if (this->windowState() != Qt::WindowMaximized)
        {

            if(dir != NONE)
            {
                QRect newRect(topLeft, bottomRight); //定义一个矩形

                switch(dir)
                {
                case LEFT:

                    if(bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                    {
                        newRect.setLeft(topLeft.x());  //小于界面的最小宽度时，设置为左上角横坐标为窗口x
                        //只改变左边界
                    }
                    else
                    {
                        newRect.setLeft(globalPoint.x());
                    }
                    break;
                case RIGHT:
                    newRect.setWidth(globalPoint.x() - topLeft.x());  //只能改变右边界
                    break;
                case UP:
                    if(bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                    {
                        newRect.setY(topLeft.y());
                    }
                    else
                    {
                        newRect.setY(globalPoint.y());
                    }
                    break;
                case DOWN:
                    newRect.setHeight(globalPoint.y() - topLeft.y());
                    break;
                case LEFTTOP:
                    if(bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                    {
                        newRect.setX(topLeft.x());
                    }
                    else
                    {
                        newRect.setX(globalPoint.x());
                    }

                    if(bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                    {
                        newRect.setY(topLeft.y());
                    }
                    else
                    {
                        newRect.setY(globalPoint.y());
                    }
                    break;
                case RIGHTTOP:
                    if (globalPoint.x() - topLeft.x() >= this->minimumWidth())
                    {
                        newRect.setWidth(globalPoint.x() - topLeft.x());
                    }
                    else
                    {
                        newRect.setWidth(bottomRight.x() - topLeft.x());
                    }
                    if (bottomRight.y() - globalPoint.y() >= this->minimumHeight())
                    {
                        newRect.setY(globalPoint.y());
                    }
                    else
                    {
                        newRect.setY(topLeft.y());
                    }
                    break;
                case LEFTBOTTOM:
                    if (bottomRight.x() - globalPoint.x() >= this->minimumWidth())
                    {
                        newRect.setX(globalPoint.x());
                    }
                    else
                    {
                        newRect.setX(topLeft.x());
                    }
                    if (globalPoint.y() - topLeft.y() >= this->minimumHeight())
                    {
                        newRect.setHeight(globalPoint.y() - topLeft.y());
                    }
                    else
                    {
                        newRect.setHeight(bottomRight.y() - topLeft.y());
                    }
                    break;
                case RIGHTBOTTOM:
                    newRect.setWidth(globalPoint.x() - topLeft.x());
                    newRect.setHeight(globalPoint.y() - topLeft.y());
                    break;
                default:
                    break;
                }
                this->setGeometry(newRect);
            }
            else
            {
                //move(e->globalPos() - m_pressPoint); //移动窗口
                e->accept();
            }
        }
    }
}
void BcWidget::mouseReleaseEvent(QMouseEvent*e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_isLeftPressDown = false;
        if (dir != NONE)
        {
            this->releaseMouse(); //释放鼠标抓取
            this->setCursor(QCursor(Qt::ArrowCursor));
            dir = NONE; //热心网友指正
        }
    }
    if (m_isMove)
    {
        m_isMove = false;
    }

}
//绘制窗口
void BcWidget::paintEvent(QPaintEvent* e){
    paintWidget();
    paintButton();
}
void BcWidget::paintWidget()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    painter.setClipping(true);
    QPainterPath canDrawingPathArea; // 能画上的区域
    canDrawingPathArea.addRoundedRect(rect(), 20, 20);
    canDrawingPathArea.setFillRule(Qt::WindingFill); // 多块区域组合填充模式

    painter.setClipPath(canDrawingPathArea);

    QColor color("#212529");
    color.setAlpha(220);
    painter.setBrush(color);
    painter.drawRect(rect());

    QColor color2("#dee2e6");
    color2.setAlpha(10);
    painter.setPen(color2);
    painter.setBrush(color2);
    painter.drawRect(0,TITLE_BAR_HEIGHT,width()+1,height()+1);

    QColor color3("#dee2e6");
    color3.setAlpha(20);
    painter.setPen(color3);
    painter.setBrush(color3);
    painter.drawRect(0,0,width()+1,TITLE_BAR_HEIGHT);

    color2.setAlpha(255);
    painter.setPen(color2);
    painter.setBrush(Qt::NoBrush);
    QFont f;
    f.setPixelSize(13);
    //f.setBold(true);//设置文字为粗体
    painter.setFont(f);
    painter.drawText(titleTextXBeginPos,20,title_text);
    painter.drawImage(titleImageXBeginPos,5,title_img);
}
void BcWidget::paintButton()
{
    int x_close = this->width()-close_button->width();
    close_button->move(x_close-titleButtonXEndPos,0);
    if(b_canMin && b_canMax){
        min_button->show();
        max_button->show();
        max_button->move(x_close-titleButtonXEndPos-max_button->width(),0);
        min_button->move(x_close-titleButtonXEndPos-max_button->width()-min_button->width(),0);
    }else if(b_canMin){
        max_button->hide();
        min_button->show();
        min_button->move(x_close-titleButtonXEndPos-min_button->width(),0);
    }else{
        min_button->hide();
        max_button->show();
        max_button->move(x_close-titleButtonXEndPos-max_button->width(),0);
    }
}

void BcWidget::setIsCanMax(bool b_isCan){
    b_canMax = b_isCan;
}
void BcWidget::setIsCanMin(bool b_isCan){
    b_canMin = b_isCan;
}
