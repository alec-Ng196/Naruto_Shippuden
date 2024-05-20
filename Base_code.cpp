//
// Created by Admin on 14/4/2024.
//
#include "Base_code.h"
using namespace std;

Object::Object()
{
    g_object = NULL;
    g_rect.x = 0;
    g_rect.y = 0;
    g_rect.h = 0;
    g_rect.w = 0;
}

Object::~Object(){
    FreeObject();

}

bool Object::LoadingIMG(std::string filename, SDL_Renderer* g_screen){
    FreeObject();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loading_surface = IMG_Load(filename.c_str());
    if(loading_surface != NULL){
        SDL_SetColorKey(loading_surface, SDL_TRUE, SDL_MapRGB(loading_surface->format, Color_key_R, Color_key_G, Color_key_B));
        new_texture = SDL_CreateTextureFromSurface(g_screen, loading_surface);
        if(new_texture != NULL){
            g_rect.w = loading_surface->w;
            g_rect.h = loading_surface->h;
        }
        SDL_FreeSurface(loading_surface);
    }
    g_object = new_texture;
    return (g_object != NULL);
}

void Object::toRender(SDL_Renderer* des, const SDL_Rect* clip){
    SDL_Rect dest = {g_rect.x, g_rect.y, g_rect.w, g_rect.h};
    SDL_RenderCopy(des,g_object,clip, &dest);
}

void Object::FreeObject(){
    if(g_object != NULL){
        SDL_DestroyTexture(g_object);
        g_object = NULL;
        g_rect.w = 0;
        g_rect.h = 0;
    }
}
