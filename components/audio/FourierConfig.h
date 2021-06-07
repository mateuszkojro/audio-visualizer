//
// Created by studio25 on 07.06.2021.
//

#ifndef EQUALIZER_FOURIERCONFIG_H
#define EQUALIZER_FOURIERCONFIG_H

struct FourierConfig {
    int number_of_samples;
    int scaling_factor;
    int winding_start;
    int winding_end;
    int winding_step;
    bool skip_forward;
    bool skip_backward;
    uint16_t volume;
    std::vector<int> freqs;
};

#endif //EQUALIZER_FOURIERCONFIG_H
