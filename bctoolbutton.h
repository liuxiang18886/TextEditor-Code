#ifndef BCTOOLBUTTON_H
#define BCTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>//关闭按钮
#include <QMenu>
#include <QAction>
#define BUTTON_STYLE "QToolButton{background-color:transparent;"\
    "color:white; border : none;}"\
    "QToolButton:hover{background-color:rgba(100,100,100,80);"\
    "color:white; border : none;}"\
    "QToolButton::menu-indicator { image: None; }"\
    "QToolButton:pressed{color:white;background-color:rgba(100,100,100,150);}"
#define MENU_STYLE " QMenu {background-color:rgba(20,20,20,150);border-radius:8px;font-size:13px;color:white;}"\
" QMenu::item {background-color:rgba(100,100,100,100);height:25px; width:90px;padding-left:20px;border: 0px solid none;}"\
"QMenu::item:selected {background-color:rgba(50,50,50,100);\
padding-left:20px;border: 1px solid white;}"
class BcToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit BcToolButton(QWidget *parent = nullptr);
    explicit BcToolButton(QString name,QWidget *parent = nullptr);
    void set();
    QMenu* menu;
signals:

public slots:
};

#endif // BCTOOLBUTTON_H
