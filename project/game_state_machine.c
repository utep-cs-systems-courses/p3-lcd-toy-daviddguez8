#include <msp430.h>
#include <stdlib.h>
#include "libTimer.h"
#include "ui.h"
#include "switches.h"
#include "buzzer.h"

#define STEP 5
 
extern u_int work_to_be_done = 0; //flag to indicates CPU need to come back on

extern u_int state = 1; //start in main menu (0), for testing using 1 (game) 
static u_int initialize = 1; //flag to indicate the state was just switched, thus initialize it.
static u_int to_shoot = 0;
static u_int winner = 0;

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
    if(to_shoot == 0) {
      //error happened?
      state = 0;
      initialize = 0; //start over
      break;
    }
    looser_song();
    int bullet_hit = update_bullet_towards_player(to_shoot);
    if(bullet_hit){ 
      reset_player(to_shoot);//reset position
      state = 1;//change state
      initialize = 0;//don't reinitialize the screen
      to_shoot = 0;//reset the person to shoot
      buzzer_set_period(0);//turn off the song
    }
    break;
  case 3: ;//player scored
    //will reproduce a song, returns 1 when done so we can reset player
    int done = winner_song();
    if(done == 1) {
      reset_player(1);
      reset_player(2);
      update_score(winner);
      state = 1;
      initialize = 0;
      to_shoot = 0;
      winner = 0;
      buzzer_set_period(0);
    }
    break;
  }    
}

//called about 4 times per second, reproduce a different note every time
//returns 0 until song is done.
int winner_song() {
  static u_int index = 0;
  const int notes[4] = {3000, 4000, 4050, 2000};
  static u_int count = 0;
  const int periods[4] = {3, 1, 1, 4};

  buzzer_set_period(notes[index]);

  if(count >= periods[index]) {
    count = 0;
    index++;
  }

  if(index >= 4){
    index = 0;
    count = 0;
    return 1;
  }
  count++;
  return 0;
}

//called once every 10th of a second, reproduces a song
void looser_song() {
  static u_int index = 0;
  const int notes[5] = {1100, 2000, 3100, 5100, 8100};
  
  buzzer_set_period(notes[index]);
  index++;
  if(index>=5) {
    index = 0;
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
    break;
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
    if(update_player(player, STEP) == 1) {
      //player won, change state
      state = 3;
      winner = player;
      return;
    }
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

//called every second, flips the color of the light by different time frames
void light_timer(void) {
  const int times[12] = {4, 3, 5, 3, 1, 2, 4, 2, 3, 4, 1, 1};
  static int times_idx = 0;
  //const  u_int second_limit = 250;
  static u_int main_count = 0;
  //static u_int second_count = 0;
  static u_int curr_limit = 3;

  
  ++main_count;

  if (main_count >= curr_limit) {
    flip_light();
    if (light.color == COLOR_GREEN) {
      //it flipped to a green color
      curr_limit = times[times_idx]; 
      times_idx++;
      if(times_idx >= 12) {
	times_idx = 0;
      }
    }
    else {
      curr_limit = 2; //red light to always last 2 seconds
    }
    main_count = 0;
  }
}

