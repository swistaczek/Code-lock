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
    while(true){
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

void CheckThread::getValue(){
    QString input;
    input = this->usb_keyboard.getInput();
    emit enteredValue(input);
}

void CheckThread::reinitializeController(){
    this->usb_keyboard.init();
}
