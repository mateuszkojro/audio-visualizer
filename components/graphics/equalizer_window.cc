//
// Created by pc on 20.04.2021.
//

#include "equalizer_window.h"
#include "../../tiny_message.h"
#include "../audio/audio_playback.h"
#include "handle_events.h"

std::string assets = R"(..\components\graphics\assets)";



void DrawHistogram(Canvas &surface, uint16_t volume) {
  // for now let's assume that  from left to right is precisely 10s
}

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

  Coord mouse_position = {0, 0};

  SDL_Event event;
  SDL_Window *window = SDL_CreateWindow("lele",           // window title
                                        100,              // initial x position
                                        100,              // initial y_ position
                                        WINDOW_WIDTH,     // width, in pixels
                                        WINDOW_HEIGHT,    // height, in pixels
                                        SDL_WINDOW_OPENGL // flags - see below
  );

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  Canvas *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
  std::array<Button, BUTTONS_COUNT> butt_vec = LoadButtons();

  while (true) { // main loop
    if (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        goto quit;

      case SDL_MOUSEMOTION:
        HandleMouseMovement(mouse_position, window);
        break;
      case SDL_MOUSEBUTTONUP:
        HandleMousePress(butt_vec, mouse_position, audio_state);
        break;
      case SDL_MOUSEWHEEL: {
        if (event.wheel.y > 0)
          HandleMouseScrollUp(butt_vec, mouse_position, audio_state);
        if (event.wheel.y < 0)
          HandleMouseScrollDown(butt_vec, mouse_position, audio_state);
      } break;
      }
    }

    {

      /// clear the screen
      surface->Fill({0, 0, 0});
      surface->SetPrimaryColor({0, 255, 0});

      if (butt_vec[AXIS].State() == 1) {
        DrawAxis(surface, butt_vec[SNAP_FUNCTION].State() == 1);
      }

      /// draw function
      auto local_fourier_data = audio_state->config->freqs;

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

      if (butt_vec[CROSSHAIR].State() == 0)
        DrawCursor(surface, mouse_position);

      SDL_UpdateTexture(texture, NULL, surface->GetPixelPtr(),
                        surface->Pitch());

      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
  }
quit:

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
