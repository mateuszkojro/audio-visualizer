//
// Created by piotr233  on 16.04.2021.
//



#include "components/graphics/equalizer_window.h"
#include <numeric>
#include <thread>
#include <complex>
#include <cfloat>

#include "components/audio/FourierConfig.h"

// todo We need to test that
/// This function for given sample and frequency gives back the "amount" of this frequency -- not tested
/// \param freq frequency
/// \param data ptr to uint16_t of current sample
/// \param size sample size in bytes
/// \return complex value with the "amount"
std::complex<double_t> get_value_for_freq(double_t freq, uint16_t *data, uint32_t size) {
    std::complex<double_t> result;

    for (int itr = 0; itr < 4096; itr += 1) {
        assert(data[itr] <= UINT16_MAX);
        std::complex<double> const_part(0, -2 * M_PI / (4096 / 1.0));
        std::complex<double> var_part(freq * itr, 0);
        result += std::complex<double>(data[itr], 0) * std::exp(const_part * var_part);
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
    length = length > progress->time_left_ ? progress->time_left_ : length;


    //std::cout << "New data packet, time left: " << progress->time_left_ << ", playiing: " << length;

    /// Vector containing frequencies to be shown by the graphics engine
    std::vector<int> frequencies;
    frequencies.reserve(200/3);
    /// Collect data evry 5000Hz in the range that can be heard by the humans
    for (int i = 0; i < 200; i += 5){//UINT16_MAX / WINDOW_WIDTH) {
        if (i > length)
            continue;
        auto value = get_value_for_freq(i, reinterpret_cast<uint16_t *>(progress->current_position_),
                                        length / 2);
        // todo the value there should be double but for testing rn we leave it at that
//        double vector_len = (std::abs(value) /* /(DBL_MAX * 1.0)*/)/10e6;
        double vector_len = abs(value) / 10000;/* /(DBL_MAX * 1.0)*/;
        // We are taking the magnitude because math is hard xD
//        std::clog << "i: " << i << "->" << vector_len << ",";
        frequencies.push_back(vector_len);
    }

//    frequencies->erase(frequencies->cbegin());
    /// Copy audio data to the audio sink - tell the system to play it
    SDL_memcpy(stream, progress->current_position_, length);

    /// Assign ptr with new data to sink
    *progress->graphics_sink_ = frequencies;

    /// Update position in the file
    progress->time_left_ -= length;
    progress->current_position_ += length;
};


int main(int argc, char *argv[]) {
    ;
    /// Setup SDL audio handling
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not be inited " << SDL_GetError() << std::endl;
        exit(1);
    }

    uint32_t file_length;
    uint8_t *audio_data;
    SDL_AudioSpec file_information;

    std::string path = "C:\\Users\\studio25\\Documents\\audio_visualizer\\files\\test.wav";

    /// Load file information and data
    if (SDL_LoadWAV(path.c_str(), &file_information, &audio_data, &file_length) == NULL) {
        std::cerr << "Could not load audio file: " << path << " " << SDL_GetError() << std::endl;
        exit(2);
    }


    FourierConfig data;
    for (int i = 0; i < 5; i++) { // generates some starting points for our graph
        data.freqs.push_back(WINDOW_HEIGHT / 2);
    }

    std::thread visualizer_window(equalizer_window_from_data, data); // thread containing window


    auto user_data = new AudioProgress;
    /// Current position in file is the begining of the file xdd
    user_data->current_position_ = audio_data;
    /// Time left is all the time in the file
    user_data->time_left_ = file_length;
    /// Sink is the ptr that is later passed to other tyhread
    user_data->graphics_sink_ = &data.freqs;

    file_information.userdata = user_data;
    file_information.callback = audio_callback;

    /// Start reading the audio file
    if (SDL_OpenAudio(&file_information, NULL) < 0) {
        std::cerr << "Could not open audio file " << SDL_GetError() << std::endl;
        exit(3);
    }

    printf("Chanells: %d, Freq: %d, Samples: %d \n",
           file_information.channels,
           file_information.freq,
           file_information.samples
    );

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

    visualizer_window.join();

    return 0;
}