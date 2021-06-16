//
// Created by piotr233 on 18.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_

#include <SDL.h>
#include <array>
#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 800
#include <SDL.h>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "../audio/fourier_config.h"
#include "drawing_stuff.h"
#include "fps_counter.h"

#include "../audio/audio_progress.h"
#include "Buttons/canvas_button.h"
#include "canvas.h"
#include "canvas.h"
#include <cmath>

/// generates RAINBOW gradient across window
/// \return color derived from gradient at given height
/// \param height drawn pixel height \note height < max_height
/// \pram max_height height of gradient effect
RgbColor GenRainbow(unsigned height, unsigned max_height);


void DrawAxis(Canvas *surface, bool snap);

void DrawCursor(Canvas *surface, Coord mouse_position);

std::vector<Coord> GenFunctionBetweenPoints(Coord begin, Coord end);

std::vector<Coord> CreatePoints(int begin, int end,
                                std::vector<int> &values_to_be_drown);

std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown);

void DrawFunction(Canvas &surface, std::vector<int> local_values,
                  bool draw_big_points, bool static_color, bool snap_middle,
                  bool normalize);

#endif // EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_
