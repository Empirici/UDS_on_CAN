#ifndef CANRXTHREAD_H
#define CANRXTHREAD_H

#include <QThread>


class CanRxThread : public QThread
{
public:
    CanRxThread();
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
};

#endif // CANRXTHREAD_H
