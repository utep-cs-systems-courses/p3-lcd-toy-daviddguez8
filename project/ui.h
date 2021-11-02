#ifndef _UI_H_
#define _UI_H_

#include <lcdutils.h>

typedef struct player_st {
  int top_left_row;
  int top_left_col;
  int old_row;
  int old_col;
  u_char height;
  u_char width;
} Player;

//TODO: add actual things to this
typedef struct bullet_st {
  int top_left_row;
  int top_left_col;
  int old_row;
  int old_col;
  u_char height;
  u_char width;
} Bullet;

typedef struct light_st {
  int top_left_row;
  int top_left_col;
  u_int color;
  u_char height;
  u_char width;
} Light;

//initializes a new match, with the initial ui
void init_ui(void);

//clears the previous position and updates to new one
//params: 1 for player 1, 2 for player 2
void update_player(int);

//change the color of the light (red or green)
void flip_light(void);

#endif // _UI_H_
