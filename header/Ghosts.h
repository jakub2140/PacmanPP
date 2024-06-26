#pragma once
#include "constants.h"
#include "Pacman.h"
#include <memory>
#include <SFML/Graphics.hpp>



//base class
class Ghosts
{

private:
	Position Gposition, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	int aiType;
public:

	virtual	void draw(sf::RenderWindow& window);
	virtual void setPosition(short int x, short int y);
	virtual void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	virtual void collidePacman();
	virtual	void setAI(int ai);
	virtual bool getActive();

};

//derived classes below
class Pinky:public Ghosts
{
private:
	Position Pinky_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	int aiType, tempAI;
	bool active, gatePass;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(short int x, short int y);
	Pinky(std::shared_ptr<Pacman> pacman, int ai, short startDir) {
		pacPointer = pacman;
		aiType = tempAI = ai;
		direction = startDir;
		active = false;
		gatePass = true;
	}
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void pinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
	void collidePacman();
	void setAI(int ai);
	void activate();
	bool getActive();
	
};

class Blinky :public Ghosts
{
private:
	Position Blinky_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	int aiType, tempAI;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(short int x, short int y);
	Blinky(std::shared_ptr<Pacman> pacman, int ai, unsigned short startDir) {
		pacPointer = pacman;
		aiType = tempAI = ai;
		direction = startDir;
	}
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void blinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
	void collidePacman();
	void setAI(int ai);
	Position getPosition();
};

class Clyde :public Ghosts
{
private:
	Position Clyde_position, Pposition;
	std::shared_ptr<Pacman> pacPointer;
	unsigned short direction;
	bool active, gatePass;
	int aiType, tempAI;
public:
	void draw(sf::RenderWindow& window);
		
	void setPosition(short int x, short int y);
	Clyde(std::shared_ptr<Pacman> pacman, int ai, unsigned short startDir) {
		pacPointer = pacman;
		direction = startDir;
		aiType = tempAI = ai;
		gatePass = true;
		active = false;
	}
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void clydeAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
	void collidePacman();
	void setAI(int ai);
	void activate();
	bool getActive();
};


class Inky :public Ghosts
{
private:
	Position Inky_position, Pposition, Bposition;
	std::shared_ptr<Pacman> pacPointer;
	Blinky* blinkyPtr;
	unsigned short direction;
	bool active, gatePass;
	int aiType, tempAI;
public:
	void draw(sf::RenderWindow& window);

	void setPosition(short int x, short int y);
	Inky(std::shared_ptr<Pacman> pacman, int ai, short startdirection, Blinky* blinky) {//inky has to be passed a pointer to blinky because of how he targets
		pacPointer = pacman;
		blinkyPtr = blinky;
		aiType = tempAI = ai;
		direction = startdirection;
		gatePass = true;
		active = false;
	}
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void inkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType);
	void collidePacman();
	void setAI(int ai);
	void activate();
	bool getActive();
};