#include "Potter.h"
Potter::Potter(const char* const* m, int width, int height, int x, int y) : Moving(m, width, height, x, y) {
	appearance = 'M';
	MoveDirection direction;
	direction = NONE;
}

void Potter::makeMove() {
	if (direction == UP)
		yPos--;
	else if (direction == DOWN)
		yPos++;
	else if (direction == LEFT)
		xPos--;
	else if (direction == RIGHT)
		xPos++;
}

void Potter::setDirection(MoveDirection dir) {
	direction = dir;
}
