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

  bool operator==(Pair &other) { return x = other.x && y == other.y; }
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

  void set(int x, int y, int w, int h) {
    pos.x = x;
    pos.y = y;
    size.width = w;
    size.height = h;
  }

  virtual void resize() { /* Optional callback */ }

  virtual void draw() = 0;

  UI(Pair pos, Pair size) : pos(pos), size(size) {};

  UI(int x, int y, int w, int h) : pos(x, y), size(w, h) {};

  UI() : pos(0, 0), size(0, 0) {};
};

class DebugBox : public UI, public InputReceiver {
  int color;

public:
  void draw() override;

  bool accept(Event) override;

  DebugBox(int color) { this->color = color; };
};

class Separator : public UI {
  void draw() override;
};

class UIPlacer {
public:
  Context ctx;

  void move(Pair);

  void moveX(int);

  void moveY(int);

  void align(Direction);

  void place(UI &, Pair);
};

void uidraw(std::vector<UI *>);
