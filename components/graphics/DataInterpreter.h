//
// Created by pc on 22.04.2021.
//

#ifndef EQUALIZER_DATAINTERPRETER_H
#define EQUALIZER_DATAINTERPRETER_H
#include <vector>
#include<iostream>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

class DataInterpreter {
public:
    virtual void add_effect(std::vector<int>& data) =0 ;
};

class simple_graph:public DataInterpreter{
public:
    void add_effect(std::vector<int>& data){
        for (int &i:data) i = WINDOW_HEIGHT - i;
    }
};


#endif //EQUALIZER_DATAINTERPRETER_H
