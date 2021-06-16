//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER__AUDIO_PROGRESS_H_
#define EQUALIZER__AUDIO_PROGRESS_H_

#include "components/audio/fourier_config.h"
#include <SDL_audio.h>
#include <iostream>

/// \brief Data structure containing information needed by the play audio
/// callback
struct AudioProgress {

  enum Mode { PAUSED, FILE, MICROPHONE, CLOSE };

  Mode mode;

  bool is_paused = true;

  /// Common interface to exchange info
  FourierConfig *config;

  SDL_AudioSpec file_info;
  /// Current position in the audio file
  uint8_t *live_mic_buffer;
  uint8_t *current_position;

  /// Time until the end of the file
  uint32_t time_left;

  friend std::ostream &operator<<(std::ostream &out, AudioProgress *progress) {
    out << "Time left: " << progress->time_left << std::endl
        << "Current position: " << (int)progress->current_position << std::endl
        << "Config" << std::endl
        << "" << std::endl;
    return out;
  }
};

#endif // EQUALIZER__AUDIO_PROGRESS_H_
