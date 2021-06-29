//
// Created by piotr233 on 20.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_

#include "drawing_stuff.h"
#include "../../../tiny_message.h"
#include "../../audio/audio_playback.h"
#include <queue>

// todo remove window_width and height and figure something better in place

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
  // RAINBOW,

  BUTTONS_COUNT

};

/// handles all of the output features of a equalizer
/// both display and user interaction with the app
/// everything is happening in the constructor of a class
class EqualizerWindow {

public:
  EqualizerWindow();
  EqualizerWindow(AudioProgress *audio_state);

public:
  AudioProgress *GetAudioState() const;
  void SetAudioState(AudioProgress *audio_state);

  const int GetWidth() const;
  const int GetHeight() const;

  /// main window loop
  void ThEqualizerWindowFromData();



private:
  std::array<Button, BUTTONS_COUNT> butt_vec_;



  AudioProgress *audio_state_;
  const int width_;
  const int height_;



  void LoadButtons();

  void HandleMouseMovement(Coord &mouse_position, SDL_Window *window);

  void HandleMousePress(Coord &mouse_position, AudioProgress *audio_state);

  void HandleMouseScrollUp(Coord &mouse_position, AudioProgress *audio_state);

  void HandleMouseScrollDown(Coord &mouse_position, AudioProgress *audio_state);

/// generates visual effect based on values passed in local_values
/// \param renderer pointer to our renderer
/// \param local_values array representing positions of drawn points
/// the values given will be processed before placement on screen
/// \return window will be updated with new data
/// the structures already displayed will perish
  void DrawFunction(Canvas &surface, std::vector<int> local_values,
                    bool draw_big_points, bool static_color, bool snap_middle,
                    bool normalize);



};

#endif // EQUALIZER_COMPONENTS_GRAPHICS_EQUALIZER_WINDOW_H_
