#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>




class Ghosts
{

private:
	Position Gposition;

public:

	void draw(sf::RenderWindow& window);
	void setPosition(unsigned short int x, unsigned short int y);


};


