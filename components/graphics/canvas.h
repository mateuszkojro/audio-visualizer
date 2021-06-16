//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_CANVAS_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_CANVAS_H_

#include "rgb_color.h"
#include <string>

#include "coord.h"

/// canvas is a simple to use low level tool to safely and Quickly generate
/// video frames it's made in a way that can be quickly understood by SDL
/// texture

class Canvas {
public:
  /// Canvas always has to have size
  Canvas() = delete;

  /// basic copy constructor
  Canvas(const Canvas &other);

  Canvas(std::string path, size_t width, size_t height);

  /// proper canvas declaration
  /// canvas will be created with default color a.k.a. black
  Canvas(size_t width, size_t height);

  /// proper canvas declaration
  /// canvas will be created with chosen color a.k.a.  fill_color
  Canvas(size_t width, size_t height, RgbColor fill_color);

  /// \brief
  /// changes all of the pixels to chosen color
  /// \param fill_color whole canvas will be overwritten with this color
  void Fill(RgbColor fill_color);

  /// overrides the pixels with primary_color_
  void Clear();

  /// \brief safe access to a chosen pixel  <br>
  /// if the position is outside of canvas SetPixel will be ignored
  /// \param position 2d Coord
  /// \param color witch pixel at chosen location will be overwritten with
  void SetPixel(Coord position, RgbColor color);

  /// \brief dangerous way to access a pixel in canvas
  /// \param position 2d Coord
  /// \return the reference to chosen pixel
  RgbColor &GetPixel(Coord position);

  const RgbColor GetPixelCopy(Coord position) const;

  /// \brief dangerous way to access a pixel in canvas <br>
  /// direct access to data in memory
  /// \param position 1d position in pixel array
  /// \return the reference to chosen pixel
  RgbColor &operator[](size_t position);

  /// \brief sets default drawing color
  /// \param color new primary color
  void SetPrimaryColor(RgbColor color);

  /// \return pointer to underlying memory of a canvas
  RgbColor *GetPixelPtr();

  /// \brief draws point of given color inside the canvas
  /// \param center the position
  /// \param radius the size of a point
  /// \param point_color the color of point
  void DrawPoint(Coord center, unsigned int radius, RgbColor point_color);

  /// \brief draws point of given color inside the canvas  <br>
  /// but uses the default color of a canvas a.k.a. primary color
  /// \param center the wd coordinates
  /// \param radius the size of a point
  void DrawPoint(Coord center, unsigned int radius);

  /// \brief draws circle around the given point
  /// \param center of the circle
  /// \param radius the size
  /// \param circle_color the color of the circle
  void DrawCircle(Coord center, unsigned radius, RgbColor circle_color);

  /// \brief draws circle around the given point<br>
  /// but uses the default color of a canvas a.k.a. primary color
  /// \param center of the circle
  /// \param radius the size
  void DrawCircle(Coord center, unsigned radius);

  /// for SDL purposes
  /// return the size_of one pixel
  int Pitch() const;

  void DrawButton(const Canvas &butt, Coord left_top_corner);

  void LoadFromPpm(std::string path);

  size_t GetW() const;

  size_t GetH() const;

protected:
  /// actual pixel array
  RgbColor *pixels_;
  /// width of a Canvas a.k.a. x axis
  size_t w_;
  /// height of a Canvas a.k.a. y_ axis
  size_t h_;

  RgbColor primary_color_;
};

#endif // EQUALIZER_COMPONENTS_GRAPHICS_CANVAS_H_
