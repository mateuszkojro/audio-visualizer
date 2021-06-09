//
// Created by studio25 on 07.06.2021.
//

#include "Toggle_Button.h"

void Toggle_Button::press() {
pressed = !pressed;
}

const Canvas &Toggle_Button::getImage() const {
    if(pressed) return toggle_image;
    else return image;
}

void Toggle_Button::setImage(const Canvas &image) {
    Button::setImage(image);
}

bool Toggle_Button::State() {
    return pressed;
}

