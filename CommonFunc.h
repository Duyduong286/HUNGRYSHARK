#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <string>
#include <windows.h>
#include <SDL_image.h>
#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Renderer* g_screen = NULL;
static SDL_Window* g_window = NULL;
static SDL_Event g_event;
static SDL_Color color = { 0, 0, 0 };
static SDL_Color color1 = { 0, 0, 255 };

static Mix_Chunk* s_eat[4] = {NULL, NULL, NULL, NULL};
static Mix_Chunk* s_boom = NULL;
static Mix_Chunk* s_bgr = NULL;
static Mix_Chunk* s_push = NULL;
static Mix_Chunk* s_mermaid = NULL;
static Mix_Chunk* s_pearl = NULL;
static Mix_Chunk* s_dead = NULL;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_BPP = 32;
const int FRAME_PER_SECOND = 25; // FPS so hinh(frame) tren 1s

const int PLUS_BLOOD = 15;
const int MINUS_BLOOD = 500;
const int BLEED = 4;

const int SIZE_SRORE = 25;
const int SIZE_TEXT = 75;

const int amount_F = 25;
const int speed_M = 10;
const int speed_line = 15;
const int COLOR_KEY_R = 167; //RED
const int COLOR_KEY_G = 175; //GREEN
const int COLOR_KEY_B = 180; //BLUE

const int RENDER_DRAW_COLOR = 0xff;

struct Input{
    int left_;
    int right_;
};

namespace SDLCommonFunc{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}



#endif // COMMONFUNC_H_INCLUDED
