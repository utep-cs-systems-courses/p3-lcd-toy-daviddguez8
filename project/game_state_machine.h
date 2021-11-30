#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include <lcdutils.h>

extern u_int work_to_be_done;
extern u_int state;
extern u_int to_shoot;

int winner_song(void);

void looser_song(void);

void run_game(void);

void button_press(int);

void check_player_move(int);

int check_red_move(int);

void light_timer(void);

#endif
