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
    void getValue();
    Keyboard usb_keyboard;
    void pauseThread();
    void resumeThread();
signals:
    void getPassword();
    void getBadPassword();
    void enteredValue(QString);

public slots:
    //void stopProcess();
protected:
    void run();
private:
    bool m_abort;
    bool stopped;
    QMutex mutex;
};

#endif // CHECKTHREAD_H
