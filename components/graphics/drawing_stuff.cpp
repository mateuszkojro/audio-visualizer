//
// Created by piotr233 on 18.04.2021.
//

#include <vector>
#include "drawing_stuff.h"

RGBColor gen_rainbow(unsigned height, unsigned max_height) {
    // sine wave algorithm
    // 3 parts
    // 1 :
    // r = cos(i) , g = sin(i), b =0
    // 2 :
    // r = 0 , g = cos(i), b = sin(x)
    // 3:
    // r = sin(i) , g = 0, b = cos(x)
    // every part is max_height / 3 translates into 0, PI/2

    // so for example in point 1/3 * max_height
    // r = cos(PI/2) = 0, g = sin(PI/2) = 1, b = 0

    char witch_third = height / (max_height / 3);

    double height_in_radians;
    switch (witch_third) {
        case 0:
            height_in_radians = height * M_PI / (max_height / 3) / 2;

            return {cos(height_in_radians) * 255, sin(height_in_radians) * 255, 0};
        case 1:
            height -= max_height / 3;
            height_in_radians = height * M_PI / (max_height / 3) / 2;
            return {0, cos(height_in_radians) * 255, sin(height_in_radians) * 255};

        case 2:
            height -= 2 * max_height / 3;
            height_in_radians = height * M_PI / (max_height / 3) / 2;
            return {sin(height_in_radians) * 255, 0, cos(height_in_radians) * 255};

    }

    return {255, 0, 0};
}


void draw_circle_SDL(SDL_Renderer *renderer, Coord &point, int radius) {

    int x = radius, y = 0;

    // drawing the initial point on the axes
    // after translation

    SDL_RenderDrawPoint(renderer, x + point.x, y + point.y);
    // When radius is zero only a single
    // point will be drawn
    if (radius > 0) {
        SDL_RenderDrawPoint(renderer, x + point.x, -y + point.y);
        SDL_RenderDrawPoint(renderer, y + point.x, x + point.y);
        SDL_RenderDrawPoint(renderer, -y + point.x, x + point.y);

    } else return;

    // Initialising the value of P
    int P = 1 - radius;
    while (x > y) {
        y++;

        // Mid-point is inside or on the perimeter
        if (P <= 0)
            P = P + 2 * y + 1;
            // Mid-point is outside the perimeter
        else {
            x--;
            P = P + 2 * y - 2 * x + 1;
        }

        // All the perimeter points have already been printed
        if (x < y)
            break;

        // Printing the generated point and its reflection
        // in the other octants after translation
        SDL_RenderDrawPoint(renderer, x + point.x, y + point.y);
        SDL_RenderDrawPoint(renderer, -x + point.x, y + point.y);
        SDL_RenderDrawPoint(renderer, x + point.x, -y + point.y);
        SDL_RenderDrawPoint(renderer, -x + point.x, -y + point.y);

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed

        if (x != y) {
            SDL_RenderDrawPoint(renderer, y + point.x, x + point.y);
            SDL_RenderDrawPoint(renderer, -y + point.x, x + point.y);
            SDL_RenderDrawPoint(renderer, y + point.x, -x + point.y);
            SDL_RenderDrawPoint(renderer, -y + point.x, -x + point.y);


        }
    }


}


void draw_point_SDL(SDL_Renderer *renderer, Coord point, RGBColor color, unsigned radius) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    for (int i = 0; i < radius; i++)
        draw_circle_SDL(renderer, point, i);

}


void draw_number(SDL_Renderer *renderer, char number, char scale, RGBColor color, Coord position) {

    std::array<bool, (4 * 7)> pixel_array{};

    switch (number) {
        case 0:
            pixel_array = {false, true, true, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, false, false, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, true, true, false};
            break;
        case 1:
            pixel_array = {false, false, false, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false};
            break;
        case 2:
            pixel_array = {false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, true, true, false,
                           true, false, false, false,
                           true, false, false, false,
                           false, true, true, false};
            break;
        case 3:
            pixel_array = {false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, true, true, false};
            break;
        case 4:
            pixel_array = {false, false, false, false,
                           true, false, false, true,
                           true, false, false, true,
                           true, false, false, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false};
            break;
        case 5:
            pixel_array = {false, true, true, false,
                           true, false, false, false,
                           true, false, false, false,
                           false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, true, true, false};
            break;
        case 6:
            pixel_array = {false, false, false, false,
                           true, false, false, false,
                           true, false, false, false,
                           false, true, true, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, true, true, false};
            break;
        case 7:
            pixel_array = {false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false};
            break;
        case 8:
            pixel_array = {false, true, true, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, true, true, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, true, true, false};
            break;
        case 9:
            pixel_array = {false, true, true, false,
                           true, false, false, true,
                           true, false, false, true,
                           false, true, true, false,
                           false, false, false, true,
                           false, false, false, true,
                           false, false, false, false};
            break;


    }

    std::vector<Coord> akcual_pixels;
    for (int i = 0; i < 4 * 7; i++)
        if (pixel_array[i])
            akcual_pixels.emplace_back((position.x + 28 / 4) * scale, (position.y + 28 % 4)*scale);

for(auto i:akcual_pixels){
    for(int x=0;x<scale;x++){
        for(int y=0;y<scale;y++){

            SDL_RenderDrawPoint(renderer, i.x+x, i.y+y);

        }
    }

}

}
