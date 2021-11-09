#include <msp430.h>
#include "libTimer.h"
//#include "draw_shapes.h"
#include "ui.h"

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  run_game();
  /*
  const  u_int second_limit = 250;
  static u_int second_count = 0;

  const u_int tenth_limit = 5;

  second_count++;

  if (second_count >= second_limit) {
    //flip_light();
    //update_player(1, 1);
    //update_player(2, 2);
    second_count = 0;
    } */
} 

