#include <msp430.h>
#include <stdlib.h>
#include "libTimer.h"
#include "ui.h"
#include "switches.h"

#define STEP 3

static u_int state = 1; //start in main menu (0), for testing using 1 (game) 
static u_int initialize = 1; //flag to indicate the state was just switched, thus initialize it.
static u_int to_shoot = 0;

//called 250/second, handles state control and run of the game
void run_game(void) {
  switch(state) {
  case 0:
    //run main menu
    break;
  case 1: //match in progress
    if(initialize) {
      init_match_ui();
      initialize = 0;
    }
    light_timer();
    //if winner:
    //state = 3;
    break;
  case 2://player killed
    //shoot_player();
    //if bullet hits:
    //  reset_player();
    //  state = 1;
    //  initialize = 0; no need to initialize 
    break;
  case 3://player won
    //update_score();
    break;
  }    
}  

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
  case 2: //shooting a player, do nothing
  case 3: //player winner, do nothing
    break;
  }
}

void check_player_move(int pressed_button) {
  int expected_button;
  int player = 0;
  //It is a player 1 movement
  if (pressed_button & (SW1 | SW2)) {
    player = 1;
    expected_button = p1.move_button == 0 ? SW1 : SW2;
  }
  //it is a player 2 movement
  else if (pressed_button & (SW3 | SW4)) {
    player = 2;    
    expected_button = p2.move_button == 0 ? SW3 : SW4;
  }
  
  //correct button was pressed, move step pixels up
  if (pressed_button & expected_button) {
    update_player(player, STEP);
  }
  //wrong button, move step pixels down
  else {
    update_player(player,-STEP);
  }
}

int check_red_move(int pressed_button) {
  if (pressed_button & (SW1 | SW2)){
    //p1 invalid move
    return 1;
  }
  else if (pressed_button & (SW3 | SW4)) {
    //p2 invalid move
    return 2;
  }
  return 0; //default
}

void light_timer(void) {
  const int times[12] = {4, 3, 5, 2, 2, 2, 4, 1, 3, 1, 4, 1};
  static int times_idx = 0;
  const  u_int second_limit = 250;
  static u_int main_count = 0;
  static u_int second_count = 0;
  static u_int curr_limit = 3;

  ++main_count;

  if (main_count >= second_limit) {
    //flip_light();
    main_count = 0;
    second_count++; //indicates a second passed
  }

  if (second_count >= curr_limit) {
    flip_light();
    if (light.color == COLOR_GREEN) {
      //it flipped to a green color
      curr_limit = times[times_idx]; //max time to transition will be 6 seconds
      times_idx++;
      if(times_idx >= 12) {
	times_idx = 0;
      }
    }
    else {
      curr_limit = 2; //red light to always last 2 seconds
    }
    second_count = 0;
  }
}
