#ifndef _H_LIBAUTELEXAMPLE_201736_195135_H__
#define _H_LIBAUTELEXAMPLE_201736_195135_H__


#ifdef _USEDLL
#ifdef _WIN32
	#ifdef LIBAUTELEXAMPLE_EXPORTS
		#define LIBAUTELEXAMPLE_API __declspec(dllexport)
	#else
		#define LIBAUTELEXAMPLE_API __declspec(dllimport)
	#endif
#else
	#define LIBAUTELEXAMPLE_API __attribute__ ((visibility("default")))
#endif
#else
	#define LIBAUTELEXAMPLE_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

	/************************************************************************/
	/* 功  能： 数据加密函数
	/* 参  数： @pData：需要加密的数据
				@nLen: 加密数据长度
				@nMode: 加密模式，必须是大于0的整数
	/* 返回值： 无
	/* 说  明： 加密模式目前的取值为1,2
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelEncrypt_Mode(unsigned char* pData, unsigned int nLen, int nMode = 0);

	/************************************************************************/
	/* 功  能： 数据解密函数
	/* 参  数： @pData：需要解密的数据
				@nLen: 解密数据长度
				@nMode: 加密模式，必须是大于0的整数
	/* 返回值： 无
	/* 说  明： 加密模式目前的取值为1,2
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelDecrypt_Mode(unsigned char* pData, unsigned int nLen, int nMode = 0);



	/************************************************************************/
	/* 功  能： 数据加密函数
	/* 参  数：	@pData: 需要加密的数据
				@nDataLen: 加密数据长度
				@pKey: 秘钥
				@pKeyLen: 秘钥长度
	/* 返回值：
	/* 说  明： 使用秘钥对数据进行加密
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelEncrypt_Key(unsigned char* pData, unsigned int nDataLen, unsigned char* pKey, int nKeyLen);

	/************************************************************************/
	/* 功  能： 数据解密函数
	/* 参  数：	@pData: 需要加密的数据
				@nDataLen: 加密数据长度
				@pKey: 秘钥
				@pKeyLen: 秘钥长度
	/* 返回值：
	/* 说  明：	使用秘钥对数据进行解密
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelDecrypt_Key(unsigned char* pData, unsigned int nDataLen, unsigned char* pKey, int nKeyLen);



	/************************************************************************/
	/* 功  能： 数据加密函数
	/* 参  数：	@pData: 需要加密的数据
				@ullPassword: 秘钥
				@nMode: 加密模式，必须是大于0的整数
	/* 返回值：
	/* 说  明： 使用秘钥对数据进行加密
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelEncrypt_ModeKey(unsigned char* pData, unsigned int nDataLen, unsigned long long ullPassword, unsigned char ucMode = 0);

	/************************************************************************/
	/* 功  能： 数据解密函数
	/* 参  数：	@pData: 需要加密的数据
				@ullPassword: 秘钥
				@nMode: 加密模式，必须是大于0的整数
	/* 返回值：
	/* 说  明： 使用秘钥对数据进行加密
	/************************************************************************/
	LIBAUTELEXAMPLE_API void AutelDecrypt_ModeKey(unsigned char* pData, unsigned int nDataLen, unsigned long long ullPassword, unsigned char ucMode = 0);


#ifdef __cplusplus
};
#endif

#endif // _H_LIBAUTELEXAMPLE_201736_195135_H__