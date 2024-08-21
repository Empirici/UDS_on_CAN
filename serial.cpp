#include "serial.h"
#include "ui_serial.h"
#include "QMessageBox"
#include "QSettings"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets>
#include <QThread>
#include <QString>
#include<QDebug>

#include"CAN/canmatrix.h"
#include "CAN/CanComm.h"
#include "CAN/xlCANFunctions.h"
#include "CAN/zlgCANFunctions.h"




#include <QToolBar>
#include <QAction>

QAction * createAction(QString name)
{
   QAction *action = new QAction(name);
   action->setObjectName(name);
   return action;
}


int recieve_CAN_flag = 0;
unsigned char study_buffer[8];
#define UART_RX_MAX_NUM	(200u)
typedef struct
{
    char recBuffer[UART_RX_MAX_NUM];
    int  wrIndex;
}SerialPduType;
SerialPduType SerialPdu =
{
    {0},0
};
MSG_TPMS_375h_sig_u    g_can_TPMS_375h;

serial::serial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serial)
{
    ui->setupUi(this);
    Init();
    this->PkgCount1 = 0;
    uartport();
    rxThread = new CanRxThread;
    txThread = new CanTxThread;
    mainTimer = new QTimer;
    ui->filter_2->setPlaceholderText("请输入胎压ID 格式:XX XX XX XX");
    ui->ID->setPlaceholderText("当前胎压ID");
    ui->lineEdit1->setPlaceholderText("请输入初始计数值");
    ui->lineEdit2->setPlaceholderText("请输入初始计数值");
    ui->lineEdit3->setPlaceholderText("请输入初始计数值");
    ui->lineEdit4->setPlaceholderText("请输入初始计数值");
    setWindowFlags(Qt::WindowCloseButtonHint);
    QObject::connect(mainTimer,SIGNAL(timeout()),this,SLOT(mainTaskSlot()));
    groupButton=new QButtonGroup(this);
    groupButton->addButton(ui->study_front,0);
    groupButton->addButton(ui->study_after,1);
    connect(ui->study_front,SIGNAL(clicked(bool)),
              this,SLOT(slots_vegetables()));
    connect(ui->study_after,SIGNAL(clicked(bool)),
              this,SLOT(slots_vegetables()));
}

serial::~serial()
{
    delete ui;
}



void serial::mainTaskSlot()
{
    canProcess();
    uartProcess();
    updateWindow();
}
static char a=0;

/*
*********************************************************************************************************************
*********************************************************************************************************************
***********************************************串口模块***************************************************************
*********************************************************************************************************************
*********************************************************************************************************************
*/


/***************************************
 * 打开串口
 ***************************************/

void serial::on_actOpen_serial_triggered()
{
    QString iniFilePath="config.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    QString baud_u = settings.value("Uart/baud").toString();//波特率
    QString parity_u = settings.value("Uart/parity").toString();//校验位
    QString dataBits_u = settings.value("Uart/dataBits").toString();//数据位
    QString stopBits_u = settings.value("Uart/stopBits").toString();//停止位
    int baud = baud_u.toInt();
    int parity = parity_u.toInt();
    int dataBits = dataBits_u.toInt();
    int stopBits = stopBits_u.toInt();
    if(ui->actOpen_serial->text() == "打开串口")
    {
        SerialPort.setPortName(ui->portBox->currentText());//设置串口号
        if(SerialPort.open(QIODevice::ReadWrite))
        {
            SerialPort.setBaudRate(baud);
            switch(dataBits)
            {
            case 5: SerialPort.setDataBits(QSerialPort::Data5); break;
            case 6: SerialPort.setDataBits(QSerialPort::Data6); break;
            case 7: SerialPort.setDataBits(QSerialPort::Data7); break;
            case 8: SerialPort.setDataBits(QSerialPort::Data8); break;
            default: break;
            }
            switch(parity)
            {
            case 0: SerialPort.setParity(QSerialPort::NoParity); break;
            case 1: SerialPort.setParity(QSerialPort::OddParity); break;
            case 2: SerialPort.setParity(QSerialPort::EvenParity); break;
            default: break;
            }
            SerialPort.setFlowControl(QSerialPort::NoFlowControl);
            switch(stopBits)
            {
            case 1: SerialPort.setStopBits(QSerialPort::OneStop); break;
            case 2: SerialPort.setStopBits(QSerialPort::TwoStop); break;
            default: break;
            }
        }
        else
        {
            QMessageBox::warning(this, tr("串口状态"),"串口无法打开\r\n不存在或已被占用");
            return;
        }
        ui->actOpen_serial->setText("关闭串口");
        mainTimer->start(10);
    }
    else
    {
        SerialPort.close();
        ui->actOpen_serial->setText("打开串口");
    }
        connect(&SerialPort,SIGNAL(readyRead()),this,SLOT(serial_Read()));
}
/***************************************
 * 清空接收信息框
 ***************************************/
