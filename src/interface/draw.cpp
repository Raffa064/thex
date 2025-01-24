#include <cmath>
#include <interface/draw.h>
#include <ncurses.h>

#define draw(x, y, ch) mvaddch(y, x, ch)

int currentColor;

void draw_color(int color) {
  currentColor = color;
  attron(COLOR_PAIR(currentColor));
}

void draw_rcolor() { attroff(COLOR_PAIR(currentColor)); }

void draw_frect(int px, int py, int w, int h, char ch) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      draw(px + x, py + y, ch);
    }
  }
}

void draw_text(int x, int y, std::string str) {
  mvprintw(y, x, "%s", str.data());
}

void draw_line(int x1, int y1, int x2, int y2, char ch) {
  int lx = x2 - x1;
  int ly = y2 - y1;

  float step = sqrt(pow(lx, 2) + pow(ly, 2));
  for (float t = 0; t < 1; t += step) {
    draw(x1 + lx * t, y1 + ly * t, ch);
  }
}
