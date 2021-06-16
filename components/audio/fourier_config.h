//
// Created by studio25 on 07.06.2021.
//
#pragma once
#ifndef EQUALIZER_COMPONENTS_AUDIO_FOURIER_CONFIG_H_
#define EQUALIZER_COMPONENTS_AUDIO_FOURIER_CONFIG_H_

// fixme if ths function is declared, linker shouts at us
// also once  this is fixed correct ShowInConsole()

// void clear_window() {
//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) &&
//!defined(__CYGWIN__)
//     system("cls");
//#else
//     std::cout << "\x1B[2J\x1B[H";
//#endif
// }

#include <chrono>
#include <vector>

enum class InputType { MICROPHONE, FILE };

struct FourierConfig {
  int number_of_samples;
  double scaling_factor;
  int winding_start;
  int winding_end;

  /// must grater than 0
  int winding_step;

  bool skip_forward;
  bool skip_backward;

  std::chrono::milliseconds sleep_for;

  InputType source;
  uint16_t volume;
  std::vector<int> freqs;

  int start_frequency;
  int end_frequency;

  void ShowInConsole() const {
    system("cls");

    printf("number of samples: %d\n"
           "scaling_factor: %lf\n"
           "winding start: %d\t end: %d\n"
           "winding step: %d\n"
           "sleep_for: %lld ms\n",
           number_of_samples, scaling_factor, winding_start, winding_end,
           winding_step, sleep_for.count());

    if (source == InputType::MICROPHONE)
      printf("input: MICROPHONE\n");
    else
      printf("input: file\n");
  }
};

#endif // EQUALIZER_COMPONENTS_AUDIO_FOURIER_CONFIG_H_
