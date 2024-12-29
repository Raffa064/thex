#pragma once

#include <string>

const int BAD_FILE = -1;
const int INVALID_POSITION = -2;

struct Buffer {
  char *data;
  size_t length; // Total alocated length
  size_t count;  // Stored amount of data bytes
};

class IOFile {
  std::string path;

public:
  int read(int pos, Buffer buffer);

  int write(int pos, Buffer buffer);

  IOFile(std::string path): path(path) {}
};
