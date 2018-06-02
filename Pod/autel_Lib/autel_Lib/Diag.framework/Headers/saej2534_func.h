#ifndef SAE_J2534_FUNC
#define SAE_J2534_FUNC

#define MAX_MESSAGE_SIZE    4128

#define FILTER_PERIOD_MSG_DATA_SIZE 12

#define ALIGN_FOUR_BYTES(a) (a += ((~a + 1) & 0x03))

#define J_INT_4       int
#define J_UINT_4      unsigned int
//苹果的long是8字节 安卓的32位下是4字节，为了统一 而使用int

#define J_INT_8       long
#define J_UINT_8      unsigned long 


//用于接口的，接口仍然使用这个
#define J_EXPORT_IN_8         long
#define J_EXPORT_U_IN_8       unsigned long

#ifndef __cplusplus
typedef enum
{
    false,
    true
}bool;
#endif

typedef struct{
    J_UINT_4 ulSize;
    J_UINT_4 ulSerialNum;
    J_UINT_4 ulChannelID;
    J_UINT_4 ulOperiationMode;
    J_UINT_4 ulFunction;
}PACKET_HEAD, *PPACKET_HEAD;

typedef struct {
    J_UINT_4 ProtocolID;			/* vehicle network protocol */
    J_UINT_4 RxStatus;				/* receive message status */
    J_UINT_4 TxFlags;				/* transmit message flags */
    J_UINT_4 Timestamp;			/* receive message timestamp(in microseconds) */
    J_UINT_4 DataSize;				/* byte size of message payload in the Data array */
    J_UINT_4 ExtraDataIndex;		/* start of extra data(i.e. CRC, checksum, etc) in Data array */
}MSG_HEAD, *PMSG_HEAD;

typedef struct {
	MSG_HEAD stMsgHead;
	unsigned char Data[MAX_MESSAGE_SIZE];			/* message payload or data */
} PASSTHRU_MSG, *PPASSTHRU_MSG;

typedef struct {
    J_UINT_4 NumOfBytes;			 /* Number of functional addresses in array */
    unsigned char *BytePtr;				/* pointer to functional address array */
} SBYTE_ARRAY, *PSBYTE_ARRAY;

typedef struct {
    J_UINT_4 Parameter;			/* Name of configuration parameter */
    J_UINT_4 Value;				/* Value of configuration parameter */
} SCONFIG, *PSCONFIG;

typedef struct {
    J_UINT_4 NumOfParams;			/* size of SCONFIG array */
    SCONFIG *ConfigPtr;					/* array containing configuration item(s) */
} SCONFIG_LIST, *PSCONFIG_LIST;

typedef struct {
    J_UINT_4 TimeInterval;
    J_UINT_4 Condition;
    PASSTHRU_MSG RepeatMsgData[3];
}REPEAT_MSG_SETUP, *PREPEAT_MSG_SETUP;

typedef struct
{
    J_UINT_4 Parameter;			 /* name of parameter */
    J_UINT_4 Value;				 /* value of the parameter */
    J_UINT_4 Supported;			 /* support for parameter */
} SPARAM, *PSPARAM;

typedef struct
{
    J_UINT_4 NumOfParams;			/* number of SPARAM elements */
    SPARAM *ParamPtr;					/* array of SPARAM */
} SPARAM_LIST, *PSPARAM_LIST;


typedef struct
{
    J_UINT_4 ft_type;	
    J_UINT_4 ft_total_size;
    J_UINT_4 ft_pack_size;
    J_UINT_4 ft_pack_no;	
    //J_UINT_4 crc;
}DATA_FILE, *PDATAFILE;


/********************************************************
*  FactOry reserved config
*********************************************************/
#define MAX_FACTORY_CFG_SIZE		32
typedef struct {
    J_UINT_4 ip_mode;				/* 1: manual get ip or 0: auto get ip */
    J_UINT_4 net_mode;				/* 1: wirless 0:wire */
    J_UINT_4 power;
    J_UINT_4 ip_addr;
    J_UINT_4 mask;
    J_UINT_4 gate_way;
    J_UINT_4 dns;
    J_UINT_4 isap;
    char mac[8];
    char psw[32];			            /* wifi key */
    char essid[128];		            /* wif essid */			
}NET_CFG;


