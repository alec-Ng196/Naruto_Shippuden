//
// Created by Admin on 28/4/2024.
//

#ifndef NARUTOSHIPPUDEN_TEXTOBJ_H
#define NARUTOSHIPPUDEN_TEXTOBJ_H

#include "All_function.h"
#include "Base_code.h"
#define FADE_SPEED 0.07f
using namespace std;

class TextObject{
public:
    TextObject();
    ~TextObject();

    enum TextColor{
        WHITE_TEXT = 0,
        BLACK_TEXT = 1,
        BLUE_TEXT = 2,
        PINK_TEXT = 3,
    };

    bool LoadFromRenderTEXT(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void Set_Color(Uint8 red, Uint8 green, Uint8 blue); //truyền trực tiếp giá trị màu vào
    void Set_Color(int genre);

    void setRect(const int& x, const int& y){
        t_rect.x = x;
        t_rect.y = y;
    }
    SDL_Rect GetRect() const {return t_rect;}

    void RenderTEXT(SDL_Renderer * screen, int x_pos, int y_pos, double angle = 0.0,
                    SDL_Rect* clip = NULL,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE); // FLip kiểu soi gương

    void Set_TEXT(const string& text) {str_val = text;}
    string Get_TEXT() const {return str_val;}

    void UpdateVariable(float elapsedTime);
    bool Get_texture(){
        return (texture_!= NULL);
    }

private:
    string str_val; // Luu noi dung cua text
    SDL_Color text_color;
    SDL_Texture* texture_; //Quản lý text này
    int width;
    int height;
    SDL_Rect t_rect;
    float alpha;
    float alphaCal;


};


#endif //NARUTOSHIPPUDEN_TEXTOBJ_H
