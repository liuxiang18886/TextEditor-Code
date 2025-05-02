#include "ini.h"

InI::InI()
{

}

void InI::open(QString file){
    setting = new QSettings(file,QSettings::IniFormat);
}
void InI::write(QString key,QString value){
    if(setting!=nullptr)
        setting->setValue(key,value);
}
QString InI::read(QString key){
    if(setting!=nullptr)
        return setting->value(key).toString();
    else return "";
}
