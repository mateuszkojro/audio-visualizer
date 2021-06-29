//
// Created by studio25 on 30.05.2021.
//

#include "coord.h"

unsigned Coord::ToUint(unsigned int width) const {
  assert(x_ < width);
  return y_ * width + x_;
}

bool Coord::operator==(const Coord &rhs) const {
  return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Coord::operator!=(const Coord &rhs) const { return !(rhs == *this); }
