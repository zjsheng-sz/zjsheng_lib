#pragma once
#include "UIMessageBox.h"
class __MYEXPORT__ CUIMenu
{
public:
	CUIMenu(void);
	~CUIMenu(void);

	void Init(const CBinary &binTitleTextID);
	bool Add(CBinary const& bin);
    bool Add(const string & strItem);
	W_I16 Show(int iSelected = -1);
private:
	CUIMessageBox *pMsg;
};
