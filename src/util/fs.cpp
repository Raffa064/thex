#include <filesystem>
#include <string>
#include <unistd.h>

std::string get_cwd() { // Current Working Dir
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));

  return std::string(cwd);
}

bool is_valid_path(std::string path) {
  return std::filesystem::exists(path) &&
         std::filesystem::is_regular_file(path);
}
