//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"


std::string assets = R"(..\components\graphics\assets)";

void EqualizerWindow::LoadButtons() {

  Canvas plus_canvas(assets + "\\up-arrow.ppm", 40, 40);
  Canvas minus_canvas(assets + "\\down-arrow.ppm", 40, 40);

  butt_vec_[NUMBER_OF_SAMPLES_UP] = {WINDOW_WIDTH - 100, 80, plus_canvas};
  butt_vec_[NUMBER_OF_SAMPLES_UP_DOWN] = {WINDOW_WIDTH - 160, 80, minus_canvas};

  butt_vec_[SCALING_FACTOR_UP] = {WINDOW_WIDTH - 100, 160, plus_canvas};
  butt_vec_[SCALING_FACTOR_DOWN] = {WINDOW_WIDTH - 160, 160, minus_canvas};

  butt_vec_[WINDING_START_UP] = {WINDOW_WIDTH - 100, 240, plus_canvas};
  butt_vec_[WINDING_START_DOWN] = {WINDOW_WIDTH - 160, 240, minus_canvas};

  butt_vec_[WINDING_END_UP] = {WINDOW_WIDTH - 100, 320, plus_canvas};
  butt_vec_[WINDING_END_DOWN] = {WINDOW_WIDTH - 160, 320, minus_canvas};

  butt_vec_[WINDING_STEP_UP] = {WINDOW_WIDTH - 100, 400, plus_canvas};
  butt_vec_[WINDING_STEP_DOWN] = {WINDOW_WIDTH - 160, 400, minus_canvas};

  butt_vec_[SLOW_DOWN] = {WINDOW_WIDTH - 100, 480, plus_canvas};
  butt_vec_[SPEED_UP] = {WINDOW_WIDTH - 160, 480, minus_canvas};

  butt_vec_[BACKWARD_10_S] = {0, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[BACKWARD_10_S].SetImage(0,
                                    Canvas(assets + "\\backward.ppm", 40, 40));

  butt_vec_[PLAY_PAUSE] = {40, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[PLAY_PAUSE].SetImage(0, Canvas(assets + "\\play.ppm", 40, 40));
  butt_vec_[PLAY_PAUSE].SetImage(1, Canvas(assets + "\\pause.ppm", 40, 40));

  butt_vec_[FORWARD_10_S] = {80, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[FORWARD_10_S].SetImage(0, Canvas(assets + "\\forward.ppm", 40, 40));

  butt_vec_[SOURCE] = {180, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[SOURCE].SetImage(0, Canvas(assets + "\\microphone.ppm", 40, 40));
  butt_vec_[SOURCE].SetImage(1, Canvas(assets + "\\upload.ppm", 40, 40));

  butt_vec_[CROSSHAIR] = {220, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[CROSSHAIR].SetImage(0,
                                Canvas(assets + "\\crosshair_on.ppm", 40, 40));
  butt_vec_[CROSSHAIR].SetImage(1, Canvas(assets + "\\crosshair.ppm", 40, 40));

  butt_vec_[AXIS] = {260, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[AXIS].SetImage(0, Canvas(assets + "\\axis_off.ppm", 40, 40));
  butt_vec_[AXIS].SetImage(1, Canvas(assets + "\\axis_on.ppm", 40, 40));

  butt_vec_[SNAP_FUNCTION] = {340, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[SNAP_FUNCTION].SetImage(
      0, Canvas(assets + "\\statistics_low.ppm", 40, 40));
  butt_vec_[SNAP_FUNCTION].SetImage(
      1, Canvas(assets + "\\statistics.ppm", 40, 40));

  butt_vec_[NORMALIZE_FUNCTION] = {380, WINDOW_HEIGHT - 40, 40, 40};
  butt_vec_[NORMALIZE_FUNCTION].SetImage(
      0, Canvas(assets + "\\normalize_off.ppm", 40, 40));
  butt_vec_[NORMALIZE_FUNCTION].SetImage(
      1, Canvas(assets + "\\normalize_on.ppm", 40, 40));

  butt_vec_[REFLECT_FUNCTION] = {420, WINDOW_HEIGHT - 40, 40, 40};

  butt_vec_[REFLECT_FUNCTION].SetImage(
      0, Canvas(assets + "\\reflect_off.ppm", 40, 40));
  butt_vec_[REFLECT_FUNCTION].SetImage(
      1, Canvas(assets + "\\reflect_on.ppm", 40, 40));
}

void EqualizerWindow::ThEqualizerWindowFromData(AudioProgress *audio_state) {

  Coord mouse_position = {0, 0};

  SDL_Event event;
  SDL_Window *window = SDL_CreateWindow("lele",           // window title
                                        100,              // initial x position
                                        100,              // initial y_ position
                                        width_,           // width, in pixels
                                        height_,          // height, in pixels
                                        SDL_WINDOW_OPENGL // flags - see below
  );

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  Canvas *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

  while (true) { // main loop
    if (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        goto quit;

      case SDL_MOUSEMOTION:
        HandleMouseMovement(mouse_position, window);
        break;
      case SDL_MOUSEBUTTONUP:
        HandleMousePress( mouse_position, audio_state);
        break;
      case SDL_MOUSEWHEEL: {
        if (event.wheel.y > 0)
          HandleMouseScrollUp( mouse_position, audio_state);
        if (event.wheel.y < 0)
          HandleMouseScrollDown( mouse_position, audio_state);
      } break;
      }
    }

    /// clear the screen
    surface->Fill({0, 0, 0});
    surface->SetPrimaryColor({0, 255, 0});

    if (butt_vec_[AXIS].State() == 1) {
      DrawAxis(surface, butt_vec_[SNAP_FUNCTION].State() == 1);
    }

    /// draw function
    auto local_fourier_data = audio_state->config->freqs;

    DrawFunction(*surface, local_fourier_data, true, true,
                 butt_vec_[SNAP_FUNCTION].State() == 1,
                 butt_vec_[NORMALIZE_FUNCTION].State() == 1);

    if (butt_vec_[REFLECT_FUNCTION].State() == 1) {

      for (auto &i : local_fourier_data)
        i = -i;

      DrawFunction(*surface, local_fourier_data, true, true,
                   butt_vec_[SNAP_FUNCTION].State() == 1,
                   butt_vec_[NORMALIZE_FUNCTION].State() == 1);
    }

    /// draw buttons
    for (auto i : butt_vec_)
      surface->DrawButton(i.GetImage(), {(int)i.GetPy(), (int)i.GetPx()});

    if (butt_vec_[CROSSHAIR].State() == 0)
      DrawCursor(surface, mouse_position);

    SDL_UpdateTexture(texture, NULL, surface->GetPixelPtr(), surface->Pitch());

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    DrawTextFields(renderer, audio_state, mouse_position);

    SDL_RenderPresent(renderer);
  }
quit:
  audio_state->mode = AudioProgress::CLOSE;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

AudioProgress *EqualizerWindow::GetAudioState() const { return audio_state_; }

const int EqualizerWindow::GetWidth() const { return width_; }

const int EqualizerWindow::GetHeight() const { return height_; }

void EqualizerWindow::SetAudioState(AudioProgress *audio_state) {
  audio_state_ = audio_state;
}

EqualizerWindow::EqualizerWindow()
    : width_(1800), height_(800), audio_state_(nullptr) {

  LoadButtons();

  std::thread visualizer_window(&EqualizerWindow::ThEqualizerWindowFromData,
                                this, audio_state_);
  visualizer_window.join();
}

EqualizerWindow::EqualizerWindow(AudioProgress *audio_state)
    : width_(1800), height_(800), audio_state_(audio_state) {

  LoadButtons();

  std::thread visualizer_window(&EqualizerWindow::ThEqualizerWindowFromData,
                                this, audio_state_);
  visualizer_window.join();
}

void EqualizerWindow::HandleMouseMovement(Coord &mouse_position,
                                          SDL_Window *window) {

  SDL_GetMouseState(&mouse_position.x_, &mouse_position.y_);

  std::string title = std::to_string(mouse_position.x_) + " x ";
  title += std::to_string(mouse_position.y_) + " y ";
  SDL_SetWindowTitle(window, title.c_str());
}

void EqualizerWindow::HandleMousePress(Coord &mouse_position,
                                       AudioProgress *audio_state) {

  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec_.size(); i++) {
    if (butt_vec_[i].DetectPress(mouse_position))
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
    if (butt_vec_[SOURCE].State() == 0) {

      std::string path = Tiny::OpenFileDialog();
      if (!path.empty()) {
        AudioPlayback::UseSource(path, audio_state);
      }

    } else {
      AudioPlayback::UseMicrophone(audio_state);
    }

    butt_vec_[SOURCE].Press();

    break;
  case AXIS:

    butt_vec_[AXIS].Press();

    break;

  case PLAY_PAUSE:
    if (butt_vec_[PLAY_PAUSE].State() == 0) {
      audio_state->is_paused = false;
    } else
      audio_state->is_paused = true;

    butt_vec_[PLAY_PAUSE].Press();
    break;

  case CROSSHAIR:
    butt_vec_[CROSSHAIR].Press();
    break;

  case SNAP_FUNCTION:
    butt_vec_[SNAP_FUNCTION].Press();
    break;

  case NORMALIZE_FUNCTION:
    butt_vec_[NORMALIZE_FUNCTION].Press();
    break;

  case REFLECT_FUNCTION:
    butt_vec_[REFLECT_FUNCTION].Press();
    break;

  case BACKWARD_10_S:
    /// here
    break;
  case FORWARD_10_S:
    /// here
    break;
  default:
    break;
  }
  std::cout << audio_state;
}

void EqualizerWindow::HandleMouseScrollUp(Coord &mouse_position,
                                          AudioProgress *audio_state) {
  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec_.size(); i++) {
    if (butt_vec_[i].DetectPress(mouse_position))
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
  std::cout << audio_state;
}

void EqualizerWindow::HandleMouseScrollDown(Coord &mouse_position,
                                            AudioProgress *audio_state) {

  auto fourier_data = audio_state->config;

  int i = 0;
  for (; i < butt_vec_.size(); i++) {
    if (butt_vec_[i].DetectPress(mouse_position))
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
  std::cout << audio_state;
}
