
#include "map_creator.h"
#include "Pacman.h"
#include "Ghosts.h"
#include "constants.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <array>

using namespace std;



void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window)
{
	
	
	sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape wall_shape(sf::Vector2f(WALL_SIZE, WALL_SIZE));



	
	

	for (unsigned int y = 0; y < MAP_WIDTH; y++)
	{
		for (unsigned int x = 0; x < MAP_HEIGHT; x++)
		{
			cell_shape.setPosition(CELL_SIZE * y, CELL_SIZE * x);
			wall_shape.setPosition(WALL_SIZE * y, WALL_SIZE * x);
			switch (i_map[y][x])
			{
				case Cell::Wall:
				{
					wall_shape.setFillColor(sf::Color(0, 0, 250));
					i_window.draw(wall_shape);
					break;
				}
				case Cell::Opening:
				{
					cell_shape.setFillColor(sf::Color(250, 250, 0));
					i_window.draw(cell_shape);
					break;
				}
				case Cell::Pellets:
				{
					circle.setFillColor(sf::Color(250, 250, 0));
					circle.setRadius(CELL_SIZE / 6);
					circle.setPosition( CELL_SIZE * y + (CELL_SIZE / 2 - circle.getRadius()), CELL_SIZE* x + CELL_SIZE / 2 - circle.getRadius());
					i_window.draw(circle);
					break;
				}
				case Cell::BigPellets:
				{
					circle.setFillColor(sf::Color(255, 0, 0));
					circle.setRadius(CELL_SIZE / 4);
					circle.setPosition(CELL_SIZE * y + (CELL_SIZE / 2 - circle.getRadius()), CELL_SIZE * x + CELL_SIZE / 2 - circle.getRadius());
					i_window.draw(circle);
				}

				

			}

			
		}

	}


}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& pacman, Ghosts& pinky)
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
				case '-':
				{
					map_output[x][y] = Cell::Opening;
					break;
				}
				
				case 'p':
				{
					pacman.setPosition(CELL_SIZE * x, CELL_SIZE * y);
					break;
				}
				
				case '.':
				{
					map_output[x][y] = Cell::Pellets;
					break;
				}
				case 'O':
				{
					map_output[x][y] = Cell::BigPellets;
					break;
				}
				case '1':
				{
					pinky.setPosition(CELL_SIZE * x, CELL_SIZE * y);
					break;
				}
			}
		}
	}

	return map_output;

}