typedef union
{
    char datas[256];
    NET_CFG net_cfg;  

}FACTORY_RSD_CFG, *PFACTORY_RSD_CFG;			

enum
{
	J1850VPW = 1,
	J1850PWM,
	ISO9141,
	ISO14230,
	CAN,
	ISO15765,
	SCI_A_ENGINE,
	SCI_A_TRANS,
	SCI_B_ENGINE,
	SCI_B_TRANS,
	J1850VPW_PS = 0x8000,//_PS PIN脚可选
	J1850PWM_PS,
	ISO9141_PS,//iso
	ISO14230_PS,//kwp
	CAN_PS,
	ISO15765_PS,
	J2610_PS,//sci
	SW_ISO15765_PS,
	SW_CAN_PS,
	GM_UART_PS,//aldl 0x8009
    UART_ECHO_BYTE_PS,//1281
    HONDA_DIAGH_PS,//5v k线
    J1939_PS,
    J1708_PS,
    TP2_0_PS,
    FT_CAN_PS,// 容错can fiat
    FT_ISO15765_PS, //0x8010
    TP1_6_PS,
    J1708_WEBCO_PS,
    UART_HINO_BYTE_PS,//20160413

    CAN_CH1 = 0x9000,
    J1850VPW_CH1 = 0x9080,
    J1850PWM_CH1 = 0x9100,
    ISO9141_CH1 = 0x9180,
    ISO14230_CH1 = 0x9200,
    ISO15765_CH1 = 0x9280,
    SW_CAN_CAN_CH1 = 0x9300,
    SW_CAN_ISO15765_CH1 = 0x9380,
    J2610_CH1 = 0x9400,
    FT_CAN_CH1 = 0x9480,
    FT_ISO15765_CH1 = 0x9500,
    GM_UART_CH1 = 0x9580,
    ECHO_BYTE_CH1 = 0x9600,
    HONDA_DIAGH_CH1 = 0x9680,
    J1939_CH1 = 0x9700,
    J1708_CH1 = 0x9780,
    TP2_0_CH1 = 0x9800,
	ANALOG_IN_CH1 = 0x0000C000,

	NISSAN_PS = 0x00010000

};
typedef enum
{
	STATUS_NOERROR,
	ERR_NOT_SUPPORTED,
	ERR_INVALID_CHANNEL_ID,
	ERR_INVALID_PROTOCOL_ID,
	ERR_NULL_PARAMETER,//4
	ERR_INVALID_IOCTL_VALUE,
	ERR_INVALID_FLAGS,
	ERR_FAILED,
	ERR_DEVICE_NOT_CONNECTED,//8
	ERR_TIMEOUT,
	ERR_INVALID_MSG,
	ERR_INVALID_TIME_INTERVAL,
	ERR_EXCEEDED_LIMIT,//c
	ERR_INVALID_MSG_ID,
	ERR_DEVICE_IN_USE,
	ERR_INVALID_IOCTL_ID,
	ERR_BUFFER_EMPTY,//0x10
	ERR_BUFFER_FULL,
	ERR_BUFFER_OVERFLOW,
	ERR_PIN_INVALID,
	ERR_CHANNEL_IN_USE,//0x14
	ERR_MSG_PROTOCOL_ID,
	ERR_INVALID_FILTER_ID,
	ERR_NO_FLOW_CONTROL,
	ERR_NOT_UNIQUE,
	ERR_INVALID_BAUDRATE,
	ERR_INVALID_DEVICE_ID,
    ERR_RSVD0,
    ERR_RSVD1,
    ERR_RSVD3,
    ERR_INVALID_IOCTL_PARAM_ID = 0x1E,
    ERR_VOLTAGE_IN_USE,
    ERR_PIN_IN_USE,
    ERR_ADDRESS_NOT_CLAIMED    = 0x00010000,
    ERR_NO_CONNECTION_ESTABLISHED,
    ERR_RESOURCE_IN_USE
}ERRORCODE;

