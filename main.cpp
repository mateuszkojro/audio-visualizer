//
// Created by piotr233  on 16.04.2021.
//

#include "components/graphics/equalizer_window.h"
#include "AudioProgress.h"
#include "FourierTransform.h"
#include <numeric>
#include <thread>
#include <complex>

#include "AudioPlayback.h"




/// class Audio playback ze statycznymi
/// funkcjamy callback

int main(int argc, char *argv[]) {

//    TTF_Font* font = TTF_OpenFont("..\\components\\graphics\\assets\\FiraCode-Light", 14);

    /// Setup SDL audio handling
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Tiny::error_popup("SDL could not be inited");
        exit(1);
    }


  //  std::string path = Tiny::open_file_dialog();
   //
//   if (path.empty()) {
//        exit(1);
//    }

    FourierConfig data;
    for (int i = 0; i < 5; i++) { // generates some starting points for our graph
        data.freqs.push_back(WINDOW_HEIGHT / 2);
    }

    data.winding_start = 0;
    data.winding_end = 200;
    data.winding_step = 2;
    data.number_of_samples = 20;
    data.sleep_for = std::chrono::milliseconds(0);
    data.scaling_factor = 1.0 / 10000;

    auto progress = new AudioProgress;

    progress->mode_ = AudioProgress::file;
    progress->config_ = &data;
    progress->file_info_ = SDL_AudioSpec();
    progress->live_mic_buffer_ = new uint8_t[1000000];
    progress->file_info_.userdata = progress;
    progress->file_info_.callback = AudioPlayback::output_callback;

    AudioPlayback::use_microphone(progress);
  //  AudioPlayback::use_source(path, progress);

    std::thread visualizer_window(equalizer_window_from_data, progress); // thread containing window

    /// Wait for the end of playing
    std::thread wait([&progress]() {
        while (progress->mode_ != AudioProgress::close) {
            //  std::cout << progress;
            SDL_Delay(100);
        }
    });

    wait.join();

    /// Clean up
    SDL_CloseAudio();

    visualizer_window.join();

    return 0;
}