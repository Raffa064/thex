#pragma once

#include <functional>
#include <interface/input.h>
#include <interface/ui.h>
#include <regex>
#include <string>
#include <vector>

typedef std::vector<std::string> CmdArgs;
typedef std::function<std::string(std::string, CmdArgs)> CmdFunction;

#define cmd_func [this](std::string raw, CmdArgs args)

#define cmd_noargs()                                                           \
  if (args.size() != 1)                                                        \
  return std::string("This command doesn't expect any argument")

#define cmd_limit_args(allowed_args)                                           \
  std::vector<int> __limit_args = allowed_args;                                \
  bool __limit_args_ok = false;                                                \
  for (int arg_count : __limit_args)                                           \
    if (args.size() == arg_count) {                                            \
      __limit_args_ok = true;                                                  \
      break;                                                                   \
    }                                                                          \
  if (!__limit_args_ok)                                                        \
  return std::string("Error: Invalid argument count")

class Command {
public:
  std::regex pattern;
  CmdFunction fn;

  bool accept(std::string cmd);
};

class CommandLine : public UI, public InputReceiver {
  char *buffer = nullptr;
  std::string command_output;
  std::vector<Command> commands;

public:
  void add(std::string pattern, CmdFunction fn);

  std::string start_input(std::string label);
  void start_command();

  void draw() override;
  bool accept(Event evt) override;

  CommandLine();

  ~CommandLine();

  CommandLine &operator=(CommandLine other);
};
