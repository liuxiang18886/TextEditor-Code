#include "widget.h"
#include <QApplication>
#include <QString>
#include "ini.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString iniPath = qApp->applicationDirPath() + "/info.ini";
    Widget w(iniPath);
    if(argc > 1)
    {
        QString strOpenPath = QString::fromLocal8Bit(argv[1]);//没有 fromLocal8Bit乱码路径
        if(!strOpenPath.isEmpty())
        {
            // 将“\”转换成"/"，因为"\"系统不认
            //strOpenPath = strOpenPath.replace("\\", "/");
            // 具体实现在下面这个函数
            QString title = QString("%1 - %2").arg(getLastName(strOpenPath)).arg("BcEditor");
            w.setTitleText(title);
            w.setWindowTitle(title);
            w.update();
            w.load(strOpenPath.toUtf8());//没有toutf8 打开中文路径会失败同上
        }
    }
    w.show();
    bool ret= a.exec();

    return ret;
}
