#ifndef INI_H
#define INI_H

#include <QSettings>
#include <QString>
#include <QDebug>

class InI
{
public:
    InI();
    void open(QString file);
    void write(QString key,QString value);
    QString read(QString key);
private:
    QSettings* setting;
};

#endif // INI_H
