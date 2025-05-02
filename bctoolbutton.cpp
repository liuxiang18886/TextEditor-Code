#include "bctoolbutton.h"
#include <QDebug>


BcToolButton::BcToolButton(QWidget *parent) : QToolButton(parent)
{
    menu = new QMenu(this);
    this->setText("button");
    this->resize(60,30);
    this->setStyleSheet(BUTTON_STYLE);
    set();
}

BcToolButton::BcToolButton(QString name,QWidget *parent) : QToolButton(parent)
{
    menu = new QMenu(this);
    this->setStyleSheet(BUTTON_STYLE);
    this->setText(name);
    this->resize(60,30);
    set();
}

void BcToolButton::set()
{
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setStyleSheet(MENU_STYLE);
    this->setPopupMode(QToolButton::InstantPopup);
    this->setArrowType(Qt::NoArrow);
    this->setStyleSheet(BUTTON_STYLE);
    this->setMenu(menu);

    //QAction* actionIpSet = new QAction("按钮1", this);
    //QAction* actionAuthorize = new QAction("按钮2", this);
    //menu->addAction(actionIpSet);
    //menu->addSeparator();
    //menu->addAction(actionAuthorize);

}
