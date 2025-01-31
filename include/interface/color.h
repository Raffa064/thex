#pragma once

#include <string>

struct Color {
  std::uint8_t r, g, b;

  std::string to_string();
};

struct ColorPair {
  Color fg, bg;

  std::string to_string();
};
