#ifndef _H_UIMESSAGEBOX_H_20170222_134232
#define _H_UIMESSAGEBOX_H_20170222_134232
#include "UIPubDefine.h"
#include "Binary.h"
#include "UIMsgBoxDefine.h"

//SHOW返回事件值 从公共头文件中移动到这里
//以下宏用于对话框的返回值
#define DF_IDYES        KEY_PRESS_F1
#define DF_IDNO         KEY_PRESS_F3
#define DF_IDOK         KEY_PRESS_F1
#define DF_IDCANCEL     KEY_PRESS_F3
#define DF_IDHELP       KEY_PRESS_HELP
#define DF_IDUP         KEY_PRESS_UP
#define DF_IDDOWN       KEY_PRESS_DOWN
#define DF_IDLEFT       KEY_PRESS_LEFT
#define DF_IDRIGHT      KEY_PRESS_RIGHT
#define DF_IDBACK       KEY_PRESS_F3
#define DF_TIMER        200






__MYEXPORT__ void AutoWaitForComm(const CBinary& TTL, const CBinary& TXT);


/*-----------------------------------------------------------------------------
功    能: 显示消息对话框
参数说明: binTitle        标题
binContain      内容
nTyte           对话框类型(见上面宏定义)
nFormat         文本排版格式(见上面宏定义)
nTimer          定时器，单位ms，默认为零不处理，非零到达时自动返回
bInitWhenShowReturn  当设置为非阻塞模式时，是否需要初始化
返 回 值: 见上面宏定义
说    明: 无
2007-10-12 16:23:59
-------------------------------------------------------------------------*/
__MYEXPORT__
W_U16  adsMessageBox(const CBinary &binTitle, 
					const CBinary &binContain, 
					W_U16 nTyte = DF_MB_OK, 
					W_U16 nFormat = DT_CENTER,
					W_U16 nTimer = 0);

/*-----------------------------------------------------------------------------
功    能: 显示消息对话框
参数说明: strTitle        标题
strContain      内容
nTyte           对话框类型(见上面宏定义)
nFormat         文本排版格式(见上面宏定义)
nTimer          定时器，单位ms，默认为零不处理，非零到达时自动返回
bInitWhenShowReturn  当设置为非阻塞模式时，是否需要初始化
返 回 值: 见上面宏定义
说    明: 无
2007-10-12 16:24:07
-------------------------------------------------------------------------*/
__MYEXPORT__
W_U16 adsMessageBox(const string &strTitle, 
				   const string &strContain, 
				   W_U16 nTyte = DF_MB_OK, 
				   W_U16 nFormat = DT_CENTER,
				   W_U16 nTimer = 0
				   );


__MYEXPORT__
W_U16 adsProgressBar( const string &strTitle, 
					 const string &strPrompt/*提示语*/, 
					 W_U16 uiPercen = 0, 
					 COLORREF ClrProgress = RGB(255,0,0), 
					 COLORREF ClrText = RGB(0,0,255));

__MYEXPORT__
W_U16 adsProgressBar(const CBinary &binTitle, 
					 const CBinary &binPrompt, 
					 W_U16 uiPercen = 0, 
					 COLORREF ClrProgress = RGB(255,0,0), 
					 COLORREF ClrText = RGB(0,0,255));


class ImpMessageBox;
class __MYEXPORT__ CUIMessageBox
{
public:
	CUIMessageBox(void);
	~CUIMessageBox(void);

	CUIMessageBox(CUIMessageBox const&);
	CUIMessageBox const& operator = (CUIMessageBox const&);
	/*
	** 功    能:初始化界面数据
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:设置界面标题 
	** 参    数:
	* @param strTitleText标题文本
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetTitle_ml(const string& strTitleText);

	/*
	** 功    能:设置文本内容 
	** 参    数:
	* @param strContentText	内容文本
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetContent(const string& strContentText);

	/*
	** 功    能:设置文本位置
	** 参    数:
	* @param nFormat	内容文本显示格式
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetContentFormat(W_U16 nFormat = DT_CENTER);

		/*
	** 功    能:设置文本颜色
	** 参    数:
	* @param clrText	内容文本颜色
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetContentClr(COLORREF clrText = RGB(0,0,0));

	/*
	** 功    能:设置类型
	** 参    数:
	* @param nType 类型
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetMsgType_ml(int nType);

	/*
	** 功    能:显示
	** 参    数:
	* @param nPara:0 不阻塞等待;1阻塞等待
	** 返 回 值:返回用户按的键，超时返回-2, #define RT_TIME_OUT		-2
	** 说	 明:点击的按钮
	*/
	W_I16 Show_ml(int nPara = SHOW_WAITE);

