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
