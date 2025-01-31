#pragma once

#include "interface/color.h"
#include <string>

namespace Config {

void init();

ColorPair get_colorp(std::string color);

} // namespace Config
