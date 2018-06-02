#ifndef __DS708_TO_J2534_J1708_H__
#define __DS708_TO_J2534_J1708_H__

#include "DS708ToJ2534Base.h"



class CDS708ToJ2534_J1708 :public CDS708ToJ2534Base
{
public:
    #define MAX_J1708_ECU_LEN       21
    #define MAX_J1708_TE_LEN           4095
    #define KEEP_LINK_HEAD          "\xFF\xFF\xFF\xFF"  

    #define ALLISON_REQ_HEAD            0x34
    #define ALLISON_ANS_HEAD            0x16
    
    CDS708ToJ2534_J1708(void);
    ~CDS708ToJ2534_J1708(void);
    W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
        W_U8 uIoOutputPort,
        W_U8 ucWorkVoltage = 12,
        W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
        W_FLOAT fCompareVoltage = 0.0
        );

    enum 
    {
        //Req: AC + FE + MID + LEN
        //Ans: MID + FE + AC + LEN
        MANUDEF_MODE0_NORMAL=0,                       //0-normal mode &webco

        //格式1
        //Req: AC + FE + MID + 04 + Key1 + 80 + PID + MID + CheckSum
        //Ans: MID + FE + AC/7F + Len + Key2 + PID + DATA + CheckSum
        //格式2
        //Req: MID + FE + AC + Len + Key2 + DATA + CheckSum 
        //Ans: MID + FE + AC/7F + Len + Key2 + DATA + CheckSum
        MANUDEF_MODE1_LEN_KEY_DATA=1,        //volvo-1&Bendix-1 ,如果没有找到设置的KEY，将和Normal校验方式一致

        //Req: AC + FE + MID + Key + DATA + CS
        //Ans: MID + C4 + AC + ** + 80 + DATA + CS
        MANUDEF_MODE2_KEY=2,                            //webco-3

        //Req: AC + FE + MID + 80 + PID + DATA CS
        //Ans: MID + FE + AC + PID + DATA + CS
        MANUDEF_MODE3_PID=3,                            //Bendix

        //Req: B6 + FE + MID +PID + LEN +DATA +cs
        //Ans: MID +FE + B6 +PID + LEN +DATA +cs
        MANUDEF_MODE4_PID_LEN=4,                            //Eaton

        //Req: AC + FE + MID + DATA + CS    
        //Ans: MID + FE + AC + DATA + CS	
        MANUDEF_MODE5_DATA=5,                            //Webco-1

        //请求：AC + FE + MID + LEN + 72(固定值) + DATA + CS
        //回复：MID + FE + AC + LEN + 72(固定值) + DATA + CS     DATA前部分数据与发送的DATA相同
        // 1.
        //Req:AC FE 80 04 72 52 01 01 0C 
        //009:80 FE AC 0B 72 52 01 01 00 00 C6 31 34 56 78 2B
        // 2. 未收到数据 ans.BYTE8 != 0x00,一直重发
        //AF FE 80 04 72 58 00 00 08
        //80 FE AC 07 72 58 00 00 09 01 28 D3
        // 3. 兼容普通模式，需要设置KEY(6D)
        //AC FE 80 02 6D 30 37      
        //80 FE AC 03 6D 30 00 36
        MANUDEF_MODE6_LEN_72_DATA=6,                            //Maxxforce  2016-4-16  used for maxxforce

        //发送头字节34
        //接收头字节 16

        //第二字节为 21 A1 B1 只过滤头和第二字节
        //第二字节为51 61 过滤头和第二、第三字节
        //第二字节为81 过滤头和第二、第三、第四字节

        //第二次节为10	过滤头和第二次字为11

        //16 Fx系列数据，与标准1708总线产生数据一样，可以监听

        //Req:34 10 DB 60 81
        //000:16 11 12 56 3C 77 8C 00 43 44 37 30 50 30 31 CE 59 6C

        MANUDEF_MODE7_34_16=7,                            //Allison

        //Req: AC + FE + MID + LEN
        //Ans: MID + FE + AC + LEN
        MANUDEF_MODE8_KEY=8                            //2016-06-06 quss add
    };
    
    enum {
        // 回复属性
        J1708_NONE = 0,        // 默认属性
        J1708_FORMAT_1B,       // 回复1字节
        J1708_FORMAT_2B,       // 回复2字节
        J1708_FORMAT_SPECIFY,  // 回复指定长度
        
        // 命令属性
        J1708_CMD_ONE_PID,     // 单个 pid
        J1708_CMD_MORE_PID,    // 多个 pid
        J1708_CMD_BROADCAST,   // 广播
        J1708_CMD_USER1,       // 用户自定义1
        J1708_CMD_USER2,       // 用户自定义2
        J1708_CMD_CLEANCODE,   // 清除故障码
        J1708_CMD_MONITOR,     // 监听

        //MODE属性
        J1708_MORE_CMD_MODE,   // 多包命令模式 11
        J1708_MONITOR_MODE,    // 监听模式                12
        J1708_SEND_RECEIVE_MODE,                              // 13
        J1708_THREAD_SEND_MODE                                // 14
    };

    typedef struct {
        unsigned char mid;  //请求MID
        unsigned char pid;  //请求PID
        unsigned char spid; //被请求PID
        unsigned char smid; //被请示MID

        unsigned char TempAnsKey; //请求帧对应的KEY
        unsigned char TempAnsPID; //请求帧对应的PID
        unsigned char CheckPIDFlag;// 是否需要校验PID
        unsigned char CheckKeyFlag; //是否需要过滤KEY和PID
    }J1708_FRAME;

    typedef struct {
        unsigned char s_no;  //开始序号
        unsigned char c_no;  //当前序号
        unsigned int llen;   //指定长度
        unsigned int dlen;   //数据长度
        unsigned int len;    //实际长度
        unsigned char buff[MAX_J1708_TE_LEN];
    }J1708_PACKAGE;

    typedef struct {
        unsigned char priority;
        unsigned char state;
        unsigned int c_index;
        unsigned int s_index;
        unsigned int cnt;
    }J1708_CMD_BUFFER;
    
    typedef struct {
        unsigned char state;   //状态
        unsigned char cmd;     //命令
        unsigned char req_cnt; //请求PID个数
        unsigned char ans_flg; //应答PID标志
        unsigned char id;      //PID补充
        unsigned int len;
        unsigned long start_tim;
        unsigned long total_tim;
        bool    more_data;

        J1708_PACKAGE package;
        J1708_FRAME frame[6];
        unsigned char send[MAX_J1708_TE_LEN];
    }J1708_DATA, *PJ1708_DATA;

