#pragma once

#include <interface/input.h>
#include <interface/ui.h>
#include <functional>
#include <string>
#include <vector>

#define CommandFunction std::function<void (std::string, std::string&)>

struct Command {
  std::string name;
  CommandFunction fn;
};

class THexCommandLine : public UI, public InputReceiver {
  char* buffer = nullptr;
  std::string command_output;
  std::vector<Command> commands;

  void start_input();

public:

  void add_cmd(std::string, CommandFunction);
  
  void draw() override;
  bool accept(Event) override;

  THexCommandLine();

  ~THexCommandLine();

  THexCommandLine& operator=(THexCommandLine other) {
    buffer = other.buffer;
    commands = other.commands;
    command_output = other.command_output;

    return *this;
  }
};
