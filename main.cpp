//
// Created by piotr233  on 16.04.2021.
//



#include "components/graphics/equalizer_window.h"
#include <numeric>
#include <thread>
#include <complex>

// todo We need to test that
/// This function for given sample and frequency gives back the "amount" of this frequency -- not tested
/// \param freq frequency
/// \param data ptr to uint16_t of current sample
/// \param size sample size in bytes
/// \return complex value with the "amount"
std::complex<double_t> get_value_for_freq(double_t freq, uint16_t *data, uint32_t size) {
    std::complex<double_t> result;
    const double_t delta_t = 2.27E-5;

    for (int itr = 0; itr < (size - 1) / 2; itr++) {
        double_t avg_value = delta_t * (data[itr] + data[itr + 1]) / 2.0;
        std::complex<double_t> exponent = std::exp(
//                std::complex<double_t>(0, static_cast<const double_t>(-2 * PI * 1i * freq * ((itr + itr + 1) / 2.0))));
                std::complex<double_t>(0, (-2 * PI * freq * ((itr + itr + 1) / 2.0))));
        result += avg_value * exponent;
    }

    return result;
}

/// \brief Data structure containing information needed by the play audio callback
struct AudioProgress {
    /// Address in the memory checked by the graphics engine
    std::vector<int> *graphics_sink_;
    /// Current position in the audio file
    uint8_t *current_position_;
    /// Time until the end of the file
    uint32_t time_left_;
};

/// Function that will be called when audio sink needs more data
void audio_callback(void *user_data, uint8_t *stream, int length) {
    auto *progress = (AudioProgress *) user_data;

    /// if end of file quit
    if (progress->time_left_ == 0) {
        return;
    }

    /// We need to give the sink appropriate amount of data
    length = (length > progress->time_left_ ? progress->time_left_ : length);


    //std::cout << "New data packet, time left: " << progress->time_left_ << ", playiing: " << length;

    /// Vector containing frequencies to be shown by the graphics engine
    std::vector<int> *frequencies = new std::vector<int>;

    /// Collect data evry 5000Hz in the range that can be heard by the humans
    for (int i = 0; i < 20000; i += 4000) {
        auto value = get_value_for_freq(i, reinterpret_cast<uint16_t *>((uint16_t) progress->current_position_),
                                        progress->time_left_);
        // todo the value there should be double but for testing rn we leave it at that
        int vector_len = std::abs(value); // We are taking the magnitude because math is hard xD
        frequencies->push_back(vector_len);
    }

    /// Copy audio data to the audio sink - tell the system to play it
    SDL_memcpy(stream, progress->current_position_, length);

    /// Assign ptr with new data to sink
    *progress->graphics_sink_ = *frequencies;

    /// Update position in the file
    progress->time_left_ -= length;
    progress->current_position_ += length;
};

int main(int argc, char *argv[]) {

    /// Setup SDL audio handling
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL audio could not be inited " << SDL_GetError() << std::endl;
        exit(1);
    }

    uint32_t file_length;
    uint8_t *audio_data;
    SDL_AudioSpec file_information;
    std::string path = "./example.wav";

    /// Load file information and data
    if (SDL_LoadWAV(path.c_str(), &file_information, &audio_data, &file_length) == NULL) {
        std::cerr << "Could not load audio file: " << path << " " << SDL_GetError() << std::endl;
        exit(2);
    }


    std::vector<int> data;
    for (int i = 0; i < 5; i++) { // generates some starting points for our graph
        data.push_back(WINDOW_HEIGHT / 2);
    }

    std::thread window(equalizer_window, &data); // thread containing window


    auto user_data = new AudioProgress;
    /// Current position in file is the begining of the file xdd
    user_data->current_position_ = audio_data;
    /// Time left is all the time in the file
    user_data->time_left_ = file_length;
    /// Sink is the ptr that is later passed to other tyhread
    user_data->graphics_sink_ = &data;

    file_information.userdata = user_data;
    file_information.callback = audio_callback;

    /// Start reading the audio file
    if (SDL_OpenAudio(&file_information, NULL) < 0) {
        std::cerr << "Could not open audio file " << SDL_GetError() << std::endl;
        exit(3);
    }

    /// Unpause the audio
    SDL_PauseAudio(0);

    /// We cannot stop the main thread until the end of playing
    std::thread wait([user_data]() {
        while (user_data->time_left_ > 0) {
            SDL_Delay(100);
        }
    });

    /// Wait for the end of playing
    wait.join();

    /// Clean up
    SDL_CloseAudio();
    SDL_FreeWAV(audio_data);
    delete user_data;

    window.join();

    return 0;
}