/*********************************************************************
* Copyright (c),2008-2068,CJAE Co.,Ltd.ALL Rights Reserverd
* File Name:
* Auther:wzh
* Version:V0.1
* Date:
* Descriptions:
* History:
*
**********************************************************************/
#include "Can/ControlCAN.h"
#include "CanComm.h"
#include <string.h>

#define CanID_UDS_Base    0x700 //物理寻址
#define CanID_NM_Base     0x400 //NM基地址


int app_can_rx_id = 0;

DeviceType deviceType;
//------------------------------------------------------
T_CanMsgQueueType g_tCanAppMsgRx ;
T_CanMsgQueueType g_tCanAppMsgTx;
T_CanMsgQueueType g_tCanUdsMsgRx;
T_CanMsgQueueType g_tCanUdsMsgTx;
T_CanMsgQueueType g_tCanAllMsg;
void CanComm_Init(void)
{
   g_tCanUdsMsgRx.rd_index = 0;
   g_tCanUdsMsgRx.wr_index = 0;

   g_tCanUdsMsgTx.rd_index = 0;
   g_tCanUdsMsgTx.wr_index = 0;

   //g_tCanAllMsg.rd_index = 0;
   //g_tCanAllMsg.wr_index = 0;
}

void MemeryCopy(unsigned char *pDesc,unsigned char *pSrc,unsigned char len)
{
    while(len--)
    {
        *(pDesc+len) = *(pSrc + len);
    }
}

void COMM_WriteRxMessage(unsigned int canID,unsigned char *pbuff,unsigned char dlc)
{
    unsigned char i = 0;
   /* UDS报文 */
   if((canID >= CanID_UDS_Base)&&(canID <= CanID_UDS_Base + 0xFF))
    {
        if(!g_tCanUdsMsgRx.full)
        {
            g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.wr_index].canId  = canID;
            g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.wr_index].len    = dlc;

            for(i = 0 ; i < 8 ; i++)
            {
                g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.wr_index].buffer[i] = pbuff[i];
            }
            if(++g_tCanUdsMsgRx.wr_index >= CAN_MSG_QUEUE_LEN)
            {
                g_tCanUdsMsgRx.wr_index = 0;
            }
            if(g_tCanUdsMsgRx.wr_index == g_tCanUdsMsgRx.rd_index)
            {
                g_tCanUdsMsgRx.full = 1;
            }
        }
        if(!g_tCanAllMsg.full)
        {
            g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].canId    = canID;
            g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].len      = dlc;

            for(i = 0 ; i < 8 ; i++)
            {
                g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].buffer[i] = pbuff[i];
            }

            if(++g_tCanAllMsg.wr_index >= CAN_MSG_QUEUE_LEN)
            {
                g_tCanAllMsg.wr_index = 0;
            }
            if(g_tCanAllMsg.wr_index == g_tCanAllMsg.rd_index)
            {
                g_tCanAllMsg.full = 1;
            }
        }
    }
    /* APP&NM */
    else if(canID == app_can_rx_id)
    {
        if(!g_tCanAppMsgRx.full)
        {
            g_tCanAppMsgRx.msg[g_tCanAppMsgRx.wr_index].canId  = canID;
            g_tCanAppMsgRx.msg[g_tCanAppMsgRx.wr_index].len    = dlc;

            for(i = 0 ; i < 8 ; i++)
            {
                g_tCanAppMsgRx.msg[g_tCanAppMsgRx.wr_index].buffer[i] = pbuff[i];
            }
            if(++g_tCanAppMsgRx.wr_index >= CAN_MSG_QUEUE_LEN)
            {
                g_tCanAppMsgRx.wr_index = 0;
            }
            if(g_tCanAppMsgRx.wr_index == g_tCanAppMsgRx.rd_index)
            {
                g_tCanAppMsgRx.full = 1;
            }
        }
    }//end of else
}

