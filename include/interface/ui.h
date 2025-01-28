#pragma once

#include <interface/input.h>
#include <ncurses.h>
#include <vector>

struct Pair;

struct Pair {
  int x, y;
  int &width;
  int &height;

  Pair(int x, int y) : x(x), y(y), width(this->x), height(this->y) {}

  bool operator==(Pair &other);
};

enum Direction { VERTICAL, HORIZONTAL };

struct Context {
  int px = 0;
  int py = 0;
  Pair fill = Pair(0, 0);
  Direction alignDir = {};
};

class UI {
public:
  Pair pos, size;

  void set(int x, int y, int w, int h);

  virtual void resize() { /* Optional callback */ }

  virtual void draw() = 0;

  UI(Pair pos, Pair size) : pos(pos), size(size) {};

  UI(int x, int y, int w, int h) : pos(x, y), size(w, h) {};

  UI() : pos(0, 0), size(0, 0) {};
};

// Used for mock up unimplemented UI elements
class DebugBox : public UI, public InputReceiver {
  int color;

public:
  void draw() override;

  bool accept(Event evt) override;

  DebugBox(int color) : color(color) {};
};

// This class is responsible to handle element positioning ans scaling
class UIPlacer {
public:
  Context ctx;

  void move(Pair pos);

  void moveX(int x);

  void moveY(int y);

  void align(Direction align);

  void place(UI &ui, Pair bounds);
};

// Renderize all elements (they need to be already placeed by UIPLacer to
// correctly set their positions)
void uidraw(std::vector<UI *> uiElements);
