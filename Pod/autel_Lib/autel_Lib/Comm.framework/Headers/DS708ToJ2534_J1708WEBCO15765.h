#ifndef __DS708_TO_J2534_J1708WEBCO15765_H__
#define __DS708_TO_J2534_J1708WEBCO15765_H__

#include "DS708ToJ2534_J1708.h"


class CDS708ToJ2534_J1708WEBCO15765 :public CDS708ToJ2534_J1708
{
public:

    CDS708ToJ2534_J1708WEBCO15765(void);
    ~CDS708ToJ2534_J1708WEBCO15765(void);

    CReceiveFrame SendReceive(CSendFrame SendFrame);
    W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);
};

#endif


