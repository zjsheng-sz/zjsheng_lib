#ifndef __JNI_PUBLIC_H__
#define __JNI_PUBLIC_H__

#include "MaxiPlatform.h"

#include <string>
#include <vector>
using namespace std;
#ifdef AUTEL_SYS_ANDROID


#include <jni.h>


#define JNITRACE(tag, msg) JniTrace trace((tag), (msg));
#define JNIINFO(tag, msg) JniPublic::JniLog((tag), (msg));
#define JNIWARN(tag, msg) JniPublic::JniLog((tag), (msg), 1);
#define JNIERROR(tag, msg) JniPublic::JniLog((tag), (msg), 2);
#define JNIFAULT(tag, msg) JniPublic::JniLog((tag), (msg), 3);


template<typename JniPointType>
class JniAutoPtr;
namespace JniPublic
{
	JNIEnv* GetEnv();

	void SetEnv(JNIEnv *env);

	void SetLogSwitch(bool bOpen);

	void JniLog(const string& strTitle, const string& strMsg, int nlevel = 0);

	JniAutoPtr<jclass> FindStaticClass(string strClassName, JNIEnv *env);

	// 获取Java类
	JniAutoPtr<jclass> GetVdtPublicJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetDataStreamJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetFreezeFrameJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetCarInfoJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetEmissionCheckJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetMainMenuJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetMessageBoxJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetTroubleCodeJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetExhaustGasCheckJniClass(JNIEnv *env = NULL);
	JniAutoPtr<jclass> GetMilStatusJniClass(JNIEnv *env = NULL);

	JniAutoPtr<jobjectArray> ToJStringArray(vector<string> const& vctStrings, JNIEnv* env = NULL);
	JniAutoPtr<jobjectArray> ToJStringArray(string const* pStrings, int nSize, JNIEnv* env = NULL);
	// end

	JniAutoPtr<jintArray> ToJIntArray(vector<int> const& vctInts, JNIEnv* env = NULL);
	JniAutoPtr<jintArray> ToJIntArray(int const* pInts, int nSize, JNIEnv* env = NULL);

	JniAutoPtr<jlongArray> ToJLongArray(vector<long> const& vctInts, JNIEnv* env = NULL);
	JniAutoPtr<jlongArray> ToJLongArray(long const* pLongs, int nSize, JNIEnv* env = NULL);


	// 将string类型转换成Unicode编码的JString
	JniAutoPtr<jstring> ConverStringToJString(string strAnsi, JNIEnv *env = NULL);

	// 将Unicode的JString转成本地的Ansi编码
	string ConverJStringToString(jstring jstrUnicode, JNIEnv *env = NULL);
}

template<typename JniPointType>
class JniAutoPtr
{
public:
	explicit JniAutoPtr(JNIEnv *env, JniPointType point = NULL):m_jniPoint(point),m_env(env)
	{

	}
	JniAutoPtr(JniAutoPtr const& right):
	m_jniPoint(const_cast<JniAutoPtr&>(right).Release()),m_env(right.m_env)
	{

	}
	JniAutoPtr<JniPointType>& operator=(JniAutoPtr<JniPointType>const& right)
	{	// assign compatible _Right (assume pointer)
		Reset(const_cast<JniAutoPtr<JniPointType>& >(right).Release());
		m_env = right.m_env;
		return (*this);
	}

	JniPointType Release()
	{
		JniPointType result = m_jniPoint;
		Reset();
		return result;
	}

	operator JniPointType()
	{
		return m_jniPoint;
	}
	~JniAutoPtr()
	{
		if (NULL != m_jniPoint)
		{
			m_env->DeleteLocalRef(m_jniPoint);
		}
	}
private:
	void Reset(JniPointType jniPoint = NULL)
	{
		m_jniPoint = jniPoint;
	}
private:
	JniPointType m_jniPoint;	// the wrapped object pointer
	JNIEnv *m_env;
};


template<>
class JniAutoPtr<jobjectArray>
{
public:
	explicit JniAutoPtr(JNIEnv *env, jobjectArray point = NULL):m_jniPoint(point),m_env(env)
	{

	}
	JniAutoPtr(JniAutoPtr const& right):
	m_jniPoint(const_cast<JniAutoPtr&>(right).Release()),m_env(right.m_env)
	{

	}
	JniAutoPtr<jobjectArray>& operator=(JniAutoPtr<jobjectArray>const& right)
	{	// assign compatible _Right (assume pointer)
		Reset(const_cast<JniAutoPtr<jobjectArray>& >(right).Release());
		m_env = right.m_env;
		return (*this);
	}

	jobjectArray Release()
	{
		jobjectArray result = m_jniPoint;
		Reset();
		return result;
	}

	operator jobjectArray()
	{
		return m_jniPoint;
	}
	~JniAutoPtr()
	{
		if (NULL != m_jniPoint)
		{
			for (int i=0; i<m_env->GetArrayLength(m_jniPoint); ++i)
			{
				jobject obj = m_env->GetObjectArrayElement(m_jniPoint, i);
				m_env->DeleteLocalRef(obj);
			}
			m_env->DeleteLocalRef(m_jniPoint);
		}
	}
private:
	void Reset(jobjectArray jniPoint = NULL)
	{
		m_jniPoint = jniPoint;
	}
private:
	jobjectArray m_jniPoint;	// the wrapped object pointer
	JNIEnv *m_env;
};


class JniTrace
{
public:
	JniTrace(char const* szTag, char const* szTrace):m_szTag(szTag), m_strMsg(szTrace)
	{
		JniPublic::JniLog(m_szTag, m_strMsg + " Begin");
	}
	JniTrace(char const* szTag, string const& strTrace):m_szTag(szTag), m_strMsg(strTrace)
	{
		JniPublic::JniLog(m_szTag, m_strMsg + " Begin");
	}
	~JniTrace()
	{
		JniPublic::JniLog(m_szTag, m_strMsg + " End");
	}
private:
	char const* m_szTag;
	string m_strMsg;
};
#else
//非安卓下的一些空函数
    namespace JniPublic
    {
        void JniLog(const string& strTitle, const string& strMsg, int nlevel = 0){}
    }
    #define JNITRACE(tag, msg)  
    #define JNIINFO(tag, msg)  
    #define JNIWARN(tag, msg) 
    #define JNIERROR(tag, msg)  
    #define JNIFAULT(tag, msg) 
#endif

#endif
