#include <iostream>
#include <ncursesw/ncurses.h>
#include <string>
#include <thex/app.h>
#include <util.h>

int main(int argc, char *argv[]) {
  if (argc != 2) { // 0:thex 1:file_path
    std::cout << "An file path is expected" << std::endl;
    return 1;
  }

  std::string path(argv[1]);

  if (!is_valid_path(path)) {
    std::cout << "Invalid file path: " << path << std::endl;
    return 1;
  }

  THexApp app = THexApp(path);
  app.start();
}
