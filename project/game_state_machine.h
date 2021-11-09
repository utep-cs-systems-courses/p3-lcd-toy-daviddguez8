#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include <lcdutils.h>

void run_game(void);

void button_press(int);

void check_player_move(int);

int check_red_move(int);

void light_timer(void);

#endif
