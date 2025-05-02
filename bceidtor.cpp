#include "bceditor.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include <QFontMetrics>
#include <QFile>
#include <QApplication>
#include <QDir>
#define SIZE 15

BcEditor::BcEditor(QWidget *parent) : QWidget(parent)
{
    this->edit = new QTextEdit(this);
    this->edit->move(4,0);
    QFont f = edit->font();
    f.setPointSize(13);
    edit->setFont(f);
    QFile file(":/style/xltstyle.qss");
    file.open(QFile::ReadOnly);
    QFontMetrics metrics(edit->font());
    edit->setTabStopWidth(4 * metrics.width(' '));
    edit->setAcceptRichText(false);
    QString qss = file.readAll();
    edit->verticalScrollBar()->setStyleSheet(qss);
    edit->horizontalScrollBar()->setStyleSheet(qss);
    edit->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white;");
}

void BcEditor::wheelEvent(QWheelEvent *e)
{
    if(QApplication::keyboardModifiers() == Qt::ControlModifier)//ctrl键的判断
    {
        if(e->delta() > 0)
        {
            QFont font = edit->font();
            font.setPointSize(edit->font().pointSize()+1);
            edit->setFont(font);
        }
        else
        {
            QFont font = edit->font();
            font.setPointSize(edit->font().pointSize()-1);
            edit->setFont(font);
        }
    }
}
