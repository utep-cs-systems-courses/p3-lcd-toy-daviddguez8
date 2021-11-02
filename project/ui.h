#ifndef _UI_H_
#define _UI_H_

#include <lcdutils.h>

typedef struct player_st {
  int top_left_y;
  int top_left_x;
  int center_x;
  int center_y;
  u_char height;
  u_char width;
  u_int color;
} Player;

//TODO: add actual things to this
typedef struct bullet_st {
  int top_left_y;
  int top_left_x;
  int old_y;
  int old_x;
  u_char height;
  u_char width;
} Bullet;

typedef struct light_st {
  int top_left_y;
  int top_left_x;
  int center_x;
  int center_y;
  u_int color;
  u_char height;
  u_char width;
  u_char radius;
} Light;

//initializes a new match, with the initial ui
void init_ui(void);

//clears the previous position and updates to new one
//params: 1 for player 1, 2 for player 2
void update_player(int);

//change the color of the light (red or green)
void flip_light(void);

//draws circle with given center (row, col)  and radius
void draw_circle(int, int, int, u_int);

//draws given player in screen
void draw_player(Player *player);

//draws an equilateral triangle with given parameters
void draw_triangle(u_int height, u_int width, u_int top_y, u_int center_x, u_int color);

void draw_vertical_line(u_int y_start, u_int y_end, u_int x, u_int thickness, u_int colorBGR);

void draw_horizontal_line(u_int, u_int, u_int, u_int);

void draw_lines(u_int, u_int, u_int, u_int, u_int);

#endif // _UI_H_
