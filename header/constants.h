#pragma once

#include <string>
constexpr unsigned int CELL_SIZE = 16;
const unsigned int FONT_SIZE = 16;
constexpr unsigned int WALL_SIZE = 16;


constexpr unsigned int MAP_HEIGHT = 21;
constexpr unsigned int MAP_WIDTH = 21;

constexpr unsigned int SCREEN_RESIZE = 3;

constexpr unsigned int FRAME_DURATION = 10000;
constexpr unsigned int PACMAN_SPEED = 1;

enum Cell //Enums let us use words instead of numbers, making code more readable
{
	Opening, //Each one is a type of cell on the map
	Empty,
	Wall,
	Pellets,
	BigPellets
};

enum AIType
{
	Scatter, //Each one is a possible ghost AI type
	Chase,
	Frightened,
	Running
};

struct Position {

	short int x;
	short int y;

	bool operator==(const Position& Oposition) //allows for direct comparison of string
	{
		return this->x == Oposition.x && this->y == Oposition.y;
	}
	std::string operator<<(const Position&) //Debug overload, used to output position more easily for debugging
	{
		std::string output = std::to_string(this->x) + " " + std::to_string(this->y);
		return output;
	}
};

