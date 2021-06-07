//
// Created by pc on 30.04.2021.
//

#include <string>
#include <fstream>
#include "Canvas.h"
#include "ppm_loader/file_exception.h"

exception::invalid_file_format_exception invalid_file_format;
exception::invalid_character_exception invalid_character;

exception::bad_dimensions_exception bad_dimensions;
exception::invalid_path_exception invalid_path;


exception::not_implemented_file_format_exception not_implemented_file_format;


Canvas::Canvas(size_t width, size_t height) {
    w_ = width;
    h_ = height;
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = RGBColor(255, 0, 0);
}

Canvas::Canvas(const Canvas &other) {
    pixels_ = new RGBColor[other.w_ * other.h_];
    w_ = other.w_;
    h_ = other.h_;
    for (int i = 0; i < w_ * h_; ++i)
        pixels_[i] = other.pixels_[i];

}

Canvas::Canvas(size_t width, size_t height, RGBColor fill_color) : w_(width), h_(height), primary_color(fill_color) {
    pixels_ = new RGBColor[w_ * h_];
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}
// fixme somewhere x and y are mixed up

void Canvas::fill(RGBColor fill_color) {
    for (int i = 0; i < w_ * h_; ++i)pixels_[i] = fill_color;

}

void Canvas::clear() {
    for (int i = 0; i < w_ * h_; ++i) pixels_[i] = RGBColor();

}

void Canvas::set_pixel(Coord position, RGBColor color) {
    if (position.y >= h_ || position.y < 0 || position.x >= w_ || position.x < 0)
        return;
    if (color.a_ != 255) return;
    pixels_[position.toUint(w_)] = color;

}


RGBColor &Canvas::operator[](size_t position) {
    return pixels_[position];
}

RGBColor *Canvas::get_pixel_ptr() { return pixels_; }

int Canvas::pitch() const { return (int) w_ * 4; }

void Canvas::set_primary_color(RGBColor color) {
    primary_color = color;
}

RGBColor &Canvas::get_pixel(Coord position) {

    return pixels_[position.toUint(w_)];
}

void Canvas::draw_circle(Coord center, unsigned int radius, RGBColor circle_color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        set_pixel({ center.y + y,center.x + x}, circle_color);
        set_pixel({ center.y + x,center.x + y}, circle_color);
        set_pixel({ center.y + x,center.x - y}, circle_color);
        set_pixel({ center.y + y,center.x - x}, circle_color);
        set_pixel({ center.y - y,center.x - x}, circle_color);
        set_pixel({ center.y - x,center.x - y}, circle_color);
        set_pixel({ center.y - x,center.x + y}, circle_color);
        set_pixel({ center.y - y,center.x + x}, circle_color);

        if (err <= 0) {
            ++y;
            err += 2 * y + 1;
        } else {
            --x;
            err -= 2 * x + 1;
        }

    }
}

void Canvas::draw_point(Coord center, unsigned int radius, RGBColor point_color) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, point_color);
}

void Canvas::draw_point(Coord center, unsigned int radius) {
    for (int i = 0; i < radius; i++)
        draw_circle(center, i, primary_color);
}

void Canvas::draw_circle(Coord center, unsigned int radius) {
    draw_circle(center, radius, primary_color);
}

const RGBColor Canvas::get_pixel_copy(Coord position) const {
    return pixels_[position.toUint(w_)];
}

void Canvas::draw_button(const Canvas &butt, Coord left_top_corner) {
    for (int y = 0; y < butt.h_; y++) {
        for (int x = 0; x < butt.w_; x++) {

            set_pixel({left_top_corner.y + y, left_top_corner.x + x}, butt.get_pixel_copy({y, x}));

        }
    }


}

bool is_comment(const char &letter) { return letter == '#'; }


void ignore_comment(std::fstream &plik) {

    std::string comment;
    std::getline(plik, comment, '\n');

}


void handle_char(std::fstream &plik) {
    char letter;

    plik.clear(plik.goodbit);

    plik >> letter; // ponownie wczytuje znak

    if (is_comment(letter)) ignore_comment(plik);
    else {

        throw invalid_character;
        //napotkano nioczekiwany symbol
    }


}


int read_number(std::fstream &plik) {
    int number;
    do {
        plik >> number;
        if (plik.fail()) handle_char(plik); // obiekt fstream gdy napotka nielegalny symbol wystawia blad
            //wiecej informacji : https://www.cplusplus.com/reference/ios/ios/rdstate/
        else return number;

    } while (!plik.eof());
    throw invalid_file_format;
//plik nie posiada liczb albo ma ich za malo

}

unsigned char check_color(int color) {
    if (color < 0 || color > (int) 256) {
        throw invalid_file_format;
    } else return (unsigned char) color;


}

void read_header(std::fstream &plik) {
    char letter;
    do {

        plik >> letter;
        if (is_comment(letter)) ignore_comment(plik);// w przypadu gdy napotkamy '#' czyli poczatek komentarza

        else if (letter == 'P') {
            plik >> letter;
            if (letter == '3') return;

            else
                //napotkano nioczekiwany symbol
                throw invalid_character;

        }
    } while (!plik.eof());
    throw invalid_file_format;
// nie znaleziono naglowka pliku

}

void Canvas::load_from_PPM(std::string path) {

    std::fstream plik;
    plik.open(path, std::ios::in);
    int image_width, image_height;
    if (plik.good()) {

        read_header(plik);

        image_width = read_number(plik);

        if (image_width != w_) { throw bad_dimensions; }

        image_height = read_number(plik);

        if (image_height != h_) { throw bad_dimensions; }

        int max_color = read_number(plik);

        if (max_color < 0 || max_color > 255) { throw bad_dimensions; }

        size_t array_size = image_height * image_width; // tymczasowa  zmienna

        if (!pixels_) delete[] pixels_; // jeżeli obraz posiada już dane
        pixels_ = new RGBColor[w_ * h_];


        for (unsigned i = 0; i < array_size; i++) {

            if (plik.eof()) { throw bad_dimensions; } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

            unsigned char R = check_color(read_number(plik));

            if (plik.eof()) { throw bad_dimensions; } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

            unsigned char G = check_color(read_number(plik));

            if (plik.eof()) { throw bad_dimensions; } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

            unsigned char B = check_color(read_number(plik));

            if (R == 0 && G == 0 && B == 0) pixels_[i] = {R, G, B, 0};
           else  pixels_[i] = {R, G, B};//dodaje pobrany kolor do tablicy

        }


    } else {
        // nie znaleziono pliku pod podanym adresem lub napodkano problem z odczytaniem danych z niego
        //wiecej pod adresem: https://en.cppreference.com/w/cpp/io/basic_ios/good

        throw invalid_path;
    }

}

Canvas::Canvas(std::string path, size_t width, size_t height) {
    w_ = width;
    h_ = height;

    load_from_PPM(path);

}

size_t Canvas::getW() const {
    return w_;
}

size_t Canvas::getH() const {
    return h_;
}