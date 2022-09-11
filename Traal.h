#ifndef TRAAL_H
#define TRAAL_H

#include "Moving.h"

class Traal : public Moving {

public:
    Traal(const char* const*, int, int, int, int);
    void makeMove();

};

#endif
