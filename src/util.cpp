#include <sstream>
#include<util.h>
#include <cstddef>
#include <regex>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>

using namespace std;

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

  return input.compare(0, input.size(), sub) == 0;
}

string to_hex(char ch) {
  ostringstream stream;
  stream << hex << setw(2) << setfill('0') << (int) ch;
  return stream.str();
}

string to_hex(char ch, int length) {
  return padStart(to_hex(ch), length, '0');
}

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