void serial::on_clearuart_clicked()
{
    ui->receiveData->clear();
    this->PkgCount1 = 0;
    ui->frames->setText(QString::number(PkgCount1,10));
}
/***************************************
 * 自动读取串口号
 ***************************************/
void serial::uartport()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portBox->addItem(info.portName());
            serial.close();
        }
    }
}
/**************************************
 * uart处理
 **************************************/
void serial::uartProcess()
{
    QString str,str1,str2,str3,str4,dianliang;

    if (SerialPdu.wrIndex >= 10)
    {
        if(a==0)
        {
        if (((unsigned char)SerialPdu.recBuffer[0] == 0x5A)
          &&((unsigned char)SerialPdu.recBuffer[9] == 0x0A))
        {
            PkgCount1++;
            for (int i = 0 ; i < 10 ;i++)
            {
                if((unsigned char)SerialPdu.recBuffer[i] < 16)//显示16进制，不足16补零
                {
                    str = str + "0"+QString::number((unsigned char)SerialPdu.recBuffer[i],16).toUpper() + " ";
                    str1= QString::number((unsigned char)SerialPdu.recBuffer[1],16).toUpper() + " ";
                    str2= QString::number((unsigned char)SerialPdu.recBuffer[2],16).toUpper() + " ";
                    str3= QString::number((unsigned char)SerialPdu.recBuffer[3],16).toUpper() + " ";
                    str4= QString::number((unsigned char)SerialPdu.recBuffer[4],16).toUpper() + " ";
                    dianliang= QString::number((unsigned char)SerialPdu.recBuffer[5],10).toUpper() + " ";
                    float num = dianliang.toFloat();
                    float dianliang=4-num*0.0108;
                    QString str5=str1+str2+str3+str4;
                    QString data = QString("%1").arg(dianliang)+"V";
                    ui->ID->setText(str5);
                    ui->label_15->setText(data);

                }
                else
                {
                    str = str + QString::number((unsigned char )SerialPdu.recBuffer[i],16).toUpper() + " ";
                    str1= QString::number((unsigned char)SerialPdu.recBuffer[1],16).toUpper() + " ";
                    str2= QString::number((unsigned char)SerialPdu.recBuffer[2],16).toUpper() + " ";
                    str3= QString::number((unsigned char)SerialPdu.recBuffer[3],16).toUpper() + " ";
                    str4= QString::number((unsigned char)SerialPdu.recBuffer[4],16).toUpper() + " ";
                    dianliang= QString::number((unsigned char)SerialPdu.recBuffer[5],10).toUpper() + " ";
                    float num = dianliang.toFloat();
                    float dianliang=4-num*0.0108;
                    QString str5=str1+str2+str3+str4;
                    QString data = QString("%1").arg(dianliang)+"V";
                    ui->ID->setText(str5);
                    ui->label_15->setText(data);
                }
            }
            ui->receiveData->append(str);
            ui->frames->setText(QString::number(PkgCount1,10));
            ui->receiveData->append(str);
            memcpy(&SerialPdu.recBuffer[0],&SerialPdu.recBuffer[10], SerialPdu.wrIndex - 9);
            SerialPdu.wrIndex -= 9;
        }
        else
        {
            memcpy(&SerialPdu.recBuffer[0],&SerialPdu.recBuffer[1], SerialPdu.wrIndex - 1);
            SerialPdu.wrIndex--;
        }
        }

        else
        {

            QString ba0 = ui->filter_2->text();
            QStringList list = ba0.split(" ");
            QString ba1 = list[0];
            QString ba2 = list[1];
            QString ba3 = list[2];
            QString ba4 = list[3];
            int bit0=ba1.toInt(NULL,16);
            int bit1=ba2.toInt(NULL,16);
            int bit2=ba3.toInt(NULL,16);
            int bit3=ba4.toInt(NULL,16);
            if (((unsigned char)SerialPdu.recBuffer[0] == 0x5A)
            &&((unsigned char)SerialPdu.recBuffer[1] == bit0)
            &&((unsigned char)SerialPdu.recBuffer[2] == bit1)
            &&((unsigned char)SerialPdu.recBuffer[3] == bit2)
            &&((unsigned char)SerialPdu.recBuffer[4] == bit3)
            &&((unsigned char)SerialPdu.recBuffer[9] == 0x0A)
            )
            {
            PkgCount1++;
            for (int i = 0 ; i < 10 ;i++)
            {
                if((unsigned char)SerialPdu.recBuffer[i] < 16)//显示16进制，不足16补零
                {
                    str = str + "0"+QString::number((unsigned char)SerialPdu.recBuffer[i],16).toUpper() + " ";
                    str1= QString::number((unsigned char)SerialPdu.recBuffer[1],16).toUpper() + " ";
                    str2= QString::number((unsigned char)SerialPdu.recBuffer[2],16).toUpper() + " ";
                    str3= QString::number((unsigned char)SerialPdu.recBuffer[3],16).toUpper() + " ";
                    str4= QString::number((unsigned char)SerialPdu.recBuffer[4],16).toUpper() + " ";
                    dianliang= QString::number((unsigned char)SerialPdu.recBuffer[5],10).toUpper() + " ";
                    float num = dianliang.toFloat();
                    float dianliang=4-num*0.0108;
                    QString str5=str1+str2+str3+str4;
                    QString data = QString("%1").arg(dianliang)+"V";
                    ui->ID->setText(str5);
                    ui->label_15->setText(data);
                }
                else
                {
                    str = str + QString::number((unsigned char )SerialPdu.recBuffer[i],16).toUpper() + " ";
                    str1= QString::number((unsigned char)SerialPdu.recBuffer[1],16).toUpper() + " ";
                    str2= QString::number((unsigned char)SerialPdu.recBuffer[2],16).toUpper() + " ";
                    str3= QString::number((unsigned char)SerialPdu.recBuffer[3],16).toUpper() + " ";
                    str4= QString::number((unsigned char)SerialPdu.recBuffer[4],16).toUpper() + " ";
                    dianliang= QString::number((unsigned char)SerialPdu.recBuffer[5],10).toUpper() + " ";
                    float num = dianliang.toFloat();
                    float dianliang=4-num*0.0108;
                    QString str5=str1+str2+str3+str4;
                    QString data = QString("%1").arg(dianliang)+"V";
                    ui->ID->setText(str5);
                    ui->label_15->setText(data);
                }
            }
                ui->receiveData->append(str);
                ui->frames->setText(QString::number(PkgCount1,10));
                memcpy(&SerialPdu.recBuffer[0],&SerialPdu.recBuffer[10], SerialPdu.wrIndex - 9);
                SerialPdu.wrIndex -= 9;
            }
        else
        {
            memcpy(&SerialPdu.recBuffer[0],&SerialPdu.recBuffer[1], SerialPdu.wrIndex - 1);
            SerialPdu.wrIndex--;
        }
        }
    }
}
/***************************************
 * 获取串口数据
 ***************************************/
