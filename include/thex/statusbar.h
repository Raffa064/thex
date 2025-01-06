#pragma once

#include "thex/cursor.h"
#include <ui.h>

class THexStatusBar : public UI {
  Cursor& cursor;

public:
  void draw() override;

  THexStatusBar(Cursor& cursor) : cursor(cursor) {} 
};
