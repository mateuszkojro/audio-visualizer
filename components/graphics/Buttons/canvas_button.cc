//
// Created by studio25 on 06.06.2021.
//

#include "canvas_button.h"

Button::Button(int px, int py, int w, int h)
: px_(px), py_(py), w_(w), h_(h), images_{{0, {w, h}}} {}

Button::Button(size_t px, size_t py, size_t w, size_t h)
    : px_(px), py_(py), w_(w), h_(h), images_{{0, {w, h}}} {}

Button::Button(size_t px, size_t py, Canvas &image)
    : px_(px), py_(py), images_{{0, image}}, w_(image.GetW()), h_(image.GetH()) {
}
Button::Button() : px_(0), py_(0), w_(10), h_(10), images_{{0, {w_, h_}}} {}

Button::Button(int px, int py, Canvas &image) : px_(px), py_(py), images_{{0, image}}, w_(image.GetW()), h_(image.GetH()) {}


void Button::SetImage(int state, const Canvas &image) {

  images_.insert_or_assign(state, Canvas(image));
}

size_t Button::GetPx() const { return px_; }

size_t Button::GetPy() const { return py_; }

size_t Button::GetW() const { return w_; }

size_t Button::GetH() const { return h_; }

RgbColor &Button::GetPixel(Coord position) {

  return images_.find(current_state_)->second.GetPixel(position);
}

const Canvas &Button::GetImage() const {
  return images_.find(current_state_)->second;
}

bool Button::DetectPress(Coord cursor_position) const {
  /// this can always be ignored
  /// I mean positions on our window always are >0 sooo...
  // if (cursor_position.x < 0 || cursor_position.y_ < 0) return false;

  /// convert global cursor position to position relative to our button
  Coord relative_position = {cursor_position.x_ - (int)GetPx(),
                             cursor_position.y_ - (int)GetPy()};

  /// now if the cursor is above or to the left of button
  /// y_ or x will be < 0
  if (relative_position.x_ < 0 || relative_position.y_ < 0)
    return false;

  /// second check
  /// if the cursor is in the range of the button
  if (relative_position.x_ < GetW() && relative_position.y_ < GetH())
    return true;

  return false;
}

