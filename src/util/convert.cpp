#include <cstdint>
#include <interface/color.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <util.hpp>

std::string to_hex(int value, int width) {
  std::ostringstream stream;
  stream << std::hex << std::setw(width) << std::setfill('0') << value;
  std::string str = stream.str();

  return to_upper(str);
}

std::string to_hex(char value) { return to_hex(value, 2); }

int hex_to_int(std::string input) {
  if (starts_with(input, "0x"))
    input = input.substr(2);

  unsigned int x;
  std::stringstream ss;
  ss << std::hex << input;
  ss >> x;

  return static_cast<int>(x);
}

Buffer to_hex_seq(std::string input) {
  auto hex = split(input, "\\s+");

  Buffer tmp(hex.size());
  for (int i = 0; i < hex.size(); i++)
    tmp.data[i] = hex_to_int(hex[i]);

  return tmp;
}

Color to_color(std::string input) {
  if (input[0] == '#')
    input = input.substr(1);

  uint32_t color = hex_to_int(input);

  return {.r = (uint8_t)((color & 0xFF0000) >> 16),
          .g = (uint8_t)((color & 0xFF00) >> 8),
          .b = (uint8_t)((color & 0xFF))};
}

ColorPair to_color_pair(std::string input) {
  input = trim(input);
  auto colors = split(input, ";");
  return {.fg = to_color(colors[0]), .bg = to_color(colors[1])};
}
