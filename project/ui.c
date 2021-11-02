#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ui.h"

Player p1; //TODO: implement players

Player p2; //TODO: implement players

Light light;

u_int background_color = COLOR_BLACK;

void init_ui(void) {

  //have a circle centered at the top
  light.top_left_col = 54;
  light.top_left_row = 5;
  light.color = COLOR_RED;
  light.height = 20;
  light.width = 20;

  fillRectangle(
		light.top_left_col, light.top_left_row, light.height, light.width, light.color
		);
  
  //have green squares to the sides of the screen simulating bushes
  fillRectangle(0, 0, 20, 168, COLOR_GREEN);
  fillRectangle(108, 0, 20, 168, COLOR_GREEN);
}

void flip_light(void) {
  light.color = light.color == COLOR_GREEN ? COLOR_RED : COLOR_GREEN;

  fillRectangle(
		light.top_left_col, light.top_left_row, light.height, light.width, light.color
		);
  
}
