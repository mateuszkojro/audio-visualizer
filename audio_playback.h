//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER__AUDIO_PLAYBACK_H_
#define EQUALIZER__AUDIO_PLAYBACK_H_

#include "audio_progress.h"
#include "fourier_transform.h"
#include "tiny_message.h"
#include <SDL_audio.h>
#include <SDL_log.h>
#include <SDL_main.h>
#include <cfloat>
#include <complex>
#include <iostream>
#include <numeric>
#include <thread>

class AudioPlayback {
public:
  static void InputCallback(void *user_data, uint8_t *stream, int length);

  /// Function that will be called when audio sink needs more data
  static void OutputCallback(void *user_data, uint8_t *stream, int length);


  static void UseSource(const std::string &path, AudioProgress *progress);

  static void UseMicrophone(AudioProgress *progress);
};

#endif // EQUALIZER__AUDIO_PLAYBACK_H_
