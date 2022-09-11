#ifndef POTTER_H
#define POTTER_H

#include <iostream>
#include "Moving.h"

class Potter : public Moving {

private:
    MoveDirection direction;

public:
    Potter(const char* const*, int, int, int, int);
    void makeMove();

    void setDirection(MoveDirection);
};
#endif