#include <cctype>
#include <cstddef>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <unistd.h>
#include <util.h>
#include <vector>

std::string trim(std::string &input) {
  size_t start = input.find_first_not_of(EMPTY_SPACE);
  size_t end = input.find_last_not_of(EMPTY_SPACE);

  if (start == std::string::npos)
    start = 0;
  if (end == std::string::npos)
    end = input.size();

  return input.substr(start, end - start + 1);
}

std::vector<std::string> split(std::string input, std::string pattern) {
  std::vector<std::string> out;
  std::smatch match;
  std::regex regex(pattern);

  while (regex_search(input, match, regex)) {
    int split_on = match.position();
    out.push_back(input.substr(0, split_on));
    input = input.substr(split_on + match.length());
  }

  if (!input.empty()) {
    out.push_back(input); // and there may be one last token at the end
  }

  return out;
}

bool starts_with(std::string input, std::string sub) {
  if (input.size() < sub.size())
    return false;

  return input.compare(0, sub.size(), sub) == 0;
}

std::string to_upper(std::string str) {
  std::vector<char> chars;

  for (int i = 0; i < str.size(); i++)
    chars.push_back(toupper(str[i]));

  return std::string(chars.begin(), chars.end());
}

std::string to_hex(int v, int width) {
  std::ostringstream stream;
  stream << std::hex << std::setw(width) << std::setfill('0') << v;
  std::string str = stream.str();

  return to_upper(str);
}

std::string to_hex(char ch) { return to_hex(ch, 2); }

std::string pad_start(std::string input, int length, char ch) {
  while (input.size() < length)
    input = ch + input;

  return input;
}

std::string pad_end(std::string input, int length, char ch) {
  while (input.size() < length)
    input += ch;

  return input;
}
