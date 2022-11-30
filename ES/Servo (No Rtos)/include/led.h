#ifndef LED_H
#define LED_H

#include "stm32f303xe.h"
class led
{
private:
    GPIO_TypeDef *port;
    uint16_t pinnumber;
public:
    led(GPIO_TypeDef *port, int pinnumber);
    void init();
    void on();
    void off();
};


#endif
