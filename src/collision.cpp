#include "collision.h"
#include "constants.h"
#include <array>
#include <cmath>


//This function checks if PacMan is colliding with any map object
bool collides(int cellType, short myX, short myY, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, bool gateOpen) {
	bool output = false;
	float cellX = static_cast<float>(myX) / CELL_SIZE; //need to cast as float or you'll get truncation issues
	float cellY = static_cast<float>(myY) / CELL_SIZE;
	int x, y; //int b/c ceil/floor return an int
	for (int i = 0; i < 4; i++) { //Pacman is on a grid in the middle of 4 cells, he can collide with any corner
		if (i == 0) {
			x = floor(cellX); //upper left corner
			y = floor(cellY);
		}
		if (i == 1) {
			x = ceil(cellX); //upper right corner
			y = floor(cellY);
		}
		if (i == 2) {
			x = floor(cellX); //bottom left corner
			y = ceil(cellY);
		}
		if (i == 3) {
			x = ceil(cellX); //bottom right corner
			y = ceil(cellY);
		}
		if (!((cellX <= 0 || cellY <= 0) || (cellX >= MAP_WIDTH || cellY >= MAP_HEIGHT))) { //checks if inside map
			if (gateOpen == false) {
				if (Wall == cellType) {
					if ((i_map[x][y] == cellType) || (i_map[x][y] == Opening)) {
						output = true;
					}
				}
				else if (Pellets == cellType) {
					if (i_map[x][y] == cellType) {
						output = true;
							i_map[x][y] = Empty; //removes pellet
					}
				}
			}
			else {
				if (Wall == cellType) {
					if (i_map[x][y] == cellType) {//Checks for whatever cell type: its an enumeration so it resolves to an int
						output = true;
					}
				}

			}
		}
		
	}

	return output;
};