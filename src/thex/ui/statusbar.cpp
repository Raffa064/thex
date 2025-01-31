#include <interface/draw.hpp>
#include <interface/pallete.hpp>
#include <string>
#include <thex/editor.hpp>
#include <thex/ui/statusbar.hpp>

#define help_text " Mov: ^i <j vk >l Togg.Selection: s"

void StatusBar::draw() {
  Cursor cursor = editor->cursor;

  draw_color(PALETTE_STATUSBAR);
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');
  draw_text(pos.x, pos.y, "  THEX  " + cursor.to_string() + help_text);
  draw_rcolor();
}

StatusBar &StatusBar::operator=(StatusBar other) {
  editor = other.editor;

  return *this;
}
