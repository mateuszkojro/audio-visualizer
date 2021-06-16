//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"
#include "../../tiny_message.h"
#include "../audio/audio_playback.h"

std::string assets = R"(..\components\graphics\assets)";

std::vector<Coord> GenFunctionBetweenPoints(Coord begin, Coord end) {

  std::vector<Coord> generated_function;
  Coord mid_point = {(begin.y_ + end.y_) / 2, (begin.x_ + end.x_) / 2};

  /// like in polynomial function a
  double a;
  a = begin.y_ > end.y_ ? begin.y_ - end.y_ : end.y_ - begin.y_;
  a /= 2;
  int max_value /* distance between two points in x axis*/ =
      (end.x_ - begin.x_);

  if (max_value == 0) {

    return {begin};
  }

  double d = mid_point.y_;
  if (begin.y_ > end.y_) {

    a *= -1;
  }
  if ((begin.x_ / max_value) % 2 == 0) {
    a *= -1;
  }

  for (double i = begin.x_; i <= end.x_; ++i) {

    double radian = i / max_value;

    radian *= M_PI;

    generated_function.emplace_back((int)(a * cos(radian) + d), (int)i);
  }
  return generated_function;
}

std::vector<Coord> CreatePoints(int begin, int end,
                                std::vector<int> &values_to_be_drown) {

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

std::vector<Coord> CreatePoints(std::vector<int> &values_to_be_drown) {

  // distance between two point's in x axis
  int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() - 1);

  std::vector<Coord> dot_coordinates;

  for (int i = 0; i < values_to_be_drown.size(); i++)
    dot_coordinates.emplace_back(values_to_be_drown[i], x_shift * i);

  return dot_coordinates;
}

void DrawFunction(Canvas &surface, std::vector<int> local_values,
                  bool draw_big_points, bool static_color, bool snap_middle,
                  bool normalize) {

  std::vector<Coord> p_positions; // this i thing can be static

  if (normalize) {

    for (int &i : local_values) {
      i *= abs(i);
      i /= 200;
    }
  }

  /// flipped all values, to make them appear from the bottom of window rather
  /// than on top
  if (snap_middle) {

    for (int &i : local_values)
      i = (WINDOW_HEIGHT / 2) - i;

  } else {

    for (int &i : local_values)
      i = WINDOW_HEIGHT - 40 - i;
  }

  p_positions = CreatePoints(local_values);

  for (int i = 0; i < p_positions.size() - 1; ++i) {

    std::vector<Coord> function_between_points =
        GenFunctionBetweenPoints(p_positions[i], p_positions[i + 1]);

    for (Coord &j : function_between_points) {
      if (!static_color)
        surface.DrawPoint(j, 3, GenRainbow(j.y_, WINDOW_HEIGHT));
      else
        surface.DrawPoint(j, 2);
    }
  }

  if (draw_big_points)
    for (auto j : p_positions)
      surface.DrawPoint(j, 6, GenRainbow(j.y_, WINDOW_HEIGHT));
}

enum Buttons {
  NUMBER_OF_SAMPLES_UP,
  NUMBER_OF_SAMPLES_UP_DOWN,

  SCALING_FACTOR_UP,
  SCALING_FACTOR_DOWN,

  WINDING_START_UP,
  WINDING_START_DOWN,

  WINDING_END_UP,
  WINDING_END_DOWN,

  WINDING_STEP_UP,
  WINDING_STEP_DOWN,

  SPEED_UP,
  SLOW_DOWN,

  BACKWARD_10_S,
  FORWARD_10_S,
  PLAY_PAUSE,

  //  grid,
  SOURCE,
  CROSSHAIR,
  AXIS,
  SNAP_FUNCTION,
  NORMALIZE_FUNCTION,
  REFLECT_FUNCTION,
  RAINBOW,

  BUTTONS_COUNT
  // in plans:

};

