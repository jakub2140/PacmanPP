
#include "constants.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include "Pacman.h"
#include "Ghosts.h"


void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window);
std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch,Pacman& pacman, Ghosts& pinky);
