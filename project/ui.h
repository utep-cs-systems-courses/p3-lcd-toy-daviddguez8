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
  u_int move_button; //can be either 0 or 1, 0 for the left, 1 for right.
  char score;
} Player;

extern Player p1, p2;

//TODO: add actual things to this
typedef struct bullet_st {
  int shot; //flag to indicate if current bullet was shot(1), else(0) re-initialize
  int top_left_y;
  int top_left_x;
  int center_x;
  int center_y;
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

extern Light light;

//initializes a new match, with the initial ui
void init_match_ui(void);

void draw_scores();

void update_score(int);

//used by init_match_ui() to draw the bushes on both sides
void draw_bushes(void);
//clears the previous position and updates to new one by y_step pixels on y-axis
int update_player(int player, int y_step);

//resets specified player to initial position
void reset_player(int player);

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

//updates the bullet moving towards specified player (1 or 2)
//returns 1 if bullet hits, 0 otherwise
int update_bullet_towards_player(int);

#endif // _UI_H_
