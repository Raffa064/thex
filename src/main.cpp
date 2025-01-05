#include "file.h"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thex/app.h>
#include <ui.h>

using namespace std;

THexApp *app;

void sig_handler(int signal) {
  app->end();
  std::cout << "Finished by kill signal" << std::endl;
}

int main(int argc, char *argv[]) {
  signal(SIGTERM, sig_handler);

  if (argc != 2) { // 0:thex 1:file_path
    cout << "Invalid argument count" << endl;
    return 1;
  }

  string path(argv[1]);
  app = new THexApp(path);
  app->start();

  delete app;
}
