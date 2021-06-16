//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER__FOURIER_TRANSFORM_H_
#define EQUALIZER__FOURIER_TRANSFORM_H_
#include "audio_progress.h"

#include <SDL_main.h> /// for some reason I can't import M_Pi from cmath
#include <cassert>
#include <cfloat>
#include <complex>
#include <numeric>
#include <thread>

// todo We need to test that

/// This function for given sample and frequency gives back the "amount" of this
/// frequency -- not tested
/// \param freq frequency
/// \param data ptr to uint16_t of current sample
/// \param size sample size in bytes
/// \return complex value with the "amount"
std::complex<double_t> GetValueForFreq(double_t freq, uint16_t *data,
                                       uint32_t size, int step);

void ApplyFourierTransform(AudioProgress *progress, int length, uint8_t *data);

#endif // EQUALIZER__FOURIER_TRANSFORM_H_
