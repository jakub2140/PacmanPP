#pragma once

#include "Ghosts.h"
#include "Pacman.h"
#include "constants.h"
#include <thread>
#include <chrono>

class Manager {
public:
	static void powerupTimer(Pacman* pacman, int seconds);
	static void ghostRelease(Pinky* pinky, Clyde* clyde, Inky* inky, std::shared_ptr<Pacman> pacman, sf::Clock* clock);
};