T_CanFrameType COMM_ReadTxMessage(void)
{
    T_CanFrameType TxFrame;

    TxFrame.len = 0;

    if ((g_tCanUdsMsgTx.rd_index != g_tCanUdsMsgTx.wr_index)
       ||(g_tCanUdsMsgTx.full > 0))
    {
        g_tCanUdsMsgTx.full = 0;
        //发送
       TxFrame.canId = g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.rd_index].canId;
       MemeryCopy(TxFrame.buffer,g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.rd_index].buffer,8);
       TxFrame.len = g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.rd_index].len;
       if (++g_tCanUdsMsgTx.rd_index >= CAN_MSG_QUEUE_LEN)
       {
           g_tCanUdsMsgTx.rd_index = 0;
       }
    }
    else if ((g_tCanAppMsgTx.rd_index != g_tCanAppMsgTx.wr_index)
            || (g_tCanAppMsgTx.full > 0))
    {
       g_tCanAppMsgTx.full = 0;
       //发送
       TxFrame.canId = g_tCanAppMsgTx.msg[g_tCanAppMsgTx.rd_index].canId;
       MemeryCopy(TxFrame.buffer,g_tCanAppMsgTx.msg[g_tCanAppMsgTx.rd_index].buffer,8);
       TxFrame.len = g_tCanAppMsgTx.msg[g_tCanAppMsgTx.rd_index].len;
       if (++g_tCanAppMsgTx.rd_index >= CAN_MSG_QUEUE_LEN)
       {
           g_tCanAppMsgTx.rd_index = 0;
       }
    }

    return TxFrame;
}

/***************************************************************
**	Function Name	:	AppReadCanMsgFromCOMM
**	Description		:	应用程序从队列中读取应用报文
**	Input parameters:	NONE
**	Return Value	:	NONE
**	Version			:	V0.1
**	Author			:   WZH
***************************************************************/
unsigned char App_ReadAppMsgFromCOMM(unsigned int *can_id,unsigned char *buffer)
{
    unsigned char i = 0;
    unsigned char dlc;
    if ((g_tCanAppMsgRx.rd_index != g_tCanAppMsgRx.wr_index)
            || (g_tCanAppMsgRx.full > 0))
        {//有报文
            g_tCanAppMsgRx.full = 0;//clear
            *can_id = g_tCanAppMsgRx.msg[g_tCanAppMsgRx.rd_index].canId;
            dlc = g_tCanAppMsgRx.msg[g_tCanAppMsgRx.rd_index].len;
            for(i=0;i<8;i++)
            {
               buffer[i] = g_tCanAppMsgRx.msg[g_tCanAppMsgRx.rd_index].buffer[i];
            }
            if (++g_tCanAppMsgRx.rd_index >= CAN_MSG_QUEUE_LEN)
            {
                g_tCanAppMsgRx.rd_index = 0;
            }
            return dlc;
        }

    return 0;
}

