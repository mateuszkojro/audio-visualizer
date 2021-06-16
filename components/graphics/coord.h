//
// Created by studio25 on 30.05.2021.
//

#ifndef EQUALIZER_COORD_H
#define EQUALIZER_COORD_H
#include <cassert>

class Coord {

public:
  Coord(int y, int x) : x_(x), y_(y) {}

  /// \return 1d representation of the coord
  /// \param w given width of a 2D plane
  unsigned ToUint(unsigned w) const;

  bool operator==(const Coord &rhs) const;

  bool operator!=(const Coord &rhs) const;

  int y_;
  int x_;
};

#endif // EQUALIZER_COORD_H
