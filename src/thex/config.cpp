#include "ini.h"
#include "util.h"
#include <thex/config.h>

ini::Document configs;

void Config::init() {
  if (!load("./configs.ini", configs))
    throw std::runtime_error("Invalid configuration");
}

ColorPair Config::get_colorp(std::string color) {
  std::string df = "#eeeeee;#222222"; // TODO: set as param
  std::string pair = configs.get_df("palette." + color, df);

  if (is_color_pair(pair))
    return to_color_pair(pair);

  return to_color_pair(df);
}
