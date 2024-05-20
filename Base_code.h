//
// Created by Admin on 14/4/2024.
//

#ifndef NARUTOSHIPPUDEN_BASE_CODE_H
#define NARUTOSHIPPUDEN_BASE_CODE_H

#include "All_function.h"
#include <string>

class Object{

public:
    Object();
    ~Object();
    void setRect(const int& x, const int& y){
        g_rect.x = x;
        g_rect.y = y;
    }
    SDL_Rect GetRect() const {return g_rect;}
    virtual bool LoadingIMG(std::string filename, SDL_Renderer* g_screen);
    void toRender(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void FreeObject();

protected:
    SDL_Texture* g_object;
    SDL_Rect g_rect;
};






#endif //NARUTOSHIPPUDEN_BASE_CODE_H
