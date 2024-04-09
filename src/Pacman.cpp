#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Pacman.h"


void Pacman::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(250, 250, 0));
	circle.setPosition(Pposition.x, Pposition.y);

	window.draw(circle);

}

void Pacman::setPosition(unsigned short int x, unsigned short int y)
{
	Pposition = { x,y };
}
