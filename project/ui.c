#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ui.h"

#define START_ROW 135

Player p1; 

Player p2;

Light light;

Bullet bullet;

u_int background_color = COLOR_BLACK;

void init_match_ui(void) {  
  clearScreen(background_color);

  //have a light circle centered at the top
  light.top_left_x = 54;
  light.top_left_y = 5;
  light.color = COLOR_GREEN;
  light.height = 22;
  light.width = 22; 
  light.center_x = 128/2 + 1;
  light.center_y = 15;
  light.radius = 10;
  
  draw_circle(light.center_x, light.center_y, light.radius, light.color);  

  
  //have green squares to the sides of the screen simulating bushes
  fillRectangle(0, 0, 20, 168, COLOR_BROWN);
  fillRectangle(108, 0, 20, 168, COLOR_BROWN);
  draw_bushes();
  //initialize and draw p1
  p1.height = 25;
  p1.width = 15;
  p1.center_x = 40;
  p1.center_y = START_ROW;
  p1.top_left_x = p1.center_x - (p1.width/2);
  p1.top_left_y = START_ROW - p1.height/2 + 1;
  p1.color = COLOR_RED;
  p1.move_button = 0; //start with left button
  p1.score = '0';
  draw_player(&p1);
  
  //initialize and draw p2
  
  p2.height = 25;
  p2.width = 15;
  p2.center_x = 88;
  p2.center_y = START_ROW;
  p2.top_left_x = p2.center_x - (p2.width/2 + 1);
  p2.top_left_y = START_ROW - p2.height/2 + 1;
  p2.color = COLOR_BLUE;
  p2.move_button = 0; //start moving with left
  p2.score = '0';
  draw_player(&p2);

  draw_scores();
  
  //initialize unused bullet
  bullet.shot = 0;
  bullet.height = 3;
  bullet.width = 1; //lets make it 3x1
     
}

void draw_bushes() {
  u_int starting_y = 0;
  u_int offset = 20;
  u_int bush_r = 6;

  for(int i = 0; i < 10; i++) {
    draw_circle(10, starting_y+(offset*i), bush_r, COLOR_GREEN);
    draw_circle(118, starting_y+(offset*i)-5, bush_r, COLOR_GREEN);
  }
}

void draw_scores() {
  //clear previous scores
  drawChar5x7(57, 30, p1.score, p1.color, background_color);
  
  drawChar5x7(67, 30, p2.score, p2.color, background_color);
  
}

void update_score(int player) {
  Player *to_update = (player == 1) ? &p1 : &p2; 
  to_update->score+=1;
  draw_scores();
}

void draw_player(Player *player) {
  //fillRectangle(
  //		player->top_left_x,
  //		player->top_left_y,
  //		player->width,
  //		player->height,
  //		player->color
  //		); 
  
  //TODO: implement player graphics
  int head_radius = 3;
  int head_center_x = player->center_x;
  int head_center_y = player->top_left_y + head_radius + 2; 
  draw_circle(head_center_x, head_center_y, head_radius, COLOR_WHITE);

  //let's draw a vertical line for the body
  int start_body_y = player->top_left_y + (3*2) + 2; //already drew 8/25 pixels on y 
  int end_body_y = start_body_y + 10; //lets give it a body size of 10
  draw_vertical_line(start_body_y, end_body_y, player->center_x-1, 2, COLOR_WHITE);

  //we want to now draw the arms, just a horizontal line 3 pixels below the start_body_y
  int arms_y = start_body_y + 3;
  int start_arms = player->center_x - 4;
  draw_horizontal_line(start_arms, start_arms+9, arms_y, COLOR_WHITE);

  //for the legs I will draw two triangles
  //one on top of the first with a down offset of 2 pixels
  //this will basically draw two diagonal lines
  draw_triangle(4, 4, end_body_y-1, player->center_x, COLOR_WHITE);
  draw_triangle(4, 4, end_body_y+1, player->center_x, player->color);
}

