//Andrew Simon, Jacob Cortez

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <array>
#include <chrono>
#include <string>
#include "map_creator.h"
#include "Pacman.h"
#include "Manager.h"
#include <thread>



int main()
{
    unsigned int lag = 0;
    sf::Clock clock;

    std::chrono::time_point<std::chrono::steady_clock> Prev_time;
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
    std::shared_ptr<Pacman> pacman = nullptr;
    pacman = std::make_shared<Pacman>();

    Pinky pinky(pacman, Chase, 0);//pink
    Blinky blinky(pacman, Chase, 0);//red
    Clyde clyde(pacman, Chase, 2);//orange
    Inky inky(pacman, Chase, 0, &blinky);//blue

    std::jthread t1(Manager::aiSwitch, &pinky, &clyde, &inky, &blinky, pacman);
    t1.detach();

    map = convert_sketch(sketch, (*pacman), pinky, blinky, clyde, inky);


    Prev_time = std::chrono::steady_clock::now();

    while (1 == window.isOpen())
    {
        unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - Prev_time).count();
        lag += delta_time;
        Prev_time += std::chrono::microseconds(delta_time);

        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

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

            if (FRAME_DURATION > lag)
            {
                if((*pacman).getAlive()) {
                    window.clear();
                    draw_map(map, window);
                    Manager::ghostRelease(&pinky, &clyde, &inky, pacman, &clock);
                    (*pacman).update(map);
                    pinky.update(map);
                    blinky.update(map);
                    inky.update(map);
                    clyde.update(map);
                    (*pacman).draw(window);
                    pinky.draw(window);
                    blinky.draw(window);
                    clyde.draw(window);
                    inky.draw(window);
                    window.display();
                }
                else
                {
                    window.clear();
                    (*pacman).draw(window);
                    window.display();
                }
            }
        }
    }
    return 0;
}

