#pragma once

#include <file.h>
#include <ncurses.h>
#include <thex/ui/cmdline.h>
#include <thex/cursor.h>
#include <thex/ui/editor.h>
#include <thex/ui/statusbar.h>
#include <ui.h>

class THexApp {
  std::string path;
  BFReader openedFile;
  DisplayBuffer display;
  Cursor cursor;
  THexEditor editor;
  THexStatusBar statusbar;
  THexCommandLine cmdline;

  bool is_running;

public:
  void start();
  void loop();
  void end();

  void setup_commands();

  THexApp(std::string path) : path(path) {}
  ~THexApp();
};
