#ifndef CHECKTHREAD_H
#define CHECKTHREAD_H

#include <QThread>
#include <QObject>

class CheckThread : public QThread
{
    Q_OBJECT
public:
    explicit CheckThread(QObject *parent = 0);
    ~CheckThread();
    void checkPassword();
signals:
    void getPassword();

public slots:
    void stopProcess();
protected:
    void run();
private:
    bool m_abort;
    QMutex mutex;
};

#endif // CHECKTHREAD_H
