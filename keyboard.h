#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <iostream>
#include <string>
#include <hidapi.h>
#define MAX_STR 255

using namespace std;

class Keyboard : public QObject
{
    Q_OBJECT
public:
    explicit Keyboard(QObject *parent = 0);
    QString getInput();
    void manufacturer();
    void productStrng();
    void init();
    char getChar(int);
    QString returnString();
private:
    hid_device *handle;
    wchar_t wstr[MAX_STR];
    int res;
    unsigned char buf[256];
    QString input_grab;
    bool get_enter;
signals:

public slots:

};

#endif // KEYBOARD_H
