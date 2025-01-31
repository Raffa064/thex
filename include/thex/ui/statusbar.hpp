#pragma once

#include <interface/ui.hpp>
#include <thex/editor.hpp>

class StatusBar : public UI {
  Editor *editor;

public:
  void draw() override;

  StatusBar() {}

  StatusBar(Editor *editor) : editor(editor) {}

  StatusBar &operator=(StatusBar other);
};
