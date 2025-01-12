#pragma once

#include <interface/ui.h>
#include <ncurses.h>
#include <thex/ui/cmdline.h>
#include <thex/ui/hexeditor.h>
#include <thex/ui/statusbar.h>

class THexApp {
  Editor editor;
  HexEditor hexEditor;
  StatusBar statusbar;
  CommandLine cmdline;

  bool is_running;

public:
  void start();
  void loop();
  void end();

  void setup_commands();

  THexApp(std::string path);
  ~THexApp();
};
