//
// Created by pc on 30.04.2021.
//

#include "RGBColor.h"


RGBColor::RGBColor() : r_(0), g_(0), b_(0), a_(255) {}

RGBColor::RGBColor(int r, int g, int b, int a) :
        r_(r), g_(g), b_(b), a_(a) {}

RGBColor::RGBColor(int r, int g, int b) : r_(r), g_(g), b_(b), a_(255) {}

RGBColor::operator int() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }

RGBColor::operator size_t() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }

//RGBColor::RGBColor() : color_(0) {}
//
//RGBColor::RGBColor(int r, int g, int b, int a) {
//    color_ = a;
//    color_ += b << 8;
//    color_ += g << 16;
//    color_ += r << 24;
//}
//
//RGBColor::RGBColor(int r, int g, int b) {
//    color_ = b << 8;
//    color_ += g << 16;
//    color_ += r << 24;
//}
//
//RGBColor::operator int() const {
//    return color_;
//}
//
//RGBColor::operator size_t() const {
//    return color_;
//}
