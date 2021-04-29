//
// Created by pc on 23.04.2021.
//


#include  "SDL.h"

#include <mutex>
#include <chrono>
#include <vector>
#include <iostream>
#include <thread>

#define BYTE *8
// this well be used by time measurement equipment
std::chrono::time_point<std::chrono::system_clock> t1, t2;

#define START_CLOCK t1 = std::chrono::system_clock::now();
#define STOP_CLOCK  t2 = std::chrono::system_clock::now();
#define SHOW_TIME  std::cout << "Elapsed time in microseconds: " \
                             << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() \
                             << " µs" << std::endl; std::cout << "Elapsed time in milliseconds: "\
                             << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() \
                             << " ms" << std::endl;


struct RGBColor {

    RGBColor() : r_(0), g_(0), b_(0), a_(0) {}

    RGBColor(int r, int g, int b, int a) :
            r_(r), g_(g), b_(b), a_(a) {}

    RGBColor(int r, int g, int b) : r_(r), g_(g), b_(b), a_(255) {}

    RGBColor(const RGBColor &other) = default;

    RGBColor &operator=(const RGBColor &other) = default;

    Uint8 r_;
    Uint8 g_;
    Uint8 b_;
    Uint8 a_;


    explicit operator int() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }

    explicit operator size_t() const { return ((r_ << 24) + (g_ << 16) + (b_ << 8) + a_); }


};


class canvas {
public:
    canvas() = delete;

    canvas(const canvas &other) = delete;

    canvas(size_t width, size_t height) {
        w_ = width;
        h_ = height;
        pixels_ = new RGBColor[w_ * h_];
    }

    canvas(size_t width, size_t height, RGBColor fill_color) : w_(width), h_(height) {
        pixels_ = new RGBColor[w_ * h_];
        memset(pixels_, (int) fill_color, w_ * h_ * sizeof(RGBColor));
    }

    void fill(RGBColor fill_color) {
        memset(pixels_, (int) fill_color, w_ * h_ * sizeof(RGBColor));
    }

    void clear() {
        memset(pixels_, 0, w_ * h_ * sizeof(RGBColor));
    }

    void set_pixel(size_t x, size_t y, RGBColor color) {
        pixels_[x * w_ + y] = color;
    }

    RGBColor &get_pixel(size_t x, size_t y) {
        return pixels_[x * w_ + y];
    }

    RGBColor &operator[](size_t position) {
        return pixels_[position];

    }


    RGBColor *get_pixel_ptr() { return pixels_; }

    size_t pitch() { return w_ * sizeof(RGBColor); }

protected:

    /// actual pixel array
    RGBColor *pixels_;
    /// width of a canvas
    size_t w_;
    /// height of a canvas
    size_t h_;

};

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer *renderer;
    SDL_Window *window;

    canvas surface(1280, 720, {255, 0, 0});


    window = SDL_CreateWindow(
            "lele",                  // window title
            0,           // initial x position
            0,           // initial y position
            1280,                               // width, in pixels
            720,                               // height, in pixels
            SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL               // flags - see below
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_TARGET,
                                             1280,
                                             720);


    double counter = 0;
    for (int i = 0; i < 1920; i++) {
        t1 = std::chrono::system_clock::now();

        SDL_UpdateTexture(texture, NULL, surface.get_pixel_ptr(), surface.pitch());

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);

        t2 = std::chrono::system_clock::now();

        counter += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    }

    std::cout << counter / 1920;

    std::this_thread::sleep_for(std::chrono::seconds(2));


    //SDL_FreeSurface(surface);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}