int update_player(int player, int y_step){
  Player *to_update = (player == 1) ? &p1 : &p2; 
  //clear player 1
  fillRectangle(
		to_update->top_left_x,
		to_update->top_left_y,
		to_update->width,
		to_update->height,
		background_color
		); //clears the previous position of p1
 
  //update positions by y_step 
  to_update->center_y -= y_step;
  to_update->top_left_y -= y_step; 
  to_update->move_button = 1 - to_update->move_button; //flip the next correct move_button

  u_int final_position = to_update->center_y;
  
  if (final_position>= START_ROW) {
    to_update->center_y = START_ROW;
    to_update->top_left_y = START_ROW - to_update->height/2 + 1;
   }
  
  //redraw player with new positions
  draw_player(to_update);  

  if (final_position <= light.center_y) {
    return 1;
  }
  return 0;
}

void reset_player(int player) {
  Player *to_update = (player == 1) ? &p1 : &p2;

  //clear player 
  fillRectangle(
		to_update->top_left_x,
		to_update->top_left_y,
		to_update->width,
		to_update->height,
		background_color
		); //clears the previous position of player
  to_update->center_y = START_ROW;
  to_update->top_left_y = START_ROW - to_update->height/2 + 1; 
  draw_player(to_update);
}

//draws a vertical line starting from y_start to y_end
//thickness will be the thickness (in pixels) starting from x to the right
void
draw_vertical_line(u_int y_start, u_int y_end, u_int x, u_int thickness, u_int colorBGR) {
  u_int length = y_end - y_start;
  fillRectangle(x, y_start, thickness, y_end-y_start, COLOR_WHITE);
}

void
draw_horizontal_line(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
}

void
draw_lines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  draw_horizontal_line(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  draw_horizontal_line(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  draw_horizontal_line(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  draw_horizontal_line(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
  
}

void flip_light(void) {
  light.color = light.color == COLOR_GREEN ? COLOR_RED : COLOR_GREEN;
  draw_circle(light.center_x, light.center_y, light.radius, light.color);  

  //fillRectangle(
  //light.top_left_col, light.top_left_row, light.height, light.width, light.color
  //);  
}

void
draw_circle(int x, int y, int r, u_int color)
{
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  draw_lines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    draw_lines(x_coord, y_coord, x_point, y_point, color);
  }
}

//draws a triangle with given height. Works for drawing the legs...
void
draw_triangle(u_int height, u_int width, u_int top_y, u_int center_x, u_int color)
{
  //we want to calculate the slope
  //for that we want to get the bottom corner
  u_int left_bottom_x = center_x - (width/2);
  u_int left_bottom_y = top_y + height;

  //to calculate the slope we can use the slope formula
  //m = (y2-y1)/(x2-x1)
  u_int rise = height;
  u_int run = width/2;

  //this means that each time the slope should grow in the y-axis by rise pixels, and x-axis by run pixels
  //we are interested in how much the x should change for 1 growth in pixel on the y-axis
  u_int x_step = 1;

  u_int count = 0;

  while(count <= height) {
    u_int curr_step = x_step*count;
    draw_horizontal_line(center_x-(curr_step), center_x+(curr_step), top_y+count, color); 
    ++count;
  }
}

int update_bullet_towards_player(int towards) {
  Player *player_shot = towards == 1 ? &p1 : &p2;
  static u_int count = 10;
  
  //if bullet hasn't been shot, initialize its values
  if(!bullet.shot) {
    bullet.shot = 1;
    bullet.center_x = player_shot->center_x;
    bullet.center_y = 0;
  }
  
  //clear previous bullet position
  fillRectangle(
		bullet.center_x,
		bullet.center_y,
		3,
		3,
		background_color
		);
  
  bullet.center_y+=3;

  fillRectangle(
		bullet.center_x,
		bullet.center_y,
		1,
		3,
		COLOR_WHITE
		);
  
  if(bullet.center_y >= player_shot->center_y) {
    count = 10;//reset count
    bullet.shot = 0;
    return 1;
  }
  return 0;
}


