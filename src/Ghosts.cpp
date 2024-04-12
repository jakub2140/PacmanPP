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

void Ghosts::collidePacman() {

}
void Ghosts::setAI(int ai) {

}
bool Ghosts::getActive() {
	return 0;
}


void Pinky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	rectangle.setPosition(Pinky_position.x, Pinky_position.y + CELL_SIZE / 2);
	circle.setPosition(Pinky_position.x, Pinky_position.y);
	if ((*pacPointer).getPowerup() == true) {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(0, 0, 255));
			rectangle.setFillColor(sf::Color(0, 0, 255));
		}
	}
	else {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(255, 0, 199));
			rectangle.setFillColor(sf::Color(255, 0, 199));
		}

	}
	window.draw(circle);
	window.draw(rectangle);
}

void Pinky::setPosition(short int x, short int y)
{
	Pinky_position = { x,y };

}

bool Pinky::getActive() {
	return active;
}

void Pinky::pinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType) {
	if (active == true) {
		int counter = 0; //ensures that the ghost only moves if it's at an intersection
		Position target;
		bool blocked[] = { 0, 0, 0, 0 };
		blocked[0] = collides(Wall, Pinky_position.x + PACMAN_SPEED, Pinky_position.y, i_map, gatePass);
		blocked[1] = collides(Wall, Pinky_position.x, Pinky_position.y + PACMAN_SPEED, i_map, gatePass);
		blocked[2] = collides(Wall, Pinky_position.x - PACMAN_SPEED, Pinky_position.y, i_map, gatePass);
		blocked[3] = collides(Wall, Pinky_position.x, Pinky_position.y - PACMAN_SPEED, i_map, gatePass);
		float targetDistance;

		if (aiType == 0) {
			target.x = 0;
			target.y = 0;
		}
		if (aiType == 1) {
			switch (static_cast<unsigned short>((*pacPointer).getDirection())) {
			case 0:
				target.x = Pposition.x + 4*CELL_SIZE;
				target.y = Pposition.y;
				break;
			case 1:
				target.x = Pposition.x;
				target.y = Pposition.y + 4 * CELL_SIZE;
				break;
			case 2:
				target.x = Pposition.x - 4 * CELL_SIZE;
				target.y = Pposition.y;
				break;
			case 3:
				target.x = Pposition.x;
				target.y = Pposition.y - 4 * CELL_SIZE;
				break;
			}

		}
		if (aiType == 3) {
			target.x = 160;
			target.y = 112;
		}
		if (aiType == 3 && Pinky_position.x == 160 && Pinky_position.y == 112) {
			setAI(tempAI);
			gatePass = false;
			target.x = Pposition.x;
			target.y = Pposition.y;
		}

		if ((*pacPointer).getPowerup() == false || aiType == 3) { //Normal ai, goes to designated target
			unsigned short newDirection = 4;
			float tempDistance; //large number so it is guaranteed to fire
			targetDistance = sqrt(pow(static_cast<float>((target.x - Pinky_position.x)), 2) + pow(static_cast<float>((target.y - Pinky_position.y)), 2));
			float bestDistance = 480;
			for (int i = 0; i < 4; i++) {
				if ((blocked[i] == false) && !(i == (2 + direction) % 4)) { // (2+direction)%4 is backwards
					if (newDirection == 4) {
						newDirection = i;
					}
					counter++;
					switch (i) {
					case 0:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Pinky_position.x + 1))), 2) + pow(static_cast<float>((target.y - (Pinky_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 0;
						}
						break;
					case 1:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Pinky_position.x))), 2) + pow(static_cast<float>((target.y - (Pinky_position.y + 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 1;
						}
						break;
					case 2:
						tempDistance = sqrt(pow((static_cast<float>(target.x - (Pinky_position.x - 1))), 2) + pow(static_cast<float>((target.y - (Pinky_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 2;
						}
						break;
					case 3:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Pinky_position.x))), 2) + pow(static_cast<float>((target.y - (Pinky_position.y - 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
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


		else { //Scared ai

			unsigned short newDirection = 0;
			for (int i = 0; i < 4; i++) {
				if (blocked[i] == false && i != (direction + 2) % 4) {
					if (blocked[i] == 0) {
						counter++;
					}
				}
			}
			if (0 < counter) {
				while ((newDirection == (direction + 2) % 4) || (blocked[newDirection] == true)) {
					newDirection = rand() % 4;
				}
				direction = newDirection;
			}

		}
	}
}

void Pinky::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	if (active == true) {
		Pposition = (*pacPointer).getPosition();
		pinkyAI(i_map, aiType);
		if (direction == 0) {
			Pinky_position.x += PACMAN_SPEED;
		}
		else if (direction == 1) {
			Pinky_position.y += PACMAN_SPEED;
		}
		else if (direction == 2) {
			Pinky_position.x -= PACMAN_SPEED;
		}
		else if (direction == 3) {
			Pinky_position.y -= PACMAN_SPEED;
		}
		if (Pinky_position.x >= CELL_SIZE * 20)
		{
			Pinky_position.x = 6;
		}
		else if (Pinky_position.x < 5)
		{
			Pinky_position.x = 319;
		}
		collidePacman();
	}

}

void Pinky::collidePacman() {
	float distance = sqrt(pow(static_cast<float>(Pposition.x - Pinky_position.x), 2) + pow(static_cast<float>(Pposition.y - Pinky_position.y), 2));
	if ((*pacPointer).getPowerup() == false) {
		if (distance < 10) {
			(*pacPointer).die();
			std::cout << "Pinky killed you. Game over";
		}
	}
	else {
		if (distance < 10) {
			if (aiType != Running) {
				(*pacPointer).increaseScore(200);
			}
			aiType = 3;

		}
	}
}

void Pinky::activate() {
	active = true;
	std::cout << "Pinky activated" << std::endl;
	aiType = 3;
}

void Pinky::setAI(int ai) {
	if (aiType == Running && Pinky_position.x == 160 && Pinky_position.y == 112) {
		aiType = ai;
	}
	else if (aiType == Running) {
		tempAI = ai;
	}
	else {
		aiType = ai;
	}
}



void Blinky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	circle.setPosition(Blinky_position.x, Blinky_position.y);
	rectangle.setPosition(Blinky_position.x, Blinky_position.y + CELL_SIZE / 2);
	if ((*pacPointer).getPowerup() == true) {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(0, 0, 255));
			rectangle.setFillColor(sf::Color(0, 0, 255));
		}
		

	}
	else {
		if (aiType == 3){
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(255, 0, 0));
			rectangle.setFillColor(sf::Color(255, 0, 0));
		}

	}

	




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
	if (Blinky_position.x >= CELL_SIZE * 20)
	{
		Blinky_position.x = 6;
	}
	else if (Blinky_position.x < 5)
	{
		Blinky_position.x = 319;
	}
	collidePacman();
}

void Blinky::blinkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType) {
	int counter = 0; //ensures that the ghost only moves if it's at an intersection
	Position target;
	bool blocked[] = {0, 0, 0, 0};
	blocked[0] = collides(Wall, Blinky_position.x + PACMAN_SPEED, Blinky_position.y, i_map, false);
	blocked[1] = collides(Wall, Blinky_position.x, Blinky_position.y + PACMAN_SPEED, i_map, false);
	blocked[2] = collides(Wall, Blinky_position.x - PACMAN_SPEED, Blinky_position.y, i_map, false);
	blocked[3] = collides(Wall, Blinky_position.x, Blinky_position.y - PACMAN_SPEED, i_map, false);
	float targetDistance;

	if (aiType == 0) {
		target.x = CELL_SIZE * MAP_WIDTH;
		target.y = 0;
	}
	if (aiType == 1) {
		//Simplest AI, it targets whereever Pacman currently is.
		target.x = Pposition.x;
		target.y = Pposition.y;
	}
	if (aiType == 3) {
		target.x = 160; 
		target.y = 112;
	}
	if (aiType == 3 && Blinky_position.x == 160 && Blinky_position.y == 112) {
		setAI(tempAI);
		target.x = Pposition.x;
		target.y = Pposition.y;
	}

	if ((*pacPointer).getPowerup() == false || aiType == 3) { //Normal ai, goes to designated target
		unsigned short newDirection = 4;
		float tempDistance; //large number so it is guaranteed to fire
		targetDistance = sqrt(pow(static_cast<float>((target.x - Blinky_position.x)), 2) + pow(static_cast<float>((target.y - Blinky_position.y)), 2));
		float bestDistance = 480;
		for (int i = 0; i < 4; i++) {
			if ((blocked[i] == false) && !(i == (2 + direction) % 4)) { // (2+direction)%4 is backwards
				if (newDirection == 4) {
					newDirection = i;
				}
				counter++;
				switch (i) {
				case 0:
					tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x + 1))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y))), 2));
					if (tempDistance < bestDistance) {
						bestDistance = tempDistance;
						newDirection = 0;
					}
					break;
				case 1:
					tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y + 1))), 2));
					if (tempDistance < bestDistance) {
						bestDistance = tempDistance;
						newDirection = 1;
					}
					break;
				case 2:
					tempDistance = sqrt(pow((static_cast<float>(target.x - (Blinky_position.x - 1))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y))), 2));
					if (tempDistance < bestDistance) {
						bestDistance = tempDistance;
						newDirection = 2;
					}
					break;
				case 3:
					tempDistance = sqrt(pow(static_cast<float>((target.x - (Blinky_position.x))), 2) + pow(static_cast<float>((target.y - (Blinky_position.y - 1))), 2));
					if (tempDistance < bestDistance) {
						bestDistance = tempDistance;
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


	else { //Scared ai

		unsigned short newDirection = 0;
		for (int i = 0; i < 4; i++) {
			if (blocked[i] == false && i != (direction + 2) % 4) {
				if (blocked[i] == 0) {
					counter++;
				}
			}
		}
		if (0 < counter) {
			while ((newDirection == (direction + 2) % 4) || (blocked[newDirection] == true)) {
				newDirection = rand() % 4;
			}
			direction = newDirection;
		}

	}
}

