//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER_FOURIERTRANSFORM_H
#define EQUALIZER_FOURIERTRANSFORM_H
#include "AudioProgress.h"

#include <numeric>
#include <thread>
#include <complex>
#include <cfloat>
#include <cassert>
#include <SDL_main.h> /// for some reason I can't import M_Pi from cmath

// todo We need to test that
/// This function for given sample and frequency gives back the "amount" of this frequency -- not tested
/// \param freq frequency
/// \param data ptr to uint16_t of current sample
/// \param size sample size in bytes
/// \return complex value with the "amount"
std::complex<double_t> get_value_for_freq(double_t freq, uint16_t *data, uint32_t size, int step);

void apply_fourier_transfrom(AudioProgress *progress, int length, uint8_t *data);


#endif //EQUALIZER_FOURIERTRANSFORM_H
