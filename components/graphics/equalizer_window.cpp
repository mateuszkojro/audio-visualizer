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
        i = WINDOW_HEIGHT - i - 40;

    p_positions = create_points(local_values);

    for (int i = 0; i < p_positions.size() - 1; ++i) {

        std::vector<Coord> function_between_points = gen_function_between_points(p_positions[i], p_positions[i + 1]);

        for (Coord &j:function_between_points) {
            if (!static_color) surface.draw_point(j, 3, gen_rainbow(j.y, WINDOW_HEIGHT));
            else surface.draw_point(j, 2);

        }

    }

    if (draw_big_points)
        for (auto j:p_positions)
            surface.draw_point(j, 6, gen_rainbow(j.y, WINDOW_HEIGHT));

}


enum Buttons {
    number_of_samples_up,
    number_of_samples_up_down,

    scaling_factor_up,
    scaling_factor_down,

    winding_start_up,
    winding_start_down,

    winding_end_up,
    winding_end_down,

    winding_step_up,
    winding_step_down,

    speed_up,
    slow_down,

    //  grid,
    source,

    backward10s,
    forward10s,
    play_pause,

    buttons_count
// in plans:

};


std::array<Button, buttons_count> load_buttons() {

    std::array<Button, buttons_count> butt_vec;

    Canvas plus_canvas("..\\components\\graphics\\assets\\up-arrow.ppm",
                       40, 40);
    Canvas minus_canvas("..\\components\\graphics\\assets\\down-arrow.ppm",
                        40, 40);


    butt_vec[number_of_samples_up] = {WINDOW_WIDTH - 160, 40, plus_canvas};
    butt_vec[number_of_samples_up_down] = {WINDOW_WIDTH - 160, 80, minus_canvas};
    butt_vec[scaling_factor_up] = {WINDOW_WIDTH - 100, 40, plus_canvas};
    butt_vec[scaling_factor_down] = {WINDOW_WIDTH - 100, 80, minus_canvas};
    butt_vec[winding_start_up] = {WINDOW_WIDTH - 160, 160, plus_canvas};
    butt_vec[winding_start_down] = {WINDOW_WIDTH - 160, 200, minus_canvas};
    butt_vec[winding_end_up] = {WINDOW_WIDTH - 100, 160, plus_canvas};
    butt_vec[winding_end_down] = {WINDOW_WIDTH - 100, 200, minus_canvas};
    butt_vec[winding_step_up] = {WINDOW_WIDTH - 160, 280, plus_canvas};
    butt_vec[winding_step_down] = {WINDOW_WIDTH - 160, 320, minus_canvas};

    butt_vec[slow_down] = {WINDOW_WIDTH - 100, 280, plus_canvas};
    butt_vec[speed_up] = {WINDOW_WIDTH - 100, 320, minus_canvas};

    butt_vec[backward10s] = {0, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[backward10s].setImage(0, Canvas("..\\components\\graphics\\assets\\backward.ppm", 40, 40));

    butt_vec[play_pause] = {40, WINDOW_HEIGHT - 40, 40, 40};

    butt_vec[play_pause].setImage(0, Canvas("..\\components\\graphics\\assets\\play.ppm", 40, 40));
    butt_vec[play_pause].setImage(1, Canvas("..\\components\\graphics\\assets\\pause.ppm", 40, 40));


    butt_vec[forward10s] = {80, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[forward10s].setImage(0, Canvas("..\\components\\graphics\\assets\\forward.ppm", 40, 40));

    butt_vec[source] = {180, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[source].setImage(0, Canvas("..\\components\\graphics\\assets\\microphone.ppm", 40, 40));
    butt_vec[source].setImage(1, Canvas("..\\components\\graphics\\assets\\upload.ppm", 40, 40));

    // butt_vec[grid] = {160, WINDOW_HEIGHT - 40, canvas("..\\components\\graphics\\assets\\forward.ppm", 40, 40)};



    return butt_vec;
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


    Canvas *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});
    Coord mouse_position = {0, 0};

    /// buttons :
    SDL_Event event;

    std::array<Button, buttons_count> butt_vec = load_buttons();

    auto time_start = std::chrono::steady_clock::now();

    while (true) { // main loop
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) break;
            if (event.type == SDL_MOUSEMOTION) {

                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

                std::string title = std::to_string(mouse_position.x) + " x ";
                title += std::to_string(mouse_position.y) + " y ";
                SDL_SetWindowTitle(window, title.c_str());

            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                int i = 0;
                for (; i < butt_vec.size(); i++) {
                    if (butt_vec[i].detect_press(mouse_position)) break;
                }

                switch (i) {
                    case number_of_samples_up:
                        data->number_of_samples += 1;

                        break;
                    case number_of_samples_up_down:
                        if (data->number_of_samples > 1)
                            data->number_of_samples -= 1;

                        break;
                    case scaling_factor_up:
                        data->scaling_factor *= 0.99;

                        break;
                    case scaling_factor_down:
                        data->scaling_factor *= 1.01;

                        break;
                    case winding_start_up:
                        /// same as left arrow
                        data->winding_start += 1;

                        break;
                    case winding_start_down:
                        data->winding_start -= 1;

                        break;
                    case winding_end_up:
                        data->winding_end += 1;

                        break;
                    case winding_end_down:
                        data->winding_end -= 1;

                        break;
                    case winding_step_up:
                        data->winding_step += 1;

                        break;
                    case winding_step_down:
                        if (data->winding_step > 1)
                            data->winding_step -= 1;

                        break;
                    case speed_up:
                        if (data->sleep_for >= std::chrono::milliseconds(10))
                            data->sleep_for -= std::chrono::milliseconds(10);

                        break;
                    case slow_down:
                        data->sleep_for += std::chrono::milliseconds(10);
                        break;

                    case source:
                        butt_vec[source].press();
                        break;
                    case play_pause:
                        butt_vec[play_pause].press();
                        break;
                    default:
                        break;


                }
                data->show_in_console();


            } else if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0) // scroll up
                {

                    int i = 0;
                    for (; i < butt_vec.size(); i++) {
                        if (butt_vec[i].detect_press(mouse_position)) break;
                    }

                    switch (i) {
                        case number_of_samples_up:
                        case number_of_samples_up_down:
                            data->number_of_samples += 1;

                            break;
                        case scaling_factor_up:
                        case scaling_factor_down:
                            data->scaling_factor *= 0.99;

                            break;
                        case winding_start_up:
                        case winding_start_down:
                            data->winding_start += 1;

                            break;
                        case winding_end_up:
                        case winding_end_down:
                            data->winding_end += 1;

                            break;
                        case winding_step_up:
                        case winding_step_down:
                            data->winding_step += 1;
                            break;

                        case speed_up:
                        case slow_down:
                            if (data->sleep_for >= std::chrono::milliseconds(10))
                                data->sleep_for -= std::chrono::milliseconds(10);

                            break;

                    }
                    data->show_in_console();

                } else if (event.wheel.y < 0) {
                    int i = 0;
                    for (; i < butt_vec.size(); i++) {
                        if (butt_vec[i].detect_press(mouse_position)) break;
                    }

                    switch (i) {
                        case number_of_samples_up:
                        case number_of_samples_up_down:
                            if (data->number_of_samples > 1)
                                data->number_of_samples -= 1;

                            break;
                        case scaling_factor_up:
                        case scaling_factor_down:
                            data->scaling_factor *= 1.01;

                            break;
                        case winding_start_up:
                        case winding_start_down:
                            data->winding_start -= 1;

                            break;
                        case winding_end_up:
                        case winding_end_down:
                            data->winding_end -= 1;

                            break;
                        case winding_step_up:
                        case winding_step_down:
                            if (data->winding_step > 1)
                                data->winding_step -= 1;

                            break;
                        case speed_up:
                        case slow_down:
                            data->sleep_for += std::chrono::milliseconds(10);
                            break;

                    }
                    data->show_in_console();
                }

            }

        }

        {

            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);

            surface->fill({0, 0, 0});
            surface->set_primary_color({0, 255, 0});

            /// funkcja adriana
            /// void funkcja_adriana(  std::vector<int>& freqs);

            /// draw grid
            draw_function(*surface, data->freqs, true, true, true);


            /// draw buttons
            for (auto i:butt_vec)
                surface->draw_button(i.getImage(), {(int) i.getPy(), (int) i.getPx()});


            /// draw cursor
            for (int i = 0; i < WINDOW_HEIGHT; i++)
                surface->draw_point({i, mouse_position.x}, 1, {255, 255, 255});

            for (int i = 0; i < WINDOW_WIDTH; i++)
                surface->draw_point({mouse_position.y, i}, 1, {255, 255, 255});





            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s

            std::this_thread::sleep_for(
                    std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(
                            time_dif).count()));

            time_start = std::chrono::steady_clock::now();
            {

                SDL_UpdateTexture(texture, NULL, surface->get_pixel_ptr(), surface->pitch());
                // SDL_Surface *TTF_RenderText_Solid(TTF_Font *font, const char *text, SDL_Color fg);

            }
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);


        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}