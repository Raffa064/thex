#pragma once

#include "thex/ui/hexeditor.h"
#include <interface/ui.h>

class StatusBar : public UI {
  Editor *editor;

public:
  void draw() override;

  StatusBar() {}

  StatusBar(Editor *editor) : editor(editor) {}

  StatusBar &operator=(StatusBar other) {
    editor = other.editor;

    return *this;
  }
};
