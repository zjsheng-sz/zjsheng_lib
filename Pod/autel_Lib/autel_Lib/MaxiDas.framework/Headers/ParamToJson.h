#ifndef PARAMTOJSON_CAA8892A_924A_4D86_ABEB_94085BCFE31B_INCLUDED_
#define PARAMTOJSON_CAA8892A_924A_4D86_ABEB_94085BCFE31B_INCLUDED_
////////////////////////////////////////////////////////////////////////////////
//文件名  : ParamToJson.h
//创建者  : 梁培鹏
//功能描述: 用于将参数转换为JSON字符串，用于NativeCallAppReturnJSON的参数
//
//更新履历: 2017-3-16 14:34 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////
#include "UIPubDefine.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

struct JsonResultData
{
    JsonResultData()
    {
        i_data = NULL;
        d_data = NULL;
        b_data = NULL;
        l_data = NULL;
        s_data = NULL;

        uc_data = NULL;
        uc_len  = 0;
    }
    ~JsonResultData()
    {
        clear();
    }
    void clear()
    {
        if (i_data)
        {
            delete i_data;
            i_data = NULL;
        }
        if (d_data)
        {
            delete d_data;
            d_data = NULL;
        }
        if (b_data)
        {
            delete b_data;
            b_data = NULL;
        }
        if (l_data)
        {
            delete l_data;
            l_data = NULL;
        }
        if (s_data)
        {
            delete s_data;
            s_data = NULL;
        }
        if (uc_data)
        {
            delete uc_data;
            uc_data = NULL;
            uc_len = 0;
        }

        vi_data.clear();
        map_ss_Data.clear();
    }
    int *i_data;
    double *d_data;
    bool *b_data;
    long *l_data;
    string *s_data;

    unsigned char *uc_data;             //byte
    unsigned int uc_len;

    vector<int> vi_data;                //整形数组
    map<string, string> map_ss_Data;    //map string string
};

//待完善
class __MYEXPORT__ CParamToJson
{
public:
    //基础类型
    void Add(const string & sKey, int val);
    void Add(const string & sKey, unsigned int val);
    void Add(const string & sKey, double val);
    void Add(const string & sKey, bool val);
    void Add(const string & sKey, long val);
    void Add(const string & sKey, unsigned long val);
    void Add(const string & sKey, const string & val);
    void Add(const string & sKey, const char * val);    //C普通字符串

    //数组类型 无序 未实现
    void Add(const string & sKey, const int* & val, int nCount);
    void Add(const string & sKey, const double* & val, int nCount);
    void Add(const string & sKey, const bool* & val, int nCount);
    void Add(const string & sKey, const long* & val, int nCount);
    void Add(const string & sKey, const string* & val, int nCount);

    //vector类型 无序
    void Add(const string & sKey, const vector<unsigned int> & val);    //这个转换后将为int
    void Add(const string & sKey, const vector<int> & val);
    void Add(const string & sKey, const vector<double> & val);
    void Add(const string & sKey, const vector<bool> & val);
    void Add(const string & sKey, const vector<long> & val);
    void Add(const string & sKey, const vector<string> & val);



    //输出转换的JSON
    string ToString();

    //清空之前的Add与结果 用于对象重新使用
    void clear();


    //解析JSON获取结果 结果要么是基本类型 要么是数组类型，都是很简单的类型
    int GetJsonData(const string & jsonStr, JsonResultData & retData);

private:
    vector<string> m_vtParam;
    string m_json;
};

#endif // PARAMTOJSON_CAA8892A_924A_4D86_ABEB_94085BCFE31B_INCLUDED_
