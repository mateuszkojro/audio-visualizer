//
// Created by studio25 on 16.06.2021.
//

#include "handle_events.h"
void HandleMouseMovement(Coord &mouse_position, SDL_Window *window) {

  SDL_GetMouseState(&mouse_position.x_, &mouse_position.y_);

  std::string title = std::to_string(mouse_position.x_) + " x ";
  title += std::to_string(mouse_position.y_) + " y ";
  SDL_SetWindowTitle(window, title.c_str());
}



void HandleMousePress(std::array<Button, BUTTONS_COUNT> &butt_vec,
                      Coord &mouse_position, AudioProgress *audio_state) {

  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec.size(); i++) {
    if (butt_vec[i].DetectPress(mouse_position))
      break;
  }

  switch (i) {
  case NUMBER_OF_SAMPLES_UP:
    fourier_data->number_of_samples += 1;

    break;
  case NUMBER_OF_SAMPLES_UP_DOWN:
    if (fourier_data->number_of_samples > 1)
      fourier_data->number_of_samples -= 1;

    break;
  case SCALING_FACTOR_UP:
    fourier_data->scaling_factor *= 0.99;

    break;
  case SCALING_FACTOR_DOWN:
    fourier_data->scaling_factor *= 1.01;

    break;
  case WINDING_START_UP:
    /// same as left arrow
    fourier_data->winding_start += 1;

    break;
  case WINDING_START_DOWN:
    fourier_data->winding_start -= 1;

    break;
  case WINDING_END_UP:
    fourier_data->winding_end += 1;

    break;
  case WINDING_END_DOWN:
    fourier_data->winding_end -= 1;

    break;
  case WINDING_STEP_UP:
    fourier_data->winding_step += 1;

    break;
  case WINDING_STEP_DOWN:
    if (fourier_data->winding_step > 1)
      fourier_data->winding_step -= 1;

    break;
  case SPEED_UP:
    if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
      fourier_data->sleep_for -= std::chrono::milliseconds(10);

    break;
  case SLOW_DOWN:
    fourier_data->sleep_for += std::chrono::milliseconds(10);
    break;

  case SOURCE:
    if (butt_vec[SOURCE].State() == 0) {

      std::string path = Tiny::OpenFileDialog();
      if (!path.empty()) {
        AudioPlayback::UseSource(path, audio_state);
      }

    } else {
      AudioPlayback::UseMicrophone(audio_state);
    }

    butt_vec[SOURCE].Press();

    break;
  case AXIS:

    butt_vec[AXIS].Press();

    break;

  case PLAY_PAUSE:
    if (butt_vec[PLAY_PAUSE].State() == 0) {
      audio_state->is_paused = false;
    } else
      audio_state->is_paused = true;

    butt_vec[PLAY_PAUSE].Press();
    break;

  case CROSSHAIR:
    butt_vec[CROSSHAIR].Press();
    break;

  case SNAP_FUNCTION:
    butt_vec[SNAP_FUNCTION].Press();
    break;

  case NORMALIZE_FUNCTION:
    butt_vec[NORMALIZE_FUNCTION].Press();
    break;

  case REFLECT_FUNCTION:
    butt_vec[REFLECT_FUNCTION].Press();
    break;

  case BACKWARD_10_S:
    /// here
    break;
  case FORWARD_10_S:
/// here
    break;
  default:
    break;
  }
  fourier_data->ShowInConsole();
}



void HandleMouseScrollUp(std::array<Button, BUTTONS_COUNT> &butt_vec,
                         Coord &mouse_position, AudioProgress *audio_state) {
  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec.size(); i++) {
    if (butt_vec[i].DetectPress(mouse_position))
      break;
  }

  switch (i) {
  case NUMBER_OF_SAMPLES_UP:
  case NUMBER_OF_SAMPLES_UP_DOWN:
    fourier_data->number_of_samples += 1;

    break;
  case SCALING_FACTOR_UP:
  case SCALING_FACTOR_DOWN:
    fourier_data->scaling_factor *= 0.99;

    break;
  case WINDING_START_UP:
  case WINDING_START_DOWN:
    fourier_data->winding_start += 1;

    break;
  case WINDING_END_UP:
  case WINDING_END_DOWN:
    fourier_data->winding_end += 1;

    break;
  case WINDING_STEP_UP:
  case WINDING_STEP_DOWN:
    fourier_data->winding_step += 1;
    break;

  case SPEED_UP:
  case SLOW_DOWN:
    if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
      fourier_data->sleep_for -= std::chrono::milliseconds(10);

    break;
  }
  fourier_data->ShowInConsole();
}


void HandleMouseScrollDown(std::array<Button, BUTTONS_COUNT> &butt_vec,
                           Coord &mouse_position, AudioProgress *audio_state) {

  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec.size(); i++) {
    if (butt_vec[i].DetectPress(mouse_position))
      break;
  }

  switch (i) {
  case NUMBER_OF_SAMPLES_UP:
  case NUMBER_OF_SAMPLES_UP_DOWN:
    if (fourier_data->number_of_samples > 1)
      fourier_data->number_of_samples -= 1;

    break;
  case SCALING_FACTOR_UP:
  case SCALING_FACTOR_DOWN:
    fourier_data->scaling_factor *= 1.01;

    break;
  case WINDING_START_UP:
  case WINDING_START_DOWN:
    fourier_data->winding_start -= 1;

    break;
  case WINDING_END_UP:
  case WINDING_END_DOWN:
    fourier_data->winding_end -= 1;

    break;
  case WINDING_STEP_UP:
  case WINDING_STEP_DOWN:
    if (fourier_data->winding_step > 1)
      fourier_data->winding_step -= 1;

    break;
  case SPEED_UP:
  case SLOW_DOWN:
    fourier_data->sleep_for += std::chrono::milliseconds(10);
    break;
  }
  fourier_data->ShowInConsole();
}
