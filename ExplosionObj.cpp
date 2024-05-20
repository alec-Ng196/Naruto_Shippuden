//
// Created by Admin on 27/4/2024.
//

#include "ExplosionObj.h"

Explosion::Explosion() {
    width_frame = 0;
    height_frame = 0;
    frame = 0;
}

Explosion::~Explosion(){

}

bool Explosion::LoadingIMG(std::string name, SDL_Renderer *screen) {
    bool ret = Object::LoadingIMG(name, screen);
    if(ret){
        width_frame = g_rect.w/FRAME_NUM;
        height_frame = g_rect.h;
    }
    return ret;
}

void Explosion::set_clips() {
    if (width_frame > 0 && height_frame > 0) {
        for(int i = 0; i < 6; i++){
            frame_clip_[i].x = width_frame*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame;
            frame_clip_[i].h = height_frame;
        }
    }
}

void Explosion::ShowEffect(SDL_Renderer *screen) {
    SDL_Rect* currentClip = &frame_clip_[frame];
    SDL_Rect renderQuad = {g_rect.x, g_rect.y, width_frame, height_frame};
    if(currentClip != NULL){
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }
    SDL_RenderCopy(screen, g_object, currentClip, &renderQuad);
}