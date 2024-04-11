#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Pacman.h"
#include "collision.h"


void Pacman::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(250, 250, 0));
	circle.setPosition(Pposition.x, Pposition.y);

	window.draw(circle);

}

Pacman::Pacman()
{
	powerup = false;
	score = 0; //constructor resets his score to zero. C++ doesn't like that position isn't initialized but we do that in before he does anything
}
void Pacman::setPosition(unsigned short int x, unsigned short int y)
{
	Pposition = { x,y };
}

int Pacman::getScore() 
{
	return score;
}

bool Pacman::getPowerup()
{
	return powerup;
}

Position Pacman::getPosition()
{
	return Pposition;
}

void Pacman::update(std::array<std::array<Cell,MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	//Determines which direction Pacman is going based on key presses
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			direction = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			direction = 3;
	}
	//Pac man will continue to go in the last direction pressed

	//Moves PacMan based on the current direction, but checks for collisions
	if (direction == 0) {
		if (!collides(Wall, Pposition.x + PACMAN_SPEED, Pposition.y, i_map, false)) {
			Pposition.x += PACMAN_SPEED;
		}
	}
	else if (direction == 1) {
		if (!collides(Wall, Pposition.x, Pposition.y + PACMAN_SPEED, i_map, false)) {
			Pposition.y += PACMAN_SPEED;
		}
	}
	else if (direction == 2) {
		if (!collides(Wall, Pposition.x - PACMAN_SPEED, Pposition.y, i_map, false)) {
			Pposition.x -= PACMAN_SPEED;
		}
	}
	else if (direction == 3) {
		if (!collides(Wall, Pposition.x, Pposition.y-PACMAN_SPEED, i_map, false)) {
			Pposition.y -= PACMAN_SPEED;
		}
	}

	//Checks to see if PacMan is colliding with a pellet
	if (collides(Pellets, Pposition.x, Pposition.y, i_map, false)) {
		score += 10;
	}
}