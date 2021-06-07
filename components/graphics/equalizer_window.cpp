//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"
#include "Buttons/Button.h"


std::vector<Coord> gen_function_between_points(Coord begin, Coord end) {

    std::vector<Coord> generated_function;
    Coord mid_point = {(begin.y + end.y) / 2, (begin.x + end.x) / 2};


    /// like in polynomial function a
    double a;
    a = begin.y > end.y ? begin.y - end.y : end.y - begin.y;
    a /= 2;
    int max_value /* distance between two points in x axis*/ = (end.x - begin.x);

    if (max_value == 0) {

        return {begin};
    }

    double d = mid_point.y;
    if (begin.y > end.y) {

        a *= -1;

    }
    if ((begin.x / max_value) % 2 == 0) {
        a *= -1;
    }


    for (double i = begin.x; i <= end.x; ++i) {

        double radian = i / max_value;

        radian *= M_PI;

        generated_function.emplace_back(
                (int) (a * cos(radian) + d), (int) i);
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
        dot_coordinates.emplace_back(values_to_be_drown[i], x_shift * i);

    return dot_coordinates;
}


void draw_function(Canvas &surface, std::vector<int> local_values, bool draw_big_points, bool static_color,
                   bool connect_window_edges) {

    std::vector<Coord> p_positions; // this i thing can be static

    /// flipped all values, to make them appear from the bottom of window rather than on top
    for (int &i:local_values)
        i = WINDOW_HEIGHT - i;

    p_positions = create_points(local_values);

    for (int i = 0; i < p_positions.size() - 1; ++i) {

        std::vector<Coord> function_between_points = gen_function_between_points(p_positions[i], p_positions[i + 1]);

        for (Coord &j:function_between_points) {
            if (!static_color) surface.draw_point(j, 3, gen_rainbow(j.y, WINDOW_HEIGHT));
            else surface.draw_point(j, 3);

        }

    }

    if (draw_big_points)
        for (auto j:p_positions)
            surface.draw_point(j, 6, gen_rainbow(j.y, WINDOW_HEIGHT));

}


void
draw_function_but_fill_it_below(Canvas &surface, std::vector<int> local_values, bool draw_big_points, bool static_color,
                                bool connect_window_edges) {

    std::vector<Coord> p_positions; // this i thing can be static

    // flipped all values, to make them appear from the bottom of window rather than on top

    for (int &i:local_values) i = WINDOW_HEIGHT - i;

    p_positions = create_points(local_values);


    for (unsigned i = 0; i < p_positions.size() - 1; ++i) {

        auto function_between_points = gen_function_between_points(p_positions[i], p_positions[i + 1]);

        for (auto j:function_between_points) {

            if (!static_color) surface.draw_point(j, 3, gen_rainbow(j.y, WINDOW_HEIGHT));
            else surface.draw_point(j, 3);

            for (int k = j.x; k >= 0; k--) {

                if (!static_color)surface.draw_point({j.y, k}, 1, gen_rainbow(k, WINDOW_HEIGHT));
                else surface.draw_point({j.y, k}, 1);

            }
        }
    }

    if (draw_big_points)
        for (auto j:p_positions)
            surface.draw_point(j, 6, gen_rainbow(j.y, WINDOW_HEIGHT));

}

void draw_levels(Canvas &surface, std::vector<int> local_values, bool draw_big_points, bool static_color) {


    int x_shift = WINDOW_WIDTH / (local_values.size() + 1);
    for (int &i:local_values) i = WINDOW_HEIGHT - i;

    const std::vector<Coord> p_positions = create_points(local_values);

    for (int j = 0; j < p_positions.size(); j++) {
        for (int i = 0; i < x_shift; ++i) {

            surface.draw_point({i + x_shift * p_positions[j].y, p_positions[j].x}, 3,
                               gen_rainbow(p_positions[j].y, WINDOW_HEIGHT));

        }
    }


    if (draw_big_points)
        for (auto j:p_positions)
            surface.draw_point(j, 6, gen_rainbow(j.y, WINDOW_HEIGHT));

}

extern std::queue<frame> analyzed_bus;

void equalizer_window(Canvas *surface, std::mutex &surface_guard, std::vector<Button> &button_vector) {


    SDL_Window *window = SDL_CreateWindow(
            "lele",                  // window title
            100,           // initial x position
            100,           // initial y position
            WINDOW_WIDTH,                               // width, in pixels
            WINDOW_HEIGHT,                               // height, in pixels
            SDL_WINDOW_OPENGL                // flags - see below
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_TARGET,
                                             WINDOW_WIDTH,
                                             WINDOW_HEIGHT);


    SDL_Event event;
    auto time_start = std::chrono::steady_clock::now();


    while (true) { // main loop
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) break;
            if (event.type == SDL_MOUSEBUTTONUP) {
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                std::cout << "x: " << x << " y:  " << y;
                for (int i = 0; i < button_vector.size(); i++)
                    if (button_vector[i].detect_press({y, x})) std::cout << "   button id:  " << i;
                std::cout << "\n";
            }
        }

        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds


            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(
                            time_dif).count()));

            time_start = std::chrono::steady_clock::now();
            {
                std::lock_guard<std::mutex> guard(surface_guard);
                SDL_UpdateTexture(texture, NULL, surface->get_pixel_ptr(), surface->pitch());

            }
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);


        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void equalizer_window_from_data(FourierConfig *data) {
    SDL_Window *window = SDL_CreateWindow(
            "lele",                  // window title
            100,           // initial x position
            100,           // initial y position
            WINDOW_WIDTH,                               // width, in pixels
            WINDOW_HEIGHT,                               // height, in pixels
            SDL_WINDOW_OPENGL                // flags - see below
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_TARGET,
                                             WINDOW_WIDTH,
                                             WINDOW_HEIGHT);

    /// buttons :
    SDL_Event event;


    std::vector<Button> butt_vec;
    ///fixmy in button for some reason height and width are flipped

    Canvas back_canvas("..\\components\\graphics\\assets\\10backward.ppm",
                       40, 35);

    Button backward(0, WINDOW_HEIGHT - 35, back_canvas);

    Canvas play_canvas("..\\components\\graphics\\assets\\start.ppm", 40,
                       35);

    Button play(40, WINDOW_HEIGHT - 35, play_canvas);

    Canvas forward_canvas(
            "..\\components\\graphics\\assets\\10forward.ppm", 40, 35);
    Button forward(80, WINDOW_HEIGHT - 35, forward_canvas);

    Canvas forward_canvas2(
            "..\\components\\graphics\\assets\\10forward.ppm", 40, 35);
    Button forward2(120, WINDOW_HEIGHT - 35, forward_canvas2);


    butt_vec.push_back(backward);
    butt_vec.push_back(play);
    butt_vec.push_back(forward);
    butt_vec.push_back(forward2);


    auto time_start = std::chrono::steady_clock::now();

    Canvas *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});
    Coord mouse_position = {0, 0};

    while (true) { // main loop
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) break;

            if (event.type == SDL_MOUSEMOTION) {

                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

                std::string title = std::to_string(mouse_position.x) + " x ";
                title += std::to_string(mouse_position.y) + " y ";
                SDL_SetWindowTitle(window, title.c_str());

            }

        }

        {

            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds

            surface->fill({0, 0, 0});
            draw_function(*surface, data->freqs, false, false, true);

            /// draw cursor
            for (int i = 0; i < WINDOW_HEIGHT; i++)
                surface->draw_point({i, mouse_position.x}, 1, {255, 255, 255});

            for (int i = 0; i < WINDOW_WIDTH; i++)
                surface->draw_point({mouse_position.y, i}, 1, {255, 255, 255});
            /// draw buttons
            for (auto i:butt_vec)
                surface->draw_button(i.getImage(), {(int) i.getPy(), (int) i.getPx()});

            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(
                            time_dif).count()));

            time_start = std::chrono::steady_clock::now();
            {

                SDL_UpdateTexture(texture, NULL, surface->get_pixel_ptr(), surface->pitch());

            }
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);


        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}