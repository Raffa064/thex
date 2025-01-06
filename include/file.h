#pragma once

#include <string>

/*
CONVENTIONS:

id       -> Number of the chunk (0, 1, ..)
index    -> In buffer address
position -> In file address
*/

#define UP -1
#define DOWN 1
#define NOT_REACHED -1

class BFReader {
  std::string path;

  char *chunkBuffer;
  int chunkCount;
  int chunkLength;
  int upchunk_index;
  int upchunk_position;

  int get_buffer_size();

  int get_chunk_index(int id);

  int get_chunk_position(int id);

  int to_index(int position);

  void read_chunk(int id);

  void roll(int direction);

  void fit_to_range(int startPosition, int endPosition);

public:
  int size();
  
  void read(char *buffer, int startPosition, int length);

  // write(char *buffer, int start, int length);

  BFReader() {}

  BFReader(std::string path, int chunkCount, int chunkLength);

  ~BFReader();
};
