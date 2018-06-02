#ifndef __DS708_TO_J2534_J1708CAT_H__
#define __DS708_TO_J2534_J1708CAT_H__

#include "DS708ToJ2534_J1708.h"


class CDS708ToJ2534_J1708CAT :public CDS708ToJ2534_J1708
{
public:

#define SET_SEED_CMD                    0xF0

    typedef struct {
        unsigned char SeedValidFlag; // 加密种子有效标志
        unsigned char ReqSeed;  //请求指令加密种子
        unsigned char AnsSeed;  //应答指令加密种子
        
        unsigned char EncryptKey_Mask; //加密算法掩码
        unsigned char DecryptKey_Mask; //解密算法掩码

        unsigned char EncryptCount;//KEY低四位计数，增加加密的复杂度
    }J1708CAT_ENCRYP;

    bool mEncryptTransmit;// true --加密传输数据；false--非加密
        
    J1708CAT_ENCRYP J1708CAT_EncrypDecryp;
    J1708_FRAME J1708CAT_FilterPara;
    J1708_SPECIAL_PARA  mJ1708CATSpecialPara;

    CDS708ToJ2534_J1708CAT(void);
    ~CDS708ToJ2534_J1708CAT(void);

    W_U8 GetEncryptMask(W_U8 seed,W_U8 Key);
    long SendData(CSendFrame SendFrame);
    void ParseRqeFrame(const unsigned char *data, int len);
    bool ParseAnsFrame(const unsigned char *data, int len);
    CReceiveFrame SendReceive(CSendFrame SendFrame);
    bool J1708CatSetAccessKey(W_U8 Key1,W_U8 Key2, bool flag);
    void J1708CatClearKey(void);
    void CombiningAnsFrame(const unsigned char *data, int len);
};

#endif

