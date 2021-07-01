//
// Created by studio25 on 10.06.2021.
//

#include "audio_playback.h"
#include <future>

void AudioPlayback::InputCallback(void *user_data, uint8_t *stream,
                                  int length) {
  // Copy audio from stream
  auto *progress = (AudioProgress *)user_data;
  if (progress->is_paused)
    return;

  if (progress->mode != AudioProgress::MICROPHONE)
    return;

  memcpy(progress->live_mic_buffer, stream, length);

  //  auto x = std::async(std::launch::async, ApplyFourierTransform, progress,
  //  length, progress->live_mic_buffer);
  ApplyFourierTransform(progress, length, progress->live_mic_buffer);
}

void AudioPlayback::OutputCallback(void *user_data, uint8_t *stream,
                                   int length) {

  auto *progress = (AudioProgress *)user_data;

  if (progress->is_paused)
    return;

  if (progress->mode != AudioProgress::FILE)
    return;

  uint8_t *data_buffer;
  /// if end of file quit
  if (progress->time_left == 0) {
    progress->is_paused = true;
  }

  /// We need to give the sink appropriate amount of data
  length = length > progress->time_left ? progress->time_left : length;
  /// Copy audio data to the audio sink - tell the system to play it
  data_buffer = progress->current_position;
  SDL_memcpy(stream, progress->current_position, length);

  /// Update position in the file
  progress->time_left -= length;
  progress->current_position += length;

  ApplyFourierTransform(progress, length, data_buffer);
  //  auto x = std::async(std::launch::async, ApplyFourierTransform, progress,
  //  length, data_buffer);
}

void AudioPlayback::UseSource(const std::string &path,
                              AudioProgress *progress) {
  if (path.empty())
    return;

  progress->mode = AudioProgress::FILE;

  SDL_Log("Using source file");

  if (!progress->current_position)
    SDL_FreeWAV(progress->current_position);

  auto *callback_func = AudioPlayback::OutputCallback;
  auto *user_data = progress->file_info.userdata;

  /// Load file information and data
  if (SDL_LoadWAV(path.c_str(), &progress->file_info,
                  &progress->current_position, &progress->time_left) == NULL) {

    Tiny::ErrorPopup("Error loading WAV");
    progress->is_paused = true;
  }

  progress->file_info.callback = callback_func;
  progress->file_info.userdata = user_data;

  if (SDL_GetAudioStatus())
    /// Start reading the audio file
    if (SDL_OpenAudio(&progress->file_info, NULL) < 0) {
      //	std::cerr << "Could not open audio device " << path << " "
      //			  << SDL_GetError() << std::endl;
      Tiny::ErrorPopup("Audio device error");
      progress->is_paused = true;
    }

  SDL_PauseAudio(0);
}

void AudioPlayback::UseMicrophone(AudioProgress *progress) {

  progress->mode = AudioProgress::MICROPHONE;

  SDL_AudioSpec want, have;
  SDL_AudioDeviceID dev;

  SDL_memset(&want, 0, sizeof(want));

  want.freq = 48000;
  want.format = progress->file_info.format;
  want.channels = 2;
  want.silence = progress->file_info.silence;
  want.samples = 4096;
  want.userdata = progress;
  want.callback = InputCallback;

  dev = SDL_OpenAudioDevice(NULL, true, &want, &have,
                            SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);

  if (dev == 0) {
    Tiny::ErrorPopup("Microphone could not be opened");
  } else {
    if (have.format != want.format) {
      SDL_Log("We didn't get desired audio format");
    }
    SDL_PauseAudioDevice(dev, 0);
    //        SDL_Delay(5000); /* let the audio callback play some sound for 5
    //        seconds. */ SDL_CloseAudioDevice(dev);
  }
}
