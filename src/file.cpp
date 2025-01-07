#include <algorithm>
#include <file.h>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

#define UP -1
#define DOWN 1

int BFReader::get_buffer_size() const { return chunkCount * chunkLength; }

int BFReader::get_chunk_index(int id) const {
  return (upchunk_index + id * chunkLength) % get_buffer_size();
}

int BFReader::get_chunk_position(int id) const {
  return upchunk_position + id * chunkLength;
}

int BFReader::to_index(int position) const { 
  int relative_index = position - upchunk_position; // relative to upchunk
  return (upchunk_index + relative_index) % get_buffer_size();
}

void BFReader::read_chunk(int id) {
  int chunkIndex = get_chunk_index(id);
  int chunkPosition = get_chunk_position(id);
  char *chunk = chunkBuffer + chunkIndex;

  ifstream file(path, ios::binary);

  if (!file)
    throw new runtime_error("Can't read chunk, err=BAD_FILE");

  file.seekg(chunkPosition);
  file.read(chunk, chunkLength);
  
  // TODO: read may not completely fill the entire chunk at the end of the file!
}

void BFReader::roll(int direction) {
  /*
    NOTE: this method can't ensure valid upchunk positions
    cause it doesn't known file size. It's responsability of calling
    methods to ensure rolling up to negative positions!
  */

  upchunk_index += direction * chunkLength;
  upchunk_position += direction;

  // Calculating cyclic index:
  int max_index = get_buffer_size();

  if (upchunk_index < 0)
    upchunk_index += max_index;

  upchunk_index = max(max_index, upchunk_index);
}

void BFReader::fit_to_range(int startPosition, int endPosition) {
  while (startPosition < upchunk_position) {
    roll(UP);
    read_chunk(0);
  }

  #define downchunk_position (upchunk_position + chunkCount * chunkLength)
  while (endPosition > downchunk_position) {
    roll(DOWN);
    read_chunk(chunkCount-1);
  }
}

int BFReader::size() const {
  ifstream file(path, ios::binary | ios::ate);
  return file.tellg();
}

void BFReader::read(char *buffer, int startPosition, int length) {
  int fend = size(); // EOF position
  
  if (startPosition < 0 || startPosition >= fend || length > get_buffer_size())
    throw runtime_error("Invalid read range or position.");

  int endPosition = min(fend, startPosition + length);
  fit_to_range(startPosition, endPosition);

  length = endPosition - startPosition; // Fit buffer length to end of file (if necessary)

  int startIndex = to_index(startPosition);
  char *cBuffer = chunkBuffer + startIndex;
  
  for (int i = 0; i < length; i++)
    buffer[i] = cBuffer[i];
}

// write(char *buffer, int start, int length);

BFReader::BFReader(string path, int chunkCount, int chunkLength, bool read) {
  this->path = path;
  this->chunkCount = chunkCount;
  this->chunkLength = chunkLength;

  upchunk_index = 0;
  upchunk_position = 0;

  chunkBuffer = new char[get_buffer_size()];

  if (read)
    for (int i = 0; i < chunkCount; i++)
      read_chunk(i);
}

BFReader::BFReader(const BFReader& other) : BFReader(other.path, other.chunkCount, other.chunkLength, false) {
  upchunk_index = other.upchunk_index;
  upchunk_position = other.upchunk_position;

  memcpy(chunkBuffer, other.chunkBuffer, other.get_buffer_size());
}

BFReader::~BFReader() { 
  if (chunkBuffer != nullptr) 
    delete[] chunkBuffer; 
}
