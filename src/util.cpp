#include <cctype>
#include <cstddef>
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <util.h>
#include <vector>

using namespace std;

// TODO: split this file into multiple utility modules

string get_cwd() { // Current Working Dir
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));

  return string(cwd);
}

vector<string> read_file(string path) {
  ifstream file(path);

  if (!file)
    throw runtime_error("Can't load file");

  vector<string> lines;
  string line = "";

  while (file) {
    getline(file, line);
    lines.push_back(line);
  }

  return lines;
}

string trim(string &input) {
  size_t start = input.find_first_not_of(EMPTY_SPACE);
  size_t end = input.find_last_not_of(EMPTY_SPACE);

  if (start == string::npos)
    start = 0;
  if (end == string::npos)
    end = input.size();

  return input.substr(start, end - start + 1);
}

vector<string> split(string input, string pattern) {
  vector<string> out;
  smatch match;
  regex regex(pattern);

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

bool starts_with(string input, string sub) {
  if (input.size() < sub.size())
    return false;

  return input.compare(0, sub.size(), sub) == 0;
}

string to_upper(string str) {
  vector<char> chars;

  for (int i = 0; i < str.size(); i++)
    chars.push_back(toupper(str[i]));

  return string(chars.begin(), chars.end());
}

string to_hex(int v, int width) {
  ostringstream stream;
  stream << hex << setw(width) << setfill('0') << v;
  string str = stream.str();

  return to_upper(str);
}

string to_hex(char ch) { return to_hex(ch, 2); }

string padStart(string input, int length, char ch) {
  while (input.size() < length)
    input = ch + input;

  return input;
}

string padEnd(string input, int length, char ch) {
  while (input.size() < length)
    input += ch;

  return input;
}