unsigned char App_ReadAllMessage(unsigned int *can_id,unsigned char *buffer)
{
    unsigned char i = 0;
    unsigned char dlc;
    if ((g_tCanAllMsg.rd_index != g_tCanAllMsg.wr_index)
            || (g_tCanAllMsg.full > 0))
        {//有报文
            g_tCanAllMsg.full = 0;//clear
            *can_id = g_tCanAllMsg.msg[g_tCanAllMsg.rd_index].canId;
            dlc = g_tCanAllMsg.msg[g_tCanAllMsg.rd_index].len;

            for(i = 0 ; i < 8 ; i++)
            {
               buffer[i] = g_tCanAllMsg.msg[g_tCanAllMsg.rd_index].buffer[i];
            }
            if (++g_tCanAllMsg.rd_index >= CAN_MSG_QUEUE_LEN)
            {
                g_tCanAllMsg.rd_index = 0;
            }
            return dlc;
        }

    return 0;
}
/***************************************************************
**	Function Name	:	App_ReadUdsMsgFromCOMM
**	Description		:	应用程序从队列中读取UDS报文
**	Input parameters:	NONE
**	Return Value	:	NONE
**	Version			:	V0.1
**	Author			:   WZH
***************************************************************/
unsigned char App_ReadUdsMsgFromCOMM(unsigned int *can_id,unsigned char *buffer)
{
    unsigned char i = 0;
    unsigned char dlc = 0;
    if ((g_tCanUdsMsgRx.rd_index != g_tCanUdsMsgRx.wr_index)
        || (g_tCanUdsMsgRx.full > 0))
    {//有报文
      g_tCanUdsMsgRx.full = 0; //clear

      *can_id = g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.rd_index].canId;
      dlc = g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.rd_index].len;
      for(i=0;i<8;i++)
      {
         buffer[i] = g_tCanUdsMsgRx.msg[g_tCanUdsMsgRx.rd_index].buffer[i];
      }

      if(++g_tCanUdsMsgRx.rd_index >= CAN_MSG_QUEUE_LEN)
      {
         g_tCanUdsMsgRx.rd_index = 0;
      }

      return dlc;
    }

  return 0;
}
/***************************************************************
**	Function Name	:	App_SendAppMsgToCOMM
**	Description		:	插入应用报文到队列中去
**	Input parameters:	NONE
**	Return Value	:	NONE
**	Version			:	V0.1
**	Author			:   WZH
***************************************************************/
void App_SendAppMsgToCOMM(unsigned int can_id,unsigned char *buffer,unsigned char length)
{
    unsigned char i = 0;

    if(!g_tCanAppMsgTx.full)
    {
        g_tCanAppMsgTx.msg[g_tCanAppMsgTx.wr_index].canId = can_id;
        g_tCanAppMsgTx.msg[g_tCanAppMsgTx.wr_index].len = length;
        for( i = 0 ; i < length ; i++)
        {
          g_tCanAppMsgTx.msg[g_tCanAppMsgTx.wr_index].buffer[i] = buffer[i];
        }

        if (++g_tCanAppMsgTx.wr_index >= CAN_MSG_QUEUE_LEN)
        {
            g_tCanAppMsgTx.wr_index = 0;
        }
        if (g_tCanAppMsgTx.wr_index == g_tCanAppMsgTx.rd_index)
        {
            g_tCanAppMsgTx.full = 1;
        }
    }
    if(!g_tCanAllMsg.full)
    {
        g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].canId  = can_id;
        g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].len    = length;
        MemeryCopy(g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].buffer,buffer,8);
        if(++g_tCanAllMsg.wr_index >= CAN_MSG_QUEUE_LEN)
        {
            g_tCanAllMsg.wr_index = 0;
        }
        if(g_tCanAllMsg.wr_index == g_tCanAllMsg.rd_index)
        {
            g_tCanAllMsg.full = 1;
        }
    }
}
/***************************************************************
**	Function Name	:	App_SendUdsMsgToCOMM
**	Description		:	插入UDS报文到队列中区
**	Input parameters:	NONE
**	Return Value	:	NONE
**	Version			:	V0.1
**	Author			:   WZH
***************************************************************/
void  App_SendUdsMsgToCOMM(unsigned int can_id,unsigned char *buffer,unsigned char length)
{
    unsigned char i = 0;

    if(!g_tCanUdsMsgTx.full)
    {
        g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.wr_index].canId = can_id;
        g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.wr_index].len = length;
        for( i = 0 ; i < length ; i++)
        {
          g_tCanUdsMsgTx.msg[g_tCanUdsMsgTx.wr_index].buffer[i] = buffer[i];
        }

        if (++g_tCanUdsMsgTx.wr_index >= CAN_MSG_QUEUE_LEN)
        {
            g_tCanUdsMsgTx.wr_index = 0;
        }
        if (g_tCanUdsMsgTx.wr_index == g_tCanUdsMsgTx.rd_index)
        {
            g_tCanUdsMsgTx.full = 1;
        }
    }

    if(!g_tCanAllMsg.full)
    {
        g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].canId  = can_id;
        g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].len    = length;
        MemeryCopy(g_tCanAllMsg.msg[g_tCanAllMsg.wr_index].buffer,buffer,8);
        if(++g_tCanAllMsg.wr_index >= CAN_MSG_QUEUE_LEN)
        {
            g_tCanAllMsg.wr_index = 0;
        }
        if(g_tCanAllMsg.wr_index == g_tCanAllMsg.rd_index)
        {
            g_tCanAllMsg.full = 1;
        }
    }
}

void CanComm_set_App_rx_id(int can_id)
{
    app_can_rx_id = can_id;
}
