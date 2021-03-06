#ifndef RELAYB_H
#define RELAYB_H

#include <QObject>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
    #include <rb.h>
}
class RelayB : public QObject
{
    Q_OBJECT
public:
    explicit RelayB(char* adr, QObject *parent = 0);
    void revertPort(int);
    void openPort(int);
    void closePort(int);
signals:

public slots:

private:
    char* portName;
};

#endif // RELAYB_H
