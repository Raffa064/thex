#include "util.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <string>
#include <thex/editor.h>
#include <vector>

void Buffer::resize(uint len) {
  if (data != nullptr)
    delete[] data;

  length = len;
  data = new char[len];
}

std::string Buffer::to_string() { return std::string(data); }

Buffer::Buffer(uint length) : length(length) { data = new char[length]; }

Buffer::Buffer(std::string str) {
  length = str.size();
  data = new char[length];

  memcpy(data, str.c_str(), length);
}

Buffer::Buffer(const Buffer &other) {
  length = other.length;
  data = new char[length];

  memcpy(data, other.data, length);
}

Buffer::~Buffer() {
  if (data != nullptr)
    delete[] data;
}

bool Buffer::operator==(Buffer &other) {
  if (other.length != length)
    return false;

  for (int i = 0; i < length; i++) {
    if (other.data[i] != data[i])
      return false;
  }

  return true;
}

Buffer &Buffer::operator=(const Buffer &other) {
  if (this == &other)
    return *this;

  if (data != nullptr)
    delete[] data;

  length = other.length;
  data = new char[length];

  memcpy(data, other.data, length);

  return *this;
}

void Page::set(int fpos, char ch) {
  int index = fpos - position;

  if (index < 0 || index >= buffer.length)
    return;

  buffer.data[index] = ch;
}

char Page::get(int fpos) {
  int index = fpos - position;

  if (index < 0 || index >= buffer.length)
    return 0; // invalid positions

  return buffer.data[index];
}

uint Page::end() { return position + read; }

bool Range::overlaps(Range other) {
  return (start >= other.start && start <= other.end) ||
         (end >= other.start && end <= other.end);
}

bool Range::overlaps(uint pos) { return start <= pos && end >= pos; }

uint Cursor::get() {
  if (selection)
    return end;

  return start;
}

void Cursor::set(uint pos) {
  if (selection) {
    end = std::max(start, pos);
    return;
  }

  start = end = pos;
}

void Cursor::move(int amount) {
  int newPosition = static_cast<int>(get()) + amount;

  if (newPosition < 0)
    newPosition = 0;

  set(newPosition);
}

void Cursor::moven(int n_amount) {
  n_amount += nibble;

  if (n_amount < 0)
    move(-1);
  else
    move(n_amount / 2);

  nibble = abs(n_amount % 2);
}

void Cursor::select(Range range) {
  start = range.start;
  end = range.end;
  selection = true;
}

std::string Cursor::to_string() {
  return "[ " + to_hex(start, 8) +
         (selection ? ":" + to_hex(end, 8) + " ]" : " ]");
}

void Editor::get_markers(std::vector<Marker *> &out, Range range) {
  for (Marker *m : markers)
    if (range.overlaps(*m))
      out.push_back(m);
}

void Editor::get_markers(std::vector<Marker *> &out) {
  get_markers(out, cursor);
}

uint Editor::get_fsize() {
  std::ifstream file(path, std::ios::binary);
  file.seekg(0, std::ios::end);
  return file.tellg();
}

uint Editor::read(uint pos, Buffer &buffer) {
  std::ifstream file(path, std::ios::binary);
  if (file && file.seekg(pos)) {
    file.read(buffer.data, buffer.length);

    return file.gcount();
  }

  return 0;
}

bool Editor::write(uint pos, Buffer &buffer) {
  std::ofstream file(path, std::ios::binary | std::ios::in);

  if (file && file.seekp(pos)) {
    file.write(buffer.data, buffer.length);

    return true;
  }

  return false;
}

void Editor::inject(uint pos, Buffer &buffer) {
  // TODO: create tmp file, move content before position, append with buffer
  // content, them append the after buffer content, replace file
}

void Editor::remove(uint start, uint end) {
  // TODO: create tmp file, move content before position, skip selection range,
  // append with after contents, replace file
}

// Derivate I/O functions
void Editor::read_page(Page &page) {
  int readBytes = read(page.position, page.buffer);
  page.read = readBytes;
}

uint Editor::read_num(uint pos) {
  // TODO: make it work form multiple num types
  return 0;
}

std::string Editor::read_str(uint pos, uint length) {
  Buffer buffer(length);
  read(pos, buffer);

  return buffer.to_string();
}

void Editor::write_char(uint pos, char ch) {
  Buffer tmp = Buffer(1);
  tmp.data[0] = ch;
  write(pos, tmp);
}

void Editor::insert_num(uint pos, int num) {} // TODO: num types

void Editor::insert_str(uint pos, std::string str) {
  Buffer buffer(str);
  write(pos, buffer);
}

void Editor::fill(uint start, uint end, char ch) {
  Buffer buffer(end - start);

  for (int i = 0; i < buffer.length; i++)
    buffer.data[i] = ch;

  write(start, buffer);
}

// wipe is basically a fill with 0x00
void Editor::wipe(uint start, uint end) { fill(start, end, 0); }

uint Editor::find(uint start, Buffer sequence) {
  Buffer tmp(sequence.length);

  int pos = start;
  while (true) {
    if (read(pos, tmp) < sequence.length)
      return start;

    if (tmp == sequence)
      return pos;

    pos++;
  }
}

void Editor::inject_num(uint pos, int num) {} // TODO: num types

void Editor::inject_str(uint pos, std::string str) {
  Buffer buffer(str);
  inject(pos, buffer);
}

Editor &Editor::operator=(const Editor &other) {
  path = other.path;
  cursor = other.cursor;
  markers = other.markers;

  return *this;
}
