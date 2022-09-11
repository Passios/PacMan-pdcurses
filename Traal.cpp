#include "Traal.h"
Traal::Traal(const char* const* m, int width, int height, int x, int y) : Moving(m, width, height, x, y) {
	appearance = 'T';
}

void Traal::makeMove() {
	MoveDirection dir = NONE;

	if (auxMap[yPos][xPos - 1] == auxMap[yPos][xPos] - 1)
		dir = LEFT;
	if (auxMap[yPos + 1][xPos] == auxMap[yPos][xPos] - 1)
		dir = DOWN;
	if (auxMap[yPos - 1][xPos] == auxMap[yPos][xPos] - 1)
		dir = UP;
	if (auxMap[yPos][xPos + 1] == auxMap[yPos][xPos] - 1)
		dir = RIGHT;

	if (dir == UP)
		yPos--;
	else if (dir == DOWN)
		yPos++;
	else if (dir == RIGHT)
		xPos++;
	else if (dir == LEFT)
		xPos--;
}
