//
// Created by studio25 on 06.06.2021.
//

#ifndef EQUALIZER_BUTTON_H
#define EQUALIZER_BUTTON_H


#include "../Canvas.h"
#include <map>

/// class button describes rectangular shape that is aware of user input
/// thru this class Sdl window is able to understand and decode user input
class Button {

public:

    Button();

    /// the image attached to a button will be the same size as the button itself
    /// \param px desired position of left top corner of button in x-axis
    /// \param py desired position of left top corner of button in y-axis
    /// \param w width of the button
    /// \param h height of the button
    Button(size_t px, size_t py, size_t w, size_t h);

    Button(size_t px, size_t py, Canvas &image);

    void setImage(int state, const Canvas &image);


    size_t getPx() const;

    size_t getPy() const;

    size_t getW() const;

    size_t getH() const;

    virtual void press() {
        current_state++;
        current_state = current_state == image.size() ? 0 : current_state;
    };


    /// \brief dangerous way to access a pixel in canvas
    /// \param position 2d Coord
    /// \return the reference to chosen pixel
    RGBColor &get_pixel(Coord position);

    virtual const Canvas &getImage() const;

    bool detect_press(Coord cursor_position);


protected:
    size_t px;
    size_t py;
    size_t w;
    size_t h;

private:
    int current_state = 0;
    std::map<int, Canvas> image;


};


#endif //EQUALIZER_BUTTON_H
