#ifndef NET_LAYER_H
#define NET_LAYER_H

#ifdef _USRDLL
#define IMPORT_EXPORT _declspec(dllexport)
#else
#define IMPORT_EXPORT _declspec(dllimport)
#endif



#include "DevInterface.h"

typedef struct{
	unsigned long dev_id;
	unsigned long pin_complex;
	CDevInterface* pDevInterface;
	char dev_name[80];
}DEVICE_MANAGER, *PDEVICE_MANAGER;


long ECU_Open(char* cDevName, unsigned long* pDeviceID);
//long ECU_Close(long DeviceID);
void ECU_Close_All();

#ifdef __cplusplus
extern "C" {
#endif

    //IMPORT_EXPORT long WINAPI ECU_Open(char* cDevName, unsigned long* pDeviceID);

    //IMPORT_EXPORT long WINAPI ECU_Close(long DeviceID);

#ifdef __cplusplus
}

#else




#endif


#endif /*NET_LAYER_H*/

