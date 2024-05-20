//
// Created by Admin on 27/4/2024.
//

#ifndef NARUTOSHIPPUDEN_EXPLOSIONOBJ_H
#define NARUTOSHIPPUDEN_EXPLOSIONOBJ_H

#include "All_function.h"
#include "Base_code.h"
#define FRAME_NUM 6

class Explosion : public Object{
public:
    Explosion();
    ~Explosion();

    void set_clips();
    void set_frame(const int& fr){ frame = fr;}
    virtual bool LoadingIMG(std::string name, SDL_Renderer* screen);
    void ShowEffect(SDL_Renderer* screen);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

private:
    int width_frame;
    int height_frame;
    unsigned int frame;
    SDL_Rect frame_clip_[FRAME_NUM];
};
#endif //NARUTOSHIPPUDEN_EXPLOSIONOBJ_H
