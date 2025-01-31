#include "ini.h"
#include "util.h"
#include <string>
#include <thex/config.h>

ini::Document configs;

void Config::init() {
  std::string config_dir = get_home() + "/.config/thex";
  mkdirs(config_dir);

  // Global configs
  std::string global_cfg_file = config_dir + "/config.ini";
  load(global_cfg_file, configs);

  // Local configs
  std::string local_cfg_file = lookup_file(get_cwd(), "thex.ini");
  if (!local_cfg_file.empty())
    load(local_cfg_file, configs);
}

ColorPair Config::get_pair(std::string color, std::string df) {
  std::string pair = configs.get_df("palette." + color, df);

  if (is_color_pair(pair))
    return to_color_pair(pair);

  return to_color_pair(df);
}

bool Config::get_flag(std::string entry_path, bool df) {
  std::string flag = configs.get_df(entry_path, df ? "on" : "off");

  return flag == "on";
}

int Config::get_int(std::string entry_path, int df) {
  std::string num = configs.get_df(entry_path, std::to_string(df));

  if (is_number(num))
    return std::stoi(num);

  return df;
}
