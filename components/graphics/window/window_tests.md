#This document contains my tests of equalizer window

I've made some measurements of graphic functions, below I've listed all my findings.
all measurements were done using std::chrono::steady_clock

# Global test 
Test measures global time of generating and displaying frame

Measurements were made on git version: 6ace440d.

At the point fo making this tests the algorytm isn't perfect, there is huge memory leak, 
witch can influence performed tests, but bug comes into play only after few hundred frames.
So tests were ended before that happened. 

The timings were made once every 100 frames and then averaged

##Code in question:

```c++
 unsigned int frame_counter = 0;
  double elapsed_time = 0;
  int sample_no = 0

  // main loop
  while (true) {
    START

    if (SDL_PollEvent(&event)) {...}
    frame_counter++;
    /// clear the screen
    surface->RevertChanges({0, 0, 0});
    surface->SetPrimaryColor({0, 255, 0});

    if (StateOf(AXIS) == 1)
      DrawAxis(surface);

    /// draw function
    auto local_fourier_data = audio_state_->config->freqs;

    DrawFunction(*surface, local_fourier_data, true, true);

    if (StateOf(REFLECT_FUNCTION) == 1) {...}

    /// draw buttons
    DisplayButtons(surface);

    if (StateOf(CROSSHAIR) == 0)
      DrawCursor(surface, mouse_position);
    
    
    SDL_UpdateTexture(texture, NULL, surface->GetPixelPtr(), surface->Pitch());

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    DrawTextFields(renderer, mouse_position);

    SDL_RenderPresent(renderer);

    elapsed_time += END;

    if (frame_counter == 100) {
      std::cout <<"sample: "<<sample_no<< "average frame calculation time over 100 frames: "
                << (elapsed_time / frame_counter) << "ms\n";
      frame_counter = 0;
      elapsed_time = 0;
    }
  }
```

As u can see the START, END functions cover whole loop.


##Findings

|**test number**|**elapsed average time<br> one normal function**|**elapsed average time<br>centered double function**|
|:---:|:---:|:---:|
|1| 54.4  | 42.63 |
|2| 44.98 | 52.28 |
|3| 45.17 | 53.51 |
|4| 45.07 | 52.12 |
|5| 44.07 | 52.92 |
|6| 43.46 | 52.82 |
|7| 42.51 | 52.44 |
|8| 42.06 | 53.64 |
|9| 42.26 | 61.91 |
|10| 42.37 | 61.9 |

The nature of implemented algorithm requires to couple the experiments with different ui elements  

|**test number**|**elapsed average time<br> one normal function<br>with all buttons and axis**|**elapsed average time<br>centered double function<br>with all buttons and axis**|
|:---:|:---:|:---:|
|1| 67.06 | 52.57 |
|2| 65.49 | 77.6  |
|3| 66.49 | 86.09 |
|4| 66.22 | 86.3  |
|5| 66.43 | 86.82 |
|6| 64.94 | 86.18 |
|7| 65.43 | 85.49 |
|8| 65.03 | 86.07 |
|9| 66.14 | 87.3  |
|10| 66.77 | 88.64 |

#Local Test

Test measures time of generating frame

Measurements were made on git version: 6ace440d.

At the point fo making this tests the algorytm isn't perfect, there is huge memory leak,
witch can influence performed tests, but bug comes into play only after few hundred frames.
So tests were ended before that happened.

The timings were made once every 100 frames and then averaged

##Code in question:

```c++

 unsigned int frame_counter = 0;
  double elapsed_time = 0;
  int sample_no = 0;

  // main loop
  while (true) { // main loop

    if (SDL_PollEvent(&event)) {...}
    frame_counter++;

    START
    /// clear the screen
    surface->RevertChanges({0, 0, 0});
    surface->SetPrimaryColor({0, 255, 0});

    if (StateOf(AXIS) == 1)
      DrawAxis(surface);

    /// draw function
    auto local_fourier_data = audio_state_->config->freqs;

    DrawFunction(*surface, local_fourier_data, true, true);

    if (StateOf(REFLECT_FUNCTION) == 1) {...}

    /// draw buttons
    DisplayButtons(surface);

    if (StateOf(CROSSHAIR) == 0)
      DrawCursor(surface, mouse_position);


    elapsed_time += END;

    if (frame_counter == 100) {
      sample_no++;
      std::cout <<"sample: "<<sample_no<< "average frame calculation time over 100 frames: "
                << (elapsed_time / frame_counter) << "ms\n";
      frame_counter = 0;
      elapsed_time = 0;
    }
    
    
    SDL_UpdateTexture(texture, NULL, surface->GetPixelPtr(), surface->Pitch());

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    DrawTextFields(renderer, mouse_position);

    SDL_RenderPresent(renderer);
  }
```

As u can see the START, END functions leave out SDL functions.


##Findings

|**test number**|**elapsed average time<br> one normal function**|**elapsed average time<br>centered double function**|
|:---:|:---:|:---:|
|1| 29.56 |  |
|2| 25.34 |  |
|3| 25.41 |  |
|4| 25.71 |  |
|5| 25.38 |  |
|6| 24.85 |  |
|7| 24.8 |  |
|8| 25.16 |  |
|9| 25.59 |  |
|10| 25.22 |  |

The nature of implemented algorithm requires to couple the experiments with different ui elements

|**test number**|**elapsed average time<br> one normal function<br>with all buttons and axis**|**elapsed average time<br>centered double function<br>with all buttons and axis**|
|:---:|:---:|:---:|
|1| |  |
|2| |   |
|3| |  |
|4| |   |
|5| |  |
|6| |  |
|7| |  |
|8| |  |
|9| |   |
|10|  |  |