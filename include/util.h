#pragma once

#include <string>
#include <vector>

const std::string EMPTY_SPACE = " \n\t\r\f\v";

std::string get_cwd();

std::string trim(std::string &input);

std::vector<std::string> split(std::string input, std::string pattern);

bool starts_with(std::string input, std::string sub);

std::string to_upper(std::string);

std::string to_hex(int);

std::string to_hex(int, int);

std::string padStart(std::string, int, char = ' ');

std::string padEnd(std::string, int, char = ' ');
