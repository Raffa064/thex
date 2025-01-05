#include "draw.h"
#include "pallete.h"
#include "util.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <thex/editor.h>

using namespace std;

void DisplayBuffer::dynamic_resize(int len) {
  length = len;
  
  int new_length = len * (1. + growth_factor);

  int grow_diff = allocated * growth_factor;
  if (abs(allocated - new_length) < grow_diff)
    return;

  if (buffer != nullptr) {
    delete[] buffer;
  }

  buffer = new char[new_length];
  allocated = new_length;
}

DisplayBuffer::DisplayBuffer(int length, float growth_factor) {
  this->growth_factor = growth_factor;
  dynamic_resize(length);
}

DisplayBuffer::~DisplayBuffer() { delete[] buffer; }

void THexEditor::add_cursor(Cursor &c) { cursors.push_back(&c); }

void THexEditor::remove_cursor(Cursor &c) {
  cursors.erase(remove(cursors.begin(), cursors.end(), &c));
}

int THexEditor::get_cursor_line(Cursor &cursor) {
  int onscreen = cursor.get_start() - display.position;

  return onscreen / get_bwidth();
}

int THexEditor::get_color(int bpos) {
  int overlaps = 0;
  int color;

  for (auto c : cursors) {
    bool start = bpos == c->get_start();
    bool mid = bpos > c->get_start() && bpos < c->get_end();
    bool end = bpos == c->get_end();

    if (start || (c->is_selection() && (mid || end))) {
      overlaps++;
      color = c->get_color();
    }
  }

  if (overlaps == 1)
    return color;

  if (overlaps > 1)
    return PALETTE_CURSOR_OVERLAP;

  if (bpos < display.length)
    return PALETTE_NON_EMPTY;

  if (bpos == display.eof && display.eof >= 0)
    return PALETTE_EOF;

  return PALETTE_NORMAL;
}

int THexEditor::get_bwidth() { return (size.width - FIXED_SIZE) / 4; }

int THexEditor::get_bcount() { return get_bwidth() * size.height; }

void THexEditor::draw() {
  int bwidth = get_bwidth(); // per line displayed bytes

  for (int y = 0; y < size.height; y++) {
    int on_screen_line = bwidth * y;
    string addr_str = to_hex(display.position + on_screen_line, ADDR_SIZE);

    draw_text(pos.x, pos.y + y, addr_str);

    for (int b = 0; b < bwidth; b++) {
      int pos_d = on_screen_line + b;      // position in buffer (display buffer)
      int pos_buf = display.position + pos_d; // position in file
      int color = get_color(pos_buf);
      bool invisible = false;

      string curr_b = "  ";
      char curr_c = '.';

      if (pos_buf < display.eof) { // TODO: less than EOF
        curr_c = display.buffer[pos_d];
        curr_b = padStart(to_hex(curr_c), 2, '0');

        // Check for ASCII printable chars
        if (curr_c < 0x20 || curr_c > 0x7E) {
          curr_c = '.';
          invisible = true;
        }
      }

      draw_color(color);
      int offsetX = pos.x + ADDR_SIZE + 1;
      draw_text(offsetX + (b * 3), pos.y + y, curr_b);


      if (invisible) attron(A_REVERSE);
      
      offsetX += (bwidth * 3) + 1;
      mvaddch(pos.y + y, offsetX + b, curr_c);
      draw_rcolor();

      attroff(A_REVERSE);
    }
  }
}

/*  string empty_cell = " ";

  int nwidth = get_bwidth() * 3;
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < nwidth; j += 3) {
      int bpos = (i * nwidth + j) / 3;
      int color = get_color(bpos);
      string draw = empty_cell;

      if (bpos < display.length)
        draw = to_hex(display.buffer[bpos]);

      draw_color(color);
      draw_text(pos.x + j, pos.y + i, draw);
      draw_rcolor();
    }
  }
}


void THexAddressBar::draw() {
  for (int y = 0; y < size.height; y++) {
    string line_address = to_hex(editor.get_bwidth() * y);
    draw_text(pos.x, pos.y + y, padStart(line_address, size.width, '0'));
  }
}

int THexPreview::get_bwidth() {
  return size.width;
}

void THexPreview::draw() {
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < size.width; j++) {
      int bpos = i * size.width + j;
      int color = get_color(bpos);
      int ch = ' ';

      if (bpos < display.length)
        ch = display.buffer[bpos];

      draw_color(color);
      mvaddch(pos.y + i, pos.x + j, ch);
      draw_rcolor();
    }
  }
}*/
