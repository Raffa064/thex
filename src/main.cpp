#include <iostream>
#include <ncurses.h>
#include <string>
#include <thex/app.h>
#include <ui.h>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) { // 0:thex 1:file_path
    cout << "Invalid argument count" << endl;
    return 1;
  }

  string path(argv[1]);

  // TODO: validate path

  THexApp app = THexApp(path);
  app.start();
}
