#pragma once

#include "interface/color.h"
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
std::string to_upper(std::string input);
std::string pad_start(std::string input, int length, char ch = ' ');
std::string pad_end(std::string input, int length, char ch = ' ');

// Convert data (convert.cpp)
std::string to_hex(int value, int width);
std::string to_hex(char value);
int hex_to_int(std::string input);
Buffer to_hex_seq(std::string input); // Converts hex sequences to a Buffer
ColorPair to_color_pair(std::string input);

// Validate data (validate.cpp)
bool is_number(const std::string &input);
bool is_hex(const std::string &input);
bool is_non_printable(const char &ch);
bool is_quoted_str(const std::string &input);
bool is_hex_sequence(const std::string &input);
bool is_flag(const std::string &input);
bool is_color_pair(const std::string &input);
