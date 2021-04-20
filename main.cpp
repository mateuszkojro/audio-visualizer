//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <vector>
#include <SDL.h>
#include "drawing_stuff.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415


std::vector<double> gen_function_between_points(cord begin, cord end) {

    std::vector<double> function;
    cord mid_point = {begin.x + end.x / 2, begin.y + end.y / 2};


    // soo
    // polynomial takes form ax^3+bx^2+cx+d
    // but actually we need shape closer to ax^3+bx+d
    // right now we can declare b coz it's always 0
    // d is simply shift up or down for whole function,
    // and since mid_point is in the middle we  can move function up or down to midpoint
    // so d = midpoint.y

    // what's left is a and c
    // and we still have two point's to make system of equations
    // with two equations and two unknowns simple!
    //
    function.push_back(0);                  // a <- for now just to keep vector at bay
    function.push_back(0);                  // b
    function.push_back(0);                  // c <- for now just to keep vector at bay
    function.push_back(end.y);        // d




   // function[0] = (begin.x * end.y - begin.y * end.x) / (begin.x * end.x) * (end.x * end.x - begin.x * begin.x); // a
   // function[2] = (begin.y - pow((function[3] * begin.x), 3)) / begin.x; // c



    return function;
}


cord solve_for(std::vector<double> &letters, int x) {

    return cord(x, (int) (x * x * x * letters[0] + x * x * letters[1] + x * letters[2] + letters[3]));

}

enum key_pressed {
    up,
    down,
    left,
    right,
    space,
    none

};


/// creates even spaced (on x axis) dot's from given y values
///\param values_to_be_drown vector of values tah will end up as y values in returned coordinates
///\param begin height on witch leftmost point will be, this point is only to make function look nice
///\param end height on witch rightmost point will be, this point is only to make function look nice
///\return vector of point's that will be represented as  "big dots"
std::vector<cord> create_points(int begin, int end, std::vector<int> &values_to_be_drown) {


    // distance between two point's in x axis
    int x_shift = WINDOW_WIDTH / (values_to_be_drown.size()+1);

    std::vector<cord> dot_coordinates;
    // dot_coordinates.reserve(values_to_be_drown.size() + 2);

    dot_coordinates.emplace_back(0, begin);

    for (int i = 0; i < values_to_be_drown.size(); i++)
        dot_coordinates.emplace_back(x_shift * (i + 1), values_to_be_drown[i]);

    // to make sure that the last point is pixel perfect on the edge
    dot_coordinates.emplace_back( WINDOW_WIDTH-1, end);


    return dot_coordinates;

}
/// \param values_to_be_drown vector containing y values of the point's tah will be drawn on the screen,
/// important thing all values must be in range <0;WINDOW_HEIGHT)
void window_with_line(std::vector<int> *values_to_be_drown) {

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer); // starting line

    auto time_start = std::chrono::steady_clock::now();


    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds


            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s
            std::this_thread::sleep_for(std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(time_dif).count()));
            time_start = std::chrono::steady_clock::now();


                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer); // clear last frame

                //creates new set of point's
                std::vector<cord> p_positions = create_points(WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2, *values_to_be_drown);

               // auto  funct = gen_function_between_points(p_positions[1],p_positions[2]);
/*
                for(int j = p_positions[1].x; j < p_positions[2].x; j++) {
                    gen_rainbow(solve_for(funct,j).y, WINDOW_HEIGHT); // set colour
                    std::cout<<solve_for(funct,j).x<<"\t"<<solve_for(funct,j).y<<"\n";
                    draw_point(renderer,solve_for(funct,j));
                }

*/
                    for (unsigned  i=0;i<p_positions.size()-1;++i) {

                        draw_big_point(renderer, p_positions[i], 6);

                    auto funct = gen_function_between_points(p_positions[i],p_positions[i+1]);

                    for(int j = p_positions[i].x; j < p_positions[i+1].x; j++) {
                        gen_rainbow(solve_for(funct,j).y, WINDOW_HEIGHT); // set colour
                        draw_point(renderer,solve_for(funct,j));
                    }

                }

                // TODO TEST THE GEN_FUNCTION
                // TODO DRAW IT
                SDL_RenderPresent(renderer);

        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

std::mutex mtx;
int main(int argc, char *argv[]) {
srand(time(NULL));
    std::vector<int> data;
    for(int i=0;i<40;i++){
        data.push_back(rand()%WINDOW_HEIGHT);
    }

    std::thread window(window_with_line, &data);
    int frame =0 ;

    while(1) {
       // mtx.lock();
        for (int i = 0; i < data.size(); i++) {
            data[i] += i/5 +1 ;
            if(data[i]>=WINDOW_HEIGHT) data[i] = 0;

        }
      //  mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }

    window.join();
    return 0;
}