enum
{
	EXERR_FACTORYSET_OPEN_ETH_FILE = 0x80000,
	EXERR_FACTORYSET_OPEN_WIFI_FILE,
};

enum{
	PASSTHRU_METHOD,
	PASSTHRU_IOCONTROL,
	PASSTHRU_FACTORY_RSD,
	PASSTHRU_FACTORY_DEV,
};

enum{
	PASS_FILTER = 1,
	BLOCK_FILTER,
	FLOW_CONTROL_FILTER,
};

enum{
	KSCI_PULL_560R,
	KSCI_PULL_1K,
	KSCI_PULL_5V,
	KSCI_PULL_OFF
};

enum
{
	FACTRY_RESERVED_SET_CFG		= 0x10000,
	FACTRY_RESERVED_GET_CFG		= 0x10001,
	FACTRY_RESERVED_LOAD_DATA   = 0x10002 
};

enum
{
	// 本部分用于应用程序
	PASSTHRU_OPEN_CMD			= 0x00,
	PASSTHRU_CLOSE_CMD			= 0x01,
	PASSTHRU_CONNECT_CMD        = 0x02, // 连结命令
	PASSTHRU_DISCONNECT_CMD     = 0x03, // 断开连结
	PASSTHRU_READMSG_CMD        = 0x04, // 读消息
	PASSTHRU_WRITEMSG_CMD       = 0x05, // 写消息
	PASSTHRU_BPERIODICMSG_CMD   = 0x06, // 开始周期性消息
	PASSTHRU_EPERIODICMSG_CMD   = 0x07, // 退出周期性消息
	PASSTHRU_BMSGFILTER_CMD     = 0x08, // 开始过滤消息
	PASSTHRU_EMSGFILTER_CMD     = 0x09, // 结束过滤消息
	PASSTHRU_SPRGVOLTAGE_CMD    = 0x0A, // 设置编程电压
	PASSTHRU_READVERSION_CMD    = 0x0B, // 读版本信息  
		
};

enum
{
	IOC_GET_CONFIG              = 0x01, // 获得网络配置
	IOC_SET_CONFIG              = 0x02, // 设置网络配置
	IOC_READ_VBATT              = 0x03, // 读J1962-PIN16的电压
	IOC_FIVE_BAUD_INIT          = 0x04, // 5波特率初使化 ISO9141
	IOC_FAST_INIT               = 0x05, // 快速初使货 ISO14230
	IOC_CLEAR_TX_BUFFER         = 0x07, // 清除发送队例中的所有消息
	IOC_CLEAR_RX_BUFFER         = 0x08, // 清除接收队例中的所有消息
	IOC_CLEAR_PERIODIC_MSGS     = 0x09, // 清除所有周期性消息,因此结束周期性消息的传输
	IOC_CLEAR_MSG_FILTERS       = 0x0A, // 清除通道上的所有过滤消息
	IOC_CLEAR_FUNCT_MSG_LOOKUP_TABLE  = 0x0B, // 清除功能消息查询表
	IOC_ADD_TO_FUNCT_MSG_LOOKUP_TABLE = 0x0C, // 增加功能地址到功能消息查询表
	IOC_DELETE_FROM_FUNCT_MSG_LOOKUP_TABLE = 0x0D, // 删除功能地址从消息询表
	IOC_READ_PROG_VOLTAGE       = 0x0E,  // 读编程电压  

