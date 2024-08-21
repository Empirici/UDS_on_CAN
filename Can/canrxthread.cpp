#include "canrxthread.h"
#include "CanComm.h"
#include "xlCANFunctions.h"
#include "zlgCANFunctions.h"
#include <QtDebug>
#include <QtWidgets>

CanRxThread::CanRxThread()
{
    stopped = false;
}

void CanRxThread::run()
{
    stopped = false;
    while(!stopped)
    {
        usleep(10);
        if(deviceType == DEVICE_CANCASE)
        {
            CCANFunctions::Instance()->CANRecv(1);
        }
        else
        {
            zlgCANFunctions::Instance()->zlgCANRecv();
        }
    }
    stopped = false;
}

void CanRxThread::stop()
{
    stopped = true;
}


