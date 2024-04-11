#pragma once


constexpr unsigned int CELL_SIZE = 16;
const unsigned int FONT_SIZE = 16;
constexpr unsigned int WALL_SIZE = 16;


constexpr unsigned int MAP_HEIGHT = 21;
constexpr unsigned int MAP_WIDTH = 21;

constexpr unsigned int SCREEN_RESIZE = 3;

constexpr unsigned int FRAME_DURATION = 16667;
constexpr unsigned int PACMAN_SPEED = 1;

enum Cell
{
	Opening,
	Empty,
	Wall,
	Pellets,
	BigPellets
};

enum AIType
{
	Scatter,
	Chase,
	Frightened
};

struct Position {

	short int x;
	short int y;

	bool operator==(const Position& Oposition)
	{
		return this->x == Oposition.x && this->y == Oposition.y;
	}

};