	/*
	** 功    能:设置消息框出现漏斗,只有消息框的文字为一页时,才显示漏斗图标
	** 参    数:
	* @param bBusy         设置是否显示漏斗图标 true 则启动定时器显示漏斗图标 false 则关闭定时器
	** 返 回 值:无
	** 说	 明:该函数必须是存在视图的情况下设置才能显示漏斗图标
	*/
	//void SetBusy(bool bBusy);

	/*
	** 功    能:定时返回功能
	** 参    数:
	* @param nTimer 定时的时间 
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetTimer_ml(W_I16 nTimer);

	/*
	** 功    能:启动显示首页界面 
	** 参    数:
	* @param nPara 预留参数
	** 返 回 值:无
	** 说	 明:无
	*/
	//void SetProgressPercent(W_I16 nPercent);

	/*
	** 功    能:启动显示首页界面 
	** 参    数:
	* @param nPara 预留参数
	** 返 回 值:无
	** 说	 明:无
	*/
	//W_I16 GetProgressPercent(void);

	/*
	** 功    能:设置按钮文本 
	** 参    数:
	* @param nID	按钮序号(0~n,根据AddButton的顺序)
	* @param strBtnText	按钮文本
	** 返 回 值:无
	** 说	 明:无
	*/
	void SetButtonText(int nID, const string& strBtnText);

	/*
	** 功    能:增加按钮 
	** 参    数:
	* @param strBtnText	按钮文本
	** 返 回 值:无
	** 说	 明:无
	*/
	void AddButton(const string& strBtnText);

	/*
	** 功    能:增加标题和内容 
	** 参    数:
	* @param strItem	标题
	* @param strValue 内容
	** 返 回 值:无
	** 说	 明:无
	*/
	void AddItemAndValue(string strItem, string strValue);


    //////////////////////////////////////////////////////////////////////////移植908 begin

    /*-----------------------------------------------------------------------------
	功    能：初始化
	参数说明：binCaptionText                标题文本ID
	binContainText                内容文本ID
	nType                         响应什么按键，默认MB_OK
	详细按键响应方式见上面宏定义 
	nFormat                       排版格式(区中、区左、区右)                

	返 回 值：无
	说    明：CBinary类型的ID从文本库中查询，如果未查询到此ID时会显示
	IDxxxxxxxxx未定义
	-----------------------------------------------------------------------------*/
	void Init(CBinary binCaptionText, CBinary binContainText, int nType = DF_MB_OK, W_U16 nFormat = DT_CENTER);

	/*-----------------------------------------------------------------------------
	功    能：初始化
	参数说明：pszCaptionText                标题文本ID
	pszContainText                内容文本ID
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void Init(const string &strCaptionText, const string &strContainText , int nType = DF_MB_OK, W_U16 nFormat = DT_CENTER, W_I32 iPercen = -1);

	void SetTitle(string const& strTitle);

	void SetContext(string const& strContext,  W_U16 uFormat = DT_CENTER, COLORREF clrText = RGB(0,0,0));

	void SetMsgType(int nType);


	/*-----------------------------------------------------------------------------
	功    能：显示
	参数说明：无
	返 回 值：W_I16         返回用户按的键

	说    明：1.当用户定义为无按键时显示完成后就返回
	2.当用户定义了响应指定按键时显示后就等待用户选择
	3.如果是DF_MB_FREE风格并且自定义的回退按钮，请在跳出循环的的判断兼容由退出诊断的5
	例如:
	CUIMessageBox uiMsg;
	uiMsg.Init("","",DF_MB_FREE);
	uiMsg.AddButtonFree("1");
	uiMsg.AddButtonFree("2");
	uiMsg.AddButtonFree("3");
	uiMsg.AddButtonFree("退出");

	while(true)
	{
		int nRet = uiMsg.Show();
		if( (nRet == DF_ID_FREEBTN_3) || (nRet == 5) )
		{
			break;
		}
		switch(nRet)
		{
			case DF_ID_FREEBTN_0:
			fun0();
			break;
			case DF_ID_FREEBTN_1:
			fun1();
			break;
			case DF_ID_FREEBTN_2:
			fun2();
			break;
		}
	}
	-----------------------------------------------------------------------------*/
	W_I16 Show();

