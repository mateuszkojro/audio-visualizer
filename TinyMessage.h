//
// Created by studio25 on 10.06.2021.
//

#ifndef EQUALIZER_TINYMESSAGE_H
#define EQUALIZER_TINYMESSAGE_H

extern "C" {
#include "tinyfiledialogs/tinyfiledialogs.h"
}
class Tiny {
public:
  static  void error_popup(const std::string &title) {
        tinyfd_messageBox(title.c_str(), SDL_GetError(), "error", "error", 0);
    }

    static  std::string open_file_dialog() {

        char const *lFilterPatterns[] = {"*.wav"};
        auto file_name = tinyfd_openFileDialog(
                "Open audio file ",
                "",
                1,
                lFilterPatterns,
                NULL,
                false);
        std::cout << file_name << std::endl;
        return file_name;
    }
};
#endif //EQUALIZER_TINYMESSAGE_H
