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

#include "../audio/audio_progress.h"
#include "Buttons/canvas_button.h"
#include "canvas.h"

#include "../audio/audio_playback.h"
#include "handle_events.h"

std::string assets = R"(..\components\graphics\assets)";

// todo Fill in spaces between clocks
// todo remove window_width and height and figure something better in place

void ThEqualizerWindowFromData(AudioProgress *audio_state);

std::array<Button, BUTTONS_COUNT> LoadButtons();

void DrawHistogram(Canvas &surface, uint16_t volume);




#endif // EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
