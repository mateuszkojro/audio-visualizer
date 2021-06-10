//
// Created by studio25 on 10.06.2021.
//

#include "AudioPlayback.h"

void AudioPlayback::input_callback(void *user_data, uint8_t *stream, int length) {
    //Copy audio from stream
    AudioProgress *progress = (AudioProgress *) user_data;
    if(progress->is_paused_) return ;

    if (progress->mode_ != AudioProgress::microphone)
        return;

    memcpy(progress->live_mic_buffer_, stream, length);

    apply_fourier_transfrom(progress, length, progress->live_mic_buffer_);

}

void AudioPlayback::output_callback(void *user_data, uint8_t *stream, int length) {
    auto *progress = (AudioProgress *) user_data;

if(progress->is_paused_) return ;

    if (progress->mode_ != AudioProgress::file)
        return;

    uint8_t *data_buffer;
    /// if end of file quit
    if (progress->time_left_ == 0) {
        progress->mode_ = AudioProgress::paused;
    }

    /// We need to give the sink appropriate amount of data
    length = length > progress->time_left_ ? progress->time_left_ : length;
    /// Copy audio data to the audio sink - tell the system to play it
    data_buffer = progress->current_position_;
    SDL_memcpy(stream, progress->current_position_, length);

    /// Update position in the file
    progress->time_left_ -= length;
    progress->current_position_ += length;

    apply_fourier_transfrom(progress, length, data_buffer);
}

void AudioPlayback::use_source(const std::string &path, AudioProgress *progress) {
    if (path.empty())
        return;

    if (!progress->current_position_)
        SDL_FreeWAV(progress->current_position_);
    auto callback_func = progress->file_info_.callback;
    auto user_data = progress->file_info_.userdata;

    /// Load file information and data
    if (SDL_LoadWAV(path.c_str(), &progress->file_info_, &progress->current_position_, &progress->time_left_) == NULL) {
        std::cerr << "Could not load audio file: " << path << " " << SDL_GetError() << std::endl;
        Tiny::error_popup("Error loading WAV");

        progress->mode_ = AudioProgress::paused;
    }


    progress->file_info_.callback = callback_func;
    progress->file_info_.userdata = user_data;


    if(SDL_GetCurrentAudioDriver() == NULL) {
        /// Start reading the audio file
        if (SDL_OpenAudio(&progress->file_info_, NULL) < 0) {
            std::cerr << "Could not open audio device " << path << " " << SDL_GetError() << std::endl;
            Tiny::error_popup("Audio device error");
            progress->mode_ = AudioProgress::paused;
        }
    }

    SDL_PauseAudio(0);
}

void AudioPlayback::use_microphone(AudioProgress *progress) {

    progress->mode_ = AudioProgress::microphone;

    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_memset(&want, 0, sizeof(want));

    want.freq = 48000;
    want.format = progress->file_info_.format;
    want.channels = 2;
    want.silence = progress->file_info_.silence;
    want.samples = 4096;
    want.userdata = progress;
    want.callback = input_callback;


        dev = SDL_OpenAudioDevice(NULL, true, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);


    if (dev == 0) {
        Tiny::error_popup("Microphone could not be opened");
    } else {
        if (have.format != want.format) {
            SDL_Log("We didn't get desired audio format");
        }
        SDL_PauseAudioDevice(dev, 0);
//        SDL_Delay(5000); /* let the audio callback play some sound for 5 seconds. */
//        SDL_CloseAudioDevice(dev);
    }

}
