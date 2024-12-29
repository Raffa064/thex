#pragma once

#include <functional>
#include <vector>
class InputReceiver;

class Event {
public:
  int keycode;
  int lowercase;
  bool isValidKey;

  bool shift();
  int axis(int, int);
  int axisl(int, int);

  bool propagate(std::vector<InputReceiver *>, bool = false);
};

class InputReceiver {
public:
  virtual bool accept(Event) = 0;
};

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
