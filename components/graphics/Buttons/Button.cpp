//
// Created by studio25 on 06.06.2021.
//


#include "Button.h"

Button::Button(size_t px, size_t py, size_t w, size_t h) : px(px), py(py), w(w), h(h), image(h, w) {

}
Button::Button(size_t px, size_t py, Canvas& image): px(px), py(py), w(image.getW()), h(image.getH()), image(image){

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

bool Button::detect_press(Coord cursor_position) {
    /// this can always be ignored
    /// I mean positions on our window always are >0 sooo...
    // if (cursor_position.x < 0 || cursor_position.y < 0) return false;


    /// convert global cursor position to position relative to our button
    Coord relative_position = {cursor_position.x - (int) getPx(), cursor_position.y - (int) getPy()};

    /// now if the cursor is above or to the left of button
    /// y or x will be < 0
    if (relative_position.x < 0 || relative_position.y < 0) return false;

    /// second check
    /// if the cursor is in the range of the button
    if (relative_position.x < getW() && relative_position.y < getH()) return true;

    return false;
}