	IOC_SW_CAN_HS               = 0x8000,
	IOC_SW_CAN_NS               = 0x8001,
	IOC_SET_POLL_RESPONSE       = 0x8002,
	IOC_BECOME_MASTER           = 0x8003,
	IOC_START_REPEAT_MESSAGE	= 0x8004,
	IOC_QUERY_REPEAT_MESSSAGE	= 0x8005,
	IOC_STOP_REPEAT_MESSAGE		= 0x8006,
	IOC_GET_DEVICE_CONFIG		= 0x8007,
	IOC_SET_DEVICE_CONFIG		= 0x8008,
	IOC_PROTECT_J1939_ADDR		= 0x8009,
	IOC_REQUEST_CONNECTION		= 0x800A,
	IOC_TEARDOWN_CONNECTION		= 0x800B,
	IOC_GET_DEVICE_INFO			= 0x800C,
	IOC_GET_PROTOCOL_INFO		= 0x800D,

	IOC_DETECT_BAUDRATE_INIT    = 0x10000,
	IOC_GET_PIN_VOLATAGE		= 0x10001,
	
	IOC_UNSUPORT                = 0xffffffff,
};

enum
{
    NON_VOLATILE_STORE_1   =  0x0000C001,
    NON_VOLATILE_STORE_2   =  0x0000C002,
    NON_VOLATILE_STORE_3   =  0x0000C003,
    NON_VOLATILE_STORE_4   =  0x0000C004,
    NON_VOLATILE_STORE_5   =  0x0000C005,
    NON_VOLATILE_STORE_6   =  0x0000C006,
    NON_VOLATILE_STORE_7   =  0x0000C007,
    NON_VOLATILE_STORE_8   =  0x0000C008,
    NON_VOLATILE_STORE_9   =  0x0000C009,
    NON_VOLATILE_STORE_10  =  0x0000C00A
    //Reserved for SAE J2534-2 0x0000C00B – 0x0000FFFF
};

enum
{
    MAX_RX_BUFFER_SIZE           = 0x00000001,               
    MAX_PASS_FILTER              = 0x00000002,               
    MAX_BLOCK_FILTER             = 0x00000003,               
    MAX_FILTER_MSG_LENGTH        = 0x00000004,               
    MAX_PERIODIC_MSGS            = 0x00000005,               
    MAX_PERIODIC_MSG_LENGTH      = 0x00000006,               
    DESIRED_DATA_RATE            = 0x00000007,               
    MAX_REPEAT_MESSAGING         = 0x00000008,               
    MAX_REPEAT_MESSAGING_LENGTH  = 0x00000009,               
    NETWORK_LINE_SUPPORTED       = 0x0000000A,               
    MAX_FUNCT_MSG_LOOKUP         = 0x0000000B,               
    PARITY_SUPPORTED             = 0x0000000C,               
    DATA_BITS_SUPPORTED          = 0x0000000D,               
    FIVE_BAUD_MOD_SUPPORTED      = 0x0000000E,               
    L_LINE_SUPPORTED             = 0x0000000F,               
    CAN_11_29_IDS_SUPPORTED      = 0x00000010,               
    CAN_MIXED_FORMAT_SUPPORTED   = 0x00000011,               
    MAX_FLOW_CONTROL_FILTER      = 0x00000012,               
    MAX_ISO15765_WFT_MAX         = 0x00000013,               
    MAX_AD_ACTIVE_CHANNELS       = 0x00000014,               
    MAX_AD_SAMPLE_RATE           = 0x00000015,               
    MAX_AD_SAMPLES_PER_READING   = 0x00000016,               
    AD_SAMPLE_RESOLUTION         = 0x00000017,               
    AD_INPUT_RANGE_LOW           = 0x00000018,               
    AD_INPUT_RANGE_HIGH          = 0x00000019,               
    RESOURCE_GROUP               = 0x0000001A,               
    TIMESTAMP_RESOLUTION         = 0x0000001B                
    //Reserved for SAE J2534-2     = 0x0000001C – 0xFFFFFFFF
};

