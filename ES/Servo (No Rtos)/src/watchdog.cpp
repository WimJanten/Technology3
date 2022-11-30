#include "watchdog.h"

void WatchDog::SetWatchDog(int prValue, int rlrValue)
{
  IWDG -> KR |= IWDG_KEY_ENABLE;
  IWDG -> KR |= IWDG_KEY_WRITE_ACCESS_ENABLE;
  IWDG -> PR |= prValue;
  IWDG -> RLR = rlrValue; 
  IWDG -> KR |= IWDG_KEY_RELOAD;
  IWDG -> KR |= IWDG_KEY_ENABLE;
  IWDG -> KR |= IWDG_KEY_WRITE_ACCESS_DISABLE;
}

void WatchDog::ReloadWatchdog()
{
  IWDG -> KR |= IWDG_KEY_RELOAD;
}