void serial::serial_Read()
{
    QByteArray buffer = SerialPort.readAll();
    char *byte = buffer.data();
    if (SerialPdu.wrIndex + buffer.size() < UART_RX_MAX_NUM)
    {
        memcpy(&SerialPdu.recBuffer[SerialPdu.wrIndex],byte, buffer.size());
        SerialPdu.wrIndex += buffer.size();
    }

}

/*
*********************************************************************************************************************
*********************************************************************************************************************
***********************************************CAN模块****************************************************************
*********************************************************************************************************************
*********************************************************************************************************************
*/
/**************************************
 * 打开CAN设备函数
 **************************************/
bool serial::canDeviceOpen(unsigned char device_type, unsigned int baud, unsigned char frame_type)
{
       if(device_type == DEVICE_CANCASE)
       {
           deviceType = DEVICE_CANCASE;
           if(CCANFunctions::Instance()->CANInit())
           {
               return false;
           }
           if(CCANFunctions::Instance()->CANSetFilter(0x660,0x669))
           {
               return false;
           }
           if (1 == frame_type)
           {
               if(CCANFunctions::Instance()->CANSetFrameType(XL_CAN_EXT))
               {
                   return false;
               }
           }
           else
           {
               if(CCANFunctions::Instance()->CANSetFrameType(XL_CAN_STD))
               {
                   return false;
               }
           }
           if(CCANFunctions::Instance()->CANGoOnBus(baud))
           {
           }
                   return false;
           }
       else
       {
          deviceType = (DeviceType)device_type;

          if (frame_type == 1)
          {
              zlgCANFunctions::Instance()->zlgCANExternFlagSet(1);
          }
          else
          {
              zlgCANFunctions::Instance()->zlgCANExternFlagSet(0);
          }

          if (deviceType == DEVICE_USBCAN_II)
          {
              if(!zlgCANFunctions::Instance()->zlgCANInit(VCI_USBCAN2,baud,0))
              {
                  return false;
              }
          }
          else
          {
          if(!zlgCANFunctions::Instance()->zlgCANInit(VCI_USBCAN_2E_U,baud,0))
              {
                  return false;
              }
          }
       }
       return true;
}
/**************************************
 * 关闭CAN设备函数
 **************************************/
