#include "led.h"


led::led(GPIO_TypeDef *port, int pinnumber)
: port(port), pinnumber(pinnumber){};

void led::init(){
    //set pin as output
    port->MODER = (port->MODER & ~(3 << (pinnumber * 2))) | (1 << (pinnumber * 2));
    //set pin to push-pull
    port->OTYPER = (port->OTYPER & ~(1 << pinnumber)) | (0 << pinnumber);
}

void led::on(){
    port->ODR |= (1 << pinnumber);
}

void led::off(){
    port->ODR &= ~(1 << pinnumber);
}