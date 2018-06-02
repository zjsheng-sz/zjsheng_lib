#ifndef __DS708_TO_J2534_J1708_MAXXFORCE_H__
#define __DS708_TO_J2534_J1708_MAXXFORCE_H__

#include "DS708ToJ2534_J1708.h"



class CDS708ToJ2534_J1708MAXXFORCE :public CDS708ToJ2534_J1708
{
public:

    CDS708ToJ2534_J1708MAXXFORCE(void);
    ~CDS708ToJ2534_J1708MAXXFORCE(void);


      
    CReceiveFrame SendReceive(CSendFrame SendFrame);

    bool ParseAnsFrame(const unsigned char *data, int len);
    void ParseRqeFrame(const unsigned char *data, int len);

private:
    bool mCheckKey72ReturnStatus;
    bool mReTransfFlag;
};

#endif


