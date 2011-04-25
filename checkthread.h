#ifndef CHECKTHREAD_H
#define CHECKTHREAD_H

#include <QThread>
#include <QObject>
#include <QMutex>
#include <keyboard.h>

class CheckThread : public QThread
{
    Q_OBJECT
public:
    explicit CheckThread(QObject *parent = 0);
    //~CheckThread();
    void checkPassword();
    void reinitializeController();
signals:
    void getPassword();
    void getBadPassword();

public slots:
    //void stopProcess();
protected:
    void run();
private:
    bool m_abort;
    QMutex mutex;
    Keyboard usb_keyboard;
};

#endif // CHECKTHREAD_H
