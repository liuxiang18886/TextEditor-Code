#include "widget.h"
#include <QMessageBox>
#include <QFontDialog>  //字体对话框
#include "ini.h"
#include <QFontDatabase>
#include <windows.h>

Widget::Widget(QString iniPath_,QWidget *parent)
    : BcWidget(parent)
{
    iniPath = iniPath_;
    this->setsize(450,550);
    this->setMinimumHeight(60);
    this->setMinimumWidth(360);
    this->setTitleText("BcEditor");

    edit = new BcEditor(this);
    edit->move(0,2*TITLE_BAR_HEIGHT);

    file->move(0,TITLE_BAR_HEIGHT);
    file->menu->addAction(newfile);
    file->menu->addAction(newwidget);
    file->menu->addSeparator();
    file->menu->addAction(open);
    file->menu->addAction(save);
    file->menu->addAction(saveother);
    file->menu->addAction(exit);
    connect(newfile,&QAction::triggered,this,[=](){
        this->edit->edit->setText("");
        this->setTitleText("未命名 - BcEditor");
        this->setWindowTitle("未命名 - BcEditor");
        nowFilePath = "";
        update();
    });
    connect(newwidget,&QAction::triggered,this,[=](){
        QProcess process(this);
        process.startDetached(qAppName());
    });
    connect(open,&QAction::triggered,this,[=](){
        //打开单个文件
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("打开文件"),
                    "/home",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QString title = tr("%1 - %2").arg(getLastName(fileName)).arg("BcEditor");
        this->setTitleText(title);
        this->setWindowTitle(title);
        update();
        load(fileName);
        nowFilePath = fileName;
    });
    connect(save,&QAction::triggered,this,[=](){
        if(this->nowFilePath != ""){
            QFile file(nowFilePath);
            file.open(QFile::WriteOnly);
            file.write(this->edit->edit->toPlainText().toUtf8());
            file.close();
            return;
        }
        //该函数返回用户所设定的包含文件名的目录
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("另存为"),
                    "save.txt",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        file.write(this->edit->edit->toPlainText().toUtf8());
        file.close();
    });
    connect(saveother,&QAction::triggered,this,[=](){
        //该函数返回用户所设定的包含文件名的目录
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("另存为"),
                    "save.txt",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        file.write(this->edit->edit->toPlainText().toUtf8());
        file.close();
    });
    connect(exit,&QAction::triggered,this,[=](){
        close();
    });
    bianji->move(60,TITLE_BAR_HEIGHT);
    bianji->menu->addAction(chexiao);
    connect(chexiao,&QAction::triggered,this,[=](){
        this->edit->edit->undo();
    });
    bianji->menu->addAction(copy);
    connect(copy,&QAction::triggered,this,[=](){
        this->edit->edit->copy();
    });
    bianji->menu->addAction(puton);
    connect(puton,&QAction::triggered,this,[=](){
        this->edit->edit->paste();
    });
    bianji->menu->addAction(mputon);
    connect(mputon,&QAction::triggered,this,[=](){
        this->edit->edit->cut();
    });
    file->menu->addSeparator();
    /*bianji->menu->addAction(replace);
    connect(replace,&QAction::triggered,this,[=](){
        this->edit->edit->cut();
    });   1.1 new 功能*/

    geshi->move(120,TITLE_BAR_HEIGHT);
    geshi->menu->addAction(zdhuanhang);
    connect(zdhuanhang,&QAction::triggered,this,[=](){
        if(canzdhh){
            canzdhh = 0;
            this->edit->edit->setWordWrapMode(QTextOption::NoWrap);
        }else{
            canzdhh = 1;
            this->edit->edit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        }

        InI wt;
        wt.open(iniPath);
        wt.write("font",this->font_.toString());
        wt.write("zdhh",QString::number(this->canzdhh));
        wt.write("showSt",QString::number(this->showSt));
        wt.write("lastpath",nowFilePath);
    });
    geshi->menu->addAction(font);
    connect(font,&QAction::triggered,this,[=](){
        bool bFlag = true;
        QFont font = QFontDialog::getFont(&bFlag);
        if(bFlag){
            font_ = font;
            this->edit->edit->setFont(font);

            InI wt;
            wt.open(iniPath);
            wt.write("font",this->font_.toString());
            wt.write("zdhh",QString::number(this->canzdhh));
            wt.write("showSt",QString::number(this->showSt));
            wt.write("lastpath",nowFilePath);
        }
    });
    geshi->menu->addAction(reset);
    connect(reset,&QAction::triggered,this,[=](){
        QFont defaultFont = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
        QFont fo = defaultFont;
        fo.setPointSize(13);
        font_ = fo;
        this->edit->edit->setFont(fo);

        InI wt;
        wt.open(iniPath);
        wt.write("font",this->font_.toString());
        wt.write("zdhh",QString::number(this->canzdhh));
        wt.write("showSt",QString::number(this->showSt));
        wt.write("lastpath",nowFilePath);
    });

    chakan->move(180,TITLE_BAR_HEIGHT);
    chakan->menu->addAction(situation);
    connect(situation,&QAction::triggered,this,[=](){
        if(showSt){
            showSt = 0;
            update();
        }else{
            showSt = 1;
            update();
        }

        InI wt;
        wt.open(iniPath);
        wt.write("font",this->font_.toString());
        wt.write("zdhh",QString::number(this->canzdhh));
        wt.write("showSt",QString::number(this->showSt));
        wt.write("lastpath",nowFilePath);
    });

    help->move(240,TITLE_BAR_HEIGHT);
    help->menu->addAction(version);
    connect(version,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"版本","BcTextEditor version 1.1\n"
                                     "第二版 版权归Bcaid所有\n"
                                     "联系方式:QQ75011847");
    });

    tool->move(300,TITLE_BAR_HEIGHT);
    tool->menu->addAction(top);
    connect(top,&QAction::triggered,this,[=](){
        HWND hwnd = (HWND)this->winId();
        if(GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST){
            RECT rect;
            GetWindowRect(hwnd, &rect);
            SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
            update();
        }else{ // no top
            RECT rect;
            GetWindowRect(hwnd, &rect);
            SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
            update();
        }
    });

    initHotKey();
    edit->edit->setAcceptDrops(false);
    setAcceptDrops(true);
    initSt();

    connect(edit->edit,&QTextEdit::cursorPositionChanged,[=](){
        QTextCursor tc = edit->edit->textCursor(); //当前光标
        int rowNum = tc.blockNumber() + 1;//获取光标所在行的行号
        int colNum = tc.columnNumber() + 1;//获取光标的列数
        linerow->setText(QString("第%1行,第%2列")
                         .arg(QString::number(rowNum))
                         .arg(QString::number(colNum)));
        if(this->showSt){
            path->setText(this->nowFilePath);
            int gsw = 14*gs->text().size();
            gs->resize(gsw,30);
            gs->move(10,height()-30);
            gs->show();
            linerow->show();
            linerow->move(gsw+20,height()-30);
            int lrw = 14*linerow->text().size();
            linerow->resize(lrw,30);
            int pw = 14*path->text().size();
            path->show();
            path->move(gsw+lrw+30,height()-30);
            path->resize(pw,30);
            vframe1->show();
            vframe1->move(gsw+10,height()-25);
            vframe1->resize(1,20);
            vframe2->show();
            vframe2->move(gsw+lrw+20,height()-25);
            vframe2->resize(1,20);
        }else{
           gs->hide();
           linerow->hide();
           path->hide();
           vframe1->hide();
           vframe2->hide();
        }
    });

    InI w;
    w.open(iniPath);
    if(w.read("font")!=""){
        this->font_.fromString(w.read("font"));
        this->edit->edit->setFont(font_);
    }else{
        QFont defaultFont = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
        QFont fo = defaultFont;
        fo.setPointSize(13);
        w.write("font",fo.toString());
    }
    if(w.read("zdhh")!=""){
        this->canzdhh = w.read("zdhh").toInt();
    }else w.write("zdhh",QString::number(1));
    if(w.read("showSt")!=""){
        this->showSt = w.read("showSt").toInt();
    }else w.write("showSt",QString::number(1));
    if(w.read("lastpath")!=""){
        this->nowFilePath = w.read("lastpath");
        QString title = getLastName(nowFilePath) + " - BcEditor";
        this->setTitleText(title);
        this->setWindowTitle(title);
        update();
        load(nowFilePath);
    }
    if(w.read("widget-width")!=""){
        QString widths = w.read("widget-width");
        this->setsize(widths.toInt(),height());
    }else w.write("widget-width",QString::number(450));
    if(w.read("widget-height")!=""){
        QString heights = w.read("widget-height");
        this->setsize(width(),heights.toInt());
    }else w.write("widget-height",QString::number(550));

}

