//
// Created by pc on 30.04.2021.
//

#include "canvas.h"

canvas::canvas(size_t width, size_t height) {
    w_ = width;
    h_ = height;
    pixels_ = new RGBColor[w_ * h_];
    memset(pixels_, 0, w_ * h_ * sizeof(RGBColor));
}


canvas::canvas(size_t width, size_t height, RGBColor fill_color) : w_(width), h_(height) {
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;
    //memset(pixels_, (int) fill_color, w_ * h_ );

}

void canvas::fill(RGBColor fill_color) {
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;
    //memset(pixels_, (int) fill_color, w_ * h_ );
}

void canvas::clear() {
    for (int i = 0; i < w_ * h_; ++i) pixels_[i] = RGBColor();
    // memset(pixels_, 0, w_ * h_ * sizeof(RGBColor));
}

void canvas::set_pixel(size_t x, size_t y, RGBColor color) {
    pixels_[x * w_ + y] = color;
}

void canvas::set_pixel(size_t x, size_t y) {
    pixels_[x * w_ + y] = primary_color;
}


RGBColor &canvas::get_pixel(size_t x, size_t y) {
    return pixels_[x * w_ + y];
}

RGBColor &canvas::operator[](size_t position) {
    return pixels_[position];
}

RGBColor *canvas::get_pixel_ptr() { return pixels_; }

int canvas::pitch() const { return (int) w_ * 4; }

void canvas::set_primary_color(RGBColor color) {
    primary_color = color;
}