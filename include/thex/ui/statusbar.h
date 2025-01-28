#pragma once

#include "thex/editor.h"
#include <interface/ui.h>

class StatusBar : public UI {
  Editor *editor;

public:
  void draw() override;

  StatusBar() {}

  StatusBar(Editor *editor) : editor(editor) {}

  StatusBar &operator=(StatusBar other);
};
