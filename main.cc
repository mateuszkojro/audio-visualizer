//
// Created by piotr233  on 16.04.2021.
//

#include "components/audio/audio_progress.h"
#include "components/graphics/window/equalizer_window.h"

#include <numeric>
#include <thread>
#include "SDL_ttf.h"

/// class Audio playback ze statycznymi
/// funkcjamy callback

int main(int argc, char *argv[]) {
  TTF_Init();

  /// Setup SDL audio handling
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	Tiny::ErrorPopup("SDL could not be inited");
	exit(1);
  }

  FourierConfig data;
  for (int i = 0; i < 5; i++) { // generates some starting points for our graph
	data.freqs.push_back(WINDOW_HEIGHT / 2);
  }

  data.winding_start = 1;
  data.winding_end = 200;
  data.winding_step = 2;
  data.number_of_samples = 20;
  data.sleep_for = std::chrono::milliseconds(0);
  data.scaling_factor = 1.0 / 10000;

  auto progress = new AudioProgress;

  progress->mode = AudioProgress::FILE;
  progress->config = &data;
  progress->file_info = SDL_AudioSpec();
  progress->live_mic_buffer = new uint8_t[1000000];
  progress->file_info.userdata = progress;
  progress->file_info.callback = AudioPlayback::OutputCallback;

  AudioPlayback::UseMicrophone(progress);
//   AudioPlayback::UseSource("example.wav", progress);

  EqualizerWindow main_window(progress);

  /// Wait for the end of playing
  std::thread wait([&progress]() {
	while (progress->mode != AudioProgress::CLOSE) {
	  //  std::cout << progress;
	  SDL_Delay(100);
	}
  });

  wait.join();

  /// Clean up
  SDL_CloseAudio();


  return 0;
}