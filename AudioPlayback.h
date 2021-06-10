//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER_AUDIOPLAYBACK_H
#define EQUALIZER_AUDIOPLAYBACK_H


#include "AudioProgress.h"
#include "FourierTransform.h"

#include <numeric>
#include <thread>
#include <complex>
#include <cfloat>
#include <SDL_main.h>
#include <SDL_audio.h>
#include <iostream>
#include <SDL_log.h>
#include "TinyMessage.h"

class AudioPlayback {
public:

    static void input_callback(void *user_data, uint8_t *stream, int length);

/// Function that will be called when audio sink needs more data
    static  void output_callback(void *user_data, uint8_t *stream, int length);;



    static  void use_source(const std::string &path, AudioProgress *progress);

    static  void use_microphone(AudioProgress *progress);
};


#endif //EQUALIZER_AUDIOPLAYBACK_H
