//
// Created by studio25 on 30.05.2021.
//

#include "Coord.h"

unsigned Coord::toUint(unsigned int width) const {
    assert(x < width);
    return y * width + x;
}

bool Coord::operator==(const Coord &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Coord::operator!=(const Coord &rhs) const {
    return !(rhs == *this);
}
