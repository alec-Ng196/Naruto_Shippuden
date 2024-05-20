//
// Created by Admin on 14/4/2024.
//

#ifndef NARUTOSHIPPUDEN_ALL_FUNCTION_H
#define NARUTOSHIPPUDEN_ALL_FUNCTION_H

#include <vector>
#include <Windows.h>
#include <winuser.h>
#include <string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>


static SDL_Window* g_window;
static SDL_Renderer* g_screen;
static SDL_Event g_event;

//SCREEN
const int FRAME_PER_SECOND = 60; //Số frame trong 1s
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_PIXEL = 32;

const int Color_key_R = 167;
const int Color_key_B = 175;
const int Color_key_G = 180;
//const int Render_draw_color = 0xff;


#define TILE_SZ 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK 0
#define Ramen 10
#define WINNER 33
#define MAX_HP_LENGTH 40
#define MAX_HP_BOSSLEN 200
#define MAX_MANA_LEN 150

typedef struct Input{
    int left;
    int right;
    int up;
    int down;
    int jump;
    int stance;
    int attack;
    int throwing;
    int dash;
    int guard;
};

typedef struct Map{
    int begin_x;
    int begin_y;

    int end_x;
    int end_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* filename_2;
};

// khai báo namespace để nhóm các biến, các hàm lại với nhau, sau gọi code không cần phải dùng struct
namespace SDLAllFunction{
    bool CheckCollision(const SDL_Rect& obj1, const SDL_Rect& obj2);
    Mix_Music *loadMusic(const char* path);
}

enum MenuOption{
    START = 100,
    PLAY = 101,
    PAUSE = 102,
    END = 103,
    HELP = 104,
    WIN = 105,
    RESTART = 106,
    NEXT_STAGE = 107,
};
#endif //NARUTOSHIPPUDEN_ALL_FUNCTION_H
