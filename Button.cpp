//
// Created by Admin on 9/5/2024.
//

#include "Button.h"

Button::Button() {
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    currentStatus = 0;
}

Button::~Button(){

}

bool Button::LoadingIMG(std::string path, SDL_Renderer *des) {
    bool ret = Object::LoadingIMG(path, des);
    if(ret){
        width_frame_ = g_rect.w;
        height_frame_ = g_rect.h;
    }
    return ret;
}

void Button::Show(SDL_Renderer* des)
{
    SDL_Rect renderQuad = { x_pos_, y_pos_, width_frame_, height_frame_ };
    SDL_RenderCopy(des, g_object, NULL, &renderQuad);
}

void Button::handleEvent(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= x_pos_ && x < x_pos_ + width_frame_ && y >= y_pos_ && y < y_pos_ + height_frame_) {
            currentStatus = MOUSE_DOWN;
        } else {
            currentStatus = MOUSE_OUT;
        }
    } else if (e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= x_pos_ && x < x_pos_ + width_frame_ && y >= y_pos_ && y < y_pos_ + height_frame_) {
            currentStatus = MOUSE_IN;
        } else {
            currentStatus = MOUSE_OUT;
        }
    }
}

bool Button::click() {
    if (currentStatus == MOUSE_DOWN) {
        // Đặt currentStatus thành MOUSE_OUT sau khi click
        currentStatus = MOUSE_OUT;
        return true;
    }
    return false;
}

