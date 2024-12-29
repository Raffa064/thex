#include "file.h"
#include "pallete.h"
#include "thex/editor.h"
#include "thex/preview.h"
#include "thex/statusbar.h"
#include "ui.h"
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <input.h>
#include <ncurses.h>
#include <string>
#include <thex/app.h>
#include <vector>

#define DEFAULT_PREVIEW_WITH 30
#define ADDRESS_BAR_WIDTH 8

using namespace std;

void THexApp::start() {
  initscr();             // initialize screen buffer
  raw();                 // disable line buffer
  keypad(stdscr, TRUE);  // enable spacial keys
  noecho();              // Don't show typed key
  curs_set(0);           // Remove cursor
  nodelay(stdscr, TRUE); // Remove input delay
  start_color();         // use colors

  init_palette();

  loop();
  end();
}

void THexApp::loop() {
  running = true;

  UIPlacer placer;
  InputManager imanager;

  int &FILLW = placer.ctx.fill.width;
  int &FILLH = placer.ctx.fill.height;

  char *str = (char *)"This is my fake buffer, used to test how the app "
                      "handles big text sequences inside it's editor and "
                      "preview elements.\nThis app also contains a statusbar "
                      "and a command line to run useful command.";
 
  Buffer buffer{.data = str, .length = strlen(str), .count = strlen(str)};

  Cursor cursor(0, 0, PALETTE_CURSOR_BLUE, false);
  
  THexEditor editor(buffer);
  THexAddrerssBar addressbar(editor);
  THexPreview preview(buffer);
  THexStatusBar statusbar(cursor);
  DebugBox cmdline(4);
  Separator sep0, sep1;

  editor.add_cursor(cursor);
  preview.add_cursor(cursor);

  FnReceiver cursorControl = FnReceiver([&cursor, &editor](Event evt) -> bool {
    if (evt.keycode == 's') {
      cursor.toggle_selection();
      return true;
    }

    int x = evt.axisl('j', 'l') + evt.axisl(KEY_LEFT, KEY_RIGHT);
    int y = evt.axisl('i', 'k') + evt.axisl(KEY_UP, KEY_DOWN);

    if (x || y) {
      int move = x + y * editor.get_bwidth();
      cursor.move(move);
      return true;
    }

    return false;
  });

  int &editor_width = editor.size.width;
  editor_width = getmaxx(stdscr) - (DEFAULT_PREVIEW_WITH + ADDRESS_BAR_WIDTH);
  editor_width = editor_width / 3 * 3;

  int i = 0;
  while (running) {
    refresh();

    Event e = imanager.get();
    e.propagate(vector<InputReceiver *>{&cmdline, &cursorControl, &editor});

    placer.move({0, 0});
    placer.align(HORIZONTAL);
    placer.place(addressbar, { ADDRESS_BAR_WIDTH , FILLH - 2});
    placer.place(sep0, {1, FILLH});
    placer.place(editor, {editor_width, FILLH - 2});
    placer.place(sep1, {1, FILLH});
    placer.align(VERTICAL);
    placer.place(preview, {FILLW, FILLH - 2});
    placer.moveX(0);
    placer.place(statusbar, {FILLW, 1});
    placer.place(cmdline, {FILLW, 1});

    uidraw({
      &addressbar, &sep0, &editor, &sep1, &preview, 
      &statusbar, 
      &cmdline
    });

    napms(50);
  }
}

void THexApp::end() {
  running = false;
  endwin();
}

THexApp::THexApp(string path) : openedFile(IOFile(path)) {}
