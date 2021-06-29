//
// Created by pc on 30.04.2021.
//

#include "rgb_color.h"

RgbColor::RgbColor() : r_(0), g_(0), b_(0), a_(255) {}

RgbColor::RgbColor(int r, int g, int b, int a) : r_(r), g_(g), b_(b), a_(a) {}

RgbColor::RgbColor(int r, int g, int b) : r_(r), g_(g), b_(b), a_(255) {}

RgbColor::operator int() const {
  return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_);
}

// RgbColor::RgbColor() : color_(0) {}
//
// RgbColor::RgbColor(int r, int g, int b, int a) {
//     color_ = a;
//     color_ += b << 8;
//     color_ += g << 16;
//     color_ += r << 24;
// }
//
// RgbColor::RgbColor(int r, int g, int b) {
//     color_ = b << 8;
//     color_ += g << 16;
//     color_ += r << 24;
// }
//
// RgbColor::operator int() const {
//     return color_;
// }
//
// RgbColor::operator size_t() const {
//     return color_;
// }
