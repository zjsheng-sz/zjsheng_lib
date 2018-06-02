//
//  AUTVCIUpdate.hpp
//  VCIUpdate
//
//  Created by autel on 17/4/18.
//  Copyright ? 2017年 autel. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
using namespace std;

class AUTVCIUpdate
{
public:
    static bool OpenDevice();                          //打开设备
    
    static bool CloseDevice();                         //关闭设备
    
    static string GetDeviceVersion();                  //获取固件版本
    
    static int GetSignature();                         //获取硬件编号
    
    static int StartUpgrade(string jstrFilePath);      //开始升级
};
