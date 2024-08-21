/*----------------------------------------------------------------------------
| File        : xlCANFunctions.cpp
| Project     : Vector CAN Example 
|
| Description : Shows the basic CAN functionality for the XL Driver Library
|-----------------------------------------------------------------------------
| $Author: vissj $    $Locker: $   $Revision: 59577 $
|-----------------------------------------------------------------------------
| Copyright (c) 2012 by Vector Informatik GmbH.  All rights reserved.
|---------------------------------------------------------------------------*/


#include "xlCANFunctions.h"
#include "CanComm.h"
#include <stdio.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FALSE   0
#define TRUE    1

#define XLDEBUG(B,T)

//////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCANFunctions* CCANFunctions::_instance = 0;

CCANFunctions::CCANFunctions()
{
  m_xlChannelMask[CHAN01] = 0;
  m_xlChannelMask[CHAN02] = 0;
}

CCANFunctions::~CCANFunctions()
{

}

////////////////////////////////////////////////////////////////////////////

//! CANInit

//! Open the driver, get the channelmasks and create the RX thread.
//! 
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::CANInit()
{
  XLstatus        xlStatus = XL_ERROR;

  m_bInitDone = FALSE;

  printf("CANInit\r\n");
  xlStatus = xlOpenDriver();

  if (xlStatus != XL_SUCCESS)
  {
      printf("xlOpenDriver fail\r\n");
      return xlStatus;
  }

  // ---------------------------------------
  // Get/Set the application within VHWConf
  // ---------------------------------------
  xlStatus = canGetChannelMask();
  if ( (xlStatus) || (m_xlChannelMask[CHAN01] == 0) || (m_xlChannelMask[CHAN02] == 0) )
  {
       printf("canGetChannelMask fail\r\n");
       return XL_ERROR;
  }

  // ---------------------------------------
  // Open ONE port for both channels
  // ---------------------------------------
  xlStatus = canInit();
  if (xlStatus)
  {
      printf("canInit fail\r\n");
      return xlStatus;
  }

  xlStatus = xlSetNotification (m_xlPortHandle, &m_hMsgEvent, 1);

  m_bInitDone = TRUE;

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canGetChannelMask

//! parse the registry to get the channelmask
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::canGetChannelMask()
{
  XLstatus        xlStatus = XL_ERROR;
  char            tmp[100];

  // default values
  unsigned int  hwType     = 0;
  unsigned int  hwIndex    = 0;
  unsigned int  hwChannel  = 0;
  unsigned int  appChannel = 0;
  unsigned int  busType    = XL_BUS_TYPE_CAN;   
  unsigned int  i;
  unsigned int  chan1Found = 0;
  unsigned int  chan2Found = 0;
 
  XLdriverConfig  xlDrvConfig;

   //check for hardware:
  xlStatus = xlGetDriverConfig(&xlDrvConfig);
  if (xlStatus) return xlStatus;
  
  // we check only if there is an application registered or not.
  xlStatus = xlGetApplConfig("xlCANcontrol", CHAN01, &hwType, &hwIndex, &hwChannel, busType); 
 
  // Set the params into registry (default values...!)
  if (xlStatus) {
    XLDEBUG(DEBUG_ADV,"set in VHWConf");

    for (i=0; i < xlDrvConfig.channelCount; i++) {

      sprintf_s (tmp, sizeof(tmp), "hwType: %d, bustype: %d, hwChannel: %d, cap: 0x%x", 
        xlDrvConfig.channel[i].hwType, 
        xlDrvConfig.channel[i].connectedBusType,
        xlDrvConfig.channel[i].hwChannel,
        xlDrvConfig.channel[i].channelBusCapabilities);
      XLDEBUG(DEBUG_ADV,tmp);

      // we search not the first CAN cabs
      if ( (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN) && (appChannel < 2) ) {

        hwType    = xlDrvConfig.channel[i].hwType;
        hwIndex   = xlDrvConfig.channel[i].hwIndex;
        hwChannel = xlDrvConfig.channel[i].hwChannel;

        xlStatus = xlSetApplConfig( // Registration of Application with default settings
        "xlCANcontrol",             // Application Name
        appChannel,                 // Application channel 0 or 1
        hwType,                     // hwType  (CANcardXL...)    
        hwIndex,                    // Index of hardware (slot) (0,1,...)
        hwChannel,                  // Index of channel (connector) (0,1,...)
        busType);                   // the application is for CAN.

        m_xlChannelMask[appChannel] = xlGetChannelMask(hwType, hwIndex, hwChannel);

        appChannel++;
      }
     
    }
  }
  // application is registered, get two CAN channels which are assigned
  else {
    
    // get the first channel (check if channel is assigned)
	m_xlChannelMask[CHAN01] = xlGetChannelMask(hwType, hwIndex, hwChannel);
    sprintf_s (tmp, sizeof(tmp), "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
    XLDEBUG(DEBUG_ADV,tmp);
 
    for (i=0; i < xlDrvConfig.channelCount; i++) {

      if ((xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN01]) &&
		  (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN)) {
		chan1Found = 1;
		break;
	  }
    }
	
	if (!chan1Found) {
      sprintf_s (tmp, sizeof(tmp), "No assigned CAN in VHWConf for channel 0, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
      XLDEBUG(DEBUG_ADV,tmp);
      return XL_ERROR;
	}


    // get the second channel
    xlStatus = xlGetApplConfig("xlCANcontrol", CHAN02, &hwType, &hwIndex, &hwChannel, busType); 
    if (xlStatus) return xlStatus;

    m_xlChannelMask[CHAN02] = xlGetChannelMask(hwType, hwIndex, hwChannel);
    sprintf_s (tmp, sizeof(tmp), "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN02]);
    XLDEBUG(DEBUG_ADV,tmp);

    for (i=0; i < xlDrvConfig.channelCount; i++) {

      if ((xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN02]) &&
		  (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN)) {
		chan2Found = 1;
		break;
	  }
    }

	if (!chan2Found) {
      sprintf_s (tmp, sizeof(tmp), "No assigned CAN in VHWConf for channel 1, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
      XLDEBUG(DEBUG_ADV,tmp);
      return XL_ERROR;
	}

  }

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canInit

//! xlCANcontrol use ONE port for both channels.
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::canInit()
{
  XLstatus         xlStatus = XL_ERROR;
  XLaccess         xlPermissionMask;
  char             tmp[100];

  // ---------------------------------------
  // Open ONE port for both channels 
  // ---------------------------------------

  // calculate the channelMask for both channel 
  m_xlChannelMask_both = m_xlChannelMask[CHAN01] + m_xlChannelMask[CHAN02];
  xlPermissionMask = m_xlChannelMask_both;

  xlStatus = xlOpenPort(&m_xlPortHandle, "xlCANcontrol", m_xlChannelMask_both, &xlPermissionMask, 256, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN); 
  sprintf_s(tmp, sizeof(tmp), "xlOpenPort: PortHandle: %d; Permissionmask: 0x%I64x; Status: %d", m_xlPortHandle, xlPermissionMask, xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);

  if (m_xlPortHandle == XL_INVALID_PORTHANDLE) return XL_ERROR;
  if (xlStatus == XL_ERR_INVALID_ACCESS) return xlStatus;

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canCreateRxThread

//! set the notification and creates the thread.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::canCreateRxThread()
{
  
  XLstatus      xlStatus = XL_ERROR;


  return xlStatus;
}


////////////////////////////////////////////////////////////////////////////

//! CANGoOnBus

//! set the selected baudrate and go on bus.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANGoOnBus(unsigned long baudrate)
{
  XLstatus      xlStatus = XL_ERROR;
  char          tmp[100];

  xlStatus = xlCanSetChannelBitrate(m_xlPortHandle, m_xlChannelMask_both, baudrate);
  sprintf_s(tmp, sizeof(tmp), "SetBaudrate: %d, stat: %d", baudrate, xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);

  xlStatus = xlActivateChannel(m_xlPortHandle, m_xlChannelMask_both, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
  sprintf_s(tmp, sizeof(tmp), "ActivateChannel, stat: %d",  xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANGoOffBus

//! Deactivate the channel
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANGoOffBus()
{
  XLstatus      xlStatus = XL_ERROR;
  char          tmp[100];

  xlStatus = xlDeactivateChannel(m_xlPortHandle, m_xlChannelMask_both);
  sprintf_s(tmp, sizeof(tmp), "DeactivateChannel, stat: %d",  xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANSend

//! transmit a CAN message to the selected channel with the give values.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANSend(int channel)
{
  XLevent        xlEvent;
  XLstatus       xlStatus;
  T_CanFrameType TxFrame;
  unsigned int   messageCount = 1;

  mutex.lock();
  TxFrame = COMM_ReadTxMessage();
  mutex.unlock();

  if(TxFrame.len != 0)
  {
      xlEvent.tag                 = XL_TRANSMIT_MSG;
      xlEvent.tagData.msg.id      = (unsigned int)  TxFrame.canId;
      xlEvent.tagData.msg.dlc     = (unsigned short)TxFrame.len;
      xlEvent.tagData.msg.flags   = 0;
      xlEvent.tagData.msg.data[0] = (unsigned char) TxFrame.buffer[0];
      xlEvent.tagData.msg.data[1] = (unsigned char) TxFrame.buffer[1];
      xlEvent.tagData.msg.data[2] = (unsigned char) TxFrame.buffer[2];
      xlEvent.tagData.msg.data[3] = (unsigned char) TxFrame.buffer[3];
      xlEvent.tagData.msg.data[4] = (unsigned char) TxFrame.buffer[4];
      xlEvent.tagData.msg.data[5] = (unsigned char) TxFrame.buffer[5];
      xlEvent.tagData.msg.data[6] = (unsigned char) TxFrame.buffer[6];
      xlEvent.tagData.msg.data[7] = (unsigned char) TxFrame.buffer[7];

      if (CanFrameType == XL_CAN_EXT)
      {
         xlEvent.tagData.msg.id |= XL_CAN_EXT_MSG_ID;
      }

      xlStatus = xlCanTransmit(m_xlPortHandle, m_xlChannelMask[channel], &messageCount, &xlEvent);

      if(xlStatus)
      {
          return false;
      }
      return true;
  }

  return false;

}

XLstatus CCANFunctions::CANRecv(int channel)
{
    XLstatus        xlStatus;
    XLevent         xlEvent;
    unsigned int    msgsrx = 1;

    channel = 1;

    mutex.lock();
    msgsrx = 1;
    xlStatus = xlReceive(m_xlPortHandle, &msgsrx, &xlEvent);

    if (xlStatus != XL_ERR_QUEUE_IS_EMPTY )
    {
        if (CanFrameType == XL_CAN_EXT)
        {
            COMM_WriteRxMessage(xlEvent.tagData.msg.id&~XL_CAN_EXT_MSG_ID,xlEvent.tagData.msg.data,xlEvent.tagData.msg.dlc);
        }
        else
        {
           COMM_WriteRxMessage(xlEvent.tagData.msg.id,xlEvent.tagData.msg.data,xlEvent.tagData.msg.dlc);
        }
    }

    mutex.unlock();
    return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANResetFilter

//! Reset the acceptancefilter
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANResetFilter()
{
  XLstatus      xlStatus;
  char          tmp[100];

  xlStatus = xlCanResetAcceptance(m_xlPortHandle, m_xlChannelMask_both, XL_CAN_STD);
  sprintf_s(tmp, sizeof(tmp), "CanResetAcceptance, stat: %d",  xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANSetFilter

//! Reset the acceptancefilter
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANSetFilter(unsigned long first_id, unsigned long last_id)
{
  XLstatus      xlStatus;
  char          tmp[100];
  
  // because there all filters open, we close all.
  xlStatus = xlCanSetChannelAcceptance(m_xlPortHandle, m_xlChannelMask_both, 0xFFF, 0xFFF, XL_CAN_STD);
  sprintf_s(tmp, sizeof(tmp), "CanSetChannelAcceptance, stat: %d",  xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);
  
  // and now we can set the acceptance filter range.
  xlStatus = xlCanAddAcceptanceRange(m_xlPortHandle, m_xlChannelMask_both, first_id, last_id);
  sprintf_s(tmp, sizeof(tmp), "CanAddAcceptanceRange, firstID: %d, lastID: %d, stat: %d",  first_id, last_id, xlStatus);
  XLDEBUG(DEBUG_ADV, tmp);
  
  
  return xlStatus;
}

///////////////////////////////////////////////////////////////////////////

//! ShowLicenses

//! Reads licenses from the selected channels and displays it.
//!
////////////////////////////////////////////////////////////////////////////
XLstatus CCANFunctions::ShowLicenses()
{
  XLstatus xlStatus;
  char licAvail[2048];
  char strtmp[512];


  // Show available licenses
  XLlicenseInfo licenseArray[1024];
  unsigned int licArraySize = 1024;
  xlStatus = xlGetLicenseInfo(m_xlChannelMask[CHAN01] | m_xlChannelMask[CHAN02], licenseArray, licArraySize);
  if (xlStatus == XL_SUCCESS) {
    strcpy_s(licAvail, sizeof(licAvail), "Licenses found:\n\n");
    for (unsigned int i = 0; i < licArraySize; i++) {
      if (licenseArray[i].bAvailable) {
        sprintf_s(strtmp, sizeof(strtmp), "ID 0x%03x: %s\n", i, licenseArray[i].licName);
        if ((strlen(licAvail) + strlen(strtmp)) < sizeof(licAvail)) {
          strcat_s(licAvail, sizeof(licAvail), strtmp);
        }
        else {
          // Too less memory for printing licenses
          sprintf_s(licAvail, sizeof(licAvail), "Internal Error: String size in CCANFunctions::ShowLicenses() is too small!");
          xlStatus = XL_ERROR;
        }
      }
    }
  }
  else {
    sprintf_s(licAvail, sizeof(licAvail), "Error %d when calling xlGetLicenseInfo()!", xlStatus);
  }
  
  return xlStatus;
}

XLstatus CCANFunctions::CANSetFrameType(char frameType)
{
    CanFrameType = frameType;
    return XL_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////

//! RxThread

//! thread to readout the message queue and parse the incoming messages
//!
////////////////////////////////////////////////////////////////////////////


