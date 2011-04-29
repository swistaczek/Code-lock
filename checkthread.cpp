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
    forever{
        mutex.lock();
        input = this->usb_keyboard.getInput();
        cout << "Wpisano: " << input.toStdString() << "\n";
        if(input == "123" && stopped != true){
            emit getPassword();
        }else{
            emit getBadPassword();
        }
            msleep(200);
        mutex.unlock();
    }
}

void CheckThread::getValue(){
    QString input;
    input = this->usb_keyboard.getInput();
    cout << "Pobieranie na zadanie: " << input.toStdString() << "\n";
    emit enteredValue(input);
}

void CheckThread::reinitializeController(){
    this->usb_keyboard.init();
}

void CheckThread::pauseThread(){
    stopped = 1;
}

void CheckThread::resumeThread(){
    stopped = 0;
}
