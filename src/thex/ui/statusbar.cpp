#include <interface/draw.h>
#include <interface/pallete.h>
#include <string>
#include <thex/editor.h>
#include <thex/ui/statusbar.h>

using namespace std;

#define help_text " Mov: ^i <j vk >l Togg.Selection: s"

void StatusBar::draw() {
  Cursor cursor = editor->cursor;

  draw_color(PALETTE_STATUSBAR);
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');
  draw_text(pos.x, pos.y, "  THEX  " + cursor.to_string() + help_text);
  draw_rcolor();
}
