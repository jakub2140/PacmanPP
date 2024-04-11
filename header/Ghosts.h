#pragma once
#include "constants.h"
#include "Pacman.h"
#include <memory>
#include <SFML/Graphics.hpp>




class Ghosts
{

private:
	Position Gposition, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	int aiType;
public:

	virtual	void draw(sf::RenderWindow& window);
	virtual void setPosition(unsigned short int x, unsigned short int y);
	virtual void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

};


class Pinky:public Ghosts
{
private:
	Position Pinky_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
	Pinky(std::shared_ptr<Pacman> pacman) {
		pacPointer = pacman;
	}
	//void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	//void pinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
};

class Blinky :public Ghosts
{
private:
	Position Blinky_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	int aiType;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
	Blinky(std::shared_ptr<Pacman> pacman, int ai, unsigned short startDir) {
		pacPointer = pacman;
		aiType = ai;
		direction = startDir;
	}
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void blinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
};

class Clyde :public Ghosts
{
private:
	Position Clyde_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
	Clyde(std::shared_ptr<Pacman> pacman) {
		pacPointer = pacman;
	}
	//void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	//void clydeAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
};


class Inky :public Ghosts
{
private:
	Position Inky_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(unsigned short int x, unsigned short int y);
	Inky(std::shared_ptr<Pacman> pacman) {
		pacPointer = pacman;
	}
	//void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	//void inkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
};