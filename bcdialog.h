#ifndef BCDIALOG_H
#define BCDIALOG_H

#include <QObject>
#include "bcwidget.h"
#include "bctoolbutton.h"
#include <QLabel>
#include <QEventLoop>
#include <QDebug>

class BcDialog : public BcWidget
{
    Q_OBJECT
public:
    explicit BcDialog(QWidget *parent = nullptr);
signals:

public slots:
};

#endif // BCDIALOG_H
