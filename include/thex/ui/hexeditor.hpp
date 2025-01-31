#pragma once

#include <interface/input.hpp>
#include <interface/ui.hpp>
#include <thex/editor.hpp>

class HexEditor : public UI, public InputReceiver {
public:
  static const int ADDR_SIZE = 8;
  static const int FIXED_SIZE = ADDR_SIZE + 2; // addr bar + dividers

  Editor *editor;
  Page display;

  int get_bwidth(); // byte count per row
  int get_bcount(); // total displayed bytes count

  int get_color(int addr, int nibble);
  int get_color(int addr);

  void follow_cursor(); // Fit screen to the cursor's position (scroll)

  void resize() override;
  void draw() override;
  bool accept(Event evt) override;

  void draw_addr(int x, int y, int addr);
  void draw_byte(int x, int y, int addr, char byte);
  void draw_char(int x, int y, int addr, char byte);

  HexEditor() : editor(nullptr) {}

  HexEditor(Editor *editor) : editor(editor) {}

  HexEditor &operator=(HexEditor other);
};
