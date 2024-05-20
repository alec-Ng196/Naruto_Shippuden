//
// Created by Admin on 25/4/2024.
//

#include "All_function.h"

bool SDLAllFunction::CheckCollision(const SDL_Rect &obj1, const SDL_Rect &obj2) {
    int left_a = obj1.x;
    int right_a = obj1.x + obj1.w;
    int top_a = obj1.y;
    int bottom_a = obj1.y + obj1.h;

    int left_b = obj2.x;
    int right_b = obj2.x + obj2.w;
    int top_b = obj2.y;
    int bottom_b = obj2.y + obj2.h;

    // Kiểm tra va chạm
    if (left_a >= right_b || right_a <= left_b || top_a >= bottom_b || bottom_a <= top_b) {
        return false; // Không có va chạm
    }
    return true; // Có va chạm

}

Mix_Music* SDLAllFunction::loadMusic(const char *path) {
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}


