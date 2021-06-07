//
// Created by studio25 on 07.06.2021.
//

#ifndef EQUALIZER_PSTATE_BUTTON_H
#define EQUALIZER_PSTATE_BUTTON_H
#include "Button.h"
#include <vector>
class PState_Button :public Button{
    public:
    PState_Button(size_t px, size_t py, size_t w, size_t h): Button(px,py,w,h), state(0){};

    int State(){ return  state;};

protected:
    int state;
    std::vector<Canvas> image;
};


#endif //EQUALIZER_PSTATE_BUTTON_H
