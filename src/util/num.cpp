#include "util.h"
#include <regex>
#include <sstream>
#include <string>

const std::regex REGEX_NUMBER("[\\-\\+]?[0-9]+");
const std::regex REGEX_HEX("(0x)?[0-9a-b]+", std::regex::icase);

bool is_number(std::string &input) {
  return std::regex_match(input, REGEX_NUMBER);
}

bool is_hex(std::string &input) { return std::regex_match(input, REGEX_HEX); }

int hex_to_int(std::string input) {
  if (starts_with(input, "0x"))
    input = input.substr(2);

  unsigned int x;
  std::stringstream ss;
  ss << std::hex << input;
  ss >> x;

  return static_cast<int>(x);
}
