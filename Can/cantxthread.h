#ifndef CANTXTHREAD_H
#define CANTXTHREAD_H

#include <QThread>


class CanTxThread : public QThread
{
public:
    CanTxThread();
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
};

#endif // CANTXTHREAD_H
