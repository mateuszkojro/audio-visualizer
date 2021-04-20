//
// Created by studio25 on 14.04.2021.
//

#include "drawing_stuff.h"


rgb_color gen_rainbow(unsigned height, unsigned max_height) {
    // sine wave algorythm
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
            height_in_radians = height * PI / (max_height / 3) / 2;

            return {cos(height_in_radians) * 255, sin(height_in_radians) * 255, 0};
        case 1:
            height -= max_height / 3;
            height_in_radians = height * PI / (max_height / 3) / 2;
            return {0, cos(height_in_radians) * 255, sin(height_in_radians) * 255};

        case 2:
            height -= 2 * max_height / 3;
            height_in_radians = height * PI / (max_height / 3) / 2;
            return {sin(height_in_radians) * 255, 0, cos(height_in_radians) * 255};

    }

return {255,0,0};
}
void draw_circle(SDL_Renderer *renderer, cord &point, int R){

    // following (x+a)^2 + (y+b)^2 = r^2
    //

    int x = point.x - R - 1; // tweleve'o clock
                             // -1 is there to stay true to the rule
                             // basically point is a circle with R = 1
                             // so the dot is made at point
                             // soo we subtract 1 because R.. ehh you get it
    int y = point.y;

    for(int i=0;i<R*R;i++){
        SDL_RenderDrawPoint(renderer, point.x-cos(PI/(2*R)), y-sin(PI/(2*R)));
    }





}

void draw_point(SDL_Renderer *renderer, cord point) {
    //set color
    rgb_color current_pixel_color = gen_rainbow(point.y, WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(renderer, current_pixel_color.r, current_pixel_color.g,
                           current_pixel_color.b, 255);
    //center
    SDL_RenderDrawPoint(renderer, point.x, point.y);
    // up
    SDL_RenderDrawPoint(renderer, point.x, point.y - 2);
    SDL_RenderDrawPoint(renderer, point.x, point.y - 1);

    //down
    SDL_RenderDrawPoint(renderer, point.x, point.y + 1);
    SDL_RenderDrawPoint(renderer, point.x, point.y + 2);
    // left
    SDL_RenderDrawPoint(renderer, point.x - 2, point.y);
    SDL_RenderDrawPoint(renderer, point.x - 1, point.y);
    //right
    SDL_RenderDrawPoint(renderer, point.x + 1, point.y);
    SDL_RenderDrawPoint(renderer, point.x + 2, point.y);
    // corners
    SDL_RenderDrawPoint(renderer, point.x - 1, point.y - 1);
    SDL_RenderDrawPoint(renderer, point.x - 1, point.y + 1);
    SDL_RenderDrawPoint(renderer, point.x + 1, point.y + 1);
    SDL_RenderDrawPoint(renderer, point.x + 1, point.y - 1);

}

void draw_big_point(SDL_Renderer *renderer, cord &point, int r) {
    //set color
    rgb_color current_pixel_color = gen_rainbow(point.y, WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(renderer, current_pixel_color.r, current_pixel_color.g,
                           current_pixel_color.b, 255);
    //center
    SDL_RenderDrawPoint(renderer, point.x, point.y);
    for (int i = 1; i <= r; i++) {
        // up

        SDL_RenderDrawPoint(renderer, point.x, point.y - i);

        //down

        SDL_RenderDrawPoint(renderer, point.x, point.y + i);

        // left

        SDL_RenderDrawPoint(renderer, point.x - i, point.y);

        //right

        SDL_RenderDrawPoint(renderer, point.x + i, point.y);
    }
    // corners
    for (int i = 1; i <= r / 2; i++) {
        SDL_RenderDrawPoint(renderer, point.x - i, point.y - i);
        SDL_RenderDrawPoint(renderer, point.x - i, point.y + i);
        SDL_RenderDrawPoint(renderer, point.x + i, point.y + i);
        SDL_RenderDrawPoint(renderer, point.x + i, point.y - i);
    }
}

