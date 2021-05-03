//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_P_SCHEDULER_H
#define EQUALIZER_P_SCHEDULER_H

#include "components/graphics/canvas.h"
#include "components/graphics/RGBColor.h"
#include "components/graphics/equalizer_window.h"


#include <queue>
#include <thread>
#include <map>

unsigned abs(unsigned x, unsigned y) {
    if (x < y) return y - x;
    else return x - y;
}

void stop_until(bool condition) {
    while (condition)
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

}

struct frame {
    frame(unsigned int id, canvas *surface) : id(id), surface(surface) {}


    virtual ~frame() {
        delete surface;
    }

    unsigned id;
    canvas *surface;
};

// this one needs id so
//
std::queue<std::vector<int> *> raw_bus;

std::queue<std::thread *> thread_queue;
std::queue<frame> analyzed_bus;


[[noreturn]] void main_gen_data() {

    {
        ///the idea is:
        /// frames that are generated can come faster than we show it
        /// and they can come in random time periods
        /// we need to analyze them in shortest time possible, regardless of complexity of frame
        /// or when it came to us, and we need to minimize the time periods as much as we can
        /// than we need to show them
        /// we can show frames at about 30fps right now
        /// so the idea is :
        ///
        ///     gen data -> push to data_pile  the data created is pushed to pile
        ///     data_pile -> analyze data -> display_pile  erase data from data pile add to display pile
        ///     display_pile -> show frame   delete from display pile and show frame
        ///
        /// we can not stop reading data soo we need to analyze every other
        /// so we have two counters one for every pile
        /// if the difference between two piles is to great we slow down the analyzing part
        /// and by slow down i mean analyze every other or every third
        /// i cant see memory leaks with this design but i hope there want be any

        /// analyze data:
        /// we need many speed here and we hope that lot's of them threads will assure that
        /// so analyze data will take place using threads
        ///
    }

    std::vector<int> *data_ptr;
    while (2 > 1) {
        data_ptr = new std::vector<int>();
        for (int i = 0; i < 5; ++i) data_ptr->push_back(rand() % 500);
        raw_bus.push(data_ptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}




void analyze_data(std::vector<int> *input, unsigned frame_id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //dummy code                                                        \/ this shit is the worst
    auto output = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {*input->begin() % 255, 0, 0});
    delete input; /// input cleanup

    stop_until(analyzed_bus.back().id == frame_id-1);
    analyzed_bus.push({frame_id,output});
    delete input;

}

void main_analyze_data() {

    canvas *output;
    unsigned local_frame_counter = 0;
    while (2 > 1) {
        if (raw_bus.size() > 10) {
            for (int i = 0; i < 5; i++) raw_bus.pop();
            std::thread *analyze = new std::thread(analyze_data, raw_bus.front(), local_frame_counter);
            ++local_frame_counter;
            thread_queue.push(analyze);


            /// we can sort the output!
            /// we can create array of compiled frames
            /// nah we cant it wont be nescesery only the
            /// nah thread seed to know when to end their calculation
            /// will simply slow them down a bit (these who are to fast)
            /// we still need to display every frame generated so the fast ones are errors nopt slow ones
        }

    }
}




#endif //EQUALIZER_P_SCHEDULER_H
