#pragma once

#include <string>

void draw_color(int color);

// Reset current draw color
void draw_rcolor();

// Draw Filled rect
void draw_frect(int x, int y, int w, int h, char ch);

void draw_text(int x, int y, std::string str);

void draw_line(int x1, int y1, int x2, int y2, char ch);
