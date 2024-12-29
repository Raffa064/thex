#pragma once

#include <file.h>
#include <input.h>
#include <ui.h>
#include <vector>
#include <thex/cursor.h>

class EditorBase {
public:
  Buffer &buffer;
  std::vector<Cursor *> cursors{};

  void add_cursor(Cursor &);
  void remove_cursor(Cursor &);
  virtual int get_bwidth() = 0; // byte count per row
  int get_color(int);

  EditorBase(Buffer &buffer) : buffer(buffer) {}
};

class THexEditor : public EditorBase, public UI, public InputReceiver {
public:
  int get_bwidth() override;
  void draw() override;
  bool accept(Event) override;

  THexEditor(Buffer &buffer) : EditorBase(buffer) {}
};

class THexAddrerssBar : public UI {
  THexEditor &editor;

public:
  void draw() override;

  THexAddrerssBar(THexEditor &editor) : editor(editor) {}
};
