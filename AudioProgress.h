//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER_AUDIOPROGRESS_H
#define EQUALIZER_AUDIOPROGRESS_H


#include "components/audio/FourierConfig.h"
#include <iostream>
#include <SDL_audio.h>

/// \brief Data structure containing information needed by the play audio callback
struct AudioProgress {

    enum Mode {
        paused,
        file,
        microphone,
        close
    };

    Mode mode_;

    /// Common interface to exchange info
    FourierConfig *config_;

    SDL_AudioSpec file_info_;
    /// Current position in the audio file
    uint8_t *live_mic_buffer_;
    uint8_t *current_position_;

    /// Time until the end of the file
    uint32_t time_left_;

friend std::ostream &operator<<(std::ostream &out, AudioProgress *progress) {
    out << "Time left: " << progress->time_left_ << std::endl
        << "Current position: " << (int) progress->current_position_ << std::endl
        << "Config" << std::endl
        << "" << std::endl;
    return out;
}
};



#endif //EQUALIZER_AUDIOPROGRESS_H
