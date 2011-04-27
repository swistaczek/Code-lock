#include "relayb.h"
uint8_t debugOn = 0x00;

RelayB::RelayB(char* adr, QObject *parent) :
    QObject(parent)
{
    this->portName = adr;

}

void RelayB::revertPort(int temp){
    RelayBoardPortInit(this->portName);
    RelayBoardInv(ADRESS,temp);
}
