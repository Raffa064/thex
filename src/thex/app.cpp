#include "draw.h"
#include "file.h"
#include "pallete.h"
#include "thex/editor.h"
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

  char *str = (char *) "This is my fake buffer, used to test how the app "
                       "handles big text sequences inside it's editor and "
                       "preview elements.\nThis app also contains a statusbar "
                       "and a command line to run useful command.";

  Cursor cursor(0, 0, PALETTE_CURSOR_BLUE, false);

  BFReader openedFile(path, 3, 1000);
  DisplayBuffer display(500, .2f);

  THexEditor editor(display);
  THexStatusBar statusbar(cursor);
  DebugBox cmdline(4);
  Separator sep0, sep1;

  editor.add_cursor(cursor);

  FnReceiver cursorControl = FnReceiver([&cursor, &display, &editor, &openedFile](Event evt) -> bool {
    if (evt.keycode == 's') {
      cursor.toggle_selection();
      return true;
    }

    int x = evt.axisl('j', 'l') + evt.axisl(KEY_LEFT, KEY_RIGHT);
    int y = evt.axisl('i', 'k') + evt.axisl(KEY_UP, KEY_DOWN);

    if (x || y) {
      int move = x + y * editor.get_bwidth();
      cursor.move(move);

      int fend = openedFile.size();
      cursor.limit(fend - 1);

      if (cursor.get_end() < display.position)
        display.position -= editor.get_bwidth();

      if (cursor.get_end() >= display.position + editor.get_bcount())
        display.position += editor.get_bwidth();

      display.position = min(fend, max(0, display.position));

      return true;
    }

    return false;
  });

  int i = 0;
  while (running) {
    refresh();

    display.dynamic_resize(editor.get_bcount());
    openedFile.read(display.buffer, display.position, display.length);
    display.eof = openedFile.size();

    Event e = imanager.get();
    e.propagate(vector<InputReceiver *>{&cmdline, &cursorControl});

    placer.move({0, 0});
    placer.align(VERTICAL);
    placer.place(editor, { FILLW, FILLH - 2});
    placer.moveX(0);
    placer.place(statusbar, {FILLW, 1});
    placer.place(cmdline, {FILLW, 1});

    uidraw({&editor, &statusbar, &cmdline});

    if (e.keycode == ':') running = false;
  }
}

void THexApp::end() {
  running = false;
  endwin();
}