Widget::~Widget()
{

}

void Widget::closeEvent(QCloseEvent * event){
    InI wt;
    wt.open(iniPath);
    wt.write("font",this->font_.toString());
    wt.write("zdhh",QString::number(this->canzdhh));
    wt.write("showSt",QString::number(this->showSt));
    wt.write("lastpath",nowFilePath);
    wt.write("widget-width",QString::number(width()));
    wt.write("widget-height",QString::number(height()));
}

void Widget::initHotKey(){
#define setHotKey(kname,key) QShortcut *kname = new QShortcut(this);\
    kname->setKey(tr(key));\
    kname->setAutoRepeat(false);

    setHotKey(newf,"ctrl+n")
            connect(newf, &QShortcut::activated, this, [=](){
        this->edit->edit->setText("");
        this->setTitleText("未命名 - BcEditor");
        this->setWindowTitle("未命名 - BcEditor");
        nowFilePath = "";
        update();
    });
    setHotKey(neww,"ctrl+shift+n")
            connect(neww,&QShortcut::activated,this,[=](){
        QProcess process(this);
        process.startDetached(qAppName());
    });
    setHotKey(open,"ctrl+o")
            connect(open,&QShortcut::activated,this,[=](){
        //打开单个文件
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("打开文件"),
                    "/home",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QString title = tr("%1 - %2").arg(getLastName(fileName)).arg("BcEditor");
        this->setTitleText(title);
        this->setWindowTitle(title);
        update();
        load(fileName);
        nowFilePath = fileName;
    });
    setHotKey(save,"ctrl+s")
            connect(save,&QShortcut::activated,this,[=](){
        if(this->nowFilePath != ""){
            QFile file(nowFilePath);
            file.open(QFile::WriteOnly);
            file.write(this->edit->edit->toPlainText().toUtf8());
            file.close();
            return;
        }
        //该函数返回用户所设定的包含文件名的目录
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("另存为"),
                    "save.txt",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        file.write(this->edit->edit->toPlainText().toUtf8());
        file.close();
    });
    setHotKey(saveother,"ctrl+shift+s")
            connect(saveother,&QShortcut::activated,this,[=](){
        //该函数返回用户所设定的包含文件名的目录
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("另存为"),
                    "save.txt",
                    tr("所有文件 (*.*)"));//多组扩展名用双分号";;"隔开
        if(fileName == "")return;
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        file.write(this->edit->edit->toPlainText().toUtf8());
        file.close();
    });
    setHotKey(top,"ctrl+h")
            connect(top,&QShortcut::activated,this,[=](){
        HWND hwnd = (HWND)this->winId();
        if(GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST){
            RECT rect;
            GetWindowRect(hwnd, &rect);
            SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
            update();
        }else{ // no top
            RECT rect;
            GetWindowRect(hwnd, &rect);
            SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
            update();
        }
    });

}

