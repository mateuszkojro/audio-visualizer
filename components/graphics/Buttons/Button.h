//
// Created by studio25 on 06.06.2021.
//

#ifndef EQUALIZER_BUTTON_H
#define EQUALIZER_BUTTON_H


#include "../Canvas.h"
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

    Button(size_t px, size_t py, Canvas &image);

    void setFunction(void *function);

    void setImage(const Canvas &image);

    void setDisabledImage(const Canvas &image);

    size_t getPx() const;

    size_t getPy() const;

    size_t getW() const;

    size_t getH() const;

    virtual void press(){};
    /// \brief dangerous way to access a pixel in canvas
    /// \param position 2d Coord
    /// \return the reference to chosen pixel
    RGBColor &get_pixel(Coord position);

    virtual const Canvas &getImage() const;

    bool detect_press(Coord cursor_position);

    void set_debug_color(RGBColor image_color){
        image.set_primary_color(image_color);
        image.fill(image_color);
    }

protected:
    size_t px;
    size_t py;
    size_t w;
    size_t h;

    void* function;
private:
    Canvas image;
  //  Canvas disabled_image;

};


#endif //EQUALIZER_BUTTON_H
