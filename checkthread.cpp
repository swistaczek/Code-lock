#include "checkthread.h"

CheckThread::CheckThread(QObject *parent) :
    QThread(parent)
{
}

void CheckThread::checkPassword(){
    start();
}

void CheckThread::run(){

    QString input;

    for(int i = 0; i<1000; i++){
        input = this->usb_keyboard.getInput();
        cout << "Wpisano: " << input.toStdString() << "\n";
        if(input == "123"){
            emit getPassword();
        }else{
            emit getBadPassword();
        }
        msleep(10);
    }
}

void CheckThread::reinitializeController(){
    this->usb_keyboard.init();
}
