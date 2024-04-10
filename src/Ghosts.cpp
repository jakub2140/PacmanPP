#include "Ghosts.h"
#include "constants.h"
#include <SFML/Graphics.hpp>


void Ghosts::draw(sf::RenderWindow& window)
{

	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(255, 255, 255));
	circle.setPosition(Gposition.x, Gposition.y);


	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setFillColor(sf::Color(255, 0, 199));
	rectangle.setPosition(Gposition.x, Gposition.y + CELL_SIZE / 2);





	window.draw(circle);
	window.draw(rectangle);
}

void Ghosts::setPosition(unsigned short int x, unsigned short int y)
{
	Gposition = { x,y };
}

void Pinky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(255, 0, 199));
	circle.setPosition(Pinky_position.x, Pinky_position.y);


	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setFillColor(sf::Color(255, 0, 199));
	rectangle.setPosition(Pinky_position.x, Pinky_position.y + CELL_SIZE / 2);





	window.draw(circle);
	window.draw(rectangle);
}

void Pinky::setPosition(unsigned short int x, unsigned short int y)
{
	Pinky_position = { x,y };
}



void Blinky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setPosition(Blinky_position.x, Blinky_position.y);


	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setFillColor(sf::Color(255, 0, 0));
	rectangle.setPosition(Blinky_position.x, Blinky_position.y + CELL_SIZE / 2);





	window.draw(circle);
	window.draw(rectangle);
}

void Blinky::setPosition(unsigned short int x, unsigned short int y)
{
	Blinky_position = { x,y };
}

void Clyde::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(255, 131, 0));
	circle.setPosition(Clyde_position.x, Clyde_position.y);


	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setFillColor(sf::Color(255, 131, 0));
	rectangle.setPosition(Clyde_position.x, Clyde_position.y + CELL_SIZE / 2);





	window.draw(circle);
	window.draw(rectangle);
}

void Clyde::setPosition(unsigned short int x, unsigned short int y)
{
	Clyde_position = { x,y };
}

void Inky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(0, 255, 255));
	circle.setPosition(Inky_position.x, Inky_position.y);


	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setFillColor(sf::Color(0, 255, 255));
	rectangle.setPosition(Inky_position.x, Inky_position.y + CELL_SIZE / 2);





	window.draw(circle);
	window.draw(rectangle);
}

void Inky::setPosition(unsigned short int x, unsigned short int y)
{
	Inky_position = { x,y };
}

