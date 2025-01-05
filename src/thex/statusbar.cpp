#include "draw.h"
#include "pallete.h"
#include "util.h"
#include <string>
#include <thex/statusbar.h>

using namespace std;

#define help_text "Mov: ^i <j vk >l Togg.Selection: s"

void THexStatusBar::draw() {
  string cursorEnd = cursor.is_selection() ?
    "" : 
    (":" + padStart(to_hex(cursor.get_end()), 8, '0'));

  draw_color(PALETTE_CURSOR_GREEN);
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');
  mvprintw(pos.y, pos.x, " %s [ %s%s ] %s", 
           padEnd("HEX", 7, ' ').c_str(), // HEX ASCII
           padStart(to_hex(cursor.get_start()), 8, '0').c_str(),
           cursorEnd.c_str(),
           help_text
  );
  draw_rcolor();
}
