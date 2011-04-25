#include "checkthread.h"

CheckThread::CheckThread(QObject *parent) :
    QThread(parent)
{
}

void CheckThread::checkPassword(){
    start();
}

void CheckThread::run(){
    emit getPassword();
    msleep(10);
}
