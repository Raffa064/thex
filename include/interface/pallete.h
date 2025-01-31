#pragma once

#include "interface/color.h"
#include "thex/config.h"
#include <ncurses.h>
#include <ncursesw/ncurses.h>

enum Palette {
  TERM_DEFAULT = 0,
  PALETTE_NORMAL,      // Default/base color
  PALETTE_M0,          // Marker 0
  PALETTE_M1,          // Marker 1
  PALETTE_M2,          // Marker 2
  PALETTE_CURSOR,      // Cursor
  PALETTE_CURSOR_LINE, // Color for address bar at cursor line
  PALETTE_EOF,         // End of file
  PALETTE_EMPTY,       // Empty cells (after EOF)
  PALETTE_STATUSBAR    // statusbar color
};

// Color map (from [0-255] to [0-1000])
static int cmap(uint8_t value) { return (value * 1000) / 255; }

static void set_colorp(int color_code, ColorPair pair) {
  int fg = color_code * 2;
  int bg = fg + 1;

  init_color(fg, cmap(pair.fg.r), cmap(pair.fg.g), cmap(pair.fg.b));
  init_color(bg, cmap(pair.bg.r), cmap(pair.bg.g), cmap(pair.bg.b));

  init_pair(color_code, fg, bg);
}

[[maybe_unused]]
static void init_palette() {
  if (can_change_color()) { // If custom color are supported
    set_colorp(PALETTE_NORMAL, Config::get_colorp("normal"));
    set_colorp(PALETTE_M0, Config::get_colorp("marker_0"));
    set_colorp(PALETTE_M1, Config::get_colorp("marker_1"));
    set_colorp(PALETTE_M2, Config::get_colorp("marker_2"));
    set_colorp(PALETTE_CURSOR, Config::get_colorp("cursor"));
    set_colorp(PALETTE_CURSOR_LINE, Config::get_colorp("cursor_line"));
    set_colorp(PALETTE_EOF, Config::get_colorp("eof"));
    set_colorp(PALETTE_EMPTY, Config::get_colorp("empty"));
    set_colorp(PALETTE_STATUSBAR, Config::get_colorp("statusbar"));
    return;
  }

  init_pair(PALETTE_NORMAL, COLOR_WHITE, COLOR_BLACK);
  init_pair(PALETTE_M0, COLOR_BLACK, COLOR_GREEN);
  init_pair(PALETTE_M1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PALETTE_M2, COLOR_WHITE, COLOR_RED);
  init_pair(PALETTE_CURSOR, COLOR_BLACK, COLOR_BLUE);
  init_pair(PALETTE_CURSOR_LINE, COLOR_GREEN, COLOR_BLACK);
  init_pair(PALETTE_EOF, COLOR_RED, COLOR_RED);
  init_pair(PALETTE_EMPTY, COLOR_BLACK, COLOR_BLACK);
  init_pair(PALETTE_STATUSBAR, COLOR_BLACK, COLOR_GREEN);
}