void Blinky::collidePacman() {
	float distance = sqrt(pow(static_cast<float>(Pposition.x - Blinky_position.x), 2) + pow(static_cast<float>(Pposition.y - Blinky_position.y), 2));
	if ((*pacPointer).getPowerup() == false) {
		if (distance < 10) {
			(*pacPointer).die();
			std::cout << "Blinky killed you. Game over";
		}
	}
	else {
		if (distance < 10) {
			if (aiType != Running) {
				(*pacPointer).increaseScore(200);
			}
			aiType = 3;
			
		}
	}
}

void Blinky::setAI(int ai) {
	if (aiType == Running && Blinky_position.x == 160 && Blinky_position.y == 112) {
		aiType = ai; //edge case for swiching out of running at the right spot
	}
	else if (aiType == Running) {
		tempAI = ai;
	}
	else {
		aiType = ai;
	}
}

Position Blinky::getPosition() {
	return Blinky_position;
}

void Clyde::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	circle.setPosition(Clyde_position.x, Clyde_position.y);
	rectangle.setPosition(Clyde_position.x, Clyde_position.y + CELL_SIZE / 2);
	if ((*pacPointer).getPowerup() == true) {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(0, 0, 255));
			rectangle.setFillColor(sf::Color(0, 0, 255));
		}
	}
	else {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(255, 131, 0));
			rectangle.setFillColor(sf::Color(255, 131, 0));
		}
	}
	window.draw(circle);
	window.draw(rectangle);
}

