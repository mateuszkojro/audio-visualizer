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

/// creates even spaced (on x axis) dot's from given y_ values
/// \param values_to_be_drown vector of values tah will end up as y_ values in
/// returned coordinates
/// \param begin height on witch leftmost point will be,
/// this point is only to make function look nice
/// \param end height on witch
/// rightmost point will be, this point is only to make function look nice
/// \return vector of point's that will be represented as  "big dots"
std::vector<Coord> CreatePoints(int begin, int end,
                                std::vector<int> &values_to_be_drown);

/// generates visual effect based on values passed in local_values
/// \param renderer pointer to our renderer
/// \param local_values array representing positions of drawn points
/// the values given will be processed before placement on screen
/// \return window will be updated with new data
/// the structures already displayed will perish
void DrawFunction(Canvas &surface, std::vector<int> local_values,
                  bool draw_big_points, bool static_color, bool snap_middle,
                  bool normalize);

void DrawAxis(Canvas *surface, bool snap);

void DrawCursor(Canvas *surface, Coord mouse_position);

/// creates set of points that Fill in space between two given coordinates
/// space is filled uniformly, therefore gaps might be generated
/// function used to generate filler: cos(x)
/// \return set of points that Fill the given gap
/// \param begin first point of the output function, also left side of the gap
/// \param end last point to be drowned, also the end of the gap
std::vector<Coord> GenFunctionBetweenPoints(Coord begin, Coord end);

/// creates even spaced (on x axis) dot's from given y_ values
/// the difference is that generated function won't include static points on
/// left and right margin
///\param values_to_be_drown vector of values tah will end up as y_ values in
/// returned coordinates
/// \return vector of point's that will be represented as
///"big dots"
std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown);


void DrawHistogram(Canvas &surface, uint16_t volume) {
  // for now let's assume that  from left to right is precisely 10s
}
#endif // EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_
