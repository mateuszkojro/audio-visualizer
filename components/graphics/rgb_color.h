//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_RGB_COLOR_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_RGB_COLOR_H_

using U8 = unsigned char;
class RgbColor {

public:
  using U8 = unsigned char;
  U8 r_;
  U8 g_;
  U8 b_;
  U8 a_;
  // unsigned int color_;

  RgbColor();

  RgbColor(int r, int g, int b, int a);

  RgbColor(int r, int g, int b);

  RgbColor(const RgbColor &other) = default;

  RgbColor &operator=(const RgbColor &other) = default;

  explicit operator int() const;
};

#endif // EQUALIZER_COMPONENTS_GRAPHICS_RGB_COLOR_H_
