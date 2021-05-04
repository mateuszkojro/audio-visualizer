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
    frame(unsigned int id, canvas *surface) : id(id), surface(surface) {}
    virtual ~frame() {
        delete surface;
    }
    unsigned id;
    canvas *surface;
};

extern std::queue<std::vector<int> *> raw_bus;
extern std::queue<std::thread *> thread_queue;
extern std::queue<frame> analyzed_bus;

[[noreturn]] void main_gen_data();

void analyze_data(std::vector<int> *input, unsigned frame_id);

[[noreturn]] void main_analyze_data();




#endif //EQUALIZER_P_SCHEDULER_H
