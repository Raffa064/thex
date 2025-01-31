#pragma once

#include <functional>
#include <vector>

class InputReceiver;

class Event {
public:
  int keycode;
  int lowercase;
  bool isValidKey; // False if eq. ERR (constant from ncurses)

  bool shift();
  int axis(int lowKey, int highKey);  //  output: [ -1, 0, 1 ]
  int axisl(int loyKey, int highKey); // ignore case

  bool propagate(std::vector<InputReceiver *> receivers,
                 bool allowInvalid = false);
};

class InputReceiver {
public:
  virtual bool accept(Event evt) = 0;
};

// Wrapper for lambda functions
class FnReceiver : public InputReceiver {
  std::function<bool(Event)> handler;

public:
  bool accept(Event) override;

  FnReceiver(std::function<bool(Event)> handler) : handler(handler) {}
};

class InputManager {
public:
  Event get();
};
