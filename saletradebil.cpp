#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Texture.h"
#include "Text.h"
#include "Button.h"
#include "Textfield.h"
#include "Slider.h"

#include <iostream>
// ###################################################################
void play_music(std::string);
void my_audio_callback(void* userdata, Uint8* stream, int len);
static Uint8* audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
// ###################################################################

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 500;

void try_pointer()
{
    printf("WSKAZNIK DZIALA!!");
}

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();

void setGUI();
void drawGUI();
void handle_GUI_events(SDL_Event* e);


void close();

int main(int argc, char* args[])
{
    init();

// ~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    setGUI();

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // ~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            handle_GUI_events(&e);
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);


        // ~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        drawGUI();

        SDL_RenderPresent(renderer);

    }

    return 0;
}

void setGUI()
{
    Text::setStatics("16_true_type_fonts/lazy.ttf", 28);
    Text* text = new Text();
    Text::texts.push_back(text);

    SDL_Rect vp_backGround = { 0, 0, NULL, NULL };
    Texture* backGround_texture = new Texture(renderer, vp_backGround);
    Texture::textures.push_back(backGround_texture);
    backGround_texture->load("HAHAH.png");

//music title field
    SDL_Rect title_viewport = { 60, 30, 600, 30 };
    TextField* title = new TextField(renderer, title_viewport, play_music);
    TextField::textfields.push_back(title);
    title->load(Text::texts[0]->return_TEXT_surface(""));

    int x = 40;
    Slider::sliders.push_back(new Slider(renderer, "31", x, 80));
    Slider::sliders.push_back(new Slider(renderer, "62", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "124", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "250", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "500", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "1K", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "2K", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "4K", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "8K", x+=66, 80));
    Slider::sliders.push_back(new Slider(renderer, "16K", x+=66, 80));

    Slider::sliders.push_back(new Slider(renderer, "vol", x+=66+80, 80));

}

void drawGUI()
{
    for (unsigned int i = 0; i < Texture::textures.size(); i++)
        Texture::textures[i]->render();

    TextField::textfields[0]->render();

    for (unsigned int i = 0; i < Slider::sliders.size(); i++)
        Slider::sliders[i]->draw();
}

void handle_GUI_events(SDL_Event* e)
{
//curently only title is desired
    TextField::textfields[0]->handleEvent(e);

    for (unsigned int i = 0; i < Slider::sliders.size(); i++)
        Slider::sliders[i]->handleEvent(e);
}

bool init()
{
    bool success = true;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("By_My_Own", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

//Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }

//Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void close()
{
//Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

//Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void play_music(std::string tune)
{
// local variables
    static Uint32 wav_length; // length of our sample
    static Uint8* wav_buffer; // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music


/* Load the WAV */
// the specs, length and buffer of our wav are filled
    SDL_LoadWAV(tune.c_str(), &wav_spec, &wav_buffer, &wav_length);
// set the callback function
    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;
// set our global static variables
    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length

/* Open the audio device */
    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        exit(-1);
    }

/* Start playing */
    SDL_PauseAudio(0);

// wait until we're don't playing
    while (audio_len > 0) {
        SDL_Delay(100);
    }

}

void my_audio_callback(void* userdata, Uint8* stream, int len) {

    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);
    SDL_memcpy(stream, audio_pos, len); 					// simply copy from one buffer into the other
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

    audio_pos += len;
    audio_len -= len;
}