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

