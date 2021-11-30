#include <msp430.h>
#include "led.h"

void led_init(void)
{
  P1DIR |= LEDS;		// bits attached to leds are output
  P1OUT &= ~LED_RED;
}

void red_led(int on)
{ 
  if(on) {
    P1OUT |= LED_RED;
  } else {
    P1OUT &= ~LED_RED;
  }
}

