#include "draw.h"
#include "pallete.h"
#include "util.h"
#include <string>
#include <thex/statusbar.h>

using namespace std;

#define help_text " Mov: ^i <j vk >l Togg.Selection: s"

void THexStatusBar::draw() {
  draw_color(PALETTE_CURSOR_GREEN);
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');
  draw_text(pos.x, pos.y,  "  THEX  " + cursor.to_string() + help_text);
  draw_rcolor();
}
