#pragma once

#include "thex/editor.h"
#include <string>
#include <vector>

// File system (fs.cpp)
std::string get_cwd();
bool is_valid_path(std::string path);

// String (str.cpp)
std::string trim(std::string &input);
std::vector<std::string> split(std::string input, std::string pattern);
bool starts_with(std::string input, std::string sub);
std::string to_upper(std::string);
std::string pad_start(std::string, int, char = ' ');
std::string pad_end(std::string, int, char = ' ');

// Convert data (convert.cpp)
std::string to_hex(int, int);
std::string to_hex(int);
int hex_to_int(std::string);
Buffer to_hex_seq(std::string);

// Validate data (validate.cpp)
bool is_number(std::string &);
bool is_hex(std::string &);
bool is_non_printable(char);
bool is_quoted_str(std::string);
bool is_hex_sequence(std::string);
