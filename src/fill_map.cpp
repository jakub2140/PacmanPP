
#include "map_creator.h"
#include "constants.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
using namespace std;



void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window)
{
	
	sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));


	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			cell_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
			switch (i_map[a][b])
			{
				case Cell::Wall:
				{
					cell_shape.setFillColor(sf::Color(36, 36, 255));
					i_window.draw(cell_shape);
				}
				
			}

			
		}

	}


}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch)
{
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map_output{};

	for (unsigned char y = 0; y < MAP_HEIGHT; y++)
	{
		for (unsigned char x = 0; x < MAP_WIDTH; x++)
		{
			map_output[x][y] = Cell::Empty;

			switch (i_map_sketch[y][x])
			{
				case ' ':
				{
					map_output[x][y] = Cell::Empty;
					break;
				}
				case '#':
				{
					map_output[x][y] = Cell::Wall;
					break;
				}
				
			}
		}
	}

	return map_output;

}


