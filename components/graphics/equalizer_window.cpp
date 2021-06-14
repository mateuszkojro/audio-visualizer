//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"
#include "../../TinyMessage.h"
#include "../../AudioPlayback.h"


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


void
draw_function(Canvas &surface, std::vector<int> local_values, bool draw_big_points, bool static_color, bool snap_middle,
              bool normalize) {

    std::vector<Coord> p_positions; // this i thing can be static

    /// flipped all values, to make them appear from the bottom of window rather than on top
    if (snap_middle) {

        for (int &i:local_values)
            i = (WINDOW_HEIGHT / 2) - i;

    } else {

        for (int &i:local_values)
            i = WINDOW_HEIGHT - 40 - i;
    }


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
    crosshair,
    axis,

    backward10s,
    forward10s,
    play_pause,

    normalize_function,
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
    butt_vec[number_of_samples_up_down] = {WINDOW_WIDTH - 160, 85, minus_canvas};

    butt_vec[scaling_factor_up] = {WINDOW_WIDTH - 100, 40, plus_canvas};
    butt_vec[scaling_factor_down] = {WINDOW_WIDTH - 100, 85, minus_canvas};

    butt_vec[winding_start_up] = {WINDOW_WIDTH - 160, 160, plus_canvas};
    butt_vec[winding_start_down] = {WINDOW_WIDTH - 160, 205, minus_canvas};

    butt_vec[winding_end_up] = {WINDOW_WIDTH - 100, 160, plus_canvas};
    butt_vec[winding_end_down] = {WINDOW_WIDTH - 100, 205, minus_canvas};

    butt_vec[winding_step_up] = {WINDOW_WIDTH - 160, 280, plus_canvas};
    butt_vec[winding_step_down] = {WINDOW_WIDTH - 160, 325, minus_canvas};

    butt_vec[slow_down] = {WINDOW_WIDTH - 100, 280, plus_canvas};
    butt_vec[speed_up] = {WINDOW_WIDTH - 100, 325, minus_canvas};

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

    butt_vec[crosshair] = {220, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[crosshair].setImage(0, Canvas("..\\components\\graphics\\assets\\crosshair_on.ppm", 40, 40));
    butt_vec[crosshair].setImage(1, Canvas("..\\components\\graphics\\assets\\crosshair.ppm", 40, 40));


    butt_vec[normalize_function] = {260, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[normalize_function].setImage(0, Canvas("..\\components\\graphics\\assets\\statistics_low.ppm", 40, 40));
    butt_vec[normalize_function].setImage(1, Canvas("..\\components\\graphics\\assets\\statistics.ppm", 40, 40));

    butt_vec[axis] = {300, WINDOW_HEIGHT - 40, 40, 40};
    butt_vec[axis].setImage(0, Canvas("..\\components\\graphics\\assets\\axis_off.ppm", 40, 40));
    butt_vec[axis].setImage(1, Canvas("..\\components\\graphics\\assets\\axis_on.ppm", 40, 40));

    // butt_vec[grid] = {160, WINDOW_HEIGHT - 40, canvas("..\\components\\graphics\\assets\\forward.ppm", 40, 40)};



    return butt_vec;
}

void equalizer_window_from_data(AudioProgress *audio_state) {

    auto fourier_data = audio_state->config_;

    SDL_Window *window = SDL_CreateWindow(
            "lele",                  // window title
            100,                                    // initial x position
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
                        fourier_data->number_of_samples += 1;

                        break;
                    case number_of_samples_up_down:
                        if (fourier_data->number_of_samples > 1)
                            fourier_data->number_of_samples -= 1;

                        break;
                    case scaling_factor_up:
                        fourier_data->scaling_factor *= 0.99;

                        break;
                    case scaling_factor_down:
                        fourier_data->scaling_factor *= 1.01;

                        break;
                    case winding_start_up:
                        /// same as left arrow
                        fourier_data->winding_start += 1;

                        break;
                    case winding_start_down:
                        fourier_data->winding_start -= 1;

                        break;
                    case winding_end_up:
                        fourier_data->winding_end += 1;

                        break;
                    case winding_end_down:
                        fourier_data->winding_end -= 1;

                        break;
                    case winding_step_up:
                        fourier_data->winding_step += 1;

                        break;
                    case winding_step_down:
                        if (fourier_data->winding_step > 1)
                            fourier_data->winding_step -= 1;

                        break;
                    case speed_up:
                        if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
                            fourier_data->sleep_for -= std::chrono::milliseconds(10);

                        break;
                    case slow_down:
                        fourier_data->sleep_for += std::chrono::milliseconds(10);
                        break;

                    case source:
                        if (butt_vec[source].state() == 0) {

                            std::string path = Tiny::open_file_dialog();
                            if (!path.empty()) {
                                AudioPlayback::use_source(path, audio_state);
                            }

                        } else {
                            AudioPlayback::use_microphone(audio_state);
                        }


                        butt_vec[source].press();

                        break;
                    case axis:

                        butt_vec[axis].press();

                        break;

                    case play_pause:
                        if (butt_vec[play_pause].state() == 0) {
                            audio_state->is_paused_ = false;
                        } else audio_state->is_paused_ = true;

                        butt_vec[play_pause].press();
                        break;

                    case crosshair:
                        butt_vec[crosshair].press();
                        break;
                    case normalize_function:
                        butt_vec[normalize_function].press();
                        break;
//                    case forward10s:
//
//                        auto length = audio_state->file_info_.samples;
//
//                        length = length > audio_state->time_left_ ? audio_state->time_left_ : length;
//
//                        audio_state->time_left_ -= length;
//                        audio_state->current_position_ += length;
//
//
//                        break;

                    default:
                        break;


                }
                fourier_data->show_in_console();


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
                            fourier_data->number_of_samples += 1;

                            break;
                        case scaling_factor_up:
                        case scaling_factor_down:
                            fourier_data->scaling_factor *= 0.99;

                            break;
                        case winding_start_up:
                        case winding_start_down:
                            fourier_data->winding_start += 1;

                            break;
                        case winding_end_up:
                        case winding_end_down:
                            fourier_data->winding_end += 1;

                            break;
                        case winding_step_up:
                        case winding_step_down:
                            fourier_data->winding_step += 1;
                            break;

                        case speed_up:
                        case slow_down:
                            if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
                                fourier_data->sleep_for -= std::chrono::milliseconds(10);

                            break;

                    }
                    fourier_data->show_in_console();

                } else if (event.wheel.y < 0) {
                    int i = 0;
                    for (; i < butt_vec.size(); i++) {
                        if (butt_vec[i].detect_press(mouse_position)) break;
                    }

                    switch (i) {
                        case number_of_samples_up:
                        case number_of_samples_up_down:
                            if (fourier_data->number_of_samples > 1)
                                fourier_data->number_of_samples -= 1;

                            break;
                        case scaling_factor_up:
                        case scaling_factor_down:
                            fourier_data->scaling_factor *= 1.01;

                            break;
                        case winding_start_up:
                        case winding_start_down:
                            fourier_data->winding_start -= 1;

                            break;
                        case winding_end_up:
                        case winding_end_down:
                            fourier_data->winding_end -= 1;

                            break;
                        case winding_step_up:
                        case winding_step_down:
                            if (fourier_data->winding_step > 1)
                                fourier_data->winding_step -= 1;

                            break;
                        case speed_up:
                        case slow_down:
                            fourier_data->sleep_for += std::chrono::milliseconds(10);
                            break;

                    }
                    fourier_data->show_in_console();
                }

            }


        }


        {

            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);

            surface->fill({0, 0, 0});
            surface->set_primary_color({0, 255, 0});

            if (butt_vec[axis].state() == 1) {

                /// draw both axis
                for (int i = 0; i < WINDOW_HEIGHT; i++)
                    surface->draw_point({i, 40}, 2, {255, 255, 255});
                if (butt_vec[normalize_function].state() == 1) {
                    for (int i = 0; i < WINDOW_WIDTH; i++)
                        surface->draw_point({(WINDOW_HEIGHT / 2), i}, 2, {255, 255, 255});
                } else {
                    for (int i = 0; i < WINDOW_WIDTH; i++)
                        surface->draw_point({WINDOW_HEIGHT - 40, i}, 2, {255, 255, 255});
                }
            }

            /// draw grid
            draw_function(*surface, fourier_data->freqs, true, true, butt_vec[normalize_function].state() == 1, false);


            /// draw buttons
            for (auto i:butt_vec)
                surface->draw_button(i.getImage(), {(int) i.getPy(), (int) i.getPx()});

            if (butt_vec[crosshair].state() == 0) {
                /// draw cursor
                for (int i = 0; i < WINDOW_HEIGHT; i++)
                    surface->draw_point({i, mouse_position.x}, 1, {255, 255, 255});

                for (int i = 0; i < WINDOW_WIDTH; i++)
                    surface->draw_point({mouse_position.y, i}, 1, {255, 255, 255});
            }




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