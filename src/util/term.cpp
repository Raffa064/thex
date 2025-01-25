#include <string>
#include <unistd.h>

std::string get_cwd() { // Current Working Dir
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));

  return std::string(cwd);
}
