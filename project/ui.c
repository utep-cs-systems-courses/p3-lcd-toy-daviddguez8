#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ui.h"

#define START_ROW 130;

Player p1; 

Player p2;

Light light;

u_int background_color = COLOR_BLACK;

void init_match_ui(void) {  

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
  fillRectangle(0, 0, 20, 168, COLOR_GREEN);
  fillRectangle(108, 0, 20, 168, COLOR_GREEN);

  //initialize and draw p1
  p1.height = 25;
  p1.width = 15;
  p1.center_x = 40;
  p1.center_y = START_ROW - p1.height/2 + 1;
  p1.top_left_x = p1.center_x - (p1.width/2);
  p1.top_left_y = START_ROW;
  p1.color = COLOR_RED;
  p1.move_button = 0; //start with left button

  draw_player(&p1);
  
  //initialize and draw p2
  
  p2.height = 25;
  p2.width = 15;
  p2.center_x = 88;
  p2.center_y = START_ROW - p2.height/2 + 1;
  p2.top_left_x = p2.center_x - (p2.width/2 + 1);
  p2.top_left_y = START_ROW;
  p2.color = COLOR_BLUE;
  p2.move_button = 0; //start moving with left

  draw_player(&p2);
}

void draw_player(Player *player) {
  fillRectangle(
		player->top_left_x,
		player->top_left_y,
		player->width,
		player->height,
		player->color
		); 
  
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

void update_player(int player, int y_step){
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
  to_update->center_y -= y_step;
  to_update->top_left_y -= y_step; 
  to_update->move_button = 1 - to_update->move_button; //flip the next correct move_button
  
  //redraw player with new positions
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