void Widget::initSt(){
    gs->setStyleSheet("color:white;");
    linerow->setStyleSheet("color:white;");
    path->setStyleSheet("color:white;");
    vframe1->setStyleSheet("background-color:white;");
    vframe2->setStyleSheet("background-color:white;");
    if(this->showSt){
        path->setText(this->nowFilePath);
        int gsw = 14*gs->text().size();
        gs->resize(gsw,30);
        gs->move(10,height()-30);
        gs->show();
        linerow->show();
        linerow->move(gsw+20,height()-30);
        int lrw = 14*linerow->text().size();
        linerow->resize(lrw,30);
        int pw = 14*path->text().size();
        path->show();
        path->move(gsw+lrw+30,height()-30);
        path->resize(pw,30);
        vframe1->show();
        vframe1->move(gsw+10,height()-25);
        vframe1->resize(1,20);
        vframe2->show();
        vframe2->move(gsw+lrw+20,height()-25);
        vframe2->resize(1,20);
    }else{
       gs->hide();
       linerow->hide();
       path->hide();
       vframe1->hide();
       vframe2->hide();
    }
}
void Widget::paintEvent(QPaintEvent*e){
    BcWidget::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    painter.setClipping(true);
    QPainterPath canDrawingPathArea; // 能画上的区域
    canDrawingPathArea.addRoundedRect(rect(), 20, 20);
    canDrawingPathArea.setFillRule(Qt::WindingFill); // 多块区域组合填充模式

    painter.setClipPath(canDrawingPathArea);

    QColor color(Qt::white);
    color.setAlpha(20);
    painter.setBrush(color);
    painter.drawRect(0,TITLE_BAR_HEIGHT,width()+1,TITLE_BAR_HEIGHT);
    painter.drawRect(0,height()-TITLE_BAR_HEIGHT,width()+1,TITLE_BAR_HEIGHT+1);

    edit->resize(width(),height()-TITLE_BAR_HEIGHT*3);
    edit->edit->resize(width()-8,height()-TITLE_BAR_HEIGHT*3);

    if(this->showSt){
        path->setText(this->nowFilePath);
        int gsw = 14*gs->text().size();
        gs->resize(gsw,30);
        gs->move(10,height()-30);
        gs->show();
        linerow->show();
        linerow->move(gsw+20,height()-30);
        int lrw = 14*linerow->text().size();
        linerow->resize(lrw,30);
        int pw = 14*path->text().size();
        path->show();
        path->move(gsw+lrw+30,height()-30);
        path->resize(pw,30);
        vframe1->show();
        vframe1->move(gsw+10,height()-25);
        vframe1->resize(1,20);
        vframe2->show();
        vframe2->move(gsw+lrw+20,height()-25);
        vframe2->resize(1,20);
    }else{
       gs->hide();
       linerow->hide();
       path->hide();
       vframe1->hide();
       vframe2->hide();
    }
}

