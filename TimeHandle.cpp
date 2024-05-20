//
// Created by Admin on 16/4/2024.
//

#include "TimeHandle.h"
#include "All_function.h"

Timer::Timer() {
    start_tick = 0;
    pause_tick = 0;
    is_paused_ = false;
    is_start_ = false;
}

Timer::~Timer() {

}

void Timer::start() {
    is_start_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks();
}

int Timer::get_ticks() {
    if(is_start_){
        if (is_paused_)
            return pause_tick;
        else{
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}
