//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER__AUDIO_PROGRESS_H_
#define EQUALIZER__AUDIO_PROGRESS_H_

#include "fourier_config.h"
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

	system("cls");

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
	out << "Time left: " << progress->time_left << std::endl
		<< "Current position: " << (int)progress->current_position << std::endl
		<< "number of samples:\t" << progress->config->number_of_samples << std::endl
		<< "scaling_factor:\t" << progress->config->scaling_factor << std::endl
		<< "winding start:\t" << progress->config->winding_start << std::endl
		<< "winding end:\t" << progress->config->winding_end << std::endl
		<< "winding step:\t" << progress->config->winding_step << std::endl
		<< "sleep_for:\t" << progress->config->sleep_for.count() << std::endl
		<< "is paused:\t" << std::boolalpha << progress->is_paused << std::endl;
#pragma clang diagnostic pop

	out << "Mode: \t";
	switch (progress->mode) {
	  case FILE: out << "FILE";
		break;

	  case MICROPHONE: out << "MICROPHONE";
		break;

	  case CLOSE: out << "CLOSE";
		break;
	}
	out << std::endl;

	return out;
  }
};

#endif // EQUALIZER__AUDIO_PROGRESS_H_
