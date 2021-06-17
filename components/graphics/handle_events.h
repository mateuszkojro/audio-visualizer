//
// Created by studio25 on 16.06.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_HANDLE_EVENTS_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_HANDLE_EVENTS_H_

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "../audio/fourier_config.h"
#include "drawing_stuff.h"
#include "fps_counter.h"

#include "../../tiny_message.h"
#include "../audio/audio_playback.h"
#include "../audio/audio_progress.h"
#include "Buttons/canvas_button.h"
#include "canvas.h"

enum Buttons {
  NUMBER_OF_SAMPLES_UP,
  NUMBER_OF_SAMPLES_UP_DOWN,

  SCALING_FACTOR_UP,
  SCALING_FACTOR_DOWN,

  WINDING_START_UP,
  WINDING_START_DOWN,

  WINDING_END_UP,
  WINDING_END_DOWN,

  WINDING_STEP_UP,
  WINDING_STEP_DOWN,

  SPEED_UP,
  SLOW_DOWN,

  BACKWARD_10_S,
  FORWARD_10_S,
  PLAY_PAUSE,

  //  grid,
  SOURCE,
  CROSSHAIR,
  AXIS,
  SNAP_FUNCTION,
  NORMALIZE_FUNCTION,
  REFLECT_FUNCTION,
  RAINBOW,

  BUTTONS_COUNT
  // in plans:

};

void HandleMouseMovement(Coord &mouse_position, SDL_Window *window);

void HandleMousePress(std::array<Button, BUTTONS_COUNT> &butt_vec,
                      Coord &mouse_position, AudioProgress *audio_state);

void HandleMouseScrollUp(std::array<Button, BUTTONS_COUNT> &butt_vec,
                         Coord &mouse_position, AudioProgress *audio_state);

void HandleMouseScrollDown(std::array<Button, BUTTONS_COUNT> &butt_vec,
                           Coord &mouse_position, AudioProgress *audio_state);

#endif // EQUALIZER_COMPONENTS_GRAPHICS_HANDLE_EVENTS_H_
