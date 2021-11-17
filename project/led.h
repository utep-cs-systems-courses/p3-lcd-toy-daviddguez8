#ifndef led_included
#define led_included

#define LED_RED   BIT6         // P1.6
#define LED_GREEN 0      // P1.0 not used with lcd
#define LEDS (LED_RED)


void led_init(void);
void red_led(int);

#endif // included
