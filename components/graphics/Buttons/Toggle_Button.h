//
// Created by studio25 on 07.06.2021.
//

#ifndef EQUALIZER_TOGGLE_BUTTON_H
#define EQUALIZER_TOGGLE_BUTTON_H

#include "Button.h"

class Toggle_Button : public Button {
public:
    Toggle_Button(size_t px, size_t py, size_t w, size_t h) : Button(px, py, w, h), image(h, w), toggle_image(h, w,{0,255,0}) {pressed = true;};

    void press();


     const Canvas &getImage() const override;

    void setImage(const Canvas &image);

    void setToggledImage(const Canvas &image);

    bool State();


protected:
    bool pressed;
    Canvas image;
    Canvas toggle_image;

};


#endif //EQUALIZER_TOGGLE_BUTTON_H
