#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Pacman.h"
#include "collision.h"
#include <iostream>
#include <fstream>
#include "Manager.h"
#include <thread>


void Pacman::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color(250, 250, 0));
	circle.setPosition(Pposition.x, Pposition.y);

	if (alive == false)
	{

		
		circle.setFillColor(sf::Color(250, 0, 0));
		circle.setPosition(Pposition.x, Pposition.y);

	}

	window.draw(circle);

}

Pacman::Pacman()
{
	powerup = false;
	alive = true;
	score = 0; //constructor resets his score to zero. C++ doesn't like that position isn't initialized but we do that before he does anything
}
void Pacman::setPosition(short int x, short int y)
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

bool Pacman::getAlive() 
{
	return alive;
}

void Pacman::setPowerup(bool TF) {
	powerup = TF;
}

void Pacman::update(std::array<std::array<Cell,MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	//Determines which direction Pacman is going based on key presses
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (!collides(Wall, Pposition.x + PACMAN_SPEED, Pposition.y, i_map, false)) {
				direction = 0;
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (!collides(Wall, Pposition.x, Pposition.y + PACMAN_SPEED, i_map, false)) {
				direction = 1;
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (!collides(Wall, Pposition.x - PACMAN_SPEED, Pposition.y, i_map, false)) {
				direction = 2;
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (!collides(Wall, Pposition.x, Pposition.y - PACMAN_SPEED, i_map, false)) {
				direction = 3;
			}
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
		system("CLS");
		std::cout << "Score is: " << score;
	}
	if (collides(BigPellets, Pposition.x, Pposition.y, i_map, false)) {
		score += 50;
		powerup = true;
		std::jthread t1(Manager::powerupTimer, this, 10);
		t1.detach();
	}
	// broken
	if (Pposition.x >= CELL_SIZE * 20)
	{
		Pposition.x = 6;
	}
	else if (Pposition.x < 5)
	{
		Pposition.x = 319;
	}

}

void Pacman::die() {
	alive = false;
	system("CLS");
	std::cout << "Your score was " << score << std::endl;
	std::ofstream outfile("Score.txt", std::ios::app);
	outfile << "High score: " << score << std::endl;
}

void Pacman::increaseScore(int scoreInc) {
	score += scoreInc;
}

unsigned short Pacman::getDirection() {
	return direction;
}