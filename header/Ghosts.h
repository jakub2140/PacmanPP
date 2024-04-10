#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>




class Ghosts
{

private:
	Position Gposition;

public:

	virtual	void draw(sf::RenderWindow& window);
	virtual void setPosition(unsigned short int x, unsigned short int y);


};


class Pinky:public Ghosts
{
private:
	Position Pinky_position;

public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
};

class Blinky :public Ghosts
{
private:
	Position Blinky_position;

public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
};

class Clyde :public Ghosts
{
private:
	Position Clyde_position;

public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
};


class Inky :public Ghosts
{
private:
	Position Inky_position;

public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
};