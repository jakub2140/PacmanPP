
#include "map_creator.h"
#include "Pacman.h"
#include "Ghosts.h"
#include "constants.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <array>





void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window)
{

	//sets the sizes of the rectangles and circles that are being used. 
	sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape wall_shape(sf::Vector2f(WALL_SIZE, WALL_SIZE));

	//goes thru entire map and colors it based on which cell type it is and draws it on the window
	for (unsigned int y = 0; y < MAP_WIDTH; y++)
	{
		for (unsigned int x = 0; x < MAP_HEIGHT; x++)
		{
			cell_shape.setPosition(CELL_SIZE * y, CELL_SIZE * x);//sets the position of the "cells" which are just rectangles
			wall_shape.setPosition(WALL_SIZE * y, WALL_SIZE * x);//sets the position of the walls


			if (i_map[y][x] == Cell::Wall)
			{
				wall_shape.setFillColor(sf::Color(4, 10, 137));// if cell type is wall it colors a blue rectabgle
				i_window.draw(wall_shape);
			}

			if (i_map[y][x] == Cell::Opening)
			{
				cell_shape.setFillColor(sf::Color(250, 250, 0));//if cell type is the opening changes it to yellow rectangle 
				i_window.draw(cell_shape);
			}

			if (i_map[y][x] == Cell::Pellets)
			{
				circle.setFillColor(sf::Color(250, 250, 0));
				circle.setRadius(CELL_SIZE / 6);
				circle.setPosition(CELL_SIZE * y + (CELL_SIZE / 2 - circle.getRadius()), CELL_SIZE * x + CELL_SIZE / 2 - circle.getRadius());
				i_window.draw(circle);
			}

			if (i_map[y][x] == Cell::BigPellets)
			{
				circle.setFillColor(sf::Color(255, 0, 0));
				circle.setRadius(CELL_SIZE / 4);
				circle.setPosition(CELL_SIZE * y + (CELL_SIZE / 2 - circle.getRadius()), CELL_SIZE * x + CELL_SIZE / 2 - circle.getRadius());
				i_window.draw(circle);
			}


		}

	}








}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& pacman, Pinky& pinky, Blinky& blinky, Clyde& clyde, Inky& inky)
{
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map_output{};

	//goes through every character in the map array and converts it to a cell based on the character 
	for (unsigned char y = 0; y < MAP_HEIGHT; y++)
	{
		for (unsigned char x = 0; x < MAP_WIDTH; x++)
		{
			map_output[x][y] = Cell::Empty;//entire map starts off as empty 

			if (i_map_sketch[y][x] == ' ')
			{
				map_output[x][y] = Cell::Empty;//any space is an empty cell

			}

			if (i_map_sketch[y][x] == '#')
			{
				map_output[x][y] = Cell::Wall; //any # is a wall

			}

			if (i_map_sketch[y][x] == '-')
			{
				map_output[x][y] = Cell::Opening;//the opening is -

			}

			if (i_map_sketch[y][x] == 'p')
			{
				pacman.setPosition(CELL_SIZE * x, CELL_SIZE * y); //sets the position of pacman

			}


			if (i_map_sketch[y][x] == '.')
			{
				map_output[x][y] = Cell::Pellets;//chanegs any . to pellets

			}


			if (i_map_sketch[y][x] == 'O')
			{
				map_output[x][y] = Cell::BigPellets;//changes any O to Energizers

			}

			//sets the position of the ghosts based on numbers
			if (i_map_sketch[y][x] == '1')
			{
				inky.setPosition(CELL_SIZE * x, CELL_SIZE * y);

			}

			if (i_map_sketch[y][x] == '2')
			{
				pinky.setPosition(CELL_SIZE * x, CELL_SIZE * y);

			}

			if (i_map_sketch[y][x] == '3')
			{
				clyde.setPosition(CELL_SIZE * x, CELL_SIZE * y);

			}

			if (i_map_sketch[y][x] == '4')
			{
				blinky.setPosition(CELL_SIZE * x, CELL_SIZE * y);

			}

		}
	}

	return map_output;

}


