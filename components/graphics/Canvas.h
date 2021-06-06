//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_CANVAS_H
#define EQUALIZER_CANVAS_H

#include <cstring>
#include "RGBColor.h"

#include "Coord.h"


/// canvas is a simple to use low level tool to safely and Quickly generate video frames
/// it's made in a way that can be quickly understood by SDL texture

class Canvas {
public:
    /// Canvas always has to have size
    Canvas() = delete;

    /// basic copy constructor
    Canvas(const Canvas &other);

    /// proper canvas declaration
    /// canvas will be created with default color a.k.a. black
    Canvas(size_t width, size_t height);

    /// proper canvas declaration
    /// canvas will be created with chosen color a.k.a.  fill_color
    Canvas(size_t width, size_t height, RGBColor fill_color);

    /// \brief
    /// changes all of the pixels to chosen color
    /// \param fill_color whole canvas will be overwritten with this color
    void fill(RGBColor fill_color);

    /// overrides the pixels with primary_color
    void clear();

    /// \brief safe access to a chosen pixel  <br>
    /// if the position is outside of canvas set_pixel will be ignored
    /// \param position 2d Coord
    /// \param color witch pixel at chosen location will be overwritten with
    void set_pixel(Coord position, RGBColor color);

    /// \brief dangerous way to access a pixel in canvas
    /// \param position 2d Coord
    /// \return the reference to chosen pixel
    RGBColor &get_pixel(Coord position);

    /// \brief dangerous way to access a pixel in canvas <br>
    /// direct access to data in memory
    /// \param position 1d position in pixel array
    /// \return the reference to chosen pixel
    RGBColor &operator[](size_t position);

    /// \brief sets default drawing color
    /// \param color new primary color
    void set_primary_color(RGBColor color);


    /// \return pointer to underlying memory of a canvas
    RGBColor *get_pixel_ptr();

    /// \brief draws point of given color inside the canvas
    /// \param center the position
    /// \param radius the size of a point
    /// \param point_color the color of point
    void draw_point(Coord center, unsigned int radius, RGBColor point_color);

    /// \brief draws point of given color inside the canvas  <br>
    /// but uses the default color of a canvas a.k.a. primary color
    /// \param center the wd coordinates
    /// \param radius the size of a point
    void draw_point(Coord center, unsigned int radius);

    /// \brief draws circle around the given point
    /// \param center of the circle
    /// \param radius the size
    /// \param circle_color the color of the circle
    void draw_circle(Coord center, unsigned radius, RGBColor circle_color);

    /// \brief draws circle around the given point<br>
    /// but uses the default color of a canvas a.k.a. primary color
    /// \param center of the circle
    /// \param radius the size
    void draw_circle(Coord center, unsigned radius);

    /// for SDL purposes
    /// return the size_of on epixel
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
