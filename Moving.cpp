#include "Moving.h"

Moving::Moving(const char* const* m, int width, int height, int x, int y) {
    auxMap = m;
    mapSizeX = width;
    mapSizeY = height;
    xPos = x;
    yPos = y;
}

int Moving::getX() {
    return xPos;
}

int Moving::getY() {
    return yPos;
}

char Moving::getAppearance() {
    return appearance;
}
