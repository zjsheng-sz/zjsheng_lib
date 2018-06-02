#pragma once
#include <string>
using namespace std;
class DecodeVIN_OC
{
public:
    static string StartDecordVINOnLine(const string & vin, const string & vehicleBrand, const string & vehicleAre);

    static void StopDecordVINOnLine();

    static void SetVehicleAreaToDiagVin(int vehicleAreaIndex);

    static void SetDiagVinPath(const string & path);

    static bool IsVehicleNeedComm(const string & vehicleBrand);
};
