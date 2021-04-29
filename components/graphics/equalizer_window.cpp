//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"
#include "drawing_stuff.h"
#include "FPS_Counter.h"

std::vector<Coord> gen_function_between_points(Coord begin, Coord end) {

    std::vector<Coord> generated_function;
    Coord mid_point = {(begin.x + end.x) / 2, (begin.y + end.y) / 2};

    // a cos( x ) + d

    double a;
    a = begin.y > end.y ? begin.y - end.y : end.y - begin.y;
    a /= 2;
    int max_value /* distance between two points in x axis*/ = ((end.x) - begin.x);

    double d = mid_point.y;
    if (begin.y > end.y) {

        a *= -1;

    }
    if ((begin.x / max_value) % 2 == 0) {
        a *= -1;
    }


    for (double i = begin.x; i <= end.x; i += 1) {

        double radian = i / max_value;

        radian *= M_PI;

        generated_function.emplace_back((int) i,
                                        (int) (a * cos(radian) + d));
    }
    return generated_function;

}


std::vector<Coord> create_points(int begin, int end, std::vector<int> &values_to_be_drown) {


    // distance between two point's in x axis
    int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() + 1);

    std::vector<Coord> dot_coordinates;
    // dot_coordinates.reserve(values_to_be_drown.size() + 2);

    dot_coordinates.emplace_back(0, begin);

    for (int i = 0; i < values_to_be_drown.size(); i++)
        dot_coordinates.emplace_back(x_shift * (i + 1), values_to_be_drown[i]);

    // to make sure that the last point is pixel perfect on the edge
    dot_coordinates.emplace_back(WINDOW_WIDTH, end);


    return dot_coordinates;

}

std::vector<Coord> create_points(std::vector<int> &values_to_be_drown) {

    // distance between two point's in x axis
    int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() - 1);

    std::vector<Coord> dot_coordinates;


    for (int i = 0; i < values_to_be_drown.size(); i++)
        dot_coordinates.emplace_back(x_shift * i, values_to_be_drown[i]);

    return dot_coordinates;
}


void gen_new_frame(SDL_Renderer *renderer, std::vector<int> &local_values) {


    std::vector<Coord> p_positions; // this i thing can be static


    // flipped all values, to make them appear from the bottom of window rather than on top

    for (int &i:local_values) i = WINDOW_HEIGHT - i;

    p_positions = create_points(local_values);


    for (unsigned i = 0; i < p_positions.size() - 1; ++i) {
        auto function_between_points = gen_function_between_points(p_positions[i], p_positions[i + 1]);
        for (auto j:function_between_points) {
            draw_point_SDL(renderer, j, gen_rainbow(j.y, WINDOW_HEIGHT), 3);
        }
    }

    for (auto j:p_positions)
        draw_point_SDL(renderer, j, gen_rainbow(j.y, WINDOW_HEIGHT), 6);


}


void equalizer_window(SDL_Surface *surface, std::vector<int> *values_to_be_drown) {
    SDL_Renderer *renderer;
    SDL_Window *window;

/// todo current problem faced is taht we have to have  only one renderer per window
/// or more precisely one window pre renderer, so we can easyly swap renderers
/// what we could do
/// is use plane or what's it called, but than we ware 30 x slower <- this sucks
/// coz we need to copy plane to renderer before frame generation


    //   SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    window = SDL_CreateWindow(
            "lele",                  // window title
            SDL_WINDOWPOS_UNDEFINED_MASK,           // initial x position
            SDL_WINDOWPOS_UNDEFINED_MASK,           // initial y position
            WINDOW_WIDTH,                               // width, in pixels
            WINDOW_HEIGHT,                               // height, in pixels
            SDL_WINDOW_BORDERLESS                // flags - see below
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer); // starting line

    auto time_start = std::chrono::steady_clock::now();

    // create fps counter
    FPS_Counter counter(renderer, {WINDOW_WIDTH - 100, 0});



    while (true) { // main loop
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) break;
        }


        {

            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds


            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(16 -
                                              std::chrono::duration_cast<std::chrono::milliseconds>(time_dif).count()));

            time_start = std::chrono::steady_clock::now();

            std::vector<int> local_values = *values_to_be_drown;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer); // clear last frame

            gen_new_frame(renderer, local_values);
            //draw_line_between_points(renderer, {0,0},{450,300}, {255,0,0},45);

          //  counter.draw();

            renderer = SDL_CreateSoftwareRenderer(surface);
            SDL_RenderPresent(renderer); // update screen
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}