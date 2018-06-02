/*
 * WebDefine.h
 *
 *  Created on: 2016-6-2
 *      Author: A15386
 */

#ifndef _H_UIMSGBOXDEFINE_H_20160906_164533
#define _H_UIMSGBOXDEFINE_H_20160906_164533


// 文本排版方式,用于nFormat
#ifndef DT_LEFT
#define DT_LEFT             0x00000000
#endif

#ifndef DT_CENTER
#define DT_CENTER           0x00000001
#endif

#ifndef DT_RIGHT
#define DT_RIGHT            0x00000002
#endif


//用户按键键值 用于nTyte参数
const int DF_MB_NOBUTTON = 0x00;    // 无按键(show后就返回)

const int DF_MB_YES = 0x01;    // 等待按下yes后才返回
const int DF_MB_NO = 0x02;// 等待按下no后才返回
const int DF_MB_YESNO = 0x03;    // 等待按下yes或No后才返回

const int DF_MB_OK = 0x04;    // 等待按下yes后才返回
const int DF_MB_CANCEL = 0x08;    // 等待按下no后才返回
const int DF_MB_OKCANCEL = 0x0c;    // 等待按下yes或No后才返回

const int DF_MB_START = 0x10;    
const int DF_MB_BACK = 0x20;    // back按钮    
const int DF_MB_START_BACK = 0x30;    

const int DF_MB_ANYKEYRETURN = DF_MB_OK;//0x40    // 任何按键   
const int DF_MB_HAVEBUTTON_DRAW_THEN_RETURN = 0x80;    // 有按钮绘制后然后返回    

const int DF_MB_BACKHELP = 0x0100;    // 返回和帮助(仅用于帮助模式)   

// 图标类型，可和上面组合使用,如 DF_MB_OK | DF_MB_ICONERROR
const int DF_MB_ICON_WARNING = 0x010000;  // 警告
const int DF_MB_ICON_INFO = 0x020000; // 信息
const int DF_MB_ICON_QUESTION = 0x030000;  // 问号 
const int DF_MB_ICON_ERROR = 0x040000;  // 错误



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

const int DF_IDSTART = KEY_PRESS_F1; 

// 设置自由控件风格
const int DF_MB_FREE = 0x200;

//以下宏用于点击自由按钮时对话框的返回值
const int DF_ID_FREEBTN_0 = 100;   
const int DF_ID_FREEBTN_1 = 101;    
const int DF_ID_FREEBTN_2 = 102;   
const int DF_ID_FREEBTN_3 = 103;   
const int DF_ID_FREEBTN_4 = 104;    
const int DF_ID_FREEBTN_5 = 105; 



#endif /* _H_UIMSGBOXDEFINE_H_20160906_164533 */
