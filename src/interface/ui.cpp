#include <interface/draw.h>
#include <ncurses.h>
#include <interface/ui.h>
#include <vector>

using namespace std;

void DebugBox::draw() {
  attron(COLOR_PAIR(color));
  draw_frect(pos.x, pos.y, size.width, size.height, 'X');
  draw_text(pos.x, pos.y, "[ " + to_string(pos.x) + ", " + to_string(pos.y) + ", " + to_string(size.width) + ", " + to_string(size.height) + " ]");
  attroff(COLOR_PAIR(color));
}

bool DebugBox::accept(Event evt) {
  return false;
}

void Separator::draw() {
  draw_frect(pos.x, pos.y, size.width, size.height, ' ');
}

void update_fill(Context& ctx) {
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

void UIPlacer::align(Direction align) {
  ctx.alignDir = align;
}

void UIPlacer::place(UI& ui, Pair bounds) {
  ui.set(ctx.px, ctx.py, bounds.x, bounds.y);

  if (ctx.alignDir == VERTICAL) 
    ctx.py += bounds.y;
  else 
    ctx.px += bounds.x;

  update_fill(ctx);
}

void uidraw(vector<UI*> uis) {
  for (auto u : uis) {
    draw_frect(u->pos.x, u->pos.y, u->size.width, u->size.height, ' '); // clear screen
    u->draw();
  }
}
