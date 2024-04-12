#include "Ghosts.h"
#include "Pacman.h"
#include "constants.h"
#include "Manager.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>

void Manager::powerupTimer(Pacman* pacman, int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds)); //Waits for a set amount of seconds, then turns off Pacman's powerup
	(*pacman).setPowerup(false);
}

void Manager::ghostRelease(Pinky* pinky, Clyde* clyde, Inky* inky, std::shared_ptr<Pacman> pacman, sf::Clock* clock) {
	sf::Time elapsed = (*clock).getElapsedTime(); //if elapsed time > 15s
	if (elapsed.asSeconds() > 5 && (*pinky).getActive() == false) {
		(*pinky).activate(); //Activates Pinky if he is inactive and it has been more than 5 seconds
	}
	if ((*pinky).getActive() == true && (*pacman).getScore() > 400 && (*inky).getActive() == false) {
		(*inky).activate(); //Activates inky if Pinky is active and score is >400, which roughly corresponds to 30 dots
	}
	if ((*pinky).getActive() == true && (*inky).getActive() == true && (*pacman).getScore() > 800 && (*clyde).getActive() == false) {
		(*clyde).activate(); //Activates Clyde if both other ghosts are active and more than 80 dots have been eaten
	}
}

void Manager::aiSwitch(Pinky* pinky, Clyde* clyde, Inky* inky, Blinky* blinky, std::shared_ptr<Pacman> pacman) {
	while ((*pacman).getAlive() == true) {
		std::cout << "Scatter mode" << std::endl; //Swaps between Scatter mode and Chase mode on a fixed interval
		(*pinky).setAI(Scatter);
		(*inky).setAI(Scatter);
		(*blinky).setAI(Scatter);
		(*clyde).setAI(Scatter);
		std::this_thread::sleep_for(std::chrono::seconds(7));
		std::cout << "Chase mode " << std::endl;
		(*pinky).setAI(Chase);
		(*inky).setAI(Chase);
		(*blinky).setAI(Chase);
		(*clyde).setAI(Chase);
		std::this_thread::sleep_for(std::chrono::seconds(20));
	}
}