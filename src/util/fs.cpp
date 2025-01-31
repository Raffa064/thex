#include <cstdlib>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <util.hpp>

std::string lookup_file(std::string path, std::string name) {
  int i = path.length();

  do {
    std::string file_path = path.substr(0, i) + "/" + name;

    if (std::filesystem::exists(file_path))
      return file_path;

    i = path.find_last_of("/", i - 1);
  } while (i > 0);

  return "";
}

bool mkdirs(std::string path) {
  if (!std::filesystem::exists(path))
    return std::filesystem::create_directories(path);

  return true; // already exists
}

std::string get_home() {
  char *home = std::getenv("HOME");

  if (home)
    return std::string(home);

  throw std::runtime_error("Can't find HOME path");
}

std::string get_cwd() { // Current Working Dir
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));

  return std::string(cwd);
}

bool is_valid_path(std::string path) {
  return std::filesystem::exists(path) &&
         std::filesystem::is_regular_file(path);
}