bool serial::canDeviceClose()
{
    rxThread->stop();
    txThread->stop();
    rxThread->quit();
    txThread->quit();
    if(deviceType == DEVICE_CANCASE)
    {
        CCANFunctions::Instance()->CANGoOffBus();
    }
    else
    {
        zlgCANFunctions::Instance()->zlgCANExit(0);
    }
    return true;
}
/**************************************
 * 获取can数据
 **************************************/
void serial::canProcess()
{
    QString iniFilePath="config.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    unsigned int   can_id;
    unsigned char  buffer[8];
    bool ok;
    QString pressure_number_id = settings.value("CAN/pressure_number_id").toString();//波特率
    int pressure_number_id_u = pressure_number_id.toInt(&ok,16);

    CanComm_set_App_rx_id(pressure_number_id_u);//滤波
    int ret = App_ReadAppMsgFromCOMM(&can_id,buffer);
    static  int  time=0;
    if(time < 0xFFF0)
    {
        time += 10;
    }
    if (ret > 0)
    {
        recieve_CAN_flag = 0;
        memcpy(g_can_TPMS_375h.buff,buffer,8);

    }
    if (time >= 1000)
    {
        recieve_CAN_flag = 1;
    }

}
/**************************************
 * can数据处理
 **************************************/
void serial::updateWindow()
{
    unsigned short lf_val,lr_val,rf_val,rr_val;
    float lf_Begin,lf_end,lf_Receive_rate,frames;
    float lr_Begin,lr_end,lr_Receive_rate;
    float rf_Begin,rf_end,rf_Receive_rate;
    float rr_Begin,rr_end,rr_Receive_rate;

    lf_val = g_can_TPMS_375h.bits.LF;
    lf_val = lf_val << 8;
    lf_val = lf_val | g_can_TPMS_375h.bits.LF_1;
    lr_val = g_can_TPMS_375h.bits.LR;
    lr_val = lr_val << 8;
    lr_val = lr_val | g_can_TPMS_375h.bits.LR_1;

    rf_val = g_can_TPMS_375h.bits.RF;
    rf_val = rf_val << 8;
    rf_val = rf_val | g_can_TPMS_375h.bits.RF_1;

    rr_val = g_can_TPMS_375h.bits.RR;
    rr_val = rr_val << 8;
    rr_val = rr_val | g_can_TPMS_375h.bits.RR_1;

    ui->lf->setText(QString::number(lf_val,10));
    ui->lr->setText(QString::number(lr_val,10));
    ui->rf->setText(QString::number(rf_val,10));
    ui->rr->setText(QString::number(rr_val,10));

    frames = ui->frames->text().toInt(NULL,10);
    lf_Begin=ui->lineEdit1->text().toInt(NULL,10);
    lf_end = ui->lf->text().toInt(NULL,10);
    lf_Receive_rate=(lf_end/frames-lf_Begin/frames)*100;
    QString lf_Receive=QString::asprintf("%.2f",lf_Receive_rate)+"%";
    ui->lf_Receive->setText(lf_Receive);

    lr_Begin=ui->lineEdit2->text().toInt(NULL,10);
    lr_end = ui->lr->text().toInt(NULL,10);
    lr_Receive_rate=(lr_end/frames-lr_Begin/frames)*100;
    QString lr_Receive=QString::asprintf("%.2f",lr_Receive_rate)+"%";
    ui->lr_Receive->setText(lr_Receive);

    rf_Begin=ui->lineEdit3->text().toInt(NULL,10);
    rf_end = ui->rf->text().toInt(NULL,10);
    rf_Receive_rate=(rf_end/frames-rf_Begin/frames)*100;
    QString rf_Receive=QString::asprintf("%.2f",rf_Receive_rate)+"%";
    ui->rf_Receive->setText(rf_Receive);

    rr_Begin=ui->lineEdit4->text().toInt(NULL,10);
    rr_end = ui->rr->text().toInt(NULL,10);
    rr_Receive_rate=(rr_end/frames-rr_Begin/frames)*100;
    QString rr_Receive=QString::asprintf("%.2f",rr_Receive_rate)+"%";
    ui->rr_Receive->setText(rr_Receive);

}
/**************************************
 * 打开can设备按钮
 **************************************/
