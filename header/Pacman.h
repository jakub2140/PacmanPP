#pragma once




class Pacman
{
private:

	Position Pposition;
	unsigned int direction;

public:
	void draw(sf::RenderWindow& i_window);
	void setPosition(unsigned short int i_x, unsigned short int i_y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);


	
};