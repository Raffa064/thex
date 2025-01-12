#pragma once

#include <interface/input.h>
#include <interface/ui.h>
#include <thex/editor.h>

class HexEditor : public UI, public InputReceiver {
public:
  static const int ADDR_SIZE = 8;
  static const int FIXED_SIZE = ADDR_SIZE + 2; // addr bar + dividers

  Editor *editor;
  Page display;

  int get_bwidth(); // byte count per row
  int get_bcount(); // total displayed bytes count
  int get_color(int, int);
  int get_color(int);

  void resize() override;
  void draw() override;
  bool accept(Event) override;

  void draw_addr(int, int, int);
  void draw_byte(int, int, int, char);
  void draw_char(int, int, int, char);

  HexEditor() : editor(nullptr) {}

  HexEditor(Editor *editor) : editor(editor) {}

  HexEditor &operator=(HexEditor other) {
    editor = other.editor;

    return *this;
  }
};
