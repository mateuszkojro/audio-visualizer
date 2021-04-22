//
// Created by mateu on 4/22/2021.
//

#ifndef EQUALIZER_DATAFRAME_H
#define EQUALIZER_DATAFRAME_H

#include <chrono>
#include <map>
#include <SDL.h>


class DataFrame {
public:
    enum State {
        AudioProcessing,
        ApplyAudioProcessing,
        CreateGraphics,
    };

    std::chrono::time_point<std::chrono::steady_clock> creation_time_;
    uint8_t* raw_data_;
    std::map<double_t ,double_t > frequencies_;
    SDL_Renderer* canvas_;

};


#endif //EQUALIZER_DATAFRAME_H
