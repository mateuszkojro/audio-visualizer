//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_CANVAS_H
#define EQUALIZER_CANVAS_H

#include <cstring>
#include "RGBColor.h"

class canvas {
public:
    canvas() = delete;

    canvas(const canvas &other) = delete;

    canvas(size_t width, size_t height);

    canvas(size_t width, size_t height, RGBColor fill_color);

    void fill(RGBColor fill_color);

    void clear();

    void set_pixel(size_t x, size_t y, RGBColor color);

    void set_pixel(size_t x, size_t y);

    RGBColor &get_pixel(size_t x, size_t y);

    RGBColor &operator[](size_t position);

    void set_primary_color(RGBColor color);

    RGBColor *get_pixel_ptr();

    int pitch() const;

protected:

    /// actual pixel array
    RGBColor *pixels_;
    /// width of a canvas
    size_t w_;
    /// height of a canvas
    size_t h_;

    RGBColor primary_color;
};


#endif //EQUALIZER_CANVAS_H
