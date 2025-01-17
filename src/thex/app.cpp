#include "thex/editor.h"
#include <clocale>
#include <csignal>
#include <cstdlib>
#include <interface/input.h>
#include <interface/pallete.h>
#include <interface/ui.h>
#include <locale.h>
#include <ncurses.h>
#include <thex/app.h>
#include <thex/ui/cmdline.h>
#include <thex/ui/hexeditor.h>
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

  // UI elements
  hexEditor = HexEditor(&editor);
  statusbar = StatusBar(&editor);
  cmdline = CommandLine();

  setup_commands();

  is_running = true;

  loop();
  end();
}

void THexApp::loop() {
  UIPlacer placer;
  InputManager imanager;

  int &FILLW = placer.ctx.fill.width;
  int &FILLH = placer.ctx.fill.height;

  while (is_running) {
    refresh();

    Event e = imanager.get();
    e.propagate(vector<InputReceiver *>{&cmdline, &hexEditor});

    placer.move({0, 0});
    placer.align(VERTICAL);
    placer.place(hexEditor, {FILLW, FILLH - 2});
    placer.moveX(0);
    placer.place(statusbar, {FILLW, 1});
    placer.place(cmdline, {FILLW, 1});

    uidraw({&hexEditor, &statusbar, &cmdline});

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

  cmdline.add_cmd("mr", [this](string, string &output) {
    vector<Marker *> markers;
    editor.get_markers(markers);

    vector<Marker *> &edMarkers = editor.markers;
    for (Marker *m : markers) {
      editor.markers.erase(remove(edMarkers.begin(), edMarkers.end(), m),
                           edMarkers.end());

      delete m;
    }
  });

  cmdline.add_cmd("m", [this](string input, string &output) {
    int color = PALETTE_M0;

    if (input.size() >= 2)
      switch (input.at(1)) {
      case 'b':
        color = PALETTE_M0;
        break;
      case 'n':
        color = PALETTE_M1;
        break;
      case 'm':
        color = PALETTE_M2;
        break;
      }

    Marker *marker = new Marker();
    marker->start = editor.cursor.start;
    marker->end = editor.cursor.end;
    marker->color = color;

    editor.markers.push_back(marker);
    editor.cursor.selection = false;

    output = "Placed marker";
  });
}

THexApp::THexApp(string path) { editor = Editor(path); }

THexApp::~THexApp() { end(); }
