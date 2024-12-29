#pragma once

#include "thex/editor.h"

class THexPreview : public EditorBase, public UI {
public:
  int get_bwidth() override;
  void draw() override;  

  THexPreview(Buffer& buffer) : EditorBase(buffer) {}
};
