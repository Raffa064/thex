#include <cstdlib>
#include <interface/draw.h>
#include <interface/input.h>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <thex/ui/cmdline.h>
#include <util.h>

using namespace std;

void CommandLine::add_cmd(string name, CommandFunction fn) {
  commands.push_back({name, fn});
}

void CommandLine::start_input() {
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');

  echo();
  nodelay(stdscr, FALSE);
  curs_set(1);

  wmove(stdscr, pos.y, pos.x);
  addch(':');
  wgetnstr(stdscr, buffer, 256);

  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);

  string input = string(buffer);
  for (auto cmd : commands)
    if (starts_with(input, cmd.name)) {
      cmd.fn(input, command_output);
      return;
    }

  command_output = "Unknown command: '" + input + "'";
}

void CommandLine::draw() { draw_text(pos.x, pos.y, command_output); }

bool CommandLine::accept(Event evt) {
  switch (evt.keycode) {
  case ':':
    start_input();
    break;
  case ';':
    command_output = "";
    break;
  default:
    return false;
  };

  return true;
}

CommandLine::CommandLine() { buffer = new char[256]; }

CommandLine::~CommandLine() { delete[] buffer; }
