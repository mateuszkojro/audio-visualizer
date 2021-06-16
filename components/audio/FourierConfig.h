//
// Created by studio25 on 07.06.2021.
//
#pragma once
#ifndef EQUALIZER_FOURIERCONFIG_H
#define EQUALIZER_FOURIERCONFIG_H

// fixme if ths function is declared, linker shouts at us
// also once  this is fixed correct show_in_console()


//void clear_window() {
//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//    system("cls");
//#else
//    std::cout << "\x1B[2J\x1B[H";
//#endif
//}

#include <chrono>
#include <vector>

enum input_type{
    microphone,
    file
};

struct FourierConfig {
    int number_of_samples;
    double scaling_factor;
    int winding_start;
    int winding_end;

    /// must grater than 0
    int winding_step;

    bool skip_forward;
    bool skip_backward;

    std::chrono::milliseconds sleep_for;

    input_type source;
    uint16_t volume;
    std::vector<int> freqs;

    int start_frequency;
    int end_frequency;


    void show_in_console() {
        system("cls");

        printf("number of samples: %d\n"
               "scaling_factor: %lf\n"
               "winding start: %d\t end: %d\n"
               "winding step: %d\n"
               "sleep_for: %lld ms\n", number_of_samples, scaling_factor, winding_start, winding_end, winding_step,
               sleep_for.count());

        if(source == microphone) printf("input: microphone\n");
        else printf("input: file\n");


    }

};

#endif //EQUALIZER_FOURIERCONFIG_H
