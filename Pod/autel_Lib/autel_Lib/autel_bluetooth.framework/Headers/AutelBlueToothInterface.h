//

#ifndef AutelBlueToothInterface_hpp
#define AutelBlueToothInterface_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class BluetoothManager_OC {
public:
    static void SetFunc(void *openBluetooth
                        , void *closeBluetooth
                        , void *sendToBluetooth
                        , void *receiveFromBluetooth
                        );
};

#endif /* AutelBlueToothInterface_hpp */
