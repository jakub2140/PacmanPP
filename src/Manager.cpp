#include "Ghosts.h"
#include "Pacman.h"
#include "constants.h"
#include "Manager.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>

void Manager::powerupTimer(Pacman* pacman, int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	(*pacman).setPowerup(false);
}

void Manager::ghostRelease(Pinky* pinky, Clyde* clyde, Inky* inky, std::shared_ptr<Pacman> pacman, sf::Clock* clock) {
	sf::Time elapsed = (*clock).getElapsedTime(); //if elapsed time > 15s
	if (elapsed.asSeconds() > 10 && (*pinky).getActive() == false) {
		(*pinky).activate();
	}
	if ((*pinky).getActive() == true && (*pacman).getScore() > 400 && (*inky).getActive() == false) {
		(*inky).activate();
	}
	if ((*pinky).getActive() == true && (*inky).getActive() == true && (*pacman).getScore() > 800 && (*clyde).getActive() == false) {
		(*clyde).activate();
	}
}