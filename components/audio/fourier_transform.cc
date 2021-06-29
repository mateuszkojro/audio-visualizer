//
// Created by studio25 on 10.06.2021.
//

#include "fourier_transform.h"
#include <algorithm>


std::complex<double_t> GetValueForFreq(double_t freq, uint16_t *data,
									   uint32_t size, int step) {
  std::complex<double_t> result;

  for (int itr = 0; itr < size; itr += step) {
	assert(data[itr] <= UINT16_MAX);
	std::complex<double> const_part(0, -2 * M_PI / (size / 1.0));
	std::complex<double> var_part(freq * itr, 0);
	result +=
		std::complex<double>(data[itr], 0) * std::exp(const_part * var_part);
  }
  return result;
}

void ApplyFourierTransform(AudioProgress *progress, int length, uint8_t *data) {
  auto &frequencies = progress->config->freqs;
  auto &config = progress->config;

  int desired_size =
	  1 + (config->winding_end - config->winding_start) / config->winding_step;

  while (frequencies.size() <= desired_size) {
	frequencies.push_back(0);
  }

  while (frequencies.size() > desired_size) {
	frequencies.pop_back();
  }

  int itr = 0;
  for (int i = config->winding_start; i < config->winding_end;
	   i += config->winding_step) { // UINT16_MAX / WINDOW_WIDTH) {
	if (i > length)
	  continue;
	auto value = GetValueForFreq(i, reinterpret_cast<uint16_t *>(data),
								 length / 2, config->number_of_samples);
	// todo the value there should be double but for testing rn we leave it at
	// that
	double vector_len = abs(value) * config->scaling_factor;
	// double vector_len = value.real() * config->scaling_factor;
	// We are taking the magnitude because math is hard xD
	frequencies[itr++] = (vector_len);
  }


  /// to slow down playback we slow down the thread
  std::this_thread::sleep_for(config->sleep_for);
}