void Clyde::setPosition(short int x, short int y)
{
	Clyde_position = { x,y };
}

void Clyde::activate() {
	active = true;
	std::cout << "Clyde has been activated" << std::endl;
	aiType = 3; //avoid weird edge cases from the manager setting wrong ai type
}

bool Clyde::getActive() {
	return active;
}

void Clyde::setAI(int ai) {
	if (aiType == Running && Clyde_position.x == 160 && Clyde_position.y == 112) {
		aiType = ai; //edge case for switching out of running mode at the correct spot
	}
	else if (aiType == Running) {
		tempAI = ai;
	}
	else {
		aiType = ai;
	}
}

void Clyde::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	if (active == true) {
		Pposition = (*pacPointer).getPosition();
		clydeAI(i_map, aiType);
		if (direction == 0) {
			Clyde_position.x += PACMAN_SPEED;
		}
		else if (direction == 1) {
			Clyde_position.y += PACMAN_SPEED;
		}
		else if (direction == 2) {
			Clyde_position.x -= PACMAN_SPEED;
		}
		else if (direction == 3) {
			Clyde_position.y -= PACMAN_SPEED;
		}
		if (Clyde_position.x >= CELL_SIZE * 20) //lets ghosts go through the warp tunnels
		{
			Clyde_position.x = 6;
		}
		else if (Clyde_position.x < 5)
		{
			Clyde_position.x = 319;
		}
		collidePacman();
	}
}

