//
// Created by piotr233 on 20.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_

#include "drawing_stuff.h"
#include "handle_events.h"

// todo remove window_width and height and figure something better in place

/// handles all of the output features of a equalizer
/// both display and user interaction with the app
/// everything is happening in the constructor of a class
class EqualizerWindow{

public:
  EqualizerWindow();
  EqualizerWindow(AudioProgress *audio_state);

public:

  AudioProgress *GetAudioState() const;
  void SetAudioState(AudioProgress *audio_state);
  const int GetWidth() const;
  const int GetHeight() const;

private:

  AudioProgress *audio_state_;
  const int width_;
  const int height_;

};

void ThEqualizerWindowFromData(AudioProgress *audio_state);

std::array<Button, BUTTONS_COUNT> LoadButtons();






#endif // EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