enum
{
    SERIAL_NUMBER               = 0x00000001,
    J1850PWM_SUPPORTED          = 0x00000002,
    J1850VPW_SUPPORTED          = 0x00000003,
    ISO9141_SUPPORTED           = 0x00000004,
    ISO14230_SUPPORTED          = 0x00000005,
    CAN_SUPPORTED               = 0x00000006,
    ISO15765_SUPPORTED          = 0x00000007,
    SCI_A_ENGINE_SUPPORTED      = 0x00000008,
    SCI_A_TRANS_SUPPORTED       = 0x00000009,
    SCI_B_ENGINE_SUPPORTED      = 0x0000000A,
    SCI_B_TRANS_SUPPORTED       = 0x0000000B,
    SW_ISO15765_SUPPORTED       = 0x0000000C,
    SW_CAN_SUPPORTED            = 0x0000000D,
    GM_UART_SUPPORTED           = 0x0000000E,
    UART_ECHO_BYTE_SUPPORTED    = 0x0000000F,
    HONDA_DIAGH_SUPPORTED       = 0x00000010,
    J1939_SUPPORTED             = 0x00000011,
    J1708_SUPPORTED             = 0x00000012,
    TP2_0_SUPPORTED             = 0x00000013,
    J2610_SUPPORTED             = 0x00000014,
    ANALOG_IN_SUPPORTED         = 0x00000015,
    MAX_NON_VOLATILE_STORAGE    = 0x00000016,
    SHORT_TO_GND_J1962          = 0x00000017,
    PGM_VOLTAGE_J1962           = 0x00000018,
    J1850PWM_PS_J1962           = 0x00000019,
    J1850VPW_PS_J1962           = 0x0000001A,
    ISO9141_PS_K_LINE_J1962     = 0x0000001B,
    ISO9141_PS_L_LINE_J1962     = 0x0000001C,
    ISO14230_PS_K_LINE_J1962    = 0x0000001D,
    ISO14230_PS_L_LINE_J1962    = 0x0000001E,
    CAN_PS_J1962                = 0x0000001F,
    ISO15765_PS_J1962           = 0x00000020,
    SW_CAN_PS_J1962             = 0x00000021,
    SW_ISO15765_PS_J1962        = 0x00000022,              
    GM_UART_PS_J1962            = 0x00000023,              
    UART_ECHO_BYTE_PS_J1962     = 0x00000024,              
    HONDA_DIAGH_PS_J1962        = 0x00000025,              
    J1939_PS_J1962              = 0x00000026,              
    J1708_PS_J1962              = 0x00000027,              
    TP2_0_PS_J1962              = 0x00000028,              
    J2610_PS_J1962              = 0x00000029,              
    J1939_PS_J1939              = 0x0000002A,              
    J1708_PS_J1939              = 0x0000002B,              
    ISO9141_PS_K_LINE_J1939     = 0x0000002C,              
    ISO9141_PS_L_LINE_J1939     = 0x0000002D,              
    ISO14230_PS_K_LINE_J1939    = 0x0000002E,              
    ISO14230_PS_L_LINE_J1939    = 0x0000002F,              
    J1708_PS_J1708              = 0x00000030,              
    FT_CAN_SUPPORTED            = 0x00000031,              
    FT_ISO15765_SUPPORTED       = 0x00000032,              
    FT_CAN_PS_J1962             = 0x00000033,              
    FT_ISO15765_PS_J1962        = 0x00000034,              
    J1850PWM_SIMULTANEOUS       = 0x00000035,              
    J1850VPW_SIMULTANEOUS       = 0x00000036,              
    ISO9141_SIMULTANEOUS        = 0x00000037,              
    ISO14230_SIMULTANEOUS       = 0x00000038,              
    CAN_SIMULTANEOUS            = 0x00000039,              
    ISO15765_SIMULTANEOUS       = 0x0000003A,              
    SCI_A_ENGINE_SIMULTANEOUS   = 0x0000003B,              
    SCI_A_TRANS_SIMULTANEOUS    = 0x0000003C,              
    SCI_B_ENGINE_SIMULTANEOUS   = 0x0000003D,              
    SCI_B_TRANS_SIMULTANEOUS    = 0x0000003E,              
    SW_ISO15765_SIMULTANEOUS    = 0x0000003F,              
    SW_CAN_SIMULTANEOUS         = 0x00000040,              
    GM_UART_SIMULTANEOUS        = 0x00000041,              
    UART_ECHO_BYTE_SIMULTANEOUS = 0x00000042,              
    HONDA_DIAGH_SIMULTANEOUS    = 0x00000043,              
    J1939_SIMULTANEOUS          = 0x00000044,              
    J1708_SIMULTANEOUS          = 0x00000045,              
    TP2_0_SIMULTANEOUS          = 0x00000046,              
    J2610_SIMULTANEOUS          = 0x00000047,              
    ANALOG_IN_SIMULTANEOUS      = 0x00000048,              
    PART_NUMBER                 = 0x00000049,              
    FT_CAN_SIMULTANEOUS         = 0x0000004A,              
    FT_ISO15765_SIMULTANEOUS    = 0x0000004B              
    //Reserved for SAE J2534-2  = 0x0000004C – 0xFFFFFFFF                                                 
};