void Widget::load(QString str){
    QFile file(str);
    bool ret = file.open(QFile::ReadOnly);
    if(!ret){
        QString title = QString("%1 - %2").arg(getLastName("未命名")).arg("BcEditor");
        setTitleText(title);
        setWindowTitle(title);
        update();
        return;
    }
    QByteArray data;
    data = file.readAll();
    this->edit->edit->setText(data);
    file.close();
    this->nowFilePath = str;

    if(this->showSt){
        path->setText(this->nowFilePath);
        int gsw = 14*gs->text().size();
        gs->resize(gsw,30);
        gs->move(10,height()-30);
        gs->show();
        linerow->show();
        linerow->move(gsw+20,height()-30);
        int lrw = 14*linerow->text().size();
        linerow->resize(lrw,30);
        int pw = 14*path->text().size();
        path->show();
        path->move(gsw+lrw+30,height()-30);
        path->resize(pw,30);
        vframe1->show();
        vframe1->move(gsw+10,height()-25);
        vframe1->resize(1,20);
        vframe2->show();
        vframe2->move(gsw+lrw+20,height()-25);
        vframe2->resize(1,20);
    }else{
       gs->hide();
       linerow->hide();
       path->hide();
       vframe1->hide();
       vframe2->hide();
    }
    InI wt;
    wt.open(iniPath);
    wt.write("font",this->font_.toString());
    wt.write("zdhh",QString::number(this->canzdhh));
    wt.write("showSt",QString::number(this->showSt));
    wt.write("lastpath",nowFilePath);
}
void Widget::dragEnterEvent(QDragEnterEvent *e){
    e->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}

QString getLastName(QString path){
    QString name,out;
    for(int i = path.size()-1;i >= 0;i--){
        if(path[i] == '\\'|| path[i] == '/')
            break;
        name += path[i];
    }
    for(int i = name.size()-1;i >= 0;i--)
        out += name[i];
    return out;
}

void Widget::dropEvent(QDropEvent *e){
    QList<QUrl> urls = e->mimeData()->urls();
    qDebug()<<"c";
    if(urls.isEmpty())
        return ;

    QString fileName = urls.first().toLocalFile();

    foreach (QUrl u, urls) {
        qDebug()<<u.toString();
    }
    qDebug()<< urls.size();

    if(fileName.isEmpty())
        return;

    QString title = tr("%1 - %2").arg(getLastName(fileName)).arg("BcEditor");
    this->setTitleText(title);
    this->setWindowTitle(title);
    update();
    load(fileName);
    nowFilePath = fileName;
}