	/*-----------------------------------------------------------------------------
	功    能：设置消息框出现漏斗,只有消息框的文字为一页时,才显示漏斗图标
	参数说明：bBusy         设置是否显示漏斗图标 true 则启动定时器显示漏斗图标 false 则关闭定时器
	返 回 值：无

	说    明：1.该函数必须是存在视图的情况下设置才能显示漏斗图标
	-----------------------------------------------------------------------------*/
	static void SetBusy(bool bBusy);

	/*-----------------------------------------------------------------------------
	功    能：取得按钮
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 GetKey();// 


	/*-----------------------------------------------------------------------------
	功    能：定时返回功能
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetTimer(W_I16 nTimer);

	/*-----------------------------------------------------------------------------
	功    能：设置OK、Cancel按钮的显示文本
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	static void SetOkBtnText(string str);
	static void SetCancelBtnText(string str);
	static void ResetOkBtnText();
	static void ResetCancelBtnText();


	/*-----------------------------------------------------------------------------
	功    能：添加按钮
	参数说明：
	str             按钮文本
	返 回 值：

	说    明：现在可以添加任意个按钮,不能调用adsmessagebox来显示自由按钮风格
	如
	// 该句代码会显示一个无按钮的视图
	//	adsMessageBox("2","22222\n2CUIMessageBox\n::SetCancelBtnText22222\n2CUIMessageBox",DF_MB_FREE);

	建议使用方式:
	ImpMessageBox msg;
	msg.Init("title", "\ntest\ntest\ntest\ntest\ntest\ntest\ntest\ntest\n", DF_MB_FREE);
	msg.AddButtonFree("test0");
	int nRet = msg.Show();
	if (DF_ID_FREEBTN_0 == nRet) 
	{
	//TRACE1("DF_ID_FREEBTN_0: %d\n", nRet);
	}

	注意:
	1. msg.Init("title", "\ntest\ntest\n", DF_MB_FREE);风格必须设置为DF_MB_FREE(用户添加自由按钮风格)
	2. 返回值需要与DF_ID_FREEBTN_0,DF_ID_FREEBTN_1,DF_ID_FREEBTN_2,DF_ID_FREEBTN_3,DF_ID_FREEBTN_4
	DF_ID_FREEBTN_5	等比较
	-----------------------------------------------------------------------------*/
	// 添加按钮(用户设置UImessageBox风格为 DF_MB_FREE 时该函数才能添加按钮)
	W_I16 AddButtonFree(const string& str);

	/*-----------------------------------------------------------------------------
	功    能：设置动态按钮文本
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 SetButtonText(W_I16 iBtnIndex, const string &str);

	/*-----------------------------------------------------------------------------
	功    能：设置焦点按钮
	参数说明：无
	返 回 值：无
	说    明：已经弃用
	-----------------------------------------------------------------------------*/
	W_I16 SetButtonFocus(W_I16 iBtnIndex);

	/*-----------------------------------------------------------------------------
	功    能：设置动态按钮是否启用
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	bool SetButtonStatus(W_I16 iBtnIndex, bool bEnable);

	/*-----------------------------------------------------------------------------
	功    能：清空动态按钮
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 ClearButton(); 


	/*-----------------------------------------------------------------------------
	功    能：设置获取进度条信息
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetProgressColor(COLORREF clr);
	void SetProgressPercent(W_I16 iPercent);
	W_I16 GetProgressPercent(void);

    //////////////////////////////////////////////////////////////////////////移植908 end
private:
	ImpMessageBox* m_pImpMessageBox;
};

#endif
