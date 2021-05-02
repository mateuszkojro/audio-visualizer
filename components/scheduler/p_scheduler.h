//
// Created by pc on 30.04.2021.
//

#ifndef EQUALIZER_P_SCHEDULER_H
#define EQUALIZER_P_SCHEDULER_H

#include <thread>
#include <map>


void add_to_pile(std::map<unsigned, std::vector<int> *> &pile, unsigned int current_nr, std::vector<int> *data_ptr) {
    auto search = pile.find(0);

    if (search != pile.end())
        pile.erase(0);
    pile.insert(std::pair(current_nr, data_ptr));
}

std::vector<int> *get_from_pile(std::map<unsigned, std::vector<int> *> &pile, unsigned current_nr) {




    unsigned zero = 0;
    auto search = pile.find(current_nr);
    search->first = &zero;

    return search->second;
}
void delete_from_pile(std::map<unsigned, std::vector<int> *> &pile, unsigned current_nr) {

    pile.erase(current_nr);
}

std::vector<double> velocity_and_direction;
int number_of_points = 5;

void init_velocity_and_direction() {
    for (int i = 0; i < number_of_points; i++) {
        velocity_and_direction.push_back(rand() % 10 - 5); // to make it pretty
        // we generate paths and let points follow them with different speeds
    }
}


void stop_until(const bool *condition) {
    while (*condition)
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

}

void analyze_data(std::vector<int> *data_ptr, std::map<unsigned, canvas *> &display_pile) {

    std::this_thread::sleep_for(std::chrono::seconds(1));

}




    unsigned raw_frame = 1;     // witch frame is being analyzed right now
    unsigned display_frame = 1; // witch frame is being displayed
    std::map<unsigned, std::vector<int> *> raw_pile;
    std::map<unsigned, canvas *> display_pile;
void main_gen_data(bool *data_ready) {

    bool stop_generating_data = false;

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
    std::vector<int> *data_ptr;
    while (2 > 1) {
        data_ptr = new std::vector<int>();
        for (int i = 0; i < number_of_points; ++i) data_ptr->push_back(rand() % 500);
        raw_frame-display_frame >
        if(display_frameraw_frame) std::this_thread::sleep_for(std::chrono::seconds(1));
        void add_to_pile(raw_pile, current_nr, data_ptr);

    }
}

#endif //EQUALIZER_P_SCHEDULER_H
