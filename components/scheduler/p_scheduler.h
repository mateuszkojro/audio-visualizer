//
// Created by pc on 30.04.2021.
//
#pragma once
#ifndef EQUALIZER_P_SCHEDULER_H
#define EQUALIZER_P_SCHEDULER_H

#include <queue>
#include <thread>
#include <map>
#include "../graphics/canvas.h"
#include "../graphics/equalizer_window.h"


void stop_until(bool condition);

struct frame {
    frame(unsigned int id) :
            id(id), raw_data_points(nullptr), surface(nullptr), raw_data_(nullptr),
            frequencies_(nullptr) {}

    frame(unsigned int id, std::vector<int> *raw_data_points) :
            id(id), raw_data_points(raw_data_points), surface(nullptr), raw_data_(nullptr), frequencies_(nullptr) {}

    frame(unsigned int id, canvas *surface) :
            id(id), raw_data_points(nullptr), surface(surface), raw_data_(nullptr),
            frequencies_(nullptr) {}

    virtual ~frame() {
        delete surface;
        delete raw_data_;
        delete frequencies_;
        delete raw_data_points;
    }

    unsigned id;
    uint8_t *raw_data_;
    std::vector<int> *raw_data_points;
    std::map<double_t, double_t> *frequencies_;
    canvas *surface;

};

/// creation
extern std::queue<frame> raw_bus;
/// frame analysis
extern std::queue<frame> analyzed_bus;

///way of thread co
extern std::queue<std::thread *> thread_queue;


[[noreturn]] void main_gen_data();

void analyze_data(std::vector<int> *input, unsigned frame_id);

[[noreturn]] void main_analyze_data();


#endif //EQUALIZER_P_SCHEDULER_H
