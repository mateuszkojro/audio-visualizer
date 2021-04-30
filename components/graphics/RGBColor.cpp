//
// Created by pc on 30.04.2021.
//

#include "RGBColor.h"


RGBColor::RGBColor() : r_(0), g_(0), b_(0), a_(0) {}

RGBColor::RGBColor(int r, int g, int b, int a) :
        r_(r), g_(g), b_(b), a_(a) {}

RGBColor::RGBColor(int r, int g, int b) : r_(r), g_(g), b_(b), a_(255) {}

RGBColor::operator int() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }

RGBColor::operator size_t() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }
