#include <clocale>
#include <csignal>
#include <cstdlib>
#include <interface/input.h>
#include <interface/pallete.h>
#include <interface/ui.h>
#include <locale.h>
#include <ncurses.h>
#include <string>
#include <thex/app.h>
#include <thex/cursor.h>
#include <thex/ui/cmdline.h>
#include <thex/ui/editor.h>
#include <thex/ui/statusbar.h>
#include <vector>

#define DEFAULT_PREVIEW_WITH 30
#define ADDRESS_BAR_WIDTH 8

using namespace std;

void THexApp::start() {
  setlocale(LC_ALL, "");

  initscr();             // initialize screen buffer
  raw();                 // disable line buffer
  keypad(stdscr, TRUE);  // enable spacial keys
  noecho();              // Don't show typed key
  curs_set(0);           // Remove cursor
  nodelay(stdscr, TRUE); // Remove input delay
  start_color();         // use colors

  init_palette();

  is_running = true;

  display = DisplayBuffer(0, .2f);
  cursor = Cursor(0, 0, PALETTE_CURSOR, false);

  // UI elements
  editor = THexEditor(&display);
  statusbar = THexStatusBar(&cursor);
  cmdline = THexCommandLine();

  setup_commands();

  loop();
  end();
}

void THexApp::loop() {
  UIPlacer placer;
  InputManager imanager;

  int &FILLW = placer.ctx.fill.width;
  int &FILLH = placer.ctx.fill.height;

  editor.add_cursor(cursor);

  FnReceiver cursorControl = FnReceiver([this](Event evt) -> bool {
    if (evt.keycode == 's') {
      cursor.toggle_selection();
      return true;
    }

    int x = evt.axisl('j', 'l') + evt.axisl(KEY_LEFT, KEY_RIGHT);
    int y = evt.axisl('i', 'k') + evt.axisl(KEY_UP, KEY_DOWN);

    if (x || y) {
      int move = x + y * editor.get_bwidth();
      cursor.move(move);

      if (cursor.get_end() < display.position)
        display.position -= editor.get_bwidth();

      if (cursor.get_end() >= display.position + editor.get_bcount())
        display.position += editor.get_bwidth();

      // TODO: clip display position inside file

      return true;
    }

    return false;
  });

  while (is_running) {
    refresh();

    Event e = imanager.get();
    e.propagate(vector<InputReceiver *>{&cmdline, &cursorControl});

    placer.move({0, 0});
    placer.align(VERTICAL);
    placer.place(editor, {FILLW, FILLH - 2});
    placer.moveX(0);
    placer.place(statusbar, {FILLW, 1});
    placer.place(cmdline, {FILLW, 1});

    uidraw({&editor, &statusbar, &cmdline});

    if (e.keycode == 127)
      is_running = false;
  }
}

void THexApp::end() {
  is_running = false;
  endwin();
}

void THexApp::setup_commands() {
  cmdline.add_cmd("q", [this](string, string &) { is_running = false; });

  cmdline.add_cmd("m", [this](string input, string &) {
    int color = PALETTE_CYAN;

    if (input.size() >= 2)
      switch (input.at(1)) {
      case 'm':
        color = PALETTE_MAGENTA;
        break;
      case 'y':
        color = PALETTE_YELLOW;
        break;
      }

    Cursor marquee = cursor;
    marquee.set_color(color);
    editor.add_cursor(marquee);
    cursor.set_selection(false);
  });
}

THexApp::~THexApp() { end(); }
