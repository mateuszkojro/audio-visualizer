//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_CANVAS_H
#define EQUALIZER_CANVAS_H

#include <cstring>
#include "RGBColor.h"
#include "Coord.h"


class Canvas {
public:

    Canvas() = delete;

    Canvas(const Canvas &other);

    Canvas(size_t width, size_t height);

    Canvas(size_t width, size_t height, RGBColor fill_color);

    void fill(RGBColor fill_color);

    void clear();

    void set_pixel(Coord position, RGBColor color);

    void set_pixel(Coord position);

    RGBColor &get_pixel(Coord position);

    RGBColor &operator[](size_t position);

    void set_primary_color(RGBColor color);

    RGBColor *get_pixel_ptr();

    void draw_point(Coord center, unsigned int radius, RGBColor point_color);
    void draw_point(Coord center, unsigned int radius);

    void draw_circle(Coord center, unsigned radius, RGBColor circle_color);
    void draw_circle(Coord center, unsigned radius);


    int pitch() const;

protected:

    /// actual pixel array
    RGBColor *pixels_;
    /// width of a Canvas a.k.a. x axis
    size_t w_;
    /// height of a Canvas a.k.a. y axis
    size_t h_;

    RGBColor primary_color;
};


#endif //EQUALIZER_CANVAS_H
