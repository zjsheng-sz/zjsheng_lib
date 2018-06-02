#pragma once
////////////////////////////////////////////////////////////////////////////////
//文件名  : ClientTcpInterface.h
//创建者  : 梁培鹏
//功能描述: 外部调用C++的接口
//
//更新履历: 2017-4-15 16:46 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////
void JNICALL EnableClientTcpLogMessage(bool control);

typedef struct _TCP_BYTE_ARRAY_ //代替 jbyteArray
{
    _TCP_BYTE_ARRAY_()
    {
        data = NULL;
        len = 0;
    }
    unsigned char *data;
    unsigned int len;
}TCP_BYTE_ARRAY, *PTCP_BYTE_ARRAY;

long ModuleType();

long ModuleVersion();

int Init(string ipAddress, int port);

int Send(int socketId, long service, long serviceMask, TCP_BYTE_ARRAY & data);

int SendEx(int socketId, long service, long serviceMask, TCP_BYTE_ARRAY & data, long from, long to, long id);

int SendByPointer(int socketId, long service, long serviceMask, long dataAddress,long dataLength, long from, long to, long id);

void* Receive(int socketId);

void ReceiveByRefObj(int socketId, void *resultParam);

void UnInit(int socketId);

TCP_BYTE_ARRAY EncryptDecrypt_Encrypt(TCP_BYTE_ARRAY & byteArray);
TCP_BYTE_ARRAY EncryptDecrypt_Decrypt(TCP_BYTE_ARRAY & byteArray);
