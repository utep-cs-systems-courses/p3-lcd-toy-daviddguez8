#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "game_state_machine.h"
#include "ui.h"

int switches = 0;
int switch_blame = 0;
char switch1_down;
char switch2_down;
char switch3_down;
char switch4_down;
/* Updates when the interrupt fires and returns current state of switches */
static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init(void)		/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}
//debugged, it works
void
switch_interrupt_handler(void)
{
  char p2val = switch_update_interrupt_sense();

  switches = ~p2val & SWITCHES;
  
  switch1_down = (p2val & SW1) ? 0 : 1;
  switch2_down = (p2val & SW2) ? 0 : 1;
  switch3_down = (p2val & SW3) ? 0 : 1;
  switch4_down = (p2val & SW4) ? 0 : 1;
  switch(switch_blame) {
  case SW1:
    if (switch1_down) {
      button_press(SW1);
    }
    break;
  case SW2:
    if (switch2_down) {  
      button_press(SW2);
    }
    break;  
  case SW3:
    if (switch3_down) {
      button_press(SW3);
    }
    break;
  case SW4:
    if (switch4_down) {
      button_press(SW4);
    }
    break;
  }
}

