#pragma once
#include <array>
#include"SFML/Graphics.hpp"



class Pacman
{
private:

	Position Pposition;
	unsigned int direction;
	unsigned int score;
	bool powerup;
	

public:
	void draw(sf::RenderWindow& i_window);
	void setPosition(unsigned short int i_x, unsigned short int i_y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	int getScore();
	bool getPowerup();
	Position getPosition();
	Pacman();
	
};