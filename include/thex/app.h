#pragma once

#include "file.h"
#include "thex/editor.h"
#include <ncurses.h>
#include <ui.h>

class THexApp {
  IOFile openedFile;
  bool running;
  
public:
  void start();
  void loop();
  void end();

  THexApp(std::string);
};
