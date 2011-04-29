#include "keyboard.h"
#include <stdio.h>

// Keyboard info:
// idVendor           0x05d5
// idProduct          0x0689

Keyboard::Keyboard(QObject *parent) : QObject(parent)
{
    this->init();
}

void Keyboard::init(){
    this->handle = hid_open(0x05d5, 0x0689, NULL);
    if (!this->handle) {
            printf("unable to open device\n");
    }

    memset(buf,0,sizeof(buf));

    hid_set_nonblocking(this->handle, 1);
    hid_read(this->handle, buf, sizeof(buf));
}

char Keyboard::getChar(int buffer){
    switch(buffer){
        case 0x62:
            return '0';
            break;
        case 0x59:
            return '1';
            break;
        case 0x5A:
            return '2';
            break;
        case 0x5B:
            return '3';
            break;
        case 0x5C:
            return '4';
            break;
        case 0x5D:
            return '5';
            break;
        case 0x5E:
            return '6';
            break;
        case 0x5F:
            return '7';
            break;
        case 0x60:
            return '8';
            break;
        case 0x61:
            return '9';
            break;
        case 0x58:
            return 'E'; // ENTER
            break;
        case 0x2A:
            return 'D'; // DELETE
            break;
        case 0x63:
            return 'D'; // . or DEL
            break;
    }
    return NULL;
}

void Keyboard::manufacturer(){
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(this->handle, wstr, MAX_STR);
    if (res < 0)
            printf("Unable to read manufacturer string\n");
    printf("Manufacturer: %ls\n", wstr);
}

void Keyboard::productStrng(){
    wstr[0] = 0x0000;
    res = hid_get_product_string(this->handle, wstr, MAX_STR);
    if (res < 0)
            printf("Unable to read product string\n");
    printf("Product: %ls\n", wstr);
}

QString Keyboard::getInput(){
    memset(buf,0,sizeof(buf));

    input_grab = "";
    get_enter = false;

    while(!get_enter){
        res = 0;
        while (res == 0) {
                res = hid_read(this->handle, buf, sizeof(buf));
                if (res < 0)
                        printf("Unable to read()\n");
        }

        if(this->getChar(buf[2]) != NULL){
            if(getChar(buf[2]) == 'E'){
                get_enter = true;
            }else{
                input_grab += this->getChar(buf[2]);
            }
        }
    };
    return input_grab;

}

