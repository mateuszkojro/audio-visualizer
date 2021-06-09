//
// Created by piotr233  on 16.04.2021.
//

#include "components/graphics/equalizer_window.h"
#include <numeric>
#include <thread>
#include <complex>
#include <cfloat>
#include "SDL_ttf/SDL_ttf.h"

extern "C" {
#include "tinyfiledialogs/tinyfiledialogs.h"
}


// todo We need to test that
/// This function for given sample and frequency gives back the "amount" of this frequency -- not tested
/// \param freq frequency
/// \param data ptr to uint16_t of current sample
/// \param size sample size in bytes
/// \return complex value with the "amount"
std::complex<double_t> get_value_for_freq(double_t freq, uint16_t *data, uint32_t size, int step) {
    std::complex<double_t> result;

    for (int itr = 0; itr < size; itr += step) {
        assert(data[itr] <= UINT16_MAX);
        std::complex<double> const_part(0, -2 * M_PI / (size / 1.0));
        std::complex<double> var_part(freq * itr, 0);
        result += std::complex<double>(data[itr], 0) * std::exp(const_part * var_part);
    }
    return result;
}

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

};

std::ostream &operator<<(std::ostream &out, AudioProgress *progress) {
    out << "Time left: " << progress->time_left_ << std::endl
        << "Current position: " << (int) progress->current_position_ << std::endl
        << "Config" << std::endl
        << "" << std::endl;
    return out;
}

void error_popup(const std::string &title) {
    tinyfd_messageBox(title.c_str(), SDL_GetError(), "error", "error", 0);
}

void apply_fourier_transfrom(AudioProgress *progress, int length, uint8_t *data) {
    auto &frequencies = progress->config_->freqs;
    auto &config = progress->config_;


    int desired_size = 1 + (config->winding_end - config->winding_start) / config->winding_step;

    while (frequencies.size() <= desired_size) {
        frequencies.push_back(0);
    }

    while (frequencies.size() > desired_size) {
        frequencies.pop_back();
    }

    int itr = 0;
    for (int i = config->winding_start;
         i < config->winding_end; i += config->winding_step) {//UINT16_MAX / WINDOW_WIDTH) {
        if (i > length)
            continue;
        auto value = get_value_for_freq(i, reinterpret_cast<uint16_t *>(data),
                                        length / 2, config->number_of_samples);
        // todo the value there should be double but for testing rn we leave it at that
        double vector_len = abs(value) * config->scaling_factor;
        // double vector_len = value.real() * config->scaling_factor;
        // We are taking the magnitude because math is hard xD
        frequencies[itr++] = (vector_len);
    }

    /// to slow down playback we slow down the thread
    std::this_thread::sleep_for(config->sleep_for);
}

void record_callback(void *user_data, uint8_t *stream, int length) {
    //Copy audio from stream
    AudioProgress *progress = (AudioProgress *) user_data;

    if (progress->mode_ != AudioProgress::microphone)
        return;

    memcpy(progress->live_mic_buffer_, stream, length);

    apply_fourier_transfrom(progress, length, progress->live_mic_buffer_);

}

/// Function that will be called when audio sink needs more data
void audio_callback(void *user_data, uint8_t *stream, int length) {
    auto *progress = (AudioProgress *) user_data;
    std::cout << "audio callbaclk" << std::endl;

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
};

void change_source_file(const std::string &path, AudioProgress *progress) {
    if (path.empty())
        return;

    if (!progress->current_position_)
        SDL_FreeWAV(progress->current_position_);

    /// Load file information and data
    if (SDL_LoadWAV(path.c_str(), &progress->file_info_, &progress->current_position_, &progress->time_left_) == NULL) {
        std::cerr << "Could not load audio file: " << path << " " << SDL_GetError() << std::endl;
        error_popup("Error loading WAV");

        progress->mode_ = AudioProgress::paused;
    }

    /// Start reading the audio file
    if (SDL_OpenAudio(&progress->file_info_, NULL) < 0) {
        std::cerr << "Could not open audio device " << path << " " << SDL_GetError() << std::endl;
        error_popup("Audio device error");
        progress->mode_ = AudioProgress::paused;
    }

    /// Unpause the audio
    SDL_PauseAudio(0);
}

void use_microphone(AudioProgress *progress) {

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
    want.callback = record_callback;

    dev = SDL_OpenAudioDevice(NULL, true, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (dev == 0) {
        error_popup("Microphone could not be opened");
    } else {
        if (have.format != want.format) {
            SDL_Log("We didn't get desired audio format");
        }
        SDL_PauseAudioDevice(dev, 0);
//        SDL_Delay(5000); /* let the audio callback play some sound for 5 seconds. */
//        SDL_CloseAudioDevice(dev);
    }

}

std::string open_file_dialog() {

    char const *lFilterPatterns[] = {"*.wav"};
    auto file_name = tinyfd_openFileDialog(
            "Open audio file ",
            "",
            1,
            lFilterPatterns,
            NULL,
            false);
    std::cout << file_name << std::endl;
    return file_name;
}

int main(int argc, char *argv[]) {

//    TTF_Font* font = TTF_OpenFont("..\\components\\graphics\\assets\\FiraCode-Light", 14);

    /// Setup SDL audio handling
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        error_popup("SDL could not be inited");
        exit(1);
    }


    std::string path = open_file_dialog();
    if (path.empty()) {
        exit(1);
    }

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
    progress->file_info_.callback = audio_callback;

    use_microphone(progress);
//    change_source_file(path, progress);

    std::thread visualizer_window(equalizer_window_from_data, &data); // thread containing window

    /// Wait for the end of playing
    std::thread wait([&progress]() {
        while (progress->mode_ != AudioProgress::close) {
            std::cout << progress;
            SDL_Delay(100);
        }
    });

    wait.join();

    /// Clean up
    SDL_CloseAudio();

    visualizer_window.join();

    return 0;
}