enum 
{
    DATA_RATE = 1,    
    LINK_LOOPBACK = 3,
    NODE_ADDRESS,
    NETWORK_LINE,
    P1_MIN,
    P1_MAX,
    P2_MIN,
    P2_MAX,//9
    P3_MIN,
    P3_MAX,
    P4_MIN,
    P4_MAX,//d    
    W1,
    W2,
    W3,//0x10
    W4,
    W5,
    TIDLE,
    TINIL,//0x14
    TWUP,
    PARITY,
    BIT_SAMPLE_POINT,
    SYNC_JUMP_WIDTH,
    W0 = 0x19,
    T1_MAX,
    T2_MAX,
    T4_MAX,
    T5_MAX,//0x1d
    ISO15765_BS,
    ISO15765_STMIN,
    DATA_BITS,
    FIVE_BAUD_MOD,//0x21
    BS_TX,
    STMIN_TX,
    T3_MAX,
    ISO15765_WFT_MAX,//0x25
    NBPS_IN,/*2016-1-28,add for 200bps in*/
    
    CAN_MIXED_FORMAT = 0x8000,  
    J1962_PINS,
    PARM_CAN_SPECIAL_FORMAT,
    
    SW_CAM_HS_DATA_RATE = 0x8010,
    SW_CAN_SPEEDCHANGE_ENABLE,
    SW_CAN_RES_SWITCH,

    ACTIVE_CHANNELS = 0x8020, /*0x2B*/
    SAMPLE_RATE,
    SAMPLES_PER_READING,
    READINGS_PER_MSG,
    AVERAGING_METHOD,
    SAMPLE_RESOLUTION,
    INPUT_RANGE_LOW,
    INPUT_RANGE_HIGH,//0x8027
    UEB_T0_MIN,
    UEB_T1_MAX,
    UEB_T2_MAX,
    UEB_T3_MAX,
    UEB_T4_MIN,
    UEB_T5_MAX,
    UEB_T6_MAX,
    UEB_T7_MIN,
    UEB_T7_MAX,
    UEB_T9_MIN,

    J1939_PINS = 0x0000803D,
    J1708_PINS,
    J1939_T1,
    J1939_T2,
    J1939_T3,
    J1939_T4,
    J1939_BRDCST_MIN_DELAY,
    TP2_0_T_BR_INT,
    TP2_0_T_E,
    TP2_0_MNTC,
    TP2_0_T_CTA,
    TP2_0_MNCT,
    TP2_0_MNTB,
    TP2_0_MNT,
    TP2_0_T_WAIT,
    TP2_0_T1,
    TP2_0_T3,
    TP2_0_IDENTIFER,
    TP2_0_RXIDPASSIVE,
    TP2_0_SENDPACKNUM,//20160814 quss 获取TP20 发送包的序号
    TP2_0_SETSPECIAL_T3,//20160814 quss  设置防盗要求的时间参数T3，但是因为TP2_0_T3设置达不到需求，所以专用接口

#if 0
	ISO15765_FLOWCTRL_AUTO = 0x00010000,
	TP1_6_KWP2K,
	NISSAN_CLK_PIN,
	ISO15765_PAD,
	UEB_RCV_IDMSGS,
	ISO15765_FLOWCTRL_DELAY
#else
	ISO15765_FLOWCTRL_AUTO = 0x00010000,
	ISO15765_PAD,
	ISO15765_FLOWCTRL_DELAY,
	TP1_6_KWP2K,
	ASSIST_PIN,
	UEB_RCV_IDMSGS,    
	UEB_ADRCODE_PARITY,
	IOS15765_SINGLEFRAMECANID,  //20160620 陈刚 增加：单报文ID
#endif
	MULTI_REQUEST_MODE = 0x00020000,/*2016-8-29 设置多请求发送lhq*/

