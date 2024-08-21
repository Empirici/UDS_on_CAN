#include "zlgCANFunctions.h"

#include <QtDebug>
#include "CanComm.h"

#define USBCAN_TYPE   VCI_USBCAN2

zlgCANFunctions* zlgCANFunctions::_instance = 0;
zlgCANFunctions::zlgCANFunctions()
{
}

bool zlgCANFunctions::zlgCANInit(int devtype,unsigned long baud, int canNum)
{
    VCI_INIT_CONFIG init_config;
    int baudTemp;

    m_devtype = devtype;
    m_canind  = canNum;
    m_devind  = 0;

    /* 0x700 ~ 0x7ff */
//    if (0 == canExternFlag)
//    {
//        init_config.AccCode = 0xE0000000;
//        init_config.AccMask = 0x1FFFFFFF;
//    }
//    else
//    {
//        init_config.AccCode = 0x00003800;
//        init_config.AccMask = 0xFFFFC7FF;
//    }

    /* 不滤波 */
    init_config.AccCode = 0x00;//0xE0000000;
    init_config.AccMask = 0xFFFFFFFF;//0x1FFFFFFF;

    /* 0->双滤波 , 1->单滤波 */
    init_config.Filter = 1;
    /* 0->正常模式,1->监听模式 */
    init_config.Mode   = 0;
    switch(baud)
    {
    case 500000://500k
    default:
       if (m_devtype == VCI_USBCAN2)
       {
           init_config.Timing0 = 0x00;
           init_config.Timing1 = 0x1c;
       }
       else if (((m_devtype == VCI_USBCAN_E_U))||((m_devtype == VCI_USBCAN_2E_U)))
       {
           baudTemp = 0x60007;
       }
       break;
    case 250000://250k
        if (m_devtype == VCI_USBCAN2)
        {
            init_config.Timing0 = 0x01;
            init_config.Timing1 = 0x1c;
        }
        else if (((m_devtype == VCI_USBCAN_E_U))||((m_devtype == VCI_USBCAN_2E_U)))
        {
            baudTemp = 0x1c0008;
        }
        break;
    case 125000://125k
        if (m_devtype == VCI_USBCAN2)
        {
            init_config.Timing0 = 0x03;
            init_config.Timing1 = 0x1c;
        }
        else if (((m_devtype == VCI_USBCAN_E_U))||((m_devtype == VCI_USBCAN_2E_U)))
        {
            baudTemp = 0x1c0011;
        }
        break;
    }


    if(VCI_OpenDevice(m_devtype,m_devind,0) != STATUS_OK )
    {
        return false;
    }
    if(VCI_SetReference(m_devtype,m_devind,m_canind,0,&baudTemp)!= STATUS_OK)
    {
        VCI_CloseDevice(m_devtype,m_devind);
        return false;
    }

    if(VCI_InitCAN(m_devtype,m_devind,m_canind,&init_config)!= STATUS_OK)
    {
        VCI_CloseDevice(m_devtype,m_devind);
        return false;
    }
    if(VCI_StartCAN(m_devtype,m_devind,m_canind) != STATUS_OK )
    {
        VCI_CloseDevice(m_devtype,m_devind);
        return false;
    }

    VCI_ClearBuffer(m_devtype,m_devind,0);
    return true;
}

bool zlgCANFunctions::zlgCANExit(int canNum)
{
    if(VCI_CloseDevice(m_devtype,canNum) != STATUS_OK )
    {
        return false;
    }
    return true;
}

bool zlgCANFunctions::zlgCANSend(void)
{
    VCI_CAN_OBJ    frameInfo;
    T_CanFrameType TxFrame;

    mutex.lock();
    TxFrame = COMM_ReadTxMessage();
    mutex.unlock();

    if(TxFrame.len != 0)
    {
        frameInfo.ID = TxFrame.canId;
        memcpy(frameInfo.Data,TxFrame.buffer,8);

        frameInfo.DataLen    = TxFrame.len;
        frameInfo.RemoteFlag = 0;
        if (canExternFlag)
        {
            frameInfo.ExternFlag = 1;
        }
        else
        {
            frameInfo.ExternFlag = 0;
        }

        frameInfo.SendType   = 0;

        if(1 == VCI_Transmit(m_devtype,m_devind,m_canind,&frameInfo,1))
        {
            return true;
        }
    }
    return false;
}

bool zlgCANFunctions::zlgCANRecv()
{
    VCI_CAN_OBJ rec[20];
    int reclen ,i;


    int length = VCI_GetReceiveNum(m_devtype,m_devind,m_canind);

    if(length <= 0)
    {
        return false;
    }

    if(length > 20)
    {
        length = 20;
    }

    mutex.lock();
    if((reclen = VCI_Receive(m_devtype,m_devind,m_canind,rec,length,10))>0)
    {
        for(i = 0; i < reclen; i++)
        {
            COMM_WriteRxMessage(rec[i].ID,rec[i].Data,rec[i].DataLen);
        }
    }
    mutex.unlock();
    return true;
}

bool zlgCANFunctions::zlgCANExternFlagSet(bool flag)
{
    canExternFlag = flag;
    return true;
}
