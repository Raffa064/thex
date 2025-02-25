#include <algorithm>
#include <clocale>
#include <csignal>
#include <cstdlib>
#include <interface/input.hpp>
#include <interface/pallete.hpp>
#include <interface/ui.hpp>
#include <locale.h>
#include <ncurses.h>
#include <string>
#include <thex/app.hpp>
#include <thex/config.hpp>
#include <thex/editor.hpp>
#include <thex/ui/cmdline.hpp>
#include <thex/ui/hexeditor.hpp>
#include <thex/ui/statusbar.hpp>
#include <util.hpp>
#include <vector>

#define DEFAULT_PREVIEW_WITH 30
#define ADDRESS_BAR_WIDTH 8

void THexApp::start() {
  setlocale(LC_ALL, "");

  initscr();             // initialize screen buffer
  raw();                 // disable line buffer
  keypad(stdscr, TRUE);  // enable spacial keys
  noecho();              // Don't show typed key
  curs_set(0);           // Remove cursor
  nodelay(stdscr, TRUE); // Remove input delay
  start_color();         // use colors

  Config::init();
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
    e.propagate(std::vector<InputReceiver *>{&cmdline, &hexEditor});

    placer.move({0, 0});
    placer.align(VERTICAL);
    placer.place(hexEditor, {FILLW, FILLH - 2});
    placer.moveX(0);
    placer.place(statusbar, {FILLW, 1});
    placer.place(cmdline, {FILLW, 1});

    uidraw({&hexEditor, &statusbar, &cmdline});
  }
}

void THexApp::end() {
  is_running = false;
  endwin();
}

void THexApp::setup_commands() {
#define iferr(cond, msg)                                                       \
  if (cond) {                                                                  \
    return (std::string)(msg);                                                 \
  }

  cmdline.add(
      "q", cmd_func {
        is_running = false;
        return "Quit";
      });

  cmdline.add(
      "mr", cmd_func {
        std::vector<Marker *> markers;
        editor.get_markers(markers);

        std::vector<Marker *> &edMarkers = editor.markers;
        for (Marker *m : markers) {
          edMarkers.erase(std::remove(edMarkers.begin(), edMarkers.end(), m),
                          edMarkers.end());

          delete m;
        }

        editor.cursor.selection = false;

        return "Removed " + std::to_string(markers.size()) + " markers";
      });

  cmdline.add(
      "m[bnm]?", cmd_func {
        cmd_noargs();

        int color = PALETTE_M0;

        if (args[0].size() >= 2)
          switch (args[0].at(1)) {
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

        return std::string("Placed marker");
      });

  cmdline.add(
      "jp", cmd_func {
        cmd_limit_args({2});

        std::string jumpBytes = args[1];
        iferr(!is_number(jumpBytes),
              "'" + jumpBytes + "' is not a valid number");

        editor.cursor.move(std::stoi(jumpBytes));

        return "Jumped " + jumpBytes + " bytes to " + editor.cursor.to_string();
      });

  cmdline.add(
      "gt", cmd_func {
        cmd_limit_args({2});

        std::string address = args[1];
        int addr;
        uint eof = editor.get_fsize() - 1;

        if (is_number(address))
          addr = std::stoi(address);
        else if (is_hex(address))
          addr = hex_to_int(address);
        else if (address == "end" || address == "eof")
          addr = eof;
        else {
          return "'" + address + "' is not a valid address";
        }

        addr = std::min<int>(eof, std::max(0, addr));

        editor.cursor.set(addr);
        return "Go to 0x" + to_hex(addr, 8);
      });

  cmdline.add(
      "s", cmd_func {
        std::string input;

        if (raw.empty())
          input = cmdline.start_input("str: "); // limit to selection
        else
          input = raw;

        editor.insert_str(editor.cursor.start, input);

        return "Inserted string: '" + input + "'";
      });

  cmdline.add(
      "next", cmd_func {
        uint start = editor.cursor.get();
        uint addr = start;
        uint length;

        if (is_quoted_str(raw)) {
          std::string sequence = raw.substr(1, raw.length() - 2);
          addr = editor.find(start, Buffer(sequence));
          length = sequence.size();
        } else if (is_hex_sequence(raw)) {
          Buffer buffer = to_hex_seq(raw);
          addr = editor.find(start + 1, buffer);
          length = buffer.length;
        } else
          return std::string("Invalid input: '" + raw + "'");

        if (addr != start) {
          editor.cursor.selection = true;
          editor.cursor.start = addr;
          editor.cursor.end = addr + length - 1;

          return "Found at 0x" + to_hex(addr, 8);
        }

        return std::string("Not found: " + raw);
      });

  cmdline.add(
      "select", cmd_func {
        cmd_limit_args({2});

        if (is_number(args[1])) {
          int select = std::stoi(args[1]);
          editor.cursor.selection = true;
          editor.cursor.end = editor.cursor.end + select - 1;
        }

        return std::string("Selection must be a positive number");
      });

  cmdline.add(
      "mv", cmd_func {
        cmd_limit_args({2});

        if (is_number(args[1])) {
          int amount = std::stoi(args[1]);

          editor.cursor.start += amount;
          editor.cursor.end += amount;

          return std::string("Moved " + std::to_string(amount) + " bytes");
        }

        return std::string("Invalid input: '" + args[1] + "'");
      });
}

THexApp::THexApp(std::string path) { editor = Editor(path); }

THexApp::~THexApp() { end(); }
