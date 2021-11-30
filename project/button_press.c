#include <msp430.h>
#include <stdlib.h>
#include "libTimer.h"
#include "ui.h"
#include "switches.h"
#include "buzzer.h"
#include "game_state_machine.h"

void button_press(int pressed_button) {
  switch(state) {
  case 0:
    //on state 0 we want to update the main menu ui based on the input
    //TODO
    break;
  case 1: //match in progress
    if (light.color == COLOR_GREEN){ //valid time to move
      check_player_move(pressed_button);
    }
    else if (light.color == COLOR_RED) {
      state = 2; //shoot a player
      to_shoot = check_red_move(pressed_button);
    }
    break;
  case 2: //shooting a player, do nothing
  case 3: //player winner, do nothing
    break;
  }
}
