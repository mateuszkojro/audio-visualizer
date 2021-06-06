//
// Created by pc on 30.04.2021.
//

#include "Canvas.h"

Canvas::Canvas(size_t width, size_t height) {
    w_ = width;
    h_ = height;
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = RGBColor(255, 0, 0);
}

Canvas::Canvas(const Canvas &other) {
    pixels_ = new RGBColor[other.w_ * other.h_];
    w_ = other.w_;
    h_ = other.h_;
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = other.pixels_[i];

}

Canvas::Canvas(size_t width, size_t height, RGBColor fill_color) : w_(width), h_(height), primary_color(fill_color) {
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}
// fixme somewhere x and y are mixed up

void Canvas::fill(RGBColor fill_color) {
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}

void Canvas::clear() {
    for (int i = 0; i < w_ * h_; ++i) pixels_[i] = RGBColor();

}

void Canvas::set_pixel(Coord position, RGBColor color) {
    if (position.y >= h_ || position.y < 0 || position.x >= w_ || position.x < 0)
        return;
    pixels_[position.toUint(w_)] = color;
}


RGBColor &Canvas::operator[](size_t position) {
    return pixels_[position];
}

RGBColor *Canvas::get_pixel_ptr() { return pixels_; }

int Canvas::pitch() const { return (int) w_ * 4; }

void Canvas::set_primary_color(RGBColor color) {
    primary_color = color;
}

RGBColor &Canvas::get_pixel(Coord position) {

    return pixels_[position.toUint(w_)];
}

void Canvas::draw_circle(Coord center, unsigned int radius, RGBColor circle_color) {
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

void Canvas::draw_point(Coord center, unsigned int radius, RGBColor point_color) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, point_color);
}

void Canvas::draw_point(Coord center, unsigned int radius) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, primary_color);
}

void Canvas::draw_circle(Coord center, unsigned int radius) {
    draw_circle(center, radius, primary_color);
}

const RGBColor Canvas::get_pixel_copy(Coord position) const{
    return pixels_[position.toUint(w_)];
}

void Canvas::draw_button(const Canvas &butt, Coord left_top_corner) {
    for (int y = 0; y < butt.w_; y++) {
        for (int x = 0; x < butt.h_; x++) {


            set_pixel( {left_top_corner.y + y, left_top_corner.x + x}, butt.get_pixel_copy({y,x}));

        }
    }


}

