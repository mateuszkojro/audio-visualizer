//
// Created by mateu on 4/22/2021.
//

#ifndef EQUALIZER_ACTION_H
#define EQUALIZER_ACTION_H

#include "DataFrame.h"

class Action {
public:
    virtual operator(DataFrame& data) = 0;
};


#endif //EQUALIZER_ACTION_H
