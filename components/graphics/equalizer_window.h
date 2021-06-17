//
// Created by piotr233 on 20.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_

#include "drawing_stuff.h"
#include "handle_events.h"



// todo Fill in spaces between clocks
// todo remove window_width and height and figure something better in place

void ThEqualizerWindowFromData(AudioProgress *audio_state);

std::array<Button, BUTTONS_COUNT> LoadButtons();






#endif // EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
