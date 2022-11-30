#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "cmsis_os.h"
#include "gpio.h"

class WatchDog
{
    public:

        void SetWatchDog(int prValue, int rlrValue);
        void ReloadWatchdog();
};

#endif