	GENERIC_MODE = 0x00020001, /*2016-8-29 设置通用模式lhq*/
//	FIVE_BAUD_AUTO_MODE = 0x00020002 ,/*2016-9-7 自动慢速进入lhq*/
	FIXED_FRAME_INTERVAL_TIME = 0x00020003,    /*设置打包多帧数据发送的帧之间的时间间隔参数---甘旗20161109*/
	ALDL_BLUETOOTH_CONNECT_FLAG = 0x00020004,/*ALDL用蓝牙连接会断开问题，传此值下去根据值不同有不同的---20161113*/    
//	KWP1281_REENTER_VERSION_FLAG = 0x00020005/*解决KWP1281二次进入此问题修改前和修改的一个版本之间的兼容引入的标志位---20161114*/    
	FIVE_BAUD_AUTO_MODE = 0x00020006 ,/*2017-1-19 自动慢速进入提速模式的设置,lhq*/
};

enum{
	KWP1281_REENTER_OLD_VERSION = 0,
	KWP1281_REENTER_NEW_VERSION = 1,
};

enum{
	UPGRADE_FIRMWARE = 0x80,
	DATA_FIRMWARE
};

enum{
	CAN_MIXED_FORMAT_OFF,
	CAN_MIXED_FORMAT_ON,
	CAN_MIXED_FORMAT_ALL_FRAMES
};

enum{//20160712 quss
	CAN_NORMAL_FORMAT, //普通模式
	CAN_CHANGAN_FORMAT, //长安单报文
	CAN_ALLISON_FORMAT, // Allison 类GMLAN
	CAN_SINGLE_CANBUS  // 标准单报文
};

enum{//20160712 quss
	CAN_FLOWCTRL_NORMAL, //普通模式
	CAN_CHANGAN_MODE, //长安流控制模式
	CAN_FLOWCTRL_AUTO  // 自动流控制，中间层任何时候都不做bit3清零处理  
};

/*Generic id,2016-8-29 通用模式的通用ID*/
enum
{
    MULTI_REQUEST_SET_EXPECTEDED_RESPONSE = 1,/*设置多帧发送的filterid*/
    AUTO_FIVE_BAUD_SET_PARAM = 2  /*5波特率系统进入之前打包设置参数,2017-1-19,ganqi*/
};

#define CF_MINUX_LOGIC              ( 1 << 24 )
#define CF_BUS_LEVEL				( 1 << 25 )
#define CF_ISO9141_K_LINE_ONLY		( 1 << 12 )
#define CF_ISO9141_NO_CHECKSUM      ( 1 << 9 )

#define CONNECTION_LOST             ( 1 << 17 )
#define CONNECTION_ESTABLISHED      ( 1 << 16 )

#define RF_START_OF_MESSAGE         ( 1 << 1)

#define CHANNEL_FLAG			0x80000000		