void Clyde::clydeAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType) {
	if (active == true) {
		int counter = 0; //ensures that the ghost only moves if it's at an intersection
		Position target;
		bool blocked[] = { 0, 0, 0, 0 };
		blocked[0] = collides(Wall, Clyde_position.x + PACMAN_SPEED, Clyde_position.y, i_map, gatePass);
		blocked[1] = collides(Wall, Clyde_position.x, Clyde_position.y + PACMAN_SPEED, i_map, gatePass);
		blocked[2] = collides(Wall, Clyde_position.x - PACMAN_SPEED, Clyde_position.y, i_map, gatePass);
		blocked[3] = collides(Wall, Clyde_position.x, Clyde_position.y - PACMAN_SPEED, i_map, gatePass);
		float targetDistance;
		if (aiType == 0) {
			target.x = 0;
			target.y = CELL_SIZE*MAP_HEIGHT;
		}
		if (aiType == 1) {
			//Clydes targeting mechanism: If farther than 8 tiles from pacman, go to pacman. If closer, go to his corner of the map
			if (sqrt(pow(static_cast<float>((Pposition.x - Clyde_position.x)), 2) + pow(static_cast<float>((Pposition.y - Clyde_position.y)), 2)) < 8*CELL_SIZE) {
				target.x = 0;
				target.y = CELL_SIZE * MAP_HEIGHT;
			}
			else {
				target.x = Pposition.x;
				target.y = Pposition.y;
			}
		
		}
		if (aiType == 3) {
			target.x = 160;
			target.y = 112;
		}
		if (aiType == 3 && Clyde_position.x == 160 && Clyde_position.y == 112) {
			setAI(tempAI); //need to do this to avoid overloaded definition
			gatePass = false;
			target.x = Pposition.x;
			target.y = Pposition.y;
		}
		if ((*pacPointer).getPowerup() == false || aiType == 3) { //Normal ai, goes to designated target
			unsigned short newDirection = 4;
			float tempDistance; //large number so it is guaranteed to fire
			targetDistance = sqrt(pow(static_cast<float>((target.x - Clyde_position.x)), 2) + pow(static_cast<float>((target.y - Clyde_position.y)), 2));
			float bestDistance = 480;
			for (int i = 0; i < 4; i++) {
				if ((blocked[i] == false) && !(i == (2 + direction) % 4)) { // (2+direction)%4 is backwards
					if (newDirection == 4) {
						newDirection = i;
					}
					counter++;
					switch (i) {
					case 0:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Clyde_position.x + 1))), 2) + pow(static_cast<float>((target.y - (Clyde_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 0;
						}
						break;
					case 1:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Clyde_position.x))), 2) + pow(static_cast<float>((target.y - (Clyde_position.y + 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 1;
						}
						break;
					case 2:
						tempDistance = sqrt(pow((static_cast<float>(target.x - (Clyde_position.x - 1))), 2) + pow(static_cast<float>((target.y - (Clyde_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 2;
						}
						break;
					case 3:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Clyde_position.x))), 2) + pow(static_cast<float>((target.y - (Clyde_position.y - 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
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
		else { //Scared ai

			unsigned short newDirection = 0;
			for (int i = 0; i < 4; i++) {
				if (blocked[i] == false && i != (direction + 2) % 4) {
					if (blocked[i] == 0) {
						counter++;
					}
				}
			}
			if (0 < counter) {
				while ((newDirection == (direction + 2) % 4) || (blocked[newDirection] == true)) {
					newDirection = rand() % 4;
				}
				direction = newDirection;
			}

		}
	}
}

void Clyde::collidePacman() {
	float distance = sqrt(pow(static_cast<float>(Pposition.x - Clyde_position.x), 2) + pow(static_cast<float>(Pposition.y - Clyde_position.y), 2));
	if ((*pacPointer).getPowerup() == false) {
		if (distance < 10) {
			(*pacPointer).die();
			std::cout << "Clyde killed you. Game over";
		}
	}
	else {
		if (distance < 10) {
			if (aiType != Running) {
				(*pacPointer).increaseScore(200);
			}
			aiType = 3;

		}
	}
}

void Inky::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(CELL_SIZE / 2);
	sf::RectangleShape rectangle(sf::Vector2(16.f, 7.f));
	circle.setPosition(Inky_position.x, Inky_position.y);
	rectangle.setPosition(Inky_position.x, Inky_position.y + CELL_SIZE / 2);


	if ((*pacPointer).getPowerup() == true) {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(0, 0, 255));
			rectangle.setFillColor(sf::Color(0, 0, 255));
		}


	}
	else {
		if (aiType == 3) {
			circle.setFillColor(sf::Color(255, 255, 255));
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}
		else {
			circle.setFillColor(sf::Color(0, 255, 255));
			rectangle.setFillColor(sf::Color(0, 255, 255));
		}

	}


	window.draw(circle);
	window.draw(rectangle);
}

void Inky::setPosition(short int x, short int y)
{
	Inky_position = { x,y };
}

void Inky::activate() {
	active = true;
	std::cout << "Inky active" << std::endl;
	gatePass = true;
	aiType = 3;
}

void Inky::setAI(int ai) {
	if (aiType == Running && Inky_position.x == 160 && Inky_position.y == 112) {
		aiType = ai;
	}
	else if (aiType == Running) {
		tempAI = ai;
	}
	else {
		aiType = ai;
	}
}

bool Inky::getActive() {
	return active;
}

void Inky::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
	if (active == true) {
		Pposition = (*pacPointer).getPosition();
		inkyAI(i_map, aiType);
		if (direction == 0) {
			Inky_position.x += PACMAN_SPEED;
		}
		else if (direction == 1) {
			Inky_position.y += PACMAN_SPEED;
		}
		else if (direction == 2) {
			Inky_position.x -= PACMAN_SPEED;
		}
		else if (direction == 3) {
			Inky_position.y -= PACMAN_SPEED;
		}
		if (Inky_position.x >= CELL_SIZE * 20)
		{
			Inky_position.x = 6;
		}
		else if (Inky_position.x < 5)
		{
			Inky_position.x = 319;
		}
		collidePacman();
	}
}

void Inky::inkyAI(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, int aiType) {
	if (active == true) {
		int counter = 0; //ensures that the ghost only moves if it's at an intersection
		Position target;
		bool blocked[] = { 0, 0, 0, 0 };
		blocked[0] = collides(Wall, Inky_position.x + PACMAN_SPEED, Inky_position.y, i_map, gatePass);
		blocked[1] = collides(Wall, Inky_position.x, Inky_position.y + PACMAN_SPEED, i_map, gatePass);
		blocked[2] = collides(Wall, Inky_position.x - PACMAN_SPEED, Inky_position.y, i_map, gatePass);
		blocked[3] = collides(Wall, Inky_position.x, Inky_position.y - PACMAN_SPEED, i_map, gatePass);
		float targetDistance;
		if (aiType == 0) {
			target.x = CELL_SIZE * MAP_WIDTH;
			target.y = CELL_SIZE * MAP_HEIGHT;
		}
		if (aiType == 1) {
			//This is the only difference in the Inky AI: he finds a vector pointing from Blinky to Pacman, and sets his target to twice that vector
			Bposition = (*blinkyPtr).getPosition();
			target.x = Bposition.x + 2 * (Pposition.x - Bposition.x);
			target.y = Bposition.y + 2 * (Pposition.y - Bposition.y);
		}
		if (aiType == 3) {
			target.x = 160;
			target.y = 112;
		}
		if (aiType == 3 && Inky_position.x == 160 && Inky_position.y == 112) {
			setAI(tempAI); //need to do this to avoid overloaded definition
			target.x = Pposition.x;
			target.y = Pposition.y;
		}
		if ((*pacPointer).getPowerup() == false || aiType == 3) { //Normal ai, goes to designated target
			unsigned short newDirection = 4;
			float tempDistance; //large number so it is guaranteed to fire
			targetDistance = sqrt(pow(static_cast<float>((target.x - Inky_position.x)), 2) + pow(static_cast<float>((target.y - Inky_position.y)), 2));
			float bestDistance = 480;
			for (int i = 0; i < 4; i++) {
				if ((blocked[i] == false) && !(i == (2 + direction) % 4)) { // (2+direction)%4 is backwards
					if (newDirection == 4) {
						newDirection = i;
					}
					counter++;
					switch (i) {
					case 0:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Inky_position.x + 1))), 2) + pow(static_cast<float>((target.y - (Inky_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 0;
						}
						break;
					case 1:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Inky_position.x))), 2) + pow(static_cast<float>((target.y - (Inky_position.y + 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 1;
						}
						break;
					case 2:
						tempDistance = sqrt(pow((static_cast<float>(target.x - (Inky_position.x - 1))), 2) + pow(static_cast<float>((target.y - (Inky_position.y))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
							newDirection = 2;
						}
						break;
					case 3:
						tempDistance = sqrt(pow(static_cast<float>((target.x - (Inky_position.x))), 2) + pow(static_cast<float>((target.y - (Inky_position.y - 1))), 2));
						if (tempDistance < bestDistance) {
							bestDistance = tempDistance;
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
		else { //Scared ai

			unsigned short newDirection = 0;
			for (int i = 0; i < 4; i++) {
				if (blocked[i] == false && i != (direction + 2) % 4) {
					if (blocked[i] == 0) {
						counter++;
					}
				}
			}
			if (0 < counter) {
				while ((newDirection == (direction + 2) % 4) || (blocked[newDirection] == true)) {
					newDirection = rand() % 4;
				}
				direction = newDirection;
			}

		}
	}
}

void Inky::collidePacman() {
	float distance = sqrt(pow(static_cast<float>(Pposition.x - Inky_position.x), 2) + pow(static_cast<float>(Pposition.y - Inky_position.y), 2));
	if ((*pacPointer).getPowerup() == false) {
		if (distance < 10) {
			(*pacPointer).die();
			std::cout << "Inky killed you. Game over";
		}
	}
	else {
		if (distance < 10) {
			if (aiType != Running) {
				(*pacPointer).increaseScore(200);
			}
			aiType = 3;

		}
	}
}