#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "ui.h"
#include "game_state_machine.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

void main()
{
  configureClocks();
  buzzer_init();
  led_init();
  red_led(1); //turn red led on since CPU being used
  lcd_init();
  clearScreen(background_color);
  switch_init();
  init_match_ui();

  enableWDTInterrupts();

  or_sr(0x18);	/**< CPU off , GIE on*/

  red_led(0); //turn red led off since CPU not being used
  while(1) {
    if(work_to_be_done){
      red_led(1);//CPU being used
      work_to_be_done = 0;
      run_game();
    }
    
    or_sr(0x18); // CPU off, GIE on
    red_led(0); //CPU not used anymore
  }
}
