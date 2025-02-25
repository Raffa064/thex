#include <interface/draw.hpp>
#include <interface/ui.hpp>
#include <ncurses.h>
#include <vector>

bool Pair::operator==(Pair &other) { return x = other.x && y == other.y; }

void UI::set(int x, int y, int w, int h) {
  pos.x = x;
  pos.y = y;
  size.width = w;
  size.height = h;
}

void DebugBox::draw() {
  attron(COLOR_PAIR(color));
  draw_frect(pos.x, pos.y, size.width, size.height, 'X');
  draw_text(pos.x, pos.y,
            "[ " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " +
                std::to_string(size.width) + ", " +
                std::to_string(size.height) + " ]");
  attroff(COLOR_PAIR(color));
}

bool DebugBox::accept(Event evt) { return false; }

void update_fill(Context &ctx) {
  getmaxyx(stdscr, ctx.fill.y, ctx.fill.x);
  ctx.fill.x -= ctx.px;
  ctx.fill.y -= ctx.py;
}

void UIPlacer::move(Pair pos) {
  ctx.px = pos.x;
  ctx.py = pos.y;

  align(VERTICAL);
  update_fill(ctx);
}

void UIPlacer::moveX(int x) {
  ctx.px = x;
  align(VERTICAL);
  update_fill(ctx);
}

void UIPlacer::moveY(int y) {
  ctx.py = y;
  align(VERTICAL);
  update_fill(ctx);
}

void UIPlacer::align(Direction align) { ctx.alignDir = align; }

void UIPlacer::place(UI &ui, Pair bounds) {
  bool is_resizing = !(ui.size == bounds);

  ui.set(ctx.px, ctx.py, bounds.x, bounds.y);

  if (is_resizing)
    ui.resize();

  if (ctx.alignDir == VERTICAL)
    ctx.py += bounds.y;
  else
    ctx.px += bounds.x;

  update_fill(ctx);
}

void uidraw(std::vector<UI *> uiElements) {
  for (auto u : uiElements) {
    draw_frect(u->pos.x, u->pos.y, u->size.width, u->size.height,
               ' '); // clear screen
    u->draw();
  }
}
