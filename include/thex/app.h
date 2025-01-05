#pragma once

#include <ncurses.h>
#include <ui.h>

class THexApp {
  std::string path;
  bool running;
  
public:
  void start();
  void loop();
  void end();

  THexApp(std::string path) : path(path) {};
};
