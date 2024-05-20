// Created by Admin on 30/4/2024.

#include "HealthBar.h"

HealthPower::HealthPower(){

    num_fr = 0;
    width_fr_ = 0;
    height_fr_ = 0;

}

HealthPower::~HealthPower(){

}

void HealthPower::reset(){
    num_fr = 0;
}

bool HealthPower::LoadingIMG(std::string name, SDL_Renderer *screen){
    bool ret = Object::LoadingIMG(name, screen);
    if(ret){
        width_fr_ = g_rect.w/FRAME_HP;
        height_fr_ = g_rect.h;
    }
    return ret;
}

void HealthPower::Set_clips_() {
    if (width_fr_ > 0 && height_fr_ > 0) {

        for(int i = 0; i < FRAME_HP; i++){
            frame_clip_[i].x = width_fr_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_fr_;
            frame_clip_[i].h = height_fr_;
        }

    }
}

void HealthPower::Show_HP(SDL_Renderer *screen) {
    SDL_Rect* currentClip = &frame_clip_[num_fr];
    SDL_Rect renderQuad = {20, 0, width_fr_, height_fr_};
    if(currentClip != NULL){
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }
    SDL_RenderCopy(screen, g_object, currentClip, &renderQuad);
}

//Làm Chakra
PlayerChakra::PlayerChakra() {
    xp_ = 0;
    yp_ = 0;
}

PlayerChakra::~PlayerChakra(){

}

void PlayerChakra::Init(SDL_Renderer *screen) {
    bool ret = LoadingIMG("img\\chakra.png",screen);
}

void PlayerChakra::Show_Chakra(SDL_Renderer *screen) {
    g_rect.x = xp_;
    g_rect.y = yp_;
    toRender(screen);
}