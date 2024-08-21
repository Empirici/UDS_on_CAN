#ifndef ZLGCANFUNCTIONS_H
#define ZLGCANFUNCTIONS_H


#include <QMutex>
#include "ControlCAN.h"

class zlgCANFunctions
{
public:
    zlgCANFunctions();
    static zlgCANFunctions* Instance()
    {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new zlgCANFunctions;
            }
        }
        return _instance;
    }
    int m_devind,m_canind,m_devtype;
    bool zlgCANInit(int devtype,unsigned long int baud,int canNum);
    bool zlgCANExit(int canNum);
    bool zlgCANSend(void);
    bool zlgCANRecv(void);
    bool zlgCANExternFlagSet(bool flag);
private:
    static zlgCANFunctions* _instance;
    QMutex mutex;
    bool canExternFlag;
};

#endif // ZLGCANFUNCTIONS_H
