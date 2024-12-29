#include "file.h"
#include <fstream>

using namespace std;

int IOFile::read(int pos, Buffer buffer) {
  ifstream file(path, ios::binary);

  if (!file)
    return BAD_FILE;

  if (file.seekg(pos)) {
    file.read(buffer.data, buffer.length);
    buffer.count = file.gcount();
    return 1;
  }

  return INVALID_POSITION;
}

int IOFile::write(int pos, Buffer buffer) {
  ofstream file(path, ios::binary);

  if (!file)
    return BAD_FILE;

  file.seekp(pos);
  file.write(buffer.data, buffer.count);

  return 1;
}
