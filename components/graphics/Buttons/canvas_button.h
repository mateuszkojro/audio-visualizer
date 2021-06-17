//
// Created by studio25 on 06.06.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_BUTTONS_CANVAS_BUTTON_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_BUTTONS_CANVAS_BUTTON_H_

#include "../canvas.h"
#include <map>

/// class button describes rectangular shape that is aware of user input
/// thru this class Sdl window is able to understand and decode user input
class Button {

public:
  Button();

  /// the image attached to a button will be the same size as the button itself
  /// \param px desired position of left top corner of button in x-axis
  /// \param py desired position of left top corner of button in y_-axis
  /// \param w width of the button
  /// \param h height of the button
  Button(size_t px, size_t py, size_t w, size_t h);

  Button(size_t px, size_t py, Canvas &image);

  void SetImage(int state, const Canvas &image);

  size_t GetPx() const;

  size_t GetPy() const;

  size_t GetW() const;

  size_t GetH() const;

  virtual void Press() {
    current_state_++;
    current_state_ = current_state_ == images_.size() ? 0 : current_state_;
  };

  bool operator ==(int state)const {
    return current_state_ == state;
  }
  int State() { return current_state_; };

  /// \brief dangerous way to access a pixel in canvas
  /// \param position 2d Coord
  /// \return the reference to chosen pixel
  RgbColor &GetPixel(Coord position);

  virtual const Canvas &GetImage() const;

  bool DetectPress(Coord cursor_position) const;

protected:
  size_t px_;
  size_t py_;
  size_t w_;
  size_t h_;

private:
  int current_state_ = 0;
  std::map<int, Canvas> images_;
};

#endif // EQUALIZER_COMPONENTS_GRAPHICS_BUTTONS_CANVAS_BUTTON_H_
