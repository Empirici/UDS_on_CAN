#ifndef SERIAL_H
#define SERIAL_H
#include <QButtonGroup>
#include <QMainWindow>
#include <QWidget>
#include "QSerialPort"      //串口访问
#include "QSerialPortInfo"  //串口端口信息访问
#include "CAN/canrxthread.h"
#include "CAN/cantxthread.h"
namespace Ui {
class serial;
}

class serial : public QMainWindow
{
    Q_OBJECT

public:
    explicit serial(QWidget *parent = 0);
        void Init();//串口初始化主函数中调用
    ~serial();

private slots:
    void mainTaskSlot();
    void serial_Read();//串口数据读取显示
    void on_clearuart_clicked();
    void on_filter_clicked(bool checked);
    void on_pushButton_5_clicked();
    void on_actOpen_can_triggered();
    void on_actOpen_serial_triggered();
    void slots_vegetables();

    void on_pushButton_2_clicked();

private:
    Ui::serial *ui;
    unsigned long PkgCount1;
    QSerialPort SerialPort;
    CanRxThread *rxThread;
    CanTxThread *txThread;
    QTimer *mainTimer;
    QTimer *timer;
    QButtonGroup *groupButton;
    bool canDeviceOpen(unsigned char index,unsigned int baud,unsigned char frame_type);
    bool canDeviceClose(void);
    void canProcess(void);
    void uartProcess(void);
    void updateWindow(void);
    void uartport(void);
};

#endif // SERIAL_H
