#include "interface/input.h"
#include <cstdlib>
#include <cstring>
#include <interface/draw.h>
#include <interface/pallete.h>
#include <ncurses.h>
#include <string>
#include <thex/ui/hexeditor.h>
#include <util.h>

int HexEditor::get_bwidth() { return (size.width - FIXED_SIZE) / 4; }

int HexEditor::get_bcount() { return get_bwidth() * size.height; }

int HexEditor::get_line_addr(int byte_addr) {
  int bwidth = get_bwidth();
  return (byte_addr / bwidth) * bwidth;
}

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
  int high_nibble = get_color(addr, Cursor::HIGH_NIBBLE);
  int low_nibble = get_color(addr, Cursor::LOW_NIBBLE);

  // Important highlights have higher value than others
  return std::max(high_nibble, low_nibble);
}

void HexEditor::resize() {
  // Resize to the on screen byte count + one more line
  int length = get_bcount();
  display.buffer.resize(length);
}

void HexEditor::draw() {
  editor->read_page(display); // TODO: optmize do read only if necessary
  follow_cursor();

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
        if (is_non_printable(byte)) {
          attron(A_REVERSE);
        }
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
    if (!cursor.selection) {
      std::string keys = "0123456789abcdef";
      int nib = keys.find((char)evt.keycode); // [ 0x0 - 0xF ]

      if (nib != std::string::npos) {
        char currByte = display.get(cursor.start);

        if (cursor.nibble == Cursor::HIGH_NIBBLE) {
          nib <<= 4;
          currByte &= 0x0F;
        } else {
          currByte &= 0xF0;
        }

        currByte |= nib;

        editor->write_char(currByte, cursor.start);

        cursor.moven(1);

        return true;
      }
    }

    return false;
  }

  cursor.move(moveY);

  unsigned eof = editor->get_fsize();

  if (cursor.selection)
    cursor.move(moveX);
  else {
    if (cursor.get() == 0 && moveX < 0) {
      cursor.start = 0;
      cursor.nibble = Cursor::LOW_NIBBLE;
    } else if (cursor.get() == (eof - 1) && moveX > 0) {
      cursor.start = eof - 1;
      cursor.nibble = Cursor::HIGH_NIBBLE;
    }

    cursor.moven(moveX);
  }

  cursor.set(std::min(eof - 1, cursor.get())); // Clamp to EOF

  return true;
}

void HexEditor::follow_cursor() {
  unsigned eof = editor->get_fsize();
  int line_bytes = get_bwidth();
  int cpos = editor->cursor.get();

  uint newPosition = display.position;
  uint cursor_line = (cpos / line_bytes) * line_bytes;
  uint display_bytes = display.buffer.length;

  if (cpos < display.position) {
    newPosition = cursor_line;
  }

  if (cpos >= display.end())
    newPosition = cursor_line - display_bytes + line_bytes;

  display.position = std::min(eof, std::max<unsigned>(0, newPosition));
}

void HexEditor::draw_addr(int x, int y, int addr) {
  Range line = {(uint)addr, (uint)(addr + get_bwidth() - 1)};
  bool overlaps_cursor = editor->cursor.overlaps(line);

  int color = overlaps_cursor ? PALETTE_CURSOR_LINE : PALETTE_NORMAL;
  std::string hex_addr = to_hex(addr, ADDR_SIZE);

  draw_color(color);
  draw_text(x, y, hex_addr);
  draw_rcolor();
}

void HexEditor::draw_byte(int x, int y, int addr, char byte) {
  std::string hex = to_hex(byte, 2);

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
  mvaddch(y, x, is_non_printable(byte) ? '.' : byte);
  draw_rcolor();
}

HexEditor &HexEditor::operator=(HexEditor other) {
  editor = other.editor;

  return *this;
}
