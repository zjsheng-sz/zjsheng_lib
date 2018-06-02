#ifndef SYSINTERFACE_H_HEADER_INCLUDED_B97FC958
#define SYSINTERFACE_H_HEADER_INCLUDED_B97FC958


#include "adsStd.h"
#include "UIMessageBox.h"


class CSysInterface
{
  public:
    CSysInterface();
  
    class CSysKeyboard
    {
    public:
        CSysKeyboard()
        {
            //m_ucBackKeyCount = 0;
        }
        typedef enum
        {
            KEY_NOKEY = 0x00,
             KEY_F1 = DF_IDYES,
            KEY_F3 = DF_IDNO,
        } KEY_DEF;
     
    };


};



#endif /* SYSINTERFACE_H_HEADER_INCLUDED_B97FC958 */
