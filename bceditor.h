#ifndef BCEIDTOR_H
#define BCEIDTOR_H

#include <QWidget>
#include <QTextEdit>
#include <QWheelEvent>

class BcEditor : public QWidget
{
    Q_OBJECT
public:
    explicit BcEditor(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *e);//滚轮事件

    QTextEdit * edit;
private:
signals:

public slots:
};

#endif // BCEIDTOR_H
