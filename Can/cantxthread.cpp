#include "cantxthread.h"
#include "CanComm.h"
#include "xlCANFunctions.h"
#include "zlgCANFunctions.h"
#include <QtDebug>
#include <QtWidgets>

CanTxThread::CanTxThread()
{
    stopped = false;
}

void CanTxThread::run()
{
    stopped = false;
    while(!stopped)
    {
        usleep(10);
        if(deviceType == DEVICE_CANCASE)
        {
            CCANFunctions::Instance()->CANSend(1);
        }
        else
        {
            zlgCANFunctions::Instance()->zlgCANSend();
        }
    }
    stopped = false;
}

void CanTxThread::stop()
{
    stopped = true;
}

