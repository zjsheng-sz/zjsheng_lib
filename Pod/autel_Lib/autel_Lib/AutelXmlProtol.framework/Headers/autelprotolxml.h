#ifndef __AUTEL_PROTOL_XML__H__
#define __AUTEL_PROTOL_XML__H__

#include "autelprotolxmlbase.h"
#include "stdint.h"

extern "C"{
	/**
	* @brief  获取加密xml版本(考虑加密算法变更,通过此版本号控制传出的文档对象)
	* @return 返回对应的加密xml版本
	*/
	AUTEL_PROTOL_XML_API int	AutelXml_GetXmlVersion();

	/**
	* @brief  分配及释放一个xml 文档对象
	*		  分配需要提供版本号
	* @return 返回代表xml文档的ID ( hXmlHandle)
	*/
	AUTEL_PROTOL_XML_API void *	AutelXml_CreateXmlInstance( __AUTEL_IN int ver );
	AUTEL_PROTOL_XML_API void	AutelXml_ReleaseXmlInstance( __AUTEL_IN void * hXmlHandle );

	/**
	* @brief  释放内部分配的缓冲区(通过**传出的数据,需要调用该函数释放 
	* @return 
	*/
	AUTEL_PROTOL_XML_API void	AutelXml_ReleaseData( __AUTEL_IN char ** lpBuffer );

	/**
	* @brief 设置xml中数据参数代表的数据类型(如在线状态on,off,HIDE,LEAVE,BUSY以及group,person等)
	*		 根据具体的交互协议设置或者获取
	* @return 
	*/
/*	AUTEL_PROTOL_XML_API void	AutelXml_SetTypeByName( __AUTEL_IN void * hXmlHandle , __AUTEL_IN char* type );
	AUTEL_PROTOL_XML_API void	AutelXml_SetTypeByValue(__AUTEL_IN void * hXmlHandle ,  __AUTEL_IN int type );
	AUTEL_PROTOL_XML_API __AUTEL_OUT __AUTEL_CONST char*	AutelXml_GetTypeName( __AUTEL_IN void * hXmlHandle );
	AUTEL_PROTOL_XML_API int	AutelXml_GetTypeInt( __AUTEL_IN void * hXmlHandle  );
*/
	/**
	* @brief 从二进制数据解析出xml文件以及交xml文件打包成二进制数据
	*		 输入及输出buf都以'\0'结尾的字符串
	*		 输出的ppBinary内存由模块内分配需调用AutelXml_ReleaseData释放
	* @return 
	*/
	AUTEL_PROTOL_XML_API void	AutelXml_Parse(__AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* data );
	AUTEL_PROTOL_XML_API bool	AutelXml_XmlToBinary( __AUTEL_IN void * hXmlHandle , __AUTEL_OUT char** ppBinary, __AUTEL_OUT unsigned int& dataLen );

	/**
	* @brief 从xml中删除一个filed,filedName为filed键值 
	* @return 
	*/
	AUTEL_PROTOL_XML_API void	AutelXml_RemoveParam( __AUTEL_IN void * hXmlHandle ,  __AUTEL_IN const char* filedName );

	/**
	* @brief 清除xml文档对象中的所有值
	* @return 
	*/
	AUTEL_PROTOL_XML_API void	AutelXml_Clear(__AUTEL_IN void * hXmlHandle);

	// IParamNode
/*	AUTEL_PROTOL_XML_API char*	AutelXml_GetParamName( __AUTEL_IN void * hXmlHandle );
	AUTEL_PROTOL_XML_API char*	AutelXml_GetParamValue( __AUTEL_IN void * hXmlHandle );
*/	
	/**
	* @brief 向xml添加filed
	* @return 
	*/
	AUTEL_PROTOL_XML_API void	AutelXml_SetString( __AUTEL_IN void * hXmlHandle ,  __AUTEL_IN const char* filedName, __AUTEL_IN const char*   filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetBinary( __AUTEL_IN void * hXmlHandle ,  __AUTEL_IN const char* filedName, __AUTEL_IN const char*   filedValue, __AUTEL_IN unsigned int valueLen);
	AUTEL_PROTOL_XML_API void	AutelXml_SetChar( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN char          filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetInt( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN int           filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetFloat( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN float         filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetDouble( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN double        filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetBool( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN bool          filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetUChar( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN unsigned char filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetUInt( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN unsigned int  filedValue );
	AUTEL_PROTOL_XML_API void	AutelXml_SetULong( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN unsigned long filedValue );
#ifdef __TARGET_PLAT_WIN__

	AUTEL_PROTOL_XML_API void	AutelXml_SetInt64( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN __int64       filedValue );

#elif defined(__TARGET_PLAT_LINUX__)

	AUTEL_PROTOL_XML_API void	AutelXml_SetInt64( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, __AUTEL_IN int64_t       filedValue );

#endif

	/**
	* @brief 从xml中获取filed
	* @return 
	*/
	AUTEL_PROTOL_XML_API __AUTEL_OUT __AUTEL_CONST char*	AutelXml_GetString( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API char	AutelXml_GetChar( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API int	AutelXml_GetInt(  __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API long	AutelXml_GetLong( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API float	AutelXml_GetFloat(  __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API double	AutelXml_GetDouble( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API bool	AutelXml_GetBool(   __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API unsigned char	AutelXml_GetUChar( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API unsigned int	AutelXml_GetUInt(  __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API unsigned long	AutelXml_GetULong( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );
	AUTEL_PROTOL_XML_API __AUTEL_OUT __AUTEL_CONST char*	AutelXml_GetBinary( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, unsigned int& dataLen );
	AUTEL_PROTOL_XML_API __AUTEL_OUT __AUTEL_CONST char*	AutelXml_GetBinaryByCoding( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName, unsigned int& dataLen );
#ifdef __TARGET_PLAT_WIN__

	AUTEL_PROTOL_XML_API __int64	AutelXml_GetInt64( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );

#elif defined(__TARGET_PLAT_LINUX__)

	AUTEL_PROTOL_XML_API int64_t	AutelXml_GetInt64( __AUTEL_IN void * hXmlHandle , __AUTEL_IN const char* filedName );

#endif

}

#endif