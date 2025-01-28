#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

typedef std::uint32_t uint;

struct Buffer {
  uint length = 0;
  char *data;

  void resize(uint len);
  std::string to_string();

  Buffer() : data(nullptr) {}

  Buffer(uint length);
  Buffer(std::string str);
  Buffer(const Buffer &other);

  ~Buffer();

  bool operator==(Buffer &other);
  Buffer &operator=(const Buffer &other);
};

struct Page {
  Buffer buffer;
  uint position = 0;
  uint read = 0;

  void set(int fpos, char ch); // set char at pos (in file pos)
  char get(int fpos);          // get (in file pos) char

  uint end();
};

struct Range {
  uint start = 0;
  uint end = 0;

  bool overlaps(Range other);
  bool overlaps(uint pos); // check pos in inside range
};

struct Cursor : public Range {
  static const int HIGH_NIBBLE = 0;
  static const int LOW_NIBBLE = 1;

  uint nibble = 0;
  bool selection = false;

  uint get();
  void set(uint pos);
  void move(int amount);
  void moven(int n_amount); // move nibble-to-nibble
  void select(Range range);
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

  void get_markers(std::vector<Marker *> &out, Range range);
  void get_markers(std::vector<Marker *> &out); // get markers from cursor range

  uint get_fsize();

  // Base I/O functions
  uint read(uint pos, Buffer &buffer);
  bool write(uint pos, Buffer &buffer);
  void inject(uint pos, Buffer &buffer);
  void remove(uint start, uint end);

  // Derivate I/O functions
  void read_page(Page &page);
  uint read_num(uint pos); // TODO: make it work for multiple num types
  std::string read_str(uint pos, uint length);

  void write_char(uint pos, char ch);
  void insert_num(uint pos, int num); // TODO: num types
  void insert_str(uint pos, std::string str);
  void fill(uint start, uint end, char ch);
  void wipe(uint start, uint end); // same as fill with zeros

  uint find(uint, Buffer);

  void inject_num(uint pos, int num); // TODO: num types
  void inject_str(uint pos, std::string str);

  Editor() {}

  Editor(std::string path) : path(path) {}

  Editor &operator=(const Editor &other);
};
