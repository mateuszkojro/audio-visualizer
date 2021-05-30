//
// Created by pc on 30.04.2021.
//

#include "canvas.h"

canvas::canvas(size_t width, size_t height) {
    w_ = width;
    h_ = height;
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = RGBColor(255, 0, 0);
}

canvas::canvas(const canvas &other) {
    pixels_ = new RGBColor[other.w_ * other.h_];
    w_ = other.w_;
    h_ = other.h_;
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = other.pixels_[i];

}

canvas::canvas(size_t width, size_t height, RGBColor fill_color) : w_(width), h_(height), primary_color(fill_color) {
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}
// fixme somewhere x and y are mixed up

void canvas::fill(RGBColor fill_color) {
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}

void canvas::clear() {
    for (int i = 0; i < w_ * h_; ++i) pixels_[i] = RGBColor();

}

void canvas::set_pixel(Coord position, RGBColor color) {
    if (position.y >= h_ || position.y < 0 || position.x >= w_ || position.x < 0)
        return;
    pixels_[position.toUint(w_)] = color;
}

void canvas::set_pixel(Coord position) {
    if (position.y >= h_ || position.y < 0 || position.x >= w_ || position.x < 0)
        return;
    pixels_[position.toUint(w_)] = primary_color;
}


RGBColor &canvas::operator[](size_t position) {
    return pixels_[position];
}

RGBColor *canvas::get_pixel_ptr() { return pixels_; }

int canvas::pitch() const { return (int) w_ * 4; }

void canvas::set_primary_color(RGBColor color) {
    primary_color = color;
}

RGBColor &canvas::get_pixel(Coord position) {
    return pixels_[position.toUint(w_)];
}

void canvas::draw_circle(Coord center, unsigned int radius, RGBColor circle_color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        set_pixel({center.x + x, center.y + y}, circle_color);
        set_pixel({center.x + y, center.y + x}, circle_color);
        set_pixel({center.x - y, center.y + x}, circle_color);
        set_pixel({center.x - x, center.y + y}, circle_color);
        set_pixel({center.x - x, center.y - y}, circle_color);
        set_pixel({center.x - y, center.y - x}, circle_color);
        set_pixel({center.x + y, center.y - x}, circle_color);
        set_pixel({center.x + x, center.y - y}, circle_color);

        if (err <= 0) {
            ++y;
            err += 2 * y + 1;
        } else {
            --x;
            err -= 2 * x + 1;
        }

    }
}

void canvas::draw_point(Coord center, unsigned int radius, RGBColor point_color) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, point_color);
}

void canvas::draw_point(Coord center, unsigned int radius) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, primary_color);
}

void canvas::draw_circle(Coord center, unsigned int radius) {
    draw_circle(center, radius, primary_color);
}

