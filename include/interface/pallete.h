#pragma once

#include "interface/color.h"
#include "thex/config.h"
#include <ncurses.h>
#include <ncursesw/ncurses.h>

enum Palette {
  TERM_DEFAULT = 0,
  PALETTE_NORMAL,     // Default/base color
  PALETTE_M0,         // Marker 0
  PALETTE_M1,         // Marker 1
  PALETTE_M2,         // Marker 2
  PALETTE_CURSOR,     // Cursor
  PALETTE_CURSORLINE, // Color for address bar at cursor line
  PALETTE_EOF,        // End of file
  PALETTE_EMPTY,      // Empty cells (after EOF)
  PALETTE_STATUSBAR   // statusbar color
};

// Color map (from [0-255] to [0-1000])
static int cmap(uint8_t value) { return (value * 1000) / 255; }

static void pallete_add(int color_code, ColorPair pair) {
  int fg = color_code * 2;
  int bg = fg + 1;

  init_color(fg, cmap(pair.fg.r), cmap(pair.fg.g), cmap(pair.fg.b));
  init_color(bg, cmap(pair.bg.r), cmap(pair.bg.g), cmap(pair.bg.b));

  init_pair(color_code, fg, bg);
}

[[maybe_unused]]
static void init_palette() {
  using namespace Config;

  if (can_change_color() && !get_flag("palette.use_native")) {
    pallete_add(PALETTE_NORMAL, get_pair("normal", "#cccccc;#222222"));
    pallete_add(PALETTE_M0, get_pair("marker_0", "#222222;#20cc88"));
    pallete_add(PALETTE_M1, get_pair("marker_1", "#222222;#ddcc00"));
    pallete_add(PALETTE_M2, get_pair("marker_2", "#dddddd;#df4a7f"));
    pallete_add(PALETTE_CURSOR, get_pair("cursor", "#222222;#00ccff"));
    pallete_add(PALETTE_CURSORLINE, get_pair("cursorline", "#60cc68;#222222"));
    pallete_add(PALETTE_EOF, get_pair("eof", "#ff0000;#ff0000"));
    pallete_add(PALETTE_EMPTY, get_pair("empty", "#222222;#222222"));
    pallete_add(PALETTE_STATUSBAR, get_pair("statusbar", "#222222;#60cc68"));
    return;
  }

  init_pair(PALETTE_NORMAL, COLOR_WHITE, COLOR_BLACK);
  init_pair(PALETTE_M0, COLOR_BLACK, COLOR_GREEN);
  init_pair(PALETTE_M1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PALETTE_M2, COLOR_WHITE, COLOR_RED);
  init_pair(PALETTE_CURSOR, COLOR_BLACK, COLOR_BLUE);
  init_pair(PALETTE_CURSORLINE, COLOR_GREEN, COLOR_BLACK);
  init_pair(PALETTE_EOF, COLOR_RED, COLOR_RED);
  init_pair(PALETTE_EMPTY, COLOR_BLACK, COLOR_BLACK);
  init_pair(PALETTE_STATUSBAR, COLOR_BLACK, COLOR_GREEN);
}
