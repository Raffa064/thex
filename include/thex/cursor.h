#pragma once

#include "util.h"
#include <algorithm>
#include <string>

/*
  A cursor that is usinig selection should move the end selection pointer,
  otherwise, the start pointer.
*/

class Cursor {
  int start;
  int end;
  int color;
  bool selection;

public:
  int get_start() { return start; }
  void set_start(int start) { this->start = std::max(0, start); }

  int get_end() { return end; }
  void set_end(int end) { this->end = std::max(start, end); }

  int get_color() { return color; }
  void set_color(int color) { this->color = color; }

  bool is_selection() { return selection; }
  void set_selection(int name) { this->selection = name; }
  bool toggle_selection() { return selection = !selection; }

  void move(int amount) {
    if (selection)
      set_end(end + amount);
    else {
      set_start(start + amount);
      set_end(start);
    }
  }

  void limit(int minPos, int maxPos) {
    set_start(std::min(maxPos, std::max(minPos, get_start())));
    set_end(std::min(maxPos, std::max(minPos, get_end())));
  }

  void limit(int mx) { limit(0, mx); }

  std::string to_string() {
    return "[ " + to_hex(start, 8) +
           (is_selection() ? ":" + to_hex(end, 8) + " ]" : " ]");
  }


  Cursor() {}

  Cursor(int start, int end, int color, bool selection)
      : start(start), end(end), color(color), selection(selection) {}

  Cursor(const Cursor& other) : Cursor(other.start, other.end, other.color, other.selection) {}
};
