#pragma once

#include <file.h>
#include <ncurses.h>
#include <thex/cmdline.h>
#include <thex/cursor.h>
#include <thex/editor.h>
#include <thex/statusbar.h>
#include <ui.h>

class THexApp {
  std::string path;
  Cursor* cursor;
  BFReader* openedFile;
  DisplayBuffer* display;
  THexEditor* editor;
  THexStatusBar* statusbar;
  THexCommandLine* cmdline;

  bool is_running;

public:
  void start();
  void loop();
  void end();

  void setup_commands();

  THexApp(std::string path) : path(path) {}
  ~THexApp();
};
