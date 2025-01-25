#pragma once

#include <ncurses.h>
#include <ncursesw/ncurses.h>

enum Palette {
  PALETTE_NORMAL,    // Default/base color
  PALETTE_M0,        // Marker 0
  PALETTE_M1,        // Marker 1
  PALETTE_M2,        // Marker 2
  PALETTE_CURSOR,    // Cursor
  PALETTE_INVISIBLE, // Non printable characters
  PALETTE_EOF,       // End of file
  PALETTE_EMPTY,     // Empty cells (after EOF)
  PALETTE_STATUSBAR  // statusbar color
};

[[maybe_unused]]
static void init_palette() {
  init_pair(PALETTE_NORMAL, COLOR_WHITE, COLOR_BLACK);
  init_pair(PALETTE_M0, COLOR_BLACK, COLOR_GREEN);
  init_pair(PALETTE_M1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PALETTE_M2, COLOR_WHITE, COLOR_RED);
  init_pair(PALETTE_CURSOR, COLOR_BLACK, COLOR_BLUE);
  init_pair(PALETTE_INVISIBLE, COLOR_BLACK, COLOR_WHITE);
  init_pair(PALETTE_EOF, COLOR_RED, COLOR_RED);
  init_pair(PALETTE_EMPTY, COLOR_BLACK, COLOR_BLACK);
  init_pair(PALETTE_STATUSBAR, COLOR_BLACK, COLOR_GREEN);
}
