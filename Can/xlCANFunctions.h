/*----------------------------------------------------------------------------
| File        : xlCANFunctions.h
| Project     : Vector CAN Example 
|
| Description : shows the basic CAN functionality for the XL Driver Library
|-----------------------------------------------------------------------------
| $Author: vishsh $    $Locker: $   $Revision: 36678 $
|-----------------------------------------------------------------------------
| Copyright (c) 2004 by Vector Informatik GmbH.  All rights reserved.
|---------------------------------------------------------------------------*/

#if !defined(AFX_XLCANFUNCTIONS_H__48DFA4A9_72B2_48FE_80D5_D318A80C4B3A__INCLUDED_)
#define AFX_XLCANFUNCTIONS_H__48DFA4A9_72B2_48FE_80D5_D318A80C4B3A__INCLUDED_

#include "vxlapi.h"

#define CHAN01 0
#define CHAN02 1


#include <QMutex>
class CCANFunctions  
{
public:
	CCANFunctions();
	virtual ~CCANFunctions();

    static CCANFunctions* Instance()
    {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new CCANFunctions;
            }
        }
        return _instance;
    }
  XLstatus CANInit();
  XLstatus CANGoOnBus(unsigned long baudrate);
  XLstatus CANGoOffBus();
  XLstatus CANSend(int channel);
  XLstatus CANRecv(int channel);
  XLstatus CANResetFilter();
  XLstatus CANSetFilter(unsigned long first_id, unsigned long last_id);
  XLstatus ShowLicenses();
  XLstatus CANSetFrameType(char frameType);
  

private:
  XLstatus         canGetChannelMask();
  XLstatus         canInit();
  XLstatus         canCreateRxThread();

  XLaccess         m_xlChannelMask[2];        //!< we support only two channels
  XLportHandle     m_xlPortHandle;            //!< and one port
  XLaccess         m_xlChannelMask_both;
  XLhandle         m_hMsgEvent;
  int              m_bInitDone;

  static CCANFunctions* _instance;
  QMutex mutex;
  char            CanFrameType;
};


#endif // !defined(AFX_XLCANFUNCTIONS_H__48DFA4A9_72B2_48FE_80D5_D318A80C4B3A__INCLUDED_)
