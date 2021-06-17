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

void DrawAxis(Canvas *surface, bool snap) {
  /// draw both axis
  for (int i = 0; i < WINDOW_HEIGHT; i++)
    surface->DrawPoint({i, 40}, 2, {255, 255, 255});

  if (snap) {

    for (int i = 0; i < WINDOW_WIDTH; i++)
      surface->DrawPoint({(WINDOW_HEIGHT / 2), i}, 2, {255, 255, 255});

  } else
    for (int i = 0; i < WINDOW_WIDTH; i++)
      surface->DrawPoint({WINDOW_HEIGHT - 40, i}, 2, {255, 255, 255});
}

void DrawCursor(Canvas *surface, Coord mouse_position) {
  /// draw cursor
  for (int i = 0; i < WINDOW_HEIGHT; i++)
    surface->DrawPoint({i, mouse_position.x_}, 1, {255, 255, 255});

  for (int i = 0; i < WINDOW_WIDTH; i++)
    surface->DrawPoint({mouse_position.y_, i}, 1, {255, 255, 255});
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
                                std::vector<int> &values_to_be_drown) {

  // distance between two point's in x axis
  int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() + 1);

  std::vector<Coord> dot_coordinates;
  // dot_coordinates.reserve(values_to_be_drown.size() + 2);

  dot_coordinates.emplace_back(0, begin);

  for (int i = 0; i < values_to_be_drown.size(); i++)
    dot_coordinates.emplace_back(x_shift * (i + 1), values_to_be_drown[i]);

  // to make sure that the last point is pixel perfect on the edge
  dot_coordinates.emplace_back(WINDOW_WIDTH, end);

  return dot_coordinates;
}

std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown) {

  // distance between two point's in x axis
  int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() - 1);

  std::vector<Coord> dot_coordinates;

  for (int i = 0; i < values_to_be_drown.size(); i++)
    dot_coordinates.emplace_back(values_to_be_drown[i], x_shift * i);

  return dot_coordinates;
}

void DrawFunction(Canvas &surface, std::vector<int> local_values,
                  bool draw_big_points, bool static_color, bool snap_middle,
                  bool normalize) {

  std::vector<Coord> p_positions;

  if (normalize) {

    for (int &i : local_values) {
      i *= abs(i);
      i /= 200;
    }
  }

  /// flipped all values, to make them appear from the bottom of window rather
  /// than on top
  if (snap_middle) {

    for (int &i : local_values)
      i = (WINDOW_HEIGHT / 2) - i;

  } else {

    for (int &i : local_values)
      i = WINDOW_HEIGHT - 40 - i;
  }

  p_positions = CreatePoints(local_values);

  for (int i = 0; i < p_positions.size() - 1; ++i) {

    std::vector<Coord> middle_points =
        GenFunctionBetweenPoints(p_positions[i], p_positions[i + 1]);

    for (int j = 1; j < middle_points.size(); j++) {
      if (!static_color)
        surface.DrawLine(middle_points[j - 1], middle_points[j], 1,
                         GenRainbow(middle_points[j].y_, WINDOW_HEIGHT));

      else
        surface.DrawLine(middle_points[j - 1], middle_points[j], 1);
    }
  }

  if (draw_big_points)
    for (auto j : p_positions)
      surface.DrawPoint(j, 3, GenRainbow(j.y_, WINDOW_HEIGHT));
}

void DrawTextFields(SDL_Renderer *renderer, AudioProgress *progress,
                    Coord cursor_position) {

  TTF_Font *sans =
      TTF_OpenFont("C:\\Users\\studio25\\Documents\\audio_"
                   "visualizer\\components\\graphics\\assets\\Baloo.ttf",
                   16);

  int dwa = 30;
  int st = 100;

  if (!sans)
    std::cout << TTF_GetError();

  SDL_Color white = {255, 255, 255};

  std::map<std::string, SDL_Rect> labels;

  labels.insert({"number of samples", {WINDOW_WIDTH - 175, 50, 120, 40}});

  labels.insert({"scaling factor", {WINDOW_WIDTH - 158, 130, 120, 40}});

  labels.insert({"winding start", {WINDOW_WIDTH - 157, 210, 120, 40}});

  labels.insert({"winding end", {WINDOW_WIDTH - 153, 290, 120, 40}});

  labels.insert({"winding step", {WINDOW_WIDTH - 153, 370, 120, 40}});

  labels.insert({"speed!", {WINDOW_WIDTH - 130, 450, 90, 40}});

  for (auto i : labels) {
    TTF_SizeText(sans, i.first.c_str(), &i.second.w, &i.second.h);

    SDL_RenderCopy(
        renderer,
        SDL_CreateTextureFromSurface(
            renderer, TTF_RenderText_Solid(sans, i.first.c_str(), white)),
        NULL, &i.second);
  }

  std::string cursor_frequency = "123,68";

  TTF_SizeText(sans, cursor_frequency.c_str(), new int(40), new int(20));

  SDL_Rect cursor_rect;
  cursor_rect.x = cursor_position.x_;
  cursor_rect.y = cursor_position.y_ - 20;
  cursor_rect.w = 40;
  cursor_rect.h = 20;

  SDL_RenderCopy(
      renderer,
      SDL_CreateTextureFromSurface(
          renderer,
          TTF_RenderText_Solid(sans, cursor_frequency.c_str(), white)),
      NULL, &cursor_rect);

}