std::array<Button, BUTTONS_COUNT> LoadButtons() {

  std::array<Button, BUTTONS_COUNT> butt_vec;

  Canvas plus_canvas(assets + "\\up-arrow.ppm", 40, 40);
  Canvas minus_canvas(assets + "\\down-arrow.ppm", 40, 40);

  butt_vec[NUMBER_OF_SAMPLES_UP] = {WINDOW_WIDTH - 160, 40, plus_canvas};
  butt_vec[NUMBER_OF_SAMPLES_UP_DOWN] = {WINDOW_WIDTH - 160, 85, minus_canvas};

  butt_vec[SCALING_FACTOR_UP] = {WINDOW_WIDTH - 100, 40, plus_canvas};
  butt_vec[SCALING_FACTOR_DOWN] = {WINDOW_WIDTH - 100, 85, minus_canvas};

  butt_vec[WINDING_START_UP] = {WINDOW_WIDTH - 160, 160, plus_canvas};
  butt_vec[WINDING_START_DOWN] = {WINDOW_WIDTH - 160, 205, minus_canvas};

  butt_vec[WINDING_END_UP] = {WINDOW_WIDTH - 100, 160, plus_canvas};
  butt_vec[WINDING_END_DOWN] = {WINDOW_WIDTH - 100, 205, minus_canvas};

  butt_vec[WINDING_STEP_UP] = {WINDOW_WIDTH - 160, 280, plus_canvas};
  butt_vec[WINDING_STEP_DOWN] = {WINDOW_WIDTH - 160, 325, minus_canvas};

  butt_vec[SLOW_DOWN] = {WINDOW_WIDTH - 100, 280, plus_canvas};
  butt_vec[SPEED_UP] = {WINDOW_WIDTH - 100, 325, minus_canvas};

  butt_vec[BACKWARD_10_S] = {0, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[BACKWARD_10_S].SetImage(0,
                                   Canvas(assets + "\\backward.ppm", 40, 40));

  butt_vec[PLAY_PAUSE] = {40, WINDOW_HEIGHT - 40, 40, 40};

  butt_vec[PLAY_PAUSE].SetImage(0, Canvas(assets + "\\play.ppm", 40, 40));
  butt_vec[PLAY_PAUSE].SetImage(1, Canvas(assets + "\\pause.ppm", 40, 40));

  butt_vec[FORWARD_10_S] = {80, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[FORWARD_10_S].SetImage(0, Canvas(assets + "\\forward.ppm", 40, 40));

  butt_vec[SOURCE] = {180, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[SOURCE].SetImage(0, Canvas(assets + "\\microphone.ppm", 40, 40));
  butt_vec[SOURCE].SetImage(1, Canvas(assets + "\\upload.ppm", 40, 40));

  butt_vec[CROSSHAIR] = {220, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[CROSSHAIR].SetImage(0,
                               Canvas(assets + "\\crosshair_on.ppm", 40, 40));
  butt_vec[CROSSHAIR].SetImage(1, Canvas(assets + "\\crosshair.ppm", 40, 40));

  butt_vec[AXIS] = {260, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[AXIS].SetImage(0, Canvas(assets + "\\axis_off.ppm", 40, 40));
  butt_vec[AXIS].SetImage(1, Canvas(assets + "\\axis_on.ppm", 40, 40));

  butt_vec[SNAP_FUNCTION] = {340, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[SNAP_FUNCTION].SetImage(
      0, Canvas(assets + "\\statistics_low.ppm", 40, 40));
  butt_vec[SNAP_FUNCTION].SetImage(1,
                                   Canvas(assets + "\\statistics.ppm", 40, 40));

  butt_vec[NORMALIZE_FUNCTION] = {380, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec[NORMALIZE_FUNCTION].SetImage(
      0, Canvas(assets + "\\normalize_off.ppm", 40, 40));
  butt_vec[NORMALIZE_FUNCTION].SetImage(
      1, Canvas(assets + "\\normalize_on.ppm", 40, 40));

  butt_vec[REFLECT_FUNCTION] = {420, WINDOW_HEIGHT - 40, 40, 40};

  butt_vec[REFLECT_FUNCTION].SetImage(
      0, Canvas(assets + "\\reflect_off.ppm", 40, 40));
  butt_vec[REFLECT_FUNCTION].SetImage(
      1, Canvas(assets + "\\reflect_on.ppm", 40, 40));

  return butt_vec;
}

void ThEqualizerWindowFromData(AudioProgress *audio_state) {

  auto fourier_data = audio_state->config;

  SDL_Window *window = SDL_CreateWindow("lele",           // window title
                                        100,              // initial x position
                                        100,              // initial y_ position
                                        WINDOW_WIDTH,     // width, in pixels
                                        WINDOW_HEIGHT,    // height, in pixels
                                        SDL_WINDOW_OPENGL // flags - see below
  );

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

  Canvas *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});
  Coord mouse_position = {0, 0};

  /// buttons :
  SDL_Event event;

  std::array<Button, BUTTONS_COUNT> butt_vec = LoadButtons();

  auto time_start = std::chrono::steady_clock::now();

  while (true) { // main loop
    if (SDL_PollEvent(&event)) {

      if (event.type == SDL_QUIT)
        break;
      if (event.type == SDL_MOUSEMOTION) {

        SDL_GetMouseState(&mouse_position.x_, &mouse_position.y_);

        std::string title = std::to_string(mouse_position.x_) + " x ";
        title += std::to_string(mouse_position.y_) + " y ";
        SDL_SetWindowTitle(window, title.c_str());
      }
      if (event.type == SDL_MOUSEBUTTONUP) {
        int i = 0;
        for (; i < butt_vec.size(); i++) {
          if (butt_vec[i].DetectPress(mouse_position))
            break;
        }

        switch (i) {
        case NUMBER_OF_SAMPLES_UP:
          fourier_data->number_of_samples += 1;

          break;
        case NUMBER_OF_SAMPLES_UP_DOWN:
          if (fourier_data->number_of_samples > 1)
            fourier_data->number_of_samples -= 1;

          break;
        case SCALING_FACTOR_UP:
          fourier_data->scaling_factor *= 0.99;

          break;
        case SCALING_FACTOR_DOWN:
          fourier_data->scaling_factor *= 1.01;

          break;
        case WINDING_START_UP:
          /// same as left arrow
          fourier_data->winding_start += 1;

          break;
        case WINDING_START_DOWN:
          fourier_data->winding_start -= 1;

          break;
        case WINDING_END_UP:
          fourier_data->winding_end += 1;

          break;
        case WINDING_END_DOWN:
          fourier_data->winding_end -= 1;

          break;
        case WINDING_STEP_UP:
          fourier_data->winding_step += 1;

          break;
        case WINDING_STEP_DOWN:
          if (fourier_data->winding_step > 1)
            fourier_data->winding_step -= 1;

          break;
        case SPEED_UP:
          if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
            fourier_data->sleep_for -= std::chrono::milliseconds(10);

          break;
        case SLOW_DOWN:
          fourier_data->sleep_for += std::chrono::milliseconds(10);
          break;

        case SOURCE:
          if (butt_vec[SOURCE].State() == 0) {

            std::string path = Tiny::OpenFileDialog();
            if (!path.empty()) {
              AudioPlayback::UseSource(path, audio_state);
            }

          } else {
            AudioPlayback::UseMicrophone(audio_state);
          }

          butt_vec[SOURCE].Press();

          break;
        case AXIS:

          butt_vec[AXIS].Press();

          break;

        case PLAY_PAUSE:
          if (butt_vec[PLAY_PAUSE].State() == 0) {
            audio_state->is_paused = false;
          } else
            audio_state->is_paused = true;

          butt_vec[PLAY_PAUSE].Press();
          break;

        case CROSSHAIR:
          butt_vec[CROSSHAIR].Press();
          break;

        case SNAP_FUNCTION:
          butt_vec[SNAP_FUNCTION].Press();
          break;

        case NORMALIZE_FUNCTION:
          butt_vec[NORMALIZE_FUNCTION].Press();
          break;

        case REFLECT_FUNCTION:
          butt_vec[REFLECT_FUNCTION].Press();
          break;

        default:
          break;
        }
        fourier_data->ShowInConsole();

      } else if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) // scroll up
        {

          int i = 0;
          for (; i < butt_vec.size(); i++) {
            if (butt_vec[i].DetectPress(mouse_position))
              break;
          }

          switch (i) {
          case NUMBER_OF_SAMPLES_UP:
          case NUMBER_OF_SAMPLES_UP_DOWN:
            fourier_data->number_of_samples += 1;

            break;
          case SCALING_FACTOR_UP:
          case SCALING_FACTOR_DOWN:
            fourier_data->scaling_factor *= 0.99;

            break;
          case WINDING_START_UP:
          case WINDING_START_DOWN:
            fourier_data->winding_start += 1;

            break;
          case WINDING_END_UP:
          case WINDING_END_DOWN:
            fourier_data->winding_end += 1;

            break;
          case WINDING_STEP_UP:
          case WINDING_STEP_DOWN:
            fourier_data->winding_step += 1;
            break;

          case SPEED_UP:
          case SLOW_DOWN:
            if (fourier_data->sleep_for >= std::chrono::milliseconds(10))
              fourier_data->sleep_for -= std::chrono::milliseconds(10);

            break;
          }
          fourier_data->ShowInConsole();

        } else if (event.wheel.y < 0) {
          int i = 0;
          for (; i < butt_vec.size(); i++) {
            if (butt_vec[i].DetectPress(mouse_position))
              break;
          }

          switch (i) {
          case NUMBER_OF_SAMPLES_UP:
          case NUMBER_OF_SAMPLES_UP_DOWN:
            if (fourier_data->number_of_samples > 1)
              fourier_data->number_of_samples -= 1;

            break;
          case SCALING_FACTOR_UP:
          case SCALING_FACTOR_DOWN:
            fourier_data->scaling_factor *= 1.01;

            break;
          case WINDING_START_UP:
          case WINDING_START_DOWN:
            fourier_data->winding_start -= 1;

            break;
          case WINDING_END_UP:
          case WINDING_END_DOWN:
            fourier_data->winding_end -= 1;

            break;
          case WINDING_STEP_UP:
          case WINDING_STEP_DOWN:
            if (fourier_data->winding_step > 1)
              fourier_data->winding_step -= 1;

            break;
          case SPEED_UP:
          case SLOW_DOWN:
            fourier_data->sleep_for += std::chrono::milliseconds(10);
            break;
          }
          fourier_data->ShowInConsole();
        }
      }
    }

    {

      ;

      surface->Fill({0, 0, 0});
      surface->SetPrimaryColor({0, 255, 0});

      if (butt_vec[AXIS].State() == 1) {

        /// draw both axis
        for (int i = 0; i < WINDOW_HEIGHT; i++)
          surface->DrawPoint({i, 40}, 2, {255, 255, 255});

        if (butt_vec[SNAP_FUNCTION].State() == 1) {

          for (int i = 0; i < WINDOW_WIDTH; i++) {
            surface->DrawPoint({(WINDOW_HEIGHT / 2), i}, 2, {255, 255, 255});
          }

        } else {

          for (int i = 0; i < WINDOW_WIDTH; i++)
            surface->DrawPoint({WINDOW_HEIGHT - 40, i}, 2, {255, 255, 255});
        }
      }

      /// draw function
      // todo mutex here
      auto local_fourier_data = fourier_data->freqs;

      DrawFunction(*surface, local_fourier_data, true, true,
                   butt_vec[SNAP_FUNCTION].State() == 1,
                   butt_vec[NORMALIZE_FUNCTION].State() == 1);

      if (butt_vec[REFLECT_FUNCTION].State() == 1) {

        for (auto &i : local_fourier_data)
          i = -i;
        DrawFunction(*surface, local_fourier_data, true, true,
                     butt_vec[SNAP_FUNCTION].State() == 1,
                     butt_vec[NORMALIZE_FUNCTION].State() == 1);
      }
      /// draw buttons
      for (auto i : butt_vec)
        surface->DrawButton(i.GetImage(), {(int)i.GetPy(), (int)i.GetPx()});

      if (butt_vec[CROSSHAIR].State() == 0) {
        /// draw cursor
        for (int i = 0; i < WINDOW_HEIGHT; i++)
          surface->DrawPoint({i, mouse_position.x_}, 1, {255, 255, 255});

        for (int i = 0; i < WINDOW_WIDTH; i++)
          surface->DrawPoint({mouse_position.y_, i}, 1, {255, 255, 255});
      }

    //  surface->DrawLine({200, 200}, {400, 200}, 1);

   //   surface->DrawLine({400, 300}, {200, 300}, 1);


      surface->DrawLine({200, 200}, {200, 300}, 1);

      surface->DrawLine({400, 300}, {400, 200}, 1);


      surface->DrawLine({200, 200}, {400, 300}, 1);

      surface->DrawLine({400, 200}, {200, 300}, 1);

      {

        SDL_UpdateTexture(texture, NULL, surface->GetPixelPtr(),
                          surface->Pitch());
        // SDL_Surface *TTF_RenderText_Solid(TTF_Font *font, const char *text,
        // SDL_Color fg);
      }
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}