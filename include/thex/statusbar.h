#pragma once

#include "thex/cursor.h"
#include <ui.h>

class THexStatusBar : public UI {
  Cursor* cursor = nullptr;

public:
  void draw() override;

  THexStatusBar() {}

  THexStatusBar(Cursor* cursor) : cursor(cursor) {} 

  THexStatusBar& operator=(THexStatusBar other) {
    cursor = other.cursor;

    return *this;
  }
};
