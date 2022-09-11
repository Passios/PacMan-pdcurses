#ifndef MOVING_H
#define MOVING_H

enum MoveDirection : int {
	NONE = 0,
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};

class Moving {

protected:
	const char* const* auxMap;
	int mapSizeX, mapSizeY;
	
	int xPos, yPos;
	char appearance;

public:

	Moving(const char* const*, int, int, int, int);

	virtual void makeMove() = 0;

	int getX();

	int getY();

	char getAppearance();

};
#endif