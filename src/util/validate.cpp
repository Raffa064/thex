#include <regex>
#include <string>
#include <util.h>

const std::regex REGEX_NUMBER("[\\-\\+]?[0-9]+");
const std::regex REGEX_HEX("(0x)?[0-9a-f]+", std::regex::icase);
const std::regex REGEX_STRING("\"(\\\"|[^\"])*\"");
const std::regex REGEX_HEX_SEQ("(\\s*[0-9a-f]{2}\\s*)+", std::regex::icase);

bool is_number(std::string &input) {
  return std::regex_match(input, REGEX_NUMBER);
}

bool is_hex(std::string &input) { return std::regex_match(input, REGEX_HEX); }

bool is_non_printable(char ch) { return ch < 0x20 || ch > 0x7E; }

bool is_quoted_str(std::string input) {
  return std::regex_match(input, REGEX_STRING);
}

bool is_hex_sequence(std::string input) {
  return std::regex_match(input, REGEX_HEX_SEQ);
}
