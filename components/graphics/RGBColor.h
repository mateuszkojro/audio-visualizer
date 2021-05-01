//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_RGBCOLOR_H
#define EQUALIZER_RGBCOLOR_H

using u8 = unsigned char;

class RGBColor {


public:
    using u8 = unsigned char;
    u8 r_;
    u8 g_;
    u8 b_;
    u8 a_;
    //unsigned int color_;


    RGBColor();

    RGBColor(int r, int g, int b, int a);

    RGBColor(int r, int g, int b);

    RGBColor(const RGBColor &other) = default;

    RGBColor &operator=(const RGBColor &other) = default;

    explicit operator int() const;

    explicit operator size_t() const;


};


#endif //EQUALIZER_RGBCOLOR_H
