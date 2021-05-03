//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_P_SCHEDULER_H
#define EQUALIZER_P_SCHEDULER_H

#include <queue>
#include <thread>
#include <map>

unsigned abs(unsigned x, unsigned y) {
    if (x < y) return y - x;
    else return x - y;
}

void stop_until(const bool *condition) {
    while (*condition)
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

}


struct raw_frame {
    raw_frame(unsigned id, std::vector<int> *data) : frame_id(id), raw_data(data) {}

    std::vector<int> *raw_data;
    unsigned frame_id; // the frame when data was created
    ~raw_frame() {
        delete raw_data;
    }
};

struct analyzed_frame {
    analyzed_frame(unsigned id, canvas *data) : frame_id(id), analyzed_data(data) {}

    canvas *analyzed_data;
    unsigned frame_id; // the frame when data was created
    ~analyzed_frame() {
        delete analyzed_data;
    }
};

std::queue<std::vector<int> *> raw_bus;
std::queue<canvas *> analyzed_bus;


void main_gen_data() {

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
        raw_bus.push(frame_counter, data_ptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}


int find_id(std::vector<raw_frame> &data, int id) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].frame_id == id) return i;
    }
}

int find_id(std::vector<analyzed_frame> &data, int id) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].frame_id == id) return i;
    }
}
void analyze_data(std::vector<int> *input) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //dummy code
    auto output = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, RBGColor(input[0], 0, 0));
    analyzed_bus.push(output);
    delete input;

}

void main_analyze_data() {
    std::queue<std::thread> thread_queue;
    canvas *output;
    while (2 > 1) {
        if (raw_bus.size() > 10) {
            for (int i = 0; i < 5; i++) raw_bus.pop();
            thread_queue.push((analyze_data, raw_bus.pop()));
        }


    }
}



#endif //EQUALIZER_P_SCHEDULER_H
