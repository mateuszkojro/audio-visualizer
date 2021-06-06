//
// Created by studio25 on 06.06.2021.
//


#include "Button.h"

Button::Button(size_t px, size_t py, size_t w, size_t h) : px(px), py(py), w(w), h(h), image(h,w) {

}

void Button::setFunction(void *function) {
    Button::function = function;
}

void Button::setImage(const Canvas &image) {
    Button::image = image;
}

size_t Button::getPx() const {
    return px;
}

size_t Button::getPy() const {
    return py;
}

size_t Button::getW() const {
    return w;
}

size_t Button::getH() const {
    return h;
}

RGBColor &Button::get_pixel(Coord position) {
    return image.get_pixel(position);
}

  const Canvas &Button::getImage() const {
    return image;
}

