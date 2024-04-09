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

void Pacman::update(std::array<std::array<Cell,MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	//std::array<bool, 4> isWall{};
	//isWall[0] = map_collision(0,0, PACMAN_SPEED + Pposition.x, i_map)
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction = 1;
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction = 2;
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction = 3;
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direction = 4;
	}
	else {
		direction = 0;
	}
	if (direction == 1) {
		Pposition.x += PACMAN_SPEED;
	}
	else if (direction == 2) {
		Pposition.y += PACMAN_SPEED;
	}
	else if (direction == 3) {
		Pposition.x -= PACMAN_SPEED;
	}
	else if (direction == 4) {
		Pposition.y -= PACMAN_SPEED;
	}
}