#ifdef __cplusplus
extern "C"{
#endif

/*#define STATIC_LOAD_DLL 1*/

/*#ifdef _USRDLL
#define IMPORT_EXPORT _declspec(dllexport)
#else
#define IMPORT_EXPORT _declspec(dllimport)
#endif

#if STATIC_LOAD_DLL*/
 J_EXPORT_IN_8  PassThruOpen (void *pName,J_EXPORT_U_IN_8 *pDeviceID);
 J_EXPORT_IN_8  PassThruClose (J_EXPORT_U_IN_8 DeviceID);
 J_EXPORT_IN_8  PassThruConnect 
        (
        J_EXPORT_U_IN_8 DeviceID,
        J_EXPORT_U_IN_8 ProtocolID,
        J_EXPORT_U_IN_8 Flags,
        J_EXPORT_U_IN_8 BaudRate,
        J_EXPORT_U_IN_8 *pChannelID
        );

 J_EXPORT_IN_8  PassThruDisconnect(J_EXPORT_U_IN_8 ChannelID);

 J_EXPORT_IN_8  PassThruReadMsgs
        (
        J_EXPORT_U_IN_8 ChannelID,
        PASSTHRU_MSG *pMsg,
        J_EXPORT_U_IN_8 *pNumMsgs,
        J_EXPORT_U_IN_8 Timeout
        );

 J_EXPORT_IN_8  PassThruWriteMsgs
        (
        J_EXPORT_U_IN_8 ChannelID,
        PASSTHRU_MSG *pMsg,
        J_EXPORT_U_IN_8 *pNumMsgs,
        J_EXPORT_U_IN_8 Timeout
        );

 J_EXPORT_IN_8  PassThruStartPeriodicMsg
        (
        J_EXPORT_U_IN_8 ChannelID,
        PASSTHRU_MSG *pMsg,
        J_EXPORT_U_IN_8 *pMsgID,
        J_EXPORT_U_IN_8 TimeInterval
        );

 J_EXPORT_IN_8  PassThruStopPeriodicMsg
        (
        J_EXPORT_U_IN_8 ChannelID,
        J_EXPORT_U_IN_8 MsgID
        );

 J_EXPORT_IN_8  PassThruStartMsgFilter
        (
        J_EXPORT_U_IN_8 ChannelID,
        J_EXPORT_U_IN_8 FilterType,
        PASSTHRU_MSG *pMaskMsg,
        PASSTHRU_MSG *pPatternMsg,
        PASSTHRU_MSG *pFlowControlMsg,
        J_EXPORT_U_IN_8 *pFilterID
        );

 J_EXPORT_IN_8  PassThruStopMsgFilter
        (
        J_EXPORT_U_IN_8 ChannelID,
        J_EXPORT_U_IN_8 FilterID
        );

 J_EXPORT_IN_8  PassThruSetProgrammingVoltage
        (
        J_EXPORT_U_IN_8 DeviceID,
        J_EXPORT_U_IN_8 PinNumber,
        J_EXPORT_U_IN_8 Voltage
        );

 J_EXPORT_IN_8  PassThruReadVersion
        (
        J_EXPORT_U_IN_8 DeviceID,
        char *pFirmwareVersion,
        char *pDllVersion,
        char *pApiVersion
        );

 J_EXPORT_IN_8  PassThruIoctl
        (
        J_EXPORT_U_IN_8 ChannelID,
        J_EXPORT_U_IN_8 IoctlID,
        void *pInput,
        void *pOutput
        );

 J_EXPORT_IN_8  PassThruGetLastError
        (
        char *pErrorDescription
        );

 J_EXPORT_IN_8  PassThruLoadData
	(
	J_EXPORT_U_IN_8 DeviceID,
	PDATAFILE pstFileData, 
	unsigned char* pData, 
	J_EXPORT_U_IN_8* pPackNo
	);

 J_EXPORT_IN_8  FactoryReadFaultCodes
	(
	J_EXPORT_U_IN_8 DeviceID,
	unsigned char* pData,
	J_EXPORT_U_IN_8* pFalutCnts
	);
 J_EXPORT_IN_8  PassThruGetSerial
	 (
	 J_EXPORT_U_IN_8 ChannelID,
	 char *SWver, 
	 char *HWver, 
	 char *pSerial, 
	 char *pManufacturerTime, 
	 char *pPassWord
	 );

	J_EXPORT_U_IN_8 PassthruGetCommPort();
	char *ReadProductName();
	bool Is906PlugIn();

#ifdef __cplusplus
}
#endif

#endif /* SAE_J2534_FUNC */
