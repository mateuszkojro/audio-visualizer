//
// Created by piotr233 on 20.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "../audio/fourier_config.h"
#include "drawing_stuff.h"
#include "fps_counter.h"

#include "../../audio_progress.h"
#include "Buttons/canvas_button.h"
#include "canvas.h"

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 800

// todo Fill in spaces between clocks
// todo remove window_width and height and figure something better in place

/// \param values_to_be_drown vector containing y_ values of the point's tah
/// will be drawn on the screen,
/// \important thing all values must be in range
/// <0;WINDOW_HEIGHT) also vector will be deleted after read
/// \param renderer the
/// renderer what will be used to update window
void EqualizerWindow(Canvas *surface, std::mutex &surface_guard,
                     std::vector<Button> &button_vector);

void ThEqualizerWindowFromData(AudioProgress *audio_state);

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

void DrawLevels(Canvas &surface, std::vector<int> local_values,
                bool draw_big_points, bool static_color);

/// creates even spaced (on x axis) dot's from given y_ values
/// the difference is that generated function won't include static points on
/// left and right margin
///\param values_to_be_drown vector of values tah will end up as y_ values in
/// returned coordinates
/// \return vector of point's that will be represented as
///"big dots"
std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown);

/// creates set of points that Fill in space between two given coordinates
/// space is filled uniformly, therefore gaps might be generated
/// function used to generate filler: cos(x)
/// \return set of points that Fill the given gap
/// \param begin first point of the output function, also left side of the gap
/// \param end last point to be drowned, also the end of the gap
std::vector<Coord> GenFunctionBetweenPoints(Coord begin, Coord end);

#endif // EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
