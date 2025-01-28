#include <iomanip>
#include <sstream>
#include <string>
#include <util.h>

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
