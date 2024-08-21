#ifndef _USB_CAN_DRIVER_H
#define _USB_CAN_DRIVER_H
#ifdef __cplusplus
extern "C"
{
#endif

#define CAN_MSG_QUEUE_LEN  500

typedef struct
{
    unsigned int  canId;
    unsigned char len;
    unsigned char buffer[8];
}T_CanFrameType;

typedef struct
{
    T_CanFrameType msg[CAN_MSG_QUEUE_LEN];
    unsigned char rd_index;
    unsigned char wr_index;
    unsigned char full;
}T_CanMsgQueueType;


typedef enum
{
    DEVICE_USBCAN_II,
    DEVICE_USBCAN_E_2E,
    DEVICE_CANCASE
}DeviceType;

extern DeviceType deviceType;

extern void CanComm_Init(void);
extern void COMM_WriteRxMessage(unsigned int canID,unsigned char *pbuff,unsigned char dlc);
extern T_CanFrameType COMM_ReadTxMessage(void);

extern void App_SendUdsMsgToCOMM(unsigned int can_id,unsigned char *buffer,unsigned char length);
extern void App_SendAppMsgToCOMM(unsigned int can_id,unsigned char *buffer,unsigned char length);

extern unsigned char App_ReadAppMsgFromCOMM(unsigned int *can_id,unsigned char *buffer);
extern unsigned char App_ReadUdsMsgFromCOMM(unsigned int *can_id,unsigned char *buffer);

extern unsigned char App_ReadAllMessage(unsigned int *can_id,unsigned char *buffer);

extern void CanComm_set_App_rx_id(int can_id);

#ifdef __cplusplus
}
#endif


#endif //_USB_CAN_DRIVER_H
