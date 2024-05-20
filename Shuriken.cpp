//
// Created by Admin on 20/4/2024.
//

#include "Shuriken.h"

Shuriken::Shuriken() {
    x_val = 0;
    y_val = 0;
    is_darted = false;
    bullet_type = SHURIKEN;
}

Shuriken::~Shuriken() {

}

bool Shuriken::LoadingIMGBullet(SDL_Renderer *des) {
    bool ret = false;
    if(bullet_type == BALL_FIRE){
        ret = LoadingIMG("img\\Fire.png",des);
    }
    else if(bullet_type == SHURIKEN)
    {
        ret = LoadingIMG("img\\shuriken.png",des);
    }
    return ret;
}

void Shuriken::Throw_Shuri(const int &x_border, const int &y_border) {
    if(shuri_dir == Dir_right){
        g_rect.x += x_val;
        if(g_rect.x > x_border){
            is_darted = false;
        }
    }
    else if(shuri_dir == Dir_left){
        g_rect.x -= x_val;
        if(g_rect.x < 0){
            is_darted = false;
        }
    }
    else if(shuri_dir == Dir_left_up){
        g_rect.x -= x_val;
        if(g_rect.x < 0){
            is_darted = false;
        }
        g_rect.y -= y_val;
        if(g_rect.y < 0){
            is_darted = false;
        }
    }
    else if(shuri_dir == Dir_right_up){
        g_rect.x += x_val;
        if(g_rect.x > x_border){
            is_darted = false;
        }
        g_rect.y -= y_val;
        if(g_rect.y < 0){
            is_darted = false;
        }
    }
    else if(shuri_dir == Dir_left_down){
        g_rect.x -= x_val;
        if(g_rect.x < 0){
            is_darted = false;
        }
        g_rect.y += y_val;
        if(g_rect.y > y_border){
            is_darted = false;
        }
    }
    else if(shuri_dir == Dir_right_down){
        g_rect.x += x_val;
        if(g_rect.x > x_border){
            is_darted = false;
        }
        g_rect.y += y_val;
        if(g_rect.y > y_border){
            is_darted = false;
        }
    }
}