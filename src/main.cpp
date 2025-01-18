#include <filesystem>
#include <iostream>
#include <string>
#include <thex/app.h>
#include <util.h>

using namespace std;

bool is_valid_path(string path) {
  return filesystem::exists(path) && filesystem::is_regular_file(path);
}

int main(int argc, char *argv[]) {
  if (argc != 2) { // 0:thex 1:file_path
    cout << "An file path is expected" << endl;
    return 1;
  }

  string path(argv[1]);

  if (!is_valid_path(path)) {
    cout << "Invalid file path: " << path << endl;
    return 1;
  }

  THexApp app = THexApp(path);
  app.start();
}
