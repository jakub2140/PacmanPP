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
	if (elapsed.asSeconds() > 15 && (*pinky).getActive() == false) {
		(*pinky).activate();
	}
	if ((*pinky).getActive() == true && (*pacman).getScore() > 400) {
		//activate Inky
	}
	if ((*pinky).getActive() == true && (*inky).getActive() == true && (*pacman).getScore() > 800) {
		//activate Clyde
	}
}