#pragma once

#include <array>
#include <constants.h>

bool collides(int celltype, short myX, short myY, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);