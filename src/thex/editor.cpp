#include "draw.h"
#include "input.h"
#include "pallete.h"
#include "util.h"
#include <algorithm>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <thex/editor.h>

using namespace std;

void EditorBase::add_cursor(Cursor& c) {
  cursors.push_back(&c);
}

void EditorBase::remove_cursor(Cursor& c) {
  cursors.erase(remove(cursors.begin(), cursors.end(), &c));
}

int EditorBase::get_color(int bpos) {
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
  
  if (bpos < buffer.count) 
    return PALETTE_NON_EMPTY;

  if (bpos == buffer.count)
    return PALETTE_EOF;

  return PALETTE_NORMAL;
}

int THexEditor::get_bwidth() {
  return size.width / 3;
}

void THexEditor::draw() {
  string empty_cell = " ";

  int nwidth = get_bwidth() * 3;
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < nwidth; j += 3) {
      int bpos = (i * nwidth + j) / 3;
      int color = get_color(bpos);
      string display = empty_cell;

      if (bpos < buffer.count)
        display = to_hex(buffer.data[bpos]);
                    
      draw_color(color);
      draw_text(pos.x + j, pos.y + i, display);
      draw_rcolor();
    }
  }
}

bool THexEditor::accept(Event evt) {
  int resize = evt.axisl('w', 'e');
  if (resize) {
    size.width += 3 * resize;
    return true;
  }

  return false;
}

void THexAddrerssBar::draw() {
  for (int y = 0; y < size.height; y++) {
    string line_address = to_hex(editor.get_bwidth() * y);
    draw_text(pos.x, pos.y + y, padStart(line_address, size.width, '0'));
  }
}
