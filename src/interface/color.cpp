#include <interface/color.hpp>
#include <util.hpp>

std::string Color::to_string() {
  return "#" + to_hex(r) + to_hex(g) + to_hex(b);
}

std::string ColorPair::to_string() {
  return fg.to_string() + ";" + bg.to_string();
}
