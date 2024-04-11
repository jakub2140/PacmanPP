#include "Ghosts.h"
#include "constants.h"
#include "collision.h"
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include <numeric>
#include <cmath>

#include <iostream> //delete this after testing is done


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

void Ghosts::setPosition(short int x, short int y)
{
	Gposition = { x,y };
}

void Ghosts::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	Pposition = (*pacPointer).getPosition();
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

void Pinky::setPosition(short int x, short int y)
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

void Blinky::setPosition(short int x, short int y)
{
	Blinky_position = { x,y };
}

void Blinky::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	Pposition = (*pacPointer).getPosition();
	blinkyAI(i_map, aiType);
	if (direction == 0) {
		Blinky_position.x += PACMAN_SPEED;
	}
	else if (direction == 1) {
		Blinky_position.y += PACMAN_SPEED;
	}
	else if (direction == 2) {
		Blinky_position.x -= PACMAN_SPEED;
	}
	else if (direction == 3) {
		Blinky_position.y -= PACMAN_SPEED;
	}
}

void Blinky::blinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType) {
	int counter = 0; //ensures that the ghost only moves if it's at an intersection
	Position target;
	unsigned short newDirection = 4;
	bool blocked[] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			if (collides(Wall, Blinky_position.x + PACMAN_SPEED, Blinky_position.y, i_map, false)) { //ghosts move at speed of pacman
				blocked[i] = 1;
			}
		}
		else if (i == 1) {
			if (collides(Wall, Blinky_position.x, Blinky_position.y + PACMAN_SPEED, i_map, false)) {
				blocked[i] = 1;
			}
		}
		else if (i == 2) {
			if (collides(Wall, Blinky_position.x - PACMAN_SPEED, Blinky_position.y, i_map, false)) {
				blocked[i] = 1;
			}
		}
		else if (i == 3) {
			if (collides(Wall, Blinky_position.x, Blinky_position.y - PACMAN_SPEED, i_map, false)) {
				blocked[i] = 1;
			}
		}
	}
	float targetDistance;
	if (aiType == 0) {
		target.x = CELL_SIZE * MAP_WIDTH;
		target.y = CELL_SIZE * MAP_HEIGHT;
	}
	if (aiType == 1) {
		target.x = Pposition.x;
		target.y = Pposition.y;
	}
	float tempDistance = 10000; //large number so it is guaranteed to fire
	targetDistance = sqrt(pow(static_cast<float>((target.x - Blinky_position.x)),2) + pow(static_cast<float>((target.y - Blinky_position.y)), 2));
	for (int i = 0; i < 4; i++) {
		if((blocked[i] == false) && !(i == (2+direction)%4)) { // (2+direction)%4 is backwards
			if (newDirection == 4) {
				newDirection = i;
			}
			counter++;
			switch (i) {
			case 0:
				tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x + PACMAN_SPEED))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y))), 2));
				if (tempDistance < targetDistance) {
					targetDistance = tempDistance;
					newDirection = 0;
				}
				break;
			case 1:
				tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y + PACMAN_SPEED))), 2));
				if (tempDistance < targetDistance) {
					targetDistance = tempDistance;
					newDirection = 1;
				}
				break;
			case 2:
				tempDistance = sqrt(pow((static_cast<float>(target.x - (Blinky_position.x - PACMAN_SPEED))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y))), 2));
				if (tempDistance < targetDistance) {
					targetDistance = tempDistance;
					newDirection = 2;
				}
				break;
			case 3:
				tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y - PACMAN_SPEED))), 2));
				if (tempDistance < targetDistance) {
					targetDistance = tempDistance;
					newDirection = 3;
				}
				break;
			}

		}
		
	}
	if (1 < counter) {
		direction = newDirection;
	}
	else {
		if (newDirection == 4) {
			direction = (direction + 2) % 4;
		}
		else {
			direction = newDirection;
		}
	}
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

void Clyde::setPosition(short int x, short int y)
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

void Inky::setPosition(short int x, short int y)
{
	Inky_position = { x,y };
}

