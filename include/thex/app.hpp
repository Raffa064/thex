#pragma once

#include <interface/ui.hpp>
#include <ncurses.h>
#include <thex/ui/cmdline.hpp>
#include <thex/ui/hexeditor.hpp>
#include <thex/ui/statusbar.hpp>

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