void serial::on_actOpen_can_triggered()
{
    QString iniFilePath="config.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    QString canbaud_u = settings.value("CAN/baud").toString();//波特率
    int can_baud = canbaud_u.toInt();
    if(ui->actOpen_can->text() == "打开CAN")
    {
        if(canDeviceOpen(0,can_baud,0)==1)
        {
            rxThread->start();
            txThread->start();
            mainTimer->start(10);
        }
        else
        {
            QMessageBox::warning(this, tr("CAN设备状态"),"打开设备失败,请检查！");
            return;
        }
        ui->actOpen_can->setText("关闭CAN");
    }
    else
    {
        canDeviceClose();
        ui->actOpen_can->setText("打开CAN");
    }
}


void serial::on_filter_clicked(bool checked)
{
    if(checked)a=1;
    else a=0;
}


void serial::Init()
{
//读取串口信息
QStringList baudList;//波特率
QStringList parityList; //校验位
QStringList dataBitsList;//数据位
QStringList stopBitsList;//停止位
QStringList can_baudList;//停止位
QStringList pressure_number_id_list;
    //波特率默认选择下拉第三项：9600
    baudList<<"1200"<<"2400"<<"4800"<<
    "9600"<<"14400"<<"19200"<<"38400"<<
    "56000"<<"57600"<<"115200";
    ui->btl->addItems(baudList);
    ui->btl->setCurrentIndex(6);
    // 校验      //校验默认选择无
    parityList<<"无"<<"奇"<<"偶";
    ui->xy->addItems(parityList);
    ui->xy->setCurrentIndex(0);
    // 数据位      //数据位默认选择8位
    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->sjw->addItems(dataBitsList);
    ui->sjw->setCurrentIndex(3);
    // 停止位      //停止位默认选择1位
    stopBitsList<<"1"<<"2";
    ui->tz->addItems(stopBitsList);
    ui->tz->setCurrentIndex(0);
    //CAN信息
    can_baudList<<"125000"<<"250000"<<"500000";
    ui->can_btl->addItems(can_baudList);
    ui->can_btl->setCurrentIndex(2);

    pressure_number_id_list<<"222"<<"375";
    ui->pressure_number_id->addItems(pressure_number_id_list);


}

void serial::on_pushButton_5_clicked()
{
    QString iniFilePath="config.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("Uart/baud",ui->btl->currentText().toInt());
    settings.setValue("Uart/parity",ui->xy->currentText().toInt());
    settings.setValue("Uart/dataBits",ui->sjw->currentText().toInt());
    settings.setValue("Uart/stopBits",ui->tz->currentText().toInt());
    settings.setValue("CAN/baud",ui->can_btl->currentText().toInt());
    settings.setValue("CAN/pressure_number_id",ui->pressure_number_id->currentText());
}

void serial::slots_vegetables()
{
    switch(groupButton->checkedId())
       {
       case 0:
        study_buffer[0]=0x31;
        study_buffer[1]=0x01;
        study_buffer[2]=0x59;
        study_buffer[3]=0x08;
        study_buffer[4]=0x00;
        study_buffer[5]=0x00;
        study_buffer[6]=0x00;
        study_buffer[7]=0x00;
        break;
       case 1:
        study_buffer[0]=0x31;
        study_buffer[1]=0x01;
        study_buffer[2]=0x59;
        study_buffer[3]=0x08;
        study_buffer[4]=0x01;
        study_buffer[5]=0x00;
        study_buffer[6]=0x00;
        study_buffer[7]=0x00;
        break;
       }
}
void serial::on_pushButton_2_clicked()
{
    if(ui->actOpen_can->text() == "关闭CAN")
    {
        App_SendAppMsgToCOMM(0X580,study_buffer,8);

    }
    else
    {
        QMessageBox::warning(this, tr("CAN设备状态"),"打开设备失败,请检查！");
        return;
    }

}
