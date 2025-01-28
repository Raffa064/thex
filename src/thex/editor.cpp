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

void Cursor::move(int pos) {
  int newPosition = static_cast<int>(get()) + pos;

  if (newPosition < 0)
    newPosition = 0;

  set(newPosition);
}

void Cursor::moven(int npos) {
  npos += nibble;

  if (npos < 0)
    move(-1);
  else
    move(npos / 2);

  nibble = abs(npos % 2);
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

uint Editor::read(Buffer &buffer, uint pos) {
  std::ifstream file(path, std::ios::binary);
  if (file && file.seekg(pos)) {
    file.read(buffer.data, buffer.length);

    return file.gcount();
  }

  return 0;
}

bool Editor::write(Buffer &buffer, uint pos) {
  std::ofstream file(path, std::ios::binary | std::ios::in);

  if (file && file.seekp(pos)) {
    file.write(buffer.data, buffer.length);

    return true;
  }

  return false;
}

void Editor::inject(Buffer &buffer, uint pos) {
  // TODO: create tmp file, move content before position, append with buffer
  // content, them append the after buffer content, replace file
}

void Editor::remove(uint pos, uint end) {
  // TODO: create tmp file, move content before position, skip selection range,
  // append with after contents, replace file
}

// Derivate I/O functions
void Editor::read_page(Page &page) {
  int readBytes = read(page.buffer, page.position);
  page.read = readBytes;
}

uint Editor::read_num(uint) {
  // TODO: make it work form multiple num types
  return 0;
}

std::string Editor::read_str(uint pos, uint length) {
  Buffer buffer(length);
  read(buffer, pos);

  return buffer.to_string();
}

void Editor::write_byte(char ch, uint pos) {
  Buffer tmp = Buffer(1);
  tmp.data[0] = ch;
  write(tmp, pos);
}

void Editor::insert_num(uint, uint) {} // TODO: num types

void Editor::insert_str(uint pos, std::string str) {
  Buffer buffer(str);
  write(buffer, pos);
}

void Editor::fill(uint pos, uint length, char ch) {
  Buffer buffer(length);

  for (int i = 0; i < length; i++)
    buffer.data[i] = ch;

  write(buffer, pos);
}

// wipe is basically a fill with 0x00
void Editor::wipe(uint pos, uint length) { fill(pos, length, 0); }

uint Editor::find(uint start, Buffer sequence) {
  Buffer tmp(sequence.length);

  int pos = start;
  while (true) {
    if (read(tmp, pos) < sequence.length)
      return start;

    if (tmp == sequence)
      return pos;

    pos++;
  }
}

void Editor::inject_num(uint, uint) {} // TODO: num types

void Editor::inject_str(uint pos, std::string str) {
  Buffer buffer(str);
  inject(buffer, pos);
}
