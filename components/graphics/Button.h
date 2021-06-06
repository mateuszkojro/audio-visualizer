//
// Created by studio25 on 06.06.2021.
//

#ifndef EQUALIZER_BUTTON_H
#define EQUALIZER_BUTTON_H


#include "Canvas.h"
/// class button describes rectangular shape that is aware of user input
/// thru this class Sdl window is able to understand and decode user input
class Button {

public:
    /// the image attached to a button will be the same size as the button itself
    /// \param px desired position of left top corner of button in x-axis
    /// \param py desired position of left top corner of button in y-axis
    /// \param w width of the button
    /// \param h height of the button
    Button(size_t px, size_t py, size_t w, size_t h);

    void setFunction(void *function);
    void setImage(const Canvas &image);


protected:
    size_t px;
    size_t py;
    size_t w;
    size_t h;

    void* function;
    Canvas image;

};


#endif //EQUALIZER_BUTTON_H
