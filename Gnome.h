#ifndef GNOME_H
#define GNOME_H

#include "Moving.h"

class Gnome : public Moving {

public:
    Gnome(const char* const*, int, int, int, int);
    void makeMove();
};

#endif
