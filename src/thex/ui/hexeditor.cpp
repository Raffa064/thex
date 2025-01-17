#include "interface/input.h"
#include <cstdlib>
#include <cstring>
#include <interface/draw.h>
#include <interface/pallete.h>
#include <ncurses.h>
#include <string>
#include <thex/ui/hexeditor.h>
#include <util.h>

using namespace std;

int HexEditor::get_bwidth() { return (size.width - FIXED_SIZE) / 4; }

int HexEditor::get_bcount() { return get_bwidth() * size.height; }

// TODO: implement nibble cursor
int HexEditor::get_color(int addr, int nibble) {
  if (addr < 0 || addr > display.end())
    return PALETTE_EMPTY;

  if (addr == editor->get_fsize())
    return PALETTE_EOF;

  Cursor cursor = editor->cursor;
  if (cursor.selection) {
    if (cursor.overlaps(addr))
      return PALETTE_CURSOR;
  } else {
    if (addr == cursor.start && nibble == cursor.nibble)
      return PALETTE_CURSOR;
  }

  int m_color = -1;
  for (Marker *m : editor->markers) {
    if (m->overlaps(addr))
      m_color = m->color;
  }

  if (m_color >= 0)
    return m_color;

  return PALETTE_NORMAL;
}

int HexEditor::get_color(int addr) {
  int high_nibble = get_color(addr, 0);
  int low_nibble = get_color(addr, 1);

  // Important highlights have higher  value than others
  return max(high_nibble, low_nibble);
}

void HexEditor::resize() {
  // Resize to the on screen byte count + one more line
  int length = get_bcount();
  display.buffer.resize(length);
}

void HexEditor::draw() {
  editor->read_page(display); // TODO: optmize do read only if necessary

  display_cursor();

  int bwidth = get_bwidth(); // line size in bytes
  int line_width = (bwidth * 3) + 1;

  for (int line = 0; line < size.height; line++) {
    int line_addr = display.position + (line * bwidth);

    draw_addr(pos.x, pos.y + line, line_addr);

    for (int b_index = 0; b_index < bwidth; b_index++) { // byte index
      int byte_addr = line_addr + b_index;
      int x = pos.x + ADDR_SIZE + 1;
      int y = pos.y + line;

      char byte = '.';

      if (byte_addr < display.end()) {
        byte = display.get(byte_addr);

        // Check for ASCII printable chars
        if (byte < 0x20 || byte > 0x7E)
          attron(A_REVERSE);
      }

      draw_byte(x + (b_index * 3), y, byte_addr, byte);
      draw_char(x + line_width + b_index, y, byte_addr, byte);

      attroff(A_REVERSE);
    }
  }
}

bool HexEditor::accept(Event evt) {
  Cursor &cursor = editor->cursor;

  int moveX = 0;
  int moveY = 0;

  switch (evt.keycode) {
  case 'j':
  case KEY_LEFT:
    moveX = -1;
    break;
  case 'l':
  case KEY_RIGHT:
    moveX = 1;
    break;
  case 'i':
  case KEY_UP:
    moveY = -get_bwidth();
    break;
  case 'k':
  case KEY_DOWN:
    moveY = get_bwidth();
    break;
  case 's':
    cursor.selection = !cursor.selection;
    break;
  default:
    return false;
  }

  cursor.move(moveY);

  if (cursor.selection)
    cursor.move(moveX);
  else
    cursor.moven(moveX);

  unsigned eof = editor->get_fsize();
  cursor.set(min(eof - 1, cursor.get())); // Clamp to EOF

  return true;
}

void HexEditor::display_cursor() {
  unsigned eof = editor->get_fsize();
  int line_bytes = get_bwidth();
  int cpos = editor->cursor.get();

  uint newPosition = display.position;

  if (cpos < display.position) {
    newPosition = (cpos / line_bytes) * line_bytes;
  }

  if (cpos >= display.end())
    newPosition += line_bytes;

  display.position = min(eof, max((unsigned)0, newPosition));
}

void HexEditor::draw_addr(int x, int y, int addr) {
  string hex_addr = to_hex(addr, ADDR_SIZE);
  draw_text(x, y, hex_addr);
}

void HexEditor::draw_byte(int x, int y, int addr, char byte) {
  string hex = to_hex(byte, 2);
  for (int nibble = 0; nibble < 2; nibble++) {
    int color = get_color(addr, nibble);

    draw_color(color);
    mvaddch(y, x + nibble, hex[nibble]);
    draw_rcolor();
  }
}

void HexEditor::draw_char(int x, int y, int addr, char byte) {
  int color = get_color(addr);

  draw_color(color);
  mvaddch(y, x, byte);
  draw_rcolor();
}
