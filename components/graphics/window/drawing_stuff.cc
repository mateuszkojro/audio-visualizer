//
// Created by piotr233 on 18.04.2021.
//

#include <vector>

#include "drawing_stuff.h"

RgbColor GenRainbow(unsigned height, unsigned max_height) {
  // sine wave algorithm
  // 3 parts
  // 1 :
  // r = cos(i) , g = sin(i), b =0
  // 2 :
  // r = 0 , g = cos(i), b = sin(x)
  // 3:
  // r = sin(i) , g = 0, b = cos(x)
  // every part is max_height / 3 translates into 0, PI/2

  // so for example in point 1/3 * max_height
  // r = cos(PI/2) = 0, g = sin(PI/2) = 1, b = 0

  char witch_third = height / (max_height / 3);

  double height_in_radians;
  switch (witch_third) {
  case 0:
    height_in_radians = height * M_PI / (max_height / 3) / 2;

    return RgbColor(cos(height_in_radians) * 255, sin(height_in_radians) * 255,
                    0);
  case 1:
    height -= max_height / 3;
    height_in_radians = height * M_PI / (max_height / 3) / 2;
    return RgbColor(0, cos(height_in_radians) * 255,
                    sin(height_in_radians) * 255);

  case 2:
    height -= 2 * max_height / 3;
    height_in_radians = height * M_PI / (max_height / 3) / 2;
    return RgbColor(sin(height_in_radians) * 255, 0,
                    cos(height_in_radians) * 255);
  }

  return {255, 0, 0};
}

std::vector<Coord> GenFunctionBetweenPoints(Coord begin, Coord end) {

  std::vector<Coord> generated_function;
  Coord mid_point = {(begin.y_ + end.y_) / 2, (begin.x_ + end.x_) / 2};

  /// like in polynomial function a
  double a;
  a = begin.y_ > end.y_ ? begin.y_ - end.y_ : end.y_ - begin.y_;
  a /= 2;
  int max_value /* distance between two points in x axis*/ =
      (end.x_ - begin.x_);

  if (max_value == 0) {

    return {begin};
  }

  double d = mid_point.y_;
  if (begin.y_ > end.y_) {

    a *= -1;
  }
  if ((begin.x_ / max_value) % 2 == 0) {
    a *= -1;
  }

  for (double i = begin.x_; i <= end.x_; ++i) {

    double radian = i / max_value;

    radian *= M_PI;

    generated_function.emplace_back((int)(a * cos(radian) + d), (int)i);
  }
  return generated_function;
}

std::vector<Coord> CreatePoints(int begin, int end,
                                std::vector<int> &values_to_be_drown,
                                unsigned window_width) {

  // distance between two point's in x axis
  int x_shift = window_width / (values_to_be_drown.size() + 1);

  std::vector<Coord> dot_coordinates;
  // dot_coordinates.reserve(values_to_be_drown.size() + 2);

  dot_coordinates.emplace_back(0, begin);

  for (int i = 0; i < values_to_be_drown.size(); i++)
    dot_coordinates.emplace_back(x_shift * (i + 1), values_to_be_drown[i]);

  // to make sure that the last point is pixel perfect on the edge
  dot_coordinates.emplace_back(window_width, end);

  return dot_coordinates;
}

std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown,
                                unsigned window_width) {

  // distance between two point's in x axis
  int x_shift = window_width / (values_to_be_drown.size() - 1);

  std::vector<Coord> dot_coordinates;

  for (int i = 0; i < values_to_be_drown.size(); i++)
    dot_coordinates.emplace_back(values_to_be_drown[i], x_shift * i);

  return dot_coordinates;
}
