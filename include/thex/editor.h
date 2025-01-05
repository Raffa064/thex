#pragma once

#include <file.h>
#include <input.h>
#include <ui.h>
#include <vector>
#include <thex/cursor.h>

/* 
 
  The display buffer uses some redundant space
  to prevent allocating buffer multiple times. 
  The grouth factor defines how much space must be
  added as extra space. 

  NOTE: growth_factor must be ranged at 0 to 1

*/

struct DisplayBuffer {
  float growth_factor;
  int length = 0; // virtual buffer size
  int allocated = 0; // real buffer size
  int eof = -1;
  int position = 0;
  char* buffer = nullptr;

  void dynamic_resize(int length);

  DisplayBuffer(int, float);
  ~DisplayBuffer();
};

class THexEditor : public UI {
public:
  static const int ADDR_SIZE = 8;
  static const int FIXED_SIZE = ADDR_SIZE + 2; // addr bar + dividers
 
  DisplayBuffer& display;
  std::vector<Cursor *> cursors{};

  void add_cursor(Cursor &);
  void remove_cursor(Cursor &);
  int get_cursor_line(Cursor &); // on screen Y position
  int get_bwidth(); // byte count per row
  int get_bcount(); // total displayed bytes count
  int get_color(int);
  void draw() override;

  THexEditor(DisplayBuffer &display) : display(display) {}
};

