//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER__TINY_MESSAGE_H_
#define EQUALIZER__TINY_MESSAGE_H_

extern "C" {
#include "tinyfiledialogs/tinyfiledialogs.h"
}
class Tiny {
public:
  static void ErrorPopup(const std::string &title) {
    tinyfd_messageBox(title.c_str(), SDL_GetError(), "error", "error", 0);
  }

  static std::string OpenFileDialog() {

    char const *l_filter_patterns[] = {"*.wav"};
    auto file_name = tinyfd_openFileDialog("Open audio file ", "", 1,
                                           l_filter_patterns, NULL, false);
    std::cout << file_name << std::endl;
    return file_name;
  }
};
#endif // EQUALIZER__TINY_MESSAGE_H_
