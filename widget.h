#ifndef WIDGET_H
#define WIDGET_H

#include "bcwidget.h"
#include "bctoolbutton.h"
#include "bceditor.h"
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QProcess>
#include <QApplication>
#include <QFileDialog>
#include <QShortcut> //kuai jiejian
#include <QLabel>
#include <QFont>
#include <QFrame>
#include <QCloseEvent>

QString getLastName(QString path);
class Widget : public BcWidget
{
    Q_OBJECT

public:
    Widget(QString iniPath_ = "./info.ini",QWidget *parent = 0);
    ~Widget();
    void load(QString str);
    void paintEvent(QPaintEvent*);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void closeEvent(QCloseEvent * event);//关闭窗口会先处理该事件函数
    void initHotKey();
    void initSt();
    BcEditor* edit;
private:
    QLabel* gs = new QLabel("UTF-8",this);
    QFrame* vframe1 = new QFrame(this);
    QLabel* linerow = new QLabel("第?行,第?列",this);
    QFrame* vframe2 = new QFrame(this);
    QLabel* path = new QLabel("C:/",this);

    QString nowFilePath = "";
    BcToolButton* file = new BcToolButton("文件(F)",this);
    BcToolButton* bianji = new BcToolButton("编辑(E)",this);
    BcToolButton* geshi = new BcToolButton("格式(O)",this);
    BcToolButton* chakan = new BcToolButton("查看(V)",this);
    BcToolButton* help = new BcToolButton("帮助(H)",this);
    BcToolButton* tool = new BcToolButton("工具(T)",this);

    QAction* newfile = new QAction("新建(N)\tctrl+N   ", this);
    QAction* newwidget = new QAction("新窗口(M)\tctrl+shift+N   ", this);
    QAction* open = new QAction("打开(O)\tctrl+O   ", this);
    QAction* save = new QAction("保存(S)\tctrl+S   ", this);
    QAction* saveother = new QAction("另存为(A)\tctrl+shift+S   ", this);
    QAction* exit = new QAction("退出(X)", this);

    QAction* chexiao = new QAction("撤销(S)\tctrl+Z   ", this);
    QAction* copy = new QAction("复制(C)\tctrl+C   ", this);
    QAction* puton = new QAction("粘贴(P)\tctrl+V   ", this);
    QAction* mputon = new QAction("剪贴(T)\tctrl+X   ", this);
    QAction* replace = new QAction("替换(S)\tctrl+H   ", this);

    QAction* zdhuanhang = new QAction("自动换行(W)", this);
    QAction* font = new QAction("字体(F)", this);
    QAction* reset = new QAction("恢复默认状态", this);

    QAction* situation = new QAction("状态栏(S)", this);

    QAction* version = new QAction("版本(V)", this);

    QAction* top = new QAction("顶置/取顶(T)\tctrl+T", this);
    //QAction* showIcon = new QAction("隐藏/显示窗口图标(S)\tctrl+H   ", this);
    bool canzdhh = 1;
    bool showSt = 1;
    QFont font_;
public:
    QString iniPath = "./info.ini";
};

#endif // WIDGET_H
