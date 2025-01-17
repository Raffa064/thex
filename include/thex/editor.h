#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef std::uint32_t uint;

struct Buffer {
  uint length = 0;
  char *data;

  void resize(uint);
  std::string to_string();

  Buffer() : data(nullptr) {}

  Buffer(uint);
  Buffer(std::string);

  ~Buffer();
};

struct Page {
  Buffer buffer;
  uint position = 0;
  uint read = 0;

  char get(int);
  uint end();
};

struct Range {
  uint start = 0;
  uint end = 0;

  bool overlaps(Range);
  bool overlaps(uint);
};

struct Cursor : public Range {
  uint nibble = 0;
  bool selection = false;

  uint get();
  void set(uint);
  void move(int);
  void moven(int);
  void select(Range);
  std::string to_string();
};

struct Marker : public Range {
  uint color;
};

class Editor {
public:
  std::string path;
  Cursor cursor;
  std::vector<Marker *> markers;

  void get_markers(std::vector<Marker *> &, Range);
  void get_markers(std::vector<Marker *> &);

  uint get_fsize();

  // Base I/O functions
  uint read(Buffer &, uint);
  void write(Buffer &, uint);
  void inject(Buffer &, uint);
  void remove(uint, uint);

  // Derivate I/O functions
  void read_page(Page &);
  uint read_num(uint); // TODO: make it work form multiple num types
  std::string read_str(uint, uint);
  std::string read_str(uint); // look for null byte

  void insert_num(uint, uint); // TODO: num types
  void insert_str(uint, std::string);
  void fill(uint, uint, char);
  void wipe(uint, uint);

  void inject_num(uint, uint); // TODO: num types
  void inject_str(uint, std::string);

  Editor() {}

  Editor(std::string path) : path(path) {}

  Editor &operator=(const Editor &other) {
    path = other.path;
    cursor = other.cursor;
    markers = other.markers;

    return *this;
  }
};
