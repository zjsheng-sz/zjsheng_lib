#pragma once
#include <string>
using namespace std;

/******************************** AutoVIN **************************************/
class AutoVINOpr_OC {
public:
    static void StartVINGetting();
    static void CancelVINGetting();
    static string GetVehicleTypeOfVIN(string strVIN);

    static void SetFunc(void *VINGettingResult
        , void *VINGettingProgress
        );
};