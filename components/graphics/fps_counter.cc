//
// Created by pc on 22.04.2021.
//

#include "fps_counter.h"

FpsCounter::FpsCounter(Canvas *surface, int scale, RgbColor color,
                       Coord counter_position)
    : time_point_(std::chrono::steady_clock::now()), surface_(surface),
      scale_(scale), draw_color_(color), counter_position_(counter_position) {}

FpsCounter::FpsCounter(Canvas *surface)
    : time_point_(std::chrono::steady_clock::now()), surface_(surface),
      scale_(6), // coz it looks good
      draw_color_({255, 255, 255}), counter_position_({0, 0}) {}

FpsCounter::FpsCounter(Canvas *surface, Coord counter_position)
    : time_point_(std::chrono::steady_clock::now()), surface_(surface),
      scale_(6), // coz it looks good
      draw_color_({255, 255, 255}), counter_position_(counter_position) {}

void FpsCounter::Draw() {
  static int frames = 0;
  static int fps = 0;

  if (frames % 10 == 9) {

    auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - time_point_);

    fps = 10000 / time_dif.count();

    time_point_ = std::chrono::steady_clock::now();
  }
  DrawNumber(*surface_, (fps / 100) % 10, scale_, draw_color_,
             counter_position_);
  DrawNumber(*surface_, (fps / 10) % 10, scale_, draw_color_,
             {counter_position_.x_ + 5 * scale_, counter_position_.y_});

  DrawNumber(*surface_, fps % 10, scale_, draw_color_,
             {counter_position_.x_ + 10 * scale_, counter_position_.y_});

  ++frames;
}
