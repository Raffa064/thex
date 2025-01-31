#pragma once

#include "interface/color.h"
#include <string>

namespace Config {

void init();

ColorPair get_pair(std::string color, std::string df);

bool get_flag(std::string entry_path, bool df = false);

int get_int(std::string entry_path, int df = 0);

} // namespace Config
