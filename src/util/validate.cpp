#include <regex>
#include <string>
#include <util.hpp>

const std::regex REGEX_NUMBER("[\\-\\+]?[0-9]+");
const std::regex REGEX_HEX("(0x)?[0-9a-f]+", std::regex::icase);
const std::regex REGEX_STRING("\"(\\\"|[^\"])*\"");
const std::regex REGEX_HEX_SEQ("(\\s*[0-9a-f]{2}\\s*)+", std::regex::icase);
const std::regex REGEX_FLAG("(on|off)");
const std::regex REGEX_COLOR_PAIR("#[0-9a-f]{6};#[0-9a-f]{6}");

bool is_number(const std::string &input) {
  return std::regex_match(input, REGEX_NUMBER);
}

bool is_hex(const std::string &input) {
  return std::regex_match(input, REGEX_HEX);
}

bool is_non_printable(const char &ch) { return ch < 0x20 || ch > 0x7E; }

bool is_quoted_str(const std::string &input) {
  return std::regex_match(input, REGEX_STRING);
}

bool is_hex_sequence(const std::string &input) {
  return std::regex_match(input, REGEX_HEX_SEQ);
}

bool is_flag(const std::string &input) {
  return std::regex_match(input, REGEX_FLAG);
}

bool is_color_pair(const std::string &input) {
  return std::regex_match(input, REGEX_COLOR_PAIR);
}
