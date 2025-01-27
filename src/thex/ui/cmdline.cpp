#include <cstdlib>
#include <interface/draw.h>
#include <interface/input.h>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <regex>
#include <thex/ui/cmdline.h>
#include <util.h>

const int COMMAND_BUFFER_SIZE = 1024;

bool Command::accept(std::string cmd) { return std::regex_match(cmd, pattern); }

void CommandLine::add(std::string pattern, CmdFunction fn) {
  std::regex regex("^" + pattern);
  commands.push_back({regex, fn});
}

std::string CommandLine::start_input(std::string label) {
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');

  echo();
  nodelay(stdscr, FALSE);
  curs_set(1);

  draw_text(pos.x, pos.y, label);

  move(pos.y, pos.x + label.size());
  wgetnstr(stdscr, buffer, COMMAND_BUFFER_SIZE);

  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);

  return std::string(buffer);
}

void CommandLine::start_command() {
  std::string input = start_input(":");

  if (input.empty())
    return;

  int divIndex = input.find(" ");
  std::string cmd_name = input.substr(0, divIndex);
  auto args = split(input, "\\s+");
  std::string raw;

  if (divIndex == std::string::npos)
    raw = "";
  else
    raw = input.substr(divIndex + 1, input.length() - divIndex);

  for (auto cmd : commands)
    if (cmd.accept(cmd_name)) {
      command_output = cmd.fn(raw, args);
      return;
    }

  command_output = "Unknown command: '" + cmd_name + "'";
}

void CommandLine::draw() { draw_text(pos.x, pos.y, command_output); }

bool CommandLine::accept(Event evt) {
  switch (evt.keycode) {
  case ':':
    start_command();
    break;
  case ';':
    command_output = "";
    break;
  default:
    return false;
  };

  return true;
}

CommandLine::CommandLine() { buffer = new char[COMMAND_BUFFER_SIZE]; }

CommandLine::~CommandLine() { delete[] buffer; }
