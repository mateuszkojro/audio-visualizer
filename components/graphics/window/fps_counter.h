//
// Created by pc on 22.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_FPS_COUNTER_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_FPS_COUNTER_H_

#include "../canvas/canvas.h"
#include "drawing_stuff.h"

#include <SDL.h>
#include <chrono>

/// class creates, and keeps track of time it takes to generate one frame
class FpsCounter {
public:
  /// no param constructor can't be created\
    /// crucial to the functionality of FPS_Counter is showing the value calculated
  /// we need at least placement of that value therefore renderer is important
  FpsCounter() = delete;

  /// \return creates FPS_Counter object
  /// \param renderer the placement of our pixels
  /// \param color the color that displayed object will have
  /// \param scale of displayed object, scale must be >=1
  /// \param position where top left corner of our object will end up
  FpsCounter(Canvas *surface, int scale, RgbColor color,
             Coord counter_position);

  /// \return creates FPS_Counter object
  /// \param renderer the placement of our pixels
  /// rest of the class fields will be declared with best (in my opinion) values
  FpsCounter(Canvas *surface);

  /// \return creates FPS_Counter object
  /// \param renderer the placement of our pixels
  /// \param position where top left corner of our object will end up
  FpsCounter(Canvas *surface, Coord counter_position);

  /// function that calculates the framerate
  /// and outputs it ont screen
  /// \return updated renderer with current fps value
  /// \note updating the renderer takes place every time this function is called
  /// but the update of FPS takes place every 10 frames, that's to make it  not
  /// flicker also the value outputted is an average framerate across last 10
  /// frames
  void Draw();

protected:
  std::chrono::time_point<std::chrono::steady_clock> time_point_;
  Canvas *surface_;
  int scale_;
  RgbColor draw_color_;
  Coord counter_position_;
};

#endif // EQUALIZER_COMPONENTS_GRAPHICS_FPS_COUNTER_H_
