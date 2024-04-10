//Andrew Simon, Jacob Cortez

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <array>
#include <chrono>
#include <string>
#include "map_creator.h"
#include "Pacman.h"



int main()
{
    std::array<std::string, MAP_HEIGHT> sketch = {
		" ################### ",
		" #........#........# ",
		" #O##.###.#.###.##O# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.###.#.### #### ",
		"    #.#...4...#.#  . ",
		"#####.#.##-##.#.#####",
		"     ...#123#...     ",
		"#####.#.##### #.#####",
		"    #.#.......#.#    ",
		" ####.#.#####.#.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #O.#.....p.....#.O# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};
	
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_SIZE + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	//Resizing the window.
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_SIZE + CELL_SIZE * MAP_HEIGHT)));

	Pacman pacman;
	
	Pinky pinky;//pink
	Blinky blinky;//red
	Clyde clyde;//orange
	Inky inky;//blue
	

	map = convert_sketch(sketch,pacman, pinky, blinky,clyde, inky);
	
	
			
	while (1 == window.isOpen())
	{
		
		
			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						//Making sure the player can close the window.
						window.close();
					}
				}
			}

			
			window.clear();
			draw_map(map, window);
			pacman.update(map);
			pacman.draw(window);
			pinky.draw(window);
			blinky.draw(window);
			clyde.draw(window);
			inky.draw(window);
			window.display();
			
		
	}

			

			







    return 0;
}

