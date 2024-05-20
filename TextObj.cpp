//
// Created by Admin on 28/4/2024.
//

#include "TextObj.h"

TextObject::TextObject() {
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    texture_ = NULL;
    alpha = 255.0;
    alphaCal = 255.0;
}

TextObject::~TextObject(){

}

bool TextObject::LoadFromRenderTEXT(TTF_Font *font, SDL_Renderer *screen) {

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if(text_surface){
         texture_ = SDL_CreateTextureFromSurface(screen,text_surface);
         width = text_surface->w;
         height = text_surface->h;

        SDL_FreeSurface(text_surface);

    }
    return texture_ != NULL;
}

void TextObject::Free() {
    if(texture_ != NULL){
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::Set_Color(Uint8 red, Uint8 green, Uint8 blue) {
    text_color.r = red;
    text_color.b = blue;
    text_color.g = green;

}

void TextObject::Set_Color(int genre) {
    if(genre == WHITE_TEXT){
        SDL_Color color =   {255, 255, 255};
        text_color = color;
    }
    else if(genre == BLACK_TEXT){
        SDL_Color color =   {0, 0, 0};
        text_color = color;
    }
    else if(genre == BLUE_TEXT){
        SDL_Color color =   {0, 0, 255};
        text_color = color;
    }
    else if(genre == PINK_TEXT){
        SDL_Color color =   {255, 0, 127};
        text_color = color;
    }
}

void TextObject::RenderTEXT(SDL_Renderer *screen, int x_pos, int y_pos, double angle,
                            SDL_Rect *clip, SDL_Point *center,
                            SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x_pos, y_pos, width, height};
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);

}

void TextObject::UpdateVariable(float elapsedTime) {
    if (texture_) {
        // Set the alpha of the texture
        SDL_SetTextureAlphaMod(texture_, alpha);
    }

    // Update the alpha value
    if (alpha > 0) {
        alphaCal -= FADE_SPEED * elapsedTime;
        alpha = alphaCal;

        // Clamp alpha to be non-negative
        if (alpha < 0) {
            alpha = 0;
            alphaCal = 0;
        }
    }
}