#define MAX_KEY_NUM             256

    typedef struct
    {
        unsigned char Req_Key;
        unsigned char Ans_Key;
        unsigned char flag; //0 无pid；1有pid
    }J1708_KEY,*PJ1708_KEY;
    
    typedef struct 
    {       
        bool ManuDefLenStatus;  // J 1708厂商自定义格式长度标志，false-不存在长度域;true-存在长度域 20160304 quss
        unsigned int SetKeysCount;
        
        J1708_KEY J1708KeyBuff[MAX_KEY_NUM];
        
    }J1708_SPECIAL_PARA, *PJ1708_SPECIAL_PARA;
      
    CReceiveFrame SendReceive(CSendFrame SendFrame);

    W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

    /*-----------------------------------------------------------------------------
    功    能：设置过滤条件或帧长识别方法
    参数说明：FilterOrFrameReceive        过滤条件或帧长识别方法参数
    返 回 值：错误代码
    说    明：调用者：CEcuInterface::SetProtocol()
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);
    
    virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);

    bool Is7F78(CBinary bin);

    void ThreadHandle(void);
    
    void SetMode(int mode);
        
    long ClearFilter(void);
    
    long StartFilter(CBinary binMask, CBinary binPattern, CBinary binFlowCtl);

    CReceiveFrame GetSendReceiveData(void);
    
    bool StartMonitor(map<unsigned long, CMonitorPara> CMonitorParameter);
    
    bool StartMonitor(void);

    bool StopMonitor(void);

    unsigned long GetMonitorDataSize(void);
    
    CReceiveFrame GetMonitorData(void);

    void ClearMonitorData(void);
    
    unsigned long GetMonitorState(void);

    map<unsigned long, CMonitorPara> GetRemainPgn(void);

    int GetKeepLinkState(void);

    bool J1708SetKey(W_U8 Key1,W_U8 Key2, W_U8 flag);

    void J1708SetKey(W_U8 Key1);

    void J1708ClearKey(void);

    void J1708SetLength(bool status);

//private:
    void CheckKeepLinkState(unsigned char state);
    int AnsSiz(const unsigned char data);
    long SendData(CSendFrame SendFrame);
    long RecvData(unsigned long &ulMsgNum, PPASSTHRU_MSG pMsg);
    bool ParseMonitorData(const unsigned char *data, int len);
    bool ParseAnsFrame(const unsigned char *data, int len);
    void ParseRqeFrame(const unsigned char *data, int len);
    bool ErgodAnsFrame(const unsigned char *data, int len);
    void CombiningAnsFrame(const unsigned char *data, int len);
    bool CombiningAnsPackage(const unsigned char *data, int len);
    void CleanPackagePara(void);
    void AddSendBufferMap(const unsigned char *data, int len);
    void AddMonitorMap(const unsigned char *data, int len);
    
    map<unsigned long, CMonitorPara> RecvPara; //上位机下发MAP
    map<unsigned long, CMonitorPara> Updata; //更新PID MAP
    map<unsigned long, CBinary> Monitor;  //监听数据MAP
    //map<unsigned long, CBinary> SendBuffer;    //上位机获取MAP
    map<unsigned long, CBinary> SendRecviceBuffer;    //上位机获取MAP
    map<unsigned long, CBinary> mBroadcastBuffer;    //广播多帧缓存
    map<unsigned long, CBinary> mMonitorBroadcastBuffer;    //监听广播多帧缓存
    map<unsigned long, CMonitorPara>::iterator Piter;

    int J1708Mode;
    int J1708SendMode;
    CBinary       FilterByte; //过滤设置
    J1708_DATA J1708Data;
    J1708_CMD_BUFFER J1708Cmd;
    bool RecvFlg;
    bool MonitorFlg;
    bool SendFlg;
    bool mClearMonitorFlg;
    long SendCnt;
    long CycleCnt;
    long SendTimPara;     //发送时间参数  200
    long RecvTimPara;     //接收时间参数  0
    unsigned long RecvOvertime;    //接收超时时间  p2
    unsigned long ToltalOvertime;  //总超时时间    p5
    unsigned long SendReceiveTim;
    //unsigned long m_Lastsendtime;
    long ThreadState;
    bool ThreadCmdState;
    bool KeepLinkErrFlg;
    bool mKeepLinkOn;
    bool mCheckKey72ReturnStatus;
    bool mReTransfFlag;
    unsigned int mMapOperatcnt;
    unsigned int mManuMonitorCount;//20160416 quss  厂商自定义格式计数
    unsigned int mManuSendCount;//20160416 quss  厂商自定义格式需要发送的数目
    unsigned int mAllisonFilterLen;  //20160425 Allison 过滤长度
    unsigned char mAllisonPacketNum; //20160427  用来记录一个序号，在发送时需要强制转换
    
    J1708_SPECIAL_PARA  mJ1708SpecialPara;// J 1708厂商自定义格式参数 20160304 quss
    unsigned char mJ1708SpecialMode;
};

#endif


