#include "thex/preview.h"
#include "draw.h"

int THexPreview::get_bwidth() {
  return size.width;
}

void THexPreview::draw() {
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < size.width; j++) {
      int bpos = i * size.width + j;
      int color = get_color(bpos);
      int ch = ' ';

      if (bpos < buffer.count)
        ch = buffer.data[bpos]; 

      draw_color(color);
      mvaddch(pos.y + i, pos.x + j, ch);
      draw_rcolor